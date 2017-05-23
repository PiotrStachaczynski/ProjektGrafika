#include "BMPPIC.h"
#include <gl/gl.h>						// standardowy plik nag��wkowy OpenGL
#include <gl/glu.h>						// plik nag��wkowy biblioteki GLU


BMPPIC::BMPPIC(char *filename){
	LoadBitmapFile(filename);
}

BMPPIC::~BMPPIC(void){
	//free(bitmapImage);
}

void BMPPIC::LoadBitmapFile(char *filename){
	FILE *filePtr;								// wska�nik pliku
	unsigned int		imageIdx = 0;			// licznik bajt�w obrazu
	unsigned char		tempRGB;				// zmienna zamiany sk�adowych

	// otwiera plik w trybie "read binary"
	filePtr = fopen(filename, "rb");
	// wczytuje nag��wek pliku
	fread(&this->bitmapFileHeader, sizeof(BITMAPFILEHEADER), 1, filePtr);
	
	// sprawdza, czy rzeczywi�cie jest to plik BMP
	if (bitmapFileHeader.bfType != BITMAP_ID){
		fclose(filePtr);
		
	}

	// wczytuje nag��wek obrazu zapisanego w pliku
	fread(&bitmapInfoHeader, sizeof(BITMAPINFOHEADER), 1, filePtr);

	// ustawia wska�nik pliku na pocz�tku danych opisuj�cych obraz
	fseek(filePtr, bitmapFileHeader.bfOffBits, SEEK_SET);

	// przydziela pami�� na bufor obrazu
	bitmapImage = (unsigned char*)malloc(this->bitmapInfoHeader.biSizeImage);

	// sprawdza, czy pami�� zosta�a przydzielona
	if (!bitmapImage){
		free(bitmapImage);
		fclose(filePtr);
	}

	// wczytuje dane obrazu
	fread(bitmapImage, 1,this->bitmapInfoHeader.biSizeImage, filePtr);

	// sprawdza, czy operacja powiod�a si�
	if (bitmapImage == NULL){
		fclose(filePtr);
		
	}

	// zamienia sk�adowe R i B values, aby uzyska� w�a�ciwy format RGB w OpenGL
	for (imageIdx = 0; imageIdx < this->bitmapInfoHeader.biSizeImage; imageIdx+=3){
		tempRGB = bitmapImage[imageIdx];
		bitmapImage[imageIdx] = bitmapImage[imageIdx + 2];
		bitmapImage[imageIdx + 2] = tempRGB;
	}

	// zamyka plik i zwraca wska�nik bufora zawieraj�cego obraz
	fclose(filePtr);

}

void BMPPIC::DrawBitmap(int pozx , int pozy){
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	glRasterPos2i(pozx,pozy);
	glDrawPixels(this->bitmapInfoHeader.biWidth, this->bitmapInfoHeader.biHeight, GL_RGB, GL_UNSIGNED_BYTE, this->bitmapImage);
}