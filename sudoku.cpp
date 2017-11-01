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
void getdat(FILE* fp, void (*updDat)(int,int,int));
void getdat2(FILE* fp, void (*updDat)(int,int,int));
vector<cell> curState;

struct tsp_inserter
{
	vector<cell>& state;
	tsp_inserter(vector<cell>& state_): state(state_){};
	tsp_inserter& operator()(int row, int col, int val)
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
	int prevRow=0;
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
		printf("%d ", c.val);
   }
   getchar();
}
void insertDat(int x, int y , int w)
{
	insert(x,y,w);
}
int main(int argc, char* argv[])
{
	FILE *fp=fopen(argv[1], "r");
	if (fp!=NULL)
	{
		getdat2(fp,insertDat);
		fclose(fp);
	}	
	   printf("Reading done\n");
	ComputeSolution(curState);
	   printf("Printing\n");
	std::sort(curState.begin(),curState.end());
	outputSol(curState);
	return 0;
}

