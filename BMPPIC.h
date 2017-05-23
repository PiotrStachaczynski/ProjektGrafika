#ifndef MYCLASS_H
#define MYCLASS_H

#include <windows.h>
#include <stdio.h>
#include <math.h>
#define BITMAP_ID 0x4D42


class BMPPIC
{
public:
	BITMAPINFOHEADER	bitmapInfoHeader;	// nag³ówek
	BITMAPFILEHEADER    bitmapFileHeader;
	unsigned char*		bitmapImage;

	BMPPIC(char *filename);
	~BMPPIC(void);
	void LoadBitmapFile(char *filename);
	void DrawBitmap(int pozx , int pozy);
};

#endif
