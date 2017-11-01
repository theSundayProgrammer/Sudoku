 #include "cell.hpp"
#include <exception>
#include <algorithm>
#include <vector>
#include <stdio.h>
using namespace std;

int boxId(int row, int col)
{
	int k = row/3;
	int l = col/3;
	return  k*3 + l;	
}

bool legal(vector<cell> const& state,  cell const& cur)
{
	return  state.cend() == find_if(state.cbegin(), state.cend(), [&](cell const& c)
	{
		return  (c.val == cur.val && (c.row == cur.row || c.col == cur.col || c.box == cur.box));
			
	});

}
cell const lastCell = { 9, 9, 9, 9 };
cell GetNextFreeCell(vector<cell> const & currentState)
{
	int cells[9][9];
	for (size_t i=0; i<9; ++i)
		for (size_t j=0; j<9; ++j)
			cells[i][j]=0;
    for (auto const& c: currentState)
    	cells[c.row][c.col] = c.val;
    for (size_t i=0; i<9; ++i)
    	for (size_t j=0; j<9; ++j)
    		if(cells[i][j]==0)
    		{
    			cell c = {i , j, boxId(i,j), 0};
    			return c;
    		}
    return lastCell;
}

bool ComputeSolution(vector<cell>& currentState){

    //printf("Compute Solution\n");
	if (currentState.size() == 81)	{
		return true;
	}
	//find the first empty cell
	cell emptycell = 	GetNextFreeCell( currentState);
     //printf("%d,%d,%d\n", emptycell.row, emptycell.col, emptycell.box);
	//fill the empty cell
	for (int val = 1; val <= 9 ; ++val)	{
		emptycell.val = val;
		bool found = legal(currentState,  emptycell);
		if (found){
			currentState.push_back(emptycell);
			if (ComputeSolution(currentState)){
				return true;
			}else{
				currentState.pop_back();
			}
		}
	}
	return false;
}
