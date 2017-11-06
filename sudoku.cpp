// sudoku.cpp : Defines the entry point for the console application.
//

//#include "stdafx.h"
#include <stdio.h>
#include <vector>
#include <cassert>
#include <stack>
#include <algorithm>

#include "cell.hpp"
#include <stdexcept>

using namespace std;
void getdat(FILE* fp, void (*updDat)(size_t,size_t,size_t));
void getdat2(FILE* fp, void (*updDat)(size_t,size_t,size_t));
vector<cell> curState;

struct tsp_inserter
{
	vector<cell>& state;
	tsp_inserter(vector<cell>& state_): state(state_){};
	tsp_inserter& operator()(size_t row, size_t col, size_t val)
	{
		cell t={row,col,boxId(row,col), val};
		if(!legal(state,t)) 
			throw std::invalid_argument("illegal");
		state.push_back(t);
		return *this;
	}
};

tsp_inserter insert(curState);


void outputSol(vector<cell> const& currentState)
{
	size_t prevRow=0;
	for (auto const& c : currentState)
	{
		if(prevRow != c.row)
		{
			prevRow = c.row;
			printf("\n");
			if(prevRow%3 == 0)
				printf("----------------------\n");
		}
		if (c.col > 0 && c.col%3==0)
			printf("| ");
		printf("%ld ", c.val);
   }
}
void insertDat(size_t x, size_t y , size_t w)
{
  cell c{x,y,0,w};
  if (is_legal(c))
    cells[x][y]=w;
}
int main(int argc, char* argv[])
{
  FILE *fp=fopen(argv[1], "r");
  if (fp!=NULL)
  {
    getdat2(fp,insertDat);
    //initi cells to zero
    for (size_t i=0; i<SUDOKU_SIZE; ++i)
      for (size_t j=0; j<SUDOKU_SIZE; ++j)
        cells[i][j]=0;
    fclose(fp);
    printf("Reading done\n");
    ComputeSolution(curState);
    printf("Printing\n");
    std::sort(curState.begin(),curState.end());
    outputSol(curState);
  }	
  return 0;
}

