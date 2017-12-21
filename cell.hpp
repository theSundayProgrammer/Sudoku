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
void output_sol();
bool is_legal(cell const& c, size_t val);
const size_t BOX_WIDTH = 3;
const size_t SUDOKU_SIZE= 2*BOX_WIDTH *BOX_WIDTH + (BOX_WIDTH -2)*BOX_WIDTH;
extern  size_t cells[SUDOKU_SIZE][SUDOKU_SIZE];
#endif // !THESUNDAYPROGRAMMER_SUDOKU
