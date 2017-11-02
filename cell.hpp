#ifndef THESUNDAYPROGRAMMER_SUDOKU
#define THESUNDAYPROGRAMMER_SUDOKU

#include <vector>
struct cell
{
	size_t row;
	size_t col;
	size_t box;
	size_t val;
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
size_t boxId(size_t row, size_t col);

bool legal(std::vector<cell> const& state, cell const& cur);

bool ComputeSolution(std::vector<cell>& currentState);
inline bool operator<(cell const& x, cell const& y)
{
	return x.row<y.row || (x.row==y.row && x.col<y.col);
}

#endif // !THESUNDAYPROGRAMMER_SUDOKU
