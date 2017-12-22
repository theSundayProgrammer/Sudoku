 #include "cell.hpp"
#include <exception>
#include <stdio.h>
using namespace std;
size_t cells[SUDOKU_SIZE][SUDOKU_SIZE];
size_t boxId(size_t row, size_t col)
{
	size_t k = row/3;
	size_t l = col/3;
	return  k*3 + l;	
}

void output_sol()
{
  for (size_t i=0; i<SUDOKU_SIZE;++i)
  {
    for (size_t j=0; j<SUDOKU_SIZE;++j)
    {
      if (j>0 && j%3==0)
        printf("|");
      printf("%-2lu", cells[i][j]);
    }
    printf("\n");
    if (i%3==2)
      printf("-------------------\n");
  }

}
  bool is_legal(cell const& c, size_t val)
  {
    for (size_t i=0; i<SUDOKU_SIZE; ++i)
      if (cells[c.row][i] == val)
        return false;
    for (size_t j=0; j<SUDOKU_SIZE; ++j)
      if (cells[j][c.col] == val)
        return false;
    auto box = boxId(c.row,c.col);
    size_t row = (box/3)*3;
    size_t col = (box%3)*3;
    for(size_t i =0; i<3; ++i)
      for(size_t j=0; j<3; ++j)
        if (cells[row+i][col+j]==val)
          return false;
    return true;
  }
cell const lastCell = { SUDOKU_SIZE, SUDOKU_SIZE};
  cell get_next_free_cell() 
  {
    //Search for the first empty cell
    for (size_t i=0; i<SUDOKU_SIZE; ++i)
      for (size_t j=0; j<SUDOKU_SIZE; ++j)
        if(cells[i][j]==0)
        {
          cell c = {i , j};
          return c;
        }
    return lastCell;
  }
