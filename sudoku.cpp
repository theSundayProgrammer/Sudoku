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



void outputSol()
{
  for (size_t i=0; i<SUDOKU_SIZE;++i)
  {
    for (size_t j=0; j<SUDOKU_SIZE;++j)
    {
      if (j>0 && j%3==0)
        printf("|");
      printf("%-2d", cells[i][j]);
    }
    printf("\n");
    if (i%3==2)
      printf("-------------------\n");
  }

}
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
    getdat2(fp,insertDat);
    //initi cells to zero
    for (size_t i=0; i<SUDOKU_SIZE; ++i)
      for (size_t j=0; j<SUDOKU_SIZE; ++j)
        cells[i][j]=0;
    fclose(fp);
    printf("Reading done\n");
    ComputeSolution();
    printf("Printing\n");
    outputSol();
  }	
  return 0;
}

