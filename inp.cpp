//#include "stdafx.h"
#include <cstdio>
void getdat2(FILE* fp, void (*updDat)(size_t,size_t,size_t))
{
  size_t c;
  size_t x =0;
  size_t y =0;
  auto incr = [&]  ()  
  {
    if (++y == 9)
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

void getdat(FILE* fp, void (*updDat)(size_t,size_t,size_t))
{
	size_t x,y,w;
	bool fin=false;
	while (!fin)
	{
		int c = getc(fp);
		while (c!='(') c = getc(fp);
		ungetc(c,fp);
		fscanf(fp,"(%ld,%ld,%ld)", &x, &y, &w);
		updDat(x,y,w);
		
		c =getc(fp);
		if( c!=';')
			ungetc(c,fp);
		else
			fin = true;
	}
}
