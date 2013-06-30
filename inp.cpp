//#include "stdafx.h"
#include <cstdio>
void getdat(FILE* fp, void (*updDat)(int,int,int))
{
	int x,y,w;
	bool fin=false;
	while (!fin)
	{
		int c = getc(fp);
		while (c!='(') c = getc(fp);
		ungetc(c,fp);
		fscanf(fp,"(%d,%d,%d)", &x, &y, &w);
		updDat(x,y,w);
		
		c =getc(fp);
		if( c!=';')
			ungetc(c,fp);
		else
			fin = true;
	}
}