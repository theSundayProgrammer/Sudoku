#ifndef THESUNDAYPROGRAMMER_SUDOKU
#define THESUNDAYPROGRAMMER_SUDOKU
#include <cstddef>
using std::size_t;
struct cell
{
  size_t row;
  size_t col;
};


bool ComputeSolution();

bool is_legal(cell const& c, size_t val);
const size_t SUDOKU_SIZE=9;
extern  size_t cells[SUDOKU_SIZE][SUDOKU_SIZE];
#endif // !THESUNDAYPROGRAMMER_SUDOKU
