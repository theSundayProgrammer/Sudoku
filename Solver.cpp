 #include "cell.hpp"
#include <exception>
#include <algorithm>
using namespace std;

int boxId(int row, int col)
{
	int k = row/3;
	int l = col/3;
	return  k*3 + l;	
}

bool legal(set<cell> const& state,  cell const& cur)
{
	set<cell>::const_iterator it = find_if(state.cbegin(), state.cend(), [&](cell const& c)
	{
		return  (c.val == cur.val && (c.row == cur.row || c.col == cur.col || c.box == cur.box));
			
	});

	return it == state.cend();
}

bool GetNextFreeCell(cell& curCell, set<cell>& currentState)
{
	
	return currentState.end() != find_if(currentState.begin(), currentState.end(),
			[&](cell const& c)
		{
			if (curCell < c)
				return true;
			else
				return ++curCell, false;
		});
}

bool ComputeSolution(set<cell>& currentState)
{
	cell const lastCell = { 9, 9, 9, 9 };

	if (currentState.size() == 81)
	{
		return true;
	}
	//find the first empty cell
	cell emptycell = { 0, 0, 0, 0 };
	GetNextFreeCell(emptycell, currentState);
	emptycell.box = boxId(emptycell.row, emptycell.col);
	//fill the empty cell
	for (int val = 1; val <= 9 ; ++val)
	{
		emptycell.val = val;
		bool found = legal(currentState,  emptycell);
		if (found)
		{
			set<cell> newstate(currentState);
			newstate.insert(emptycell);
			if (ComputeSolution(newstate))
			{
				currentState.swap(newstate);
				return true;
			}
		}
	}
	return false;
}
