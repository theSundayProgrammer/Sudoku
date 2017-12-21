//#include "stdafx.h"
#include <cstdio>
void getdat2(FILE* fp, void (*updDat)(size_t,size_t,size_t))
{
  const int SUDOKU_SIZE=21;
  size_t c;
  size_t x =0;
  size_t y =0;
  auto incr = [&]  ()  
  {
    if (++y == SUDOKU_SIZE )
    {
      ++x;
      y=0;
    }
  };
  while((c=getc(fp))!=EOF)
  {
    if (c=='.') 
      incr();
    else if (c >= '1' && c <='9' )
    {
      updDat(x,y,c-'0');
      incr();
    }
  }
}

