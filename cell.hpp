#ifndef THESUNDAYPROGRAMMER_SUDOKU
#define THESUNDAYPROGRAMMER_SUDOKU
#include <cstddef>
using std::size_t;
struct cell
{
  size_t row;
  size_t col;
  cell& operator++()
  {
    if (col<8) ++col;
    else { ++row; col= 0;}
    return *this;
  }
};
size_t boxId(size_t row, size_t col);


bool ComputeSolution();
inline bool operator<(cell const& x, cell const& y)
{
  return x.row<y.row || (x.row==y.row && x.col<y.col);
}

bool is_legal(cell const& c, size_t val);
const size_t SUDOKU_SIZE=9;
extern  size_t cells[SUDOKU_SIZE][SUDOKU_SIZE];
#endif // !THESUNDAYPROGRAMMER_SUDOKU
