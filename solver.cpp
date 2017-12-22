#include "cell.hpp"
#include <exception>
#include <stdio.h>
using namespace std;
auto const  SUB_SIZE= BOX_WIDTH * BOX_WIDTH;
size_t cells[SUDOKU_SIZE][SUDOKU_SIZE] = {0};
size_t boxId(size_t row, size_t col)
{
	size_t k = row/3;
	size_t l = col/3;
	return  k*3 + l;	
}
bool debug=false;
void output_sol()
{
  for (size_t i=0; i<SUDOKU_SIZE;++i)
  {
    for (size_t j=0; j<SUDOKU_SIZE;++j)
    {
      if (j>0 && j%3==0)
        printf("|");
      if (cells[i][j]==0) 
        printf("  ");
      else
        printf("%-2lu", cells[i][j]);
    }
    printf("\n");
    if (i%3==2)
    {
      for (size_t j=0; j<SUDOKU_SIZE;++j)
      {
        if (j>0 && j%3==0)
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
    auto box = boxId(c.row-row_start,c.col-col_start);
    size_t row = (box/3)*3+row_start;
    size_t col = (box%3)*3+col_start;
    if(debug)
    {
    printf("c_row=%u,c_col=%u\n", c.row,c.col);
    printf("start_row=%u,start_col=%u\n", row_start,col_start);
    printf("row=%u,col=%u\n", row,col);
    }
  
    for(size_t i =0; i<3; ++i)
      for(size_t j=0; j<3; ++j)
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
cell const lastCell = { SUDOKU_SIZE, SUDOKU_SIZE};
  cell GetNextFreeCell() 
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
    return lastCell;
  }
static  bool solve()
  {
    //find the first empty cell
    auto c= GetNextFreeCell( );
    if (c.row == lastCell.row)
    {
      output_sol();
      return true;
    }
   
    //fill the empty cell
    for (size_t val = 1; val <= SUB_SIZE ; ++val)	{
      //bool found = legal(currentState,c);
      //
      bool found = is_legal(c,val);
      if (found){
        cells[c.row][c.col] = val;
        if (solve()){
          return true;
        }else{
          //printf("i=%lu,j=%lu,val=%lu\n\n", c.row, c.col,val);
          cells[c.row][c.col] = 0;
        }
      }
    }
    return false;
  }
bool ComputeSolution(){
  //debug=true;
	return solve();
}
