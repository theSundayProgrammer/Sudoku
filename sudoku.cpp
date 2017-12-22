// sudoku.cpp : Defines the entry point for the console application.
//

//#include "stdafx.h"
#include <stdio.h>
#include <vector>
#include <cassert>
#include <stack>
#include <algorithm>

#include "cell.hpp"
#include <stdexcept>

using namespace std;
void getdat2(FILE* fp, void (*updDat)(size_t,size_t,size_t));

const cell  last_cell = { SUDOKU_SIZE, SUDOKU_SIZE};
bool solve();
void insertDat(size_t x, size_t y , size_t w)
{
  cell c{x,y};
  if (is_legal(c,w))
    cells[x][y]=w;
}
int main(int argc, char* argv[])
{
  FILE *fp=fopen(argv[1], "r");
  if (fp!=NULL)
  {
    //init cells to zero
    for (size_t i=0; i<SUDOKU_SIZE; ++i)
      for (size_t j=0; j<SUDOKU_SIZE; ++j)
        cells[i][j]=0;
    getdat2(fp,insertDat);
    fclose(fp);
    output_sol();
    printf("Reading done\n");
    solve();
    
  }	
  return 0;
}

bool solve()
  {
    //find the first empty cell
    auto c= get_next_free_cell( );
    if (c.row == last_cell.row)
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
size_t box_id(size_t row, size_t col)
{
	size_t k = row/BOX_WIDTH;
	size_t l = col/BOX_WIDTH;
	return  k*BOX_WIDTH + l;	
}