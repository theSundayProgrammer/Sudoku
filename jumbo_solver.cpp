#include "cell.hpp"
#include <exception>
#include <stdio.h>
using namespace std;

size_t cells[SUDOKU_SIZE][SUDOKU_SIZE] = {0};

bool debug=false;
void output_sol()
{
  for (size_t i=0; i<SUDOKU_SIZE;++i)
  {
    for (size_t j=0; j<SUDOKU_SIZE;++j)
    {
      if (j>0 && j%BOX_WIDTH==0)
        printf("|");
      if (cells[i][j]==0) 
        printf("  ");
      else
        printf("%-2lu", cells[i][j]);
    }
    printf("\n");
    if (i%BOX_WIDTH==2)
    {
      for (size_t j=0; j<SUDOKU_SIZE;++j)
      {
        if (j>0 && j%BOX_WIDTH==0)
          printf("|");
        printf("--");
      }
      printf("\n");
    }
  }

}
  bool is_legal_sub(int sub_sudoku, cell const& c, size_t val)
  {
    int row_start,row_end,col_start,col_end;
    switch(sub_sudoku) 
    {
      case 0:
      row_start =0;
      col_start =0;
      break;
      case 1:
      row_start = 0;
      col_start = SUB_SIZE + BOX_WIDTH;
      break;
      case 2:
      row_start = SUB_SIZE - BOX_WIDTH;
      col_start = SUB_SIZE - BOX_WIDTH;
      break;
      case 3:
      row_start = SUB_SIZE + BOX_WIDTH;
      col_start = 0;
      break;
      case 4:
      row_start = SUB_SIZE + BOX_WIDTH;
      col_start = SUB_SIZE + BOX_WIDTH;
      break;

    }
    row_end = row_start + SUB_SIZE;
    col_end = col_start + SUB_SIZE;
    for (size_t i=col_start; i<col_end; ++i)
      if (cells[c.row][i] == val)
        return false;
    for (size_t j=row_start; j<row_end;  ++j)
      if (cells[j][c.col] == val)
        return false;
    auto box = box_id(c.row-row_start,c.col-col_start);
    size_t row = (box/BOX_WIDTH)*BOX_WIDTH+row_start;
    size_t col = (box%BOX_WIDTH)*BOX_WIDTH+col_start;
    if(debug)
    {
      printf("c_row=%u,c_col=%u\n", c.row,c.col);
      printf("start_row=%u,start_col=%u\n", row_start,col_start);
      printf("row=%u,col=%u\n", row,col);
    }
  
    for(size_t i =0; i<BOX_WIDTH; ++i)
      for(size_t j=0; j<BOX_WIDTH; ++j)
        if (cells[row+i][col+j]==val)
          return false;
    return true;
  }
  bool is_legal(cell const& c, unsigned long val)
  {
    bool retval=false;
    if (c.row >= 0 && c.row < SUB_SIZE && c.col >=0 && c.col < SUB_SIZE)
    {
      retval = is_legal_sub(0, c, val);
      if (!retval) return false;
    }
    if (c.row >= 0 && c.row < SUB_SIZE && c.col >= SUB_SIZE+BOX_WIDTH && c.col < SUB_SIZE+SUB_SIZE+BOX_WIDTH)
    {
      retval = is_legal_sub(1, c, val);
      if (!retval) return false;
    }
    if (c.row >= SUB_SIZE - BOX_WIDTH && c.row < SUB_SIZE + SUB_SIZE - BOX_WIDTH  && c.col >=SUB_SIZE - BOX_WIDTH && c.col < SUB_SIZE + SUB_SIZE - BOX_WIDTH)
    {
      retval = is_legal_sub(2, c, val);
      if (!retval) return false;
    }
    if (c.row >= SUB_SIZE+BOX_WIDTH && c.row < SUB_SIZE + SUB_SIZE+BOX_WIDTH && c.col >=0 && c.col < SUB_SIZE)
    {
      retval = is_legal_sub(3, c, val);
      if (!retval) return false;
    }
    if (c.row >= SUB_SIZE+BOX_WIDTH && c.row < SUB_SIZE + SUB_SIZE+BOX_WIDTH && c.col >= SUB_SIZE+BOX_WIDTH && c.col < SUB_SIZE+SUB_SIZE+BOX_WIDTH)
    {
      retval = is_legal_sub(4, c, val);
      if (!retval) return false;
    }
    return retval;
  }

  cell get_next_free_cell() 
  {
    //Search for the first empty cell
    for (size_t i=0; i<SUDOKU_SIZE; ++i)
      for (size_t j=0; j<SUDOKU_SIZE; ++j)
        if(cells[i][j]==0)
        {
          cell c = {i , j};
          if (c.row >= 0 && c.row < SUB_SIZE && c.col >=0 && c.col < SUB_SIZE)
          {
            return c;
          }
          if (c.row >= 0 && c.row < SUB_SIZE && c.col >= SUB_SIZE+BOX_WIDTH && c.col < SUB_SIZE+SUB_SIZE+BOX_WIDTH)
          {
            return c;
          }
          if (c.row >= SUB_SIZE - BOX_WIDTH && c.row < SUB_SIZE + SUB_SIZE - BOX_WIDTH  && c.col >=SUB_SIZE  - BOX_WIDTH && c.col < SUB_SIZE + SUB_SIZE - BOX_WIDTH)
          {
            return c;
          }
          if (c.row >= SUB_SIZE+BOX_WIDTH && c.row < SUB_SIZE + SUB_SIZE+BOX_WIDTH && c.col >=0 && c.col < SUB_SIZE)
          {
            return c;
          }
          if (c.row >= SUB_SIZE+BOX_WIDTH && c.row < SUB_SIZE + SUB_SIZE+BOX_WIDTH && c.col >= SUB_SIZE+BOX_WIDTH && c.col < SUB_SIZE+SUB_SIZE+BOX_WIDTH)
          {
            return c;
          }
        }
    return last_cell;
  }
