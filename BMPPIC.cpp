#include "BMPPIC.h"
#include <gl/gl.h>						// standardowy plik nag³ówkowy OpenGL
#include <gl/glu.h>						// plik nag³ówkowy biblioteki GLU


BMPPIC::BMPPIC(char *filename){
	LoadBitmapFile(filename);
}

BMPPIC::~BMPPIC(void){
	//free(bitmapImage);
}

void BMPPIC::LoadBitmapFile(char *filename){
	FILE *filePtr;								// wskaŸnik pliku
	unsigned int		imageIdx = 0;			// licznik bajtów obrazu
	unsigned char		tempRGB;				// zmienna zamiany sk³adowych

	// otwiera plik w trybie "read binary"
	filePtr = fopen(filename, "rb");
	// wczytuje nag³ówek pliku
	fread(&this->bitmapFileHeader, sizeof(BITMAPFILEHEADER), 1, filePtr);
	
	// sprawdza, czy rzeczywiœcie jest to plik BMP
	if (bitmapFileHeader.bfType != BITMAP_ID){
		fclose(filePtr);
		
	}

	// wczytuje nag³ówek obrazu zapisanego w pliku
	fread(&bitmapInfoHeader, sizeof(BITMAPINFOHEADER), 1, filePtr);

	// ustawia wskaŸnik pliku na pocz¹tku danych opisuj¹cych obraz
	fseek(filePtr, bitmapFileHeader.bfOffBits, SEEK_SET);

	// przydziela pamiêæ na bufor obrazu
	bitmapImage = (unsigned char*)malloc(this->bitmapInfoHeader.biSizeImage);

	// sprawdza, czy pamiêæ zosta³a przydzielona
	if (!bitmapImage){
		free(bitmapImage);
		fclose(filePtr);
	}

	// wczytuje dane obrazu
	fread(bitmapImage, 1,this->bitmapInfoHeader.biSizeImage, filePtr);

	// sprawdza, czy operacja powiod³a siê
	if (bitmapImage == NULL){
		fclose(filePtr);
		
	}

	// zamienia sk³adowe R i B values, aby uzyskaæ w³aœciwy format RGB w OpenGL
	for (imageIdx = 0; imageIdx < this->bitmapInfoHeader.biSizeImage; imageIdx+=3){
		tempRGB = bitmapImage[imageIdx];
		bitmapImage[imageIdx] = bitmapImage[imageIdx + 2];
		bitmapImage[imageIdx + 2] = tempRGB;
	}

	// zamyka plik i zwraca wskaŸnik bufora zawieraj¹cego obraz
	fclose(filePtr);

}

void BMPPIC::DrawBitmap(int pozx , int pozy){
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	glRasterPos2i(pozx,pozy);
	glDrawPixels(this->bitmapInfoHeader.biWidth, this->bitmapInfoHeader.biHeight, GL_RGB, GL_UNSIGNED_BYTE, this->bitmapImage);
}