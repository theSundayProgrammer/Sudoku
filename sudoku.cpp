// sudoku.cpp : Defines the entry point for the console application.
//

//#include "stdafx.h"
#include <stdio.h>
#include <set>
#include <cassert>
#include <stack>
#include <algorithm>

#include "cell.hpp"
#include <exception>

using namespace std;
void getdat(FILE* fp, void (*updDat)(int,int,int));
set<cell> curState;

struct inserter
{
	set<cell>& state;
	inserter(set<cell>& state_): state(state_){};
	inserter& operator()(int row, int col, int val)
	{
		cell t={row,col,boxId(row,col), val};
		set<cell>::iterator it = state.find(t);
		if(!legal(state,t)) throw std::exception("illegal");
		state.insert(t);
		return *this;
	}
};

inserter insert(curState);


void outputSol(set<cell> const& currentState)
{
	int prevRow=0;
	set<cell>::const_iterator fin=currentState.cend();
	set<cell>::const_iterator start=currentState.cbegin();
	for(set<cell>::const_iterator it = start; it!=fin; ++it)
	{
		if(prevRow != it->row)
		{
			prevRow = it->row;
			printf("\n");
			if(prevRow%3 == 0)
				printf("----------------------\n");
		}
		if (it->col > 0 && it->col%3==0)
			printf("| ");
		printf("%d ", it->val);
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
		getdat(fp,insertDat);
		fclose(fp);
	}	

	ComputeSolution(curState);

	outputSol(curState);
	return 0;
}

