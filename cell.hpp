#ifndef THESUNDAYPROGRAMMER_SUDOKU
#define THESUNDAYPROGRAMMER_SUDOKU
#include <cstddef>
using std::size_t;
struct cell
{
  size_t row;
  size_t col;
};



void output_sol();
bool is_legal(cell const& c, size_t val);
cell get_next_free_cell();
size_t box_id(size_t row, size_t col);

const size_t BOX_WIDTH = 3;
auto const  SUB_SIZE= BOX_WIDTH * BOX_WIDTH;
#ifdef JUMBO_SUDOKU
const size_t SUDOKU_SIZE= 2*BOX_WIDTH *BOX_WIDTH + (BOX_WIDTH -2)*BOX_WIDTH;
#else
const size_t SUDOKU_SIZE= BOX_WIDTH *BOX_WIDTH;
#endif
extern  size_t cells[SUDOKU_SIZE][SUDOKU_SIZE];
extern const cell last_cell;
#endif // !THESUNDAYPROGRAMMER_SUDOKU
