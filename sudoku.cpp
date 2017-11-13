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
void getdat(FILE* fp, void (*updDat)(size_t,size_t,size_t));
void getdat2(FILE* fp, void (*updDat)(size_t,size_t,size_t));



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
    //initi cells to zero
    for (size_t i=0; i<SUDOKU_SIZE; ++i)
      for (size_t j=0; j<SUDOKU_SIZE; ++j)
        cells[i][j]=0;
    getdat2(fp,insertDat);
    fclose(fp);
    printf("Reading done\n");
    ComputeSolution();
  }	
  return 0;
}

