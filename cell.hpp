#ifndef THESUNDAYPROGRAMMER_SUDOKU
#define THESUNDAYPROGRAMMER_SUDOKU
#include <set>
struct cell
{
	int row;
	int col;
	int box;
	int val;
	cell& operator++()
	{
		if (col<8) ++col;
		else { ++row; col= 0;}
		return *this;
	}
	bool incrementVal()
	{
		if (val <9)
		{
			++val;
			return true;
		}
		else 
			return false;

	}
};  
int boxId(int row, int col);
bool legal(std::set<cell> const& state, cell const& cur);

void ComputeSolution(std::set<cell>& currentState);
inline bool operator<(cell const& x, cell const& y)
{
	return x.row<y.row || (x.row==y.row && x.col<y.col);   
}

#endif // !THESUNDAYPROGRAMMER_SUDOKU
