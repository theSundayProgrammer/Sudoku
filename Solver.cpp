#include "cell.hpp"
#include <exception>
#include <stack>
using namespace std;

//0<=row<9
//0<=col<9
//0<=box<9
//0< val<=9




int boxId(int row, int col)
{
	int k = row/3;
	int l = col/3;
	return  k*3 + l;	
}
bool legal(set<cell> const& state, cell const& cur)
{
	bool ok=true;
	for(set<cell>::const_iterator it = state.cbegin(); ok && it!=state.cend(); ++it)
	{
		if( it->val == cur.val && (it->row == cur.row || it->col == cur.col || it->box == cur.box))
			ok = false;
	}

	return ok;
}





void ComputeSolution(set<cell>& currentState)
{
	stack<cell> currentSolution;
	while (currentState.size() < 81)
	{
		//find the first empty cell
		cell emptycell={0,0,0,0};
		for(set<cell>::iterator it = currentState.begin(); it!=currentState.end(); ++it)
		{
			if (emptycell < *it)
				break;
		    ++emptycell;
		}
		emptycell.box = boxId(emptycell.row, emptycell.col);
		//fill the empty cell
		bool found = false;
		for(int val=1; val <=9 && !found; ++val)
		{
			emptycell.val = val;
			found = legal(currentState,emptycell);
		}
		if (found)
		{
			currentSolution.push(emptycell);
			currentState.insert(emptycell);

		}
		
		while(!found)
		{
			cell&   x = currentSolution.top();
			
			currentState.erase(x);
			
			while(!found && x.incrementVal())
			{
				found = legal(currentState,x);
			}
			if (found)
			{
				currentState.insert(x);
			}
			else
			{
				currentSolution.pop();
			}
		}
	}
	 
}
