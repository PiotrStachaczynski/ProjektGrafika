// Gl_template.c
//Wy³šczanie b³êdów przed "fopen"
#define  _CRT_SECURE_NO_WARNINGS



// £adowanie bibliotek:

#ifdef _MSC_VER                         // Check if MS Visual C compiler
#  pragma comment(lib, "opengl32.lib")  // Compiler-specific directive to avoid manually configuration
#  pragma comment(lib, "glu32.lib")     // Link libraries
#endif




// Ustalanie trybu tekstowego:
#ifdef _MSC_VER        // Check if MS Visual C compiler
#   ifndef _MBCS
#      define _MBCS    // Uses Multi-byte character set
#   endif
#   ifdef _UNICODE     // Not using Unicode character set
#      undef _UNICODE 
#   endif
#   ifdef UNICODE
#      undef UNICODE 
#   endif
#endif
#include <windows.h>            // Window defines
#include <gl\gl.h>              // OpenGL
#include <gl\glu.h>             // GLU library
#include <math.h>				// Define for sqrt
#include <stdio.h>
#include "resource.h"           // About box resource identifiers.

#define glRGB(x, y, z)	glColor3ub((GLubyte)x, (GLubyte)y, (GLubyte)z)
#define BITMAP_ID 0x4D42		// identyfikator formatu BMP
#define GL_PI 3.14

// Color Palette handle
HPALETTE hPalette = NULL;

// Application name and instance storeage
static LPCTSTR lpszAppName = "GL Template";
static HINSTANCE hInstance;

// Rotation amounts
static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;


static GLsizei lastHeight;
static GLsizei lastWidth;

// Opis tekstury
BITMAPINFOHEADER	bitmapInfoHeader;	// nag³ówek obrazu
unsigned char*		bitmapData;			// dane tekstury
unsigned int		texture[2];			// obiekt tekstury


// Declaration for Window procedure
LRESULT CALLBACK WndProc(   HWND    hWnd,
							UINT    message,
							WPARAM  wParam,
							LPARAM  lParam);

// Dialog procedure for about box
BOOL APIENTRY AboutDlgProc (HWND hDlg, UINT message, UINT wParam, LONG lParam);

// Set Pixel Format function - forward declaration
void SetDCPixelFormat(HDC hDC);



// Reduces a normal vector specified as a set of three coordinates,
// to a unit normal vector of length one.
void ReduceToUnit(float vector[3])
	{
	float length;
	
	// Calculate the length of the vector		
	length = (float)sqrt((vector[0]*vector[0]) + 
						(vector[1]*vector[1]) +
						(vector[2]*vector[2]));

	// Keep the program from blowing up by providing an exceptable
	// value for vectors that may calculated too close to zero.
	if(length == 0.0f)
		length = 1.0f;

	// Dividing each element by the length will result in a
	// unit normal vector.
	vector[0] /= length;
	vector[1] /= length;
	vector[2] /= length;
	}


// Points p1, p2, & p3 specified in counter clock-wise order
void calcNormal(float v[3][3], float out[3])
	{
	float v1[3],v2[3];
	static const int x = 0;
	static const int y = 1;
	static const int z = 2;

	// Calculate two vectors from the three points
	v1[x] = v[0][x] - v[1][x];
	v1[y] = v[0][y] - v[1][y];
	v1[z] = v[0][z] - v[1][z];

	v2[x] = v[1][x] - v[2][x];
	v2[y] = v[1][y] - v[2][y];
	v2[z] = v[1][z] - v[2][z];

	// Take the cross product of the two vectors to get
	// the normal vector which will be stored in out
	out[x] = v1[y]*v2[z] - v1[z]*v2[y];
	out[y] = v1[z]*v2[x] - v1[x]*v2[z];
	out[z] = v1[x]*v2[y] - v1[y]*v2[x];

	// Normalize the vector (shorten length to one)
	ReduceToUnit(out);
	}



// Change viewing volume and viewport.  Called when window is resized
void ChangeSize(GLsizei w, GLsizei h)
	{
	GLfloat nRange = 100.0f;
	GLfloat fAspect;
	// Prevent a divide by zero
	if(h == 0)
		h = 1;

	lastWidth = w;
	lastHeight = h;
		
	fAspect=(GLfloat)w/(GLfloat)h;
	// Set Viewport to window dimensions
    glViewport(0, 0, w, h);

	// Reset coordinate system
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Establish clipping volume (left, right, bottom, top, near, far)
    if (w <= h) 
		glOrtho (-nRange, nRange, -nRange*h/w, nRange*h/w, -nRange, nRange);
    else 
		glOrtho (-nRange*w/h, nRange*w/h, -nRange, nRange, -nRange, nRange);

	// Establish perspective: 
	/*
	gluPerspective(60.0f,fAspect,1.0,400);
	*/

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	}



// This function does any needed initialization on the rendering
// context.  Here it sets up and initializes the lighting for
// the scene.
void SetupRC()
	{
	// Light values and coordinates
	//GLfloat  ambientLight[] = { 0.3f, 0.3f, 0.3f, 1.0f };
	//GLfloat  diffuseLight[] = { 0.7f, 0.7f, 0.7f, 1.0f };
	//GLfloat  specular[] = { 1.0f, 1.0f, 1.0f, 1.0f};
	//GLfloat	 lightPos[] = { 0.0f, 150.0f, 150.0f, 1.0f };
	//GLfloat  specref[] =  { 1.0f, 1.0f, 1.0f, 1.0f };


	glEnable(GL_DEPTH_TEST);	// Hidden surface removal
	glFrontFace(GL_CCW);		// Counter clock-wise polygons face out
	//glEnable(GL_CULL_FACE);		// Do not calculate inside of jet

	// Enable lighting
	//glEnable(GL_LIGHTING);

	// Setup and enable light 0
	//glLightfv(GL_LIGHT0,GL_AMBIENT,ambientLight);
	//glLightfv(GL_LIGHT0,GL_DIFFUSE,diffuseLight);
	//glLightfv(GL_LIGHT0,GL_SPECULAR,specular);
	//glLightfv(GL_LIGHT0,GL_POSITION,lightPos);
	//glEnable(GL_LIGHT0);

	// Enable color tracking
	//glEnable(GL_COLOR_MATERIAL);
	
	// Set Material properties to follow glColor values
	//glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	// All materials hereafter have full specular reflectivity
	// with a high shine
	//glMaterialfv(GL_FRONT, GL_SPECULAR,specref);
	//glMateriali(GL_FRONT,GL_SHININESS,128);


	// White background
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f );
	// Black brush
	glColor3f(0.0,0.0,0.0);
	}
int test = 1;
void skrzynka(void)
{
	glColor3d(0.8,0.7,0.3);
	
	
	glEnable(GL_TEXTURE_2D); // W³¹cz teksturowanie

	glBindTexture(GL_TEXTURE_2D,texture[0]);
	glBegin(GL_QUADS);
		glNormal3d(0,0,1);
		glTexCoord2d(1.0,1.0); glVertex3d(25,25,25);
		glTexCoord2d(0.0,1.0); glVertex3d(-25,25,25);
		glTexCoord2d(0.0,0.0); glVertex3d(-25,-25,25);
		glTexCoord2d(1.0,0.0); glVertex3d(25,-25,25);
	glEnd();
	glBindTexture(GL_TEXTURE_2D,texture[1]);
	glBegin(GL_QUADS);
		glNormal3d(1,0,0);
		glTexCoord2d(1.0,1.0); glVertex3d(25,25,25);
		glTexCoord2d(0.0,1.0); glVertex3d(25,-25,25);
		glTexCoord2d(0.0,0.0); glVertex3d(25,-25,-25);
		glTexCoord2d(1.0,0.0); glVertex3d(25,25,-25);
	glEnd();

	glDisable(GL_TEXTURE_2D); // Wy³¹cz teksturowanie



	glBegin(GL_QUADS);
		glNormal3d(0,0,-1);
		glVertex3d(25,25,-25);
		glVertex3d(25,-25,-25);
		glVertex3d(-25,-25,-25);
		glVertex3d(-25,25,-25);

		glNormal3d(-1,0,0);
		glVertex3d(-25,25,-25);
		glVertex3d(-25,-25,-25);
		glVertex3d(-25,-25,25);
		glVertex3d(-25,25,25);

		glNormal3d(0,1,0);
		glVertex3d(25,25,25);
		glVertex3d(25,25,-25);
		glVertex3d(-25,25,-25);
		glVertex3d(-25,25,25);

		glNormal3d(0,-1,0);
		glVertex3d(25,-25,25);
		glVertex3d(-25,-25,25);
		glVertex3d(-25,-25,-25);
		glVertex3d(25,-25,-25);
	glEnd();
}

void walec01(void)
{
GLUquadricObj*obj;
obj=gluNewQuadric();
gluQuadricNormals(obj,GLU_SMOOTH);
glColor3d(1,0,0);
glPushMatrix();
gluCylinder(obj,20,20,30,15,7);
gluCylinder(obj,0,20,0,15,7);
glTranslated(0,0,60);
glRotated(180.0,0,1,0);
gluCylinder(obj,0,20,30,15,7);
glPopMatrix();
}

void kula(void)
{	GLUquadricObj*obj;
	obj=gluNewQuadric();
	gluQuadricTexture(obj,GL_TRUE);
	glBindTexture(GL_TEXTURE_2D,texture[0]);
	glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
	glColor3d(1.0,0.8,0.8);
	glEnable(GL_TEXTURE_2D);
	gluSphere(obj,40,15,7);
	glDisable(GL_TEXTURE_2D);
}




// LoadBitmapFile
// opis: ³aduje mapê bitow¹ z pliku i zwraca jej adres.
//       Wype³nia strukturê nag³ówka.
//	 Nie obs³uguje map 8-bitowych.
unsigned char *LoadBitmapFile(char *filename, BITMAPINFOHEADER *bitmapInfoHeader)
{
	FILE *filePtr;							// wskaŸnik pozycji pliku
	BITMAPFILEHEADER	bitmapFileHeader;		// nag³ówek pliku
	unsigned char		*bitmapImage;			// dane obrazu
	int					imageIdx = 0;		// licznik pikseli
	unsigned char		tempRGB;				// zmienna zamiany sk³adowych

	// otwiera plik w trybie "read binary"
	filePtr = fopen(filename, "rb");
	if (filePtr == NULL)
		return NULL;

	// wczytuje nag³ówek pliku
	fread(&bitmapFileHeader, sizeof(BITMAPFILEHEADER), 1, filePtr);
	
	// sprawdza, czy jest to plik formatu BMP
	if (bitmapFileHeader.bfType != BITMAP_ID)
	{
		fclose(filePtr);
		return NULL;
	}

	// wczytuje nag³ówek obrazu
	fread(bitmapInfoHeader, sizeof(BITMAPINFOHEADER), 1, filePtr);

	// ustawia wskaŸnik pozycji pliku na pocz¹tku danych obrazu
	fseek(filePtr, bitmapFileHeader.bfOffBits, SEEK_SET);

	// przydziela pamiêæ buforowi obrazu
	bitmapImage = (unsigned char*)malloc(bitmapInfoHeader->biSizeImage);

	// sprawdza, czy uda³o siê przydzieliæ pamiêæ
	if (!bitmapImage)
	{
		free(bitmapImage);
		fclose(filePtr);
		return NULL;
	}

	// wczytuje dane obrazu
	fread(bitmapImage, 1, bitmapInfoHeader->biSizeImage, filePtr);

	// sprawdza, czy dane zosta³y wczytane
	if (bitmapImage == NULL)
	{
		fclose(filePtr);
		return NULL;
	}

	// zamienia miejscami sk³adowe R i B 
	for (imageIdx = 0; imageIdx < bitmapInfoHeader->biSizeImage; imageIdx+=3)
	{
		tempRGB = bitmapImage[imageIdx];
		bitmapImage[imageIdx] = bitmapImage[imageIdx + 2];
		bitmapImage[imageIdx + 2] = tempRGB;
	}

	// zamyka plik i zwraca wskaŸnik bufora zawieraj¹cego wczytany obraz
	fclose(filePtr);
	return bitmapImage;
}
float temp = 0.0f;
float color = 1.0f;


void zadanie8(int x, int y)
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	{
		int ilosc, ilosc_w;
		int next = 0;
		float color = 0.2f;
		GLfloat sa[3] = { 0.0f,0.0f,0.0f };
		GLfloat sb[3] = { 10.0f,0.0f,0.0f };
		GLfloat sc[3] = { 10.0f,10.0f,0.0f };
		GLfloat sd[3] = { 0.0f,10.0f,0.0f };
		GLfloat se[3] = { 0.0f,0.0f,-10.0f };
		GLfloat sf[3] = { 10.0f,0.0f,-10.0f };
		GLfloat sg[3] = { 10.0f,10.0f,-10.0f };
		GLfloat sh[3] = { 0.0f,10.0f,-10.0f };

	

		for (ilosc= 0; ilosc < x; ilosc++)
		{
			for (ilosc_w = 0; ilosc_w < y; ilosc_w++)
			{
				if (ilosc_w == y - 1 && next == 1)
				{
					break;
				}

				glColor3f(0.6f - color, color, color);
				glBegin(GL_POLYGON);
				glVertex3d(sa[0] + ilosc_w * 10.f, sa[1] + ilosc * 10.f, sa[2]);
				glVertex3d(sb[0] + ilosc_w * 10.f, sb[1] + ilosc * 10.f, sb[2]);
				glVertex3d(sc[0] + ilosc_w * 10.f, sc[1] + ilosc * 10.f, sc[2]);
				glVertex3d(sd[0] + ilosc_w * 10.f, sd[1] + ilosc * 10.f, sd[2]);
				glEnd();

				if (ilosc_w == y - 1)
				{
					glColor3f(color, 0.6f - color, 0.4f - color);
					glBegin(GL_POLYGON);
					glVertex3d(sb[0] + ilosc_w * 10.f, sb[1] + ilosc * 10.f, sb[2]);
					glVertex3d(sf[0] + ilosc_w * 10.f, sf[1] + ilosc * 10.f, sf[2]);
					glVertex3d(sg[0] + ilosc_w * 10.f, sg[1] + ilosc * 10.f, sg[2]);
					glVertex3d(sc[0] + ilosc_w * 10.f, sc[1] + ilosc * 10.f, sc[2]);
					glEnd();
				}

				glColor3f(color, 0.4f - color, color);
				glBegin(GL_POLYGON);
				glVertex3d(sf[0] + ilosc_w * 10.f, sf[1] + ilosc * 10.f, sf[2]);
				glVertex3d(se[0] + ilosc_w * 10.f, se[1] + ilosc * 10.f, se[2]);
				glVertex3d(sh[0] + ilosc_w * 10.f, sh[1] + ilosc * 10.f, sh[2]);
				glVertex3d(sg[0] + ilosc_w * 10.f, sg[1] + ilosc * 10.f, sg[2]);
				glEnd();

				if (ilosc_w == 0)
				{
					glColor3f(0.4f - color, color, 0.4f - color);
					glBegin(GL_POLYGON);
					glVertex3d(se[0] + ilosc_w * 10.f, se[1] + ilosc * 10.f, se[2]);
					glVertex3d(sa[0] + ilosc_w * 10.f, sa[1] + ilosc * 10.f, sa[2]);
					glVertex3d(sd[0] + ilosc_w * 10.f, sd[1] + ilosc * 10.f, sd[2]);
					glVertex3d(sh[0] + ilosc_w * 10.f, sh[1] + ilosc * 10.f, sh[2]);
					glEnd();
				}

				if (ilosc == x - 1 || (ilosc_w == 0 && next == 0) || (ilosc_w == y - 1 && next == 0))
				{
					glColor3f(color, 0.6f - color, 0.6f - color);
					glBegin(GL_POLYGON);
					glVertex3d(sd[0] + ilosc_w * 10.f, sd[1] + ilosc * 10.f, sd[2]);
					glVertex3d(sc[0] + ilosc_w * 10.f, sc[1] + ilosc * 10.f, sc[2]);
					glVertex3d(sg[0] + ilosc_w * 10.f, sg[1] + ilosc * 10.f, sg[2]);
					glVertex3d(sh[0] + ilosc_w * 10.f, sh[1] + ilosc * 10.f, sh[2]);
					glEnd();
				}

				if (ilosc == 0 || (ilosc_w == 0 && next == 0) || (ilosc_w == y - 1 && next == 0))
				{
					glColor3f(0.3f - color, color, 0.3f - color);
					glBegin(GL_POLYGON);
					glVertex3d(sa[0] + ilosc_w * 10.f, sa[1] + ilosc * 10.f, sa[2]);
					glVertex3d(sb[0] + ilosc_w * 10.f, sb[1] + ilosc * 10.f, sb[2]);
					glVertex3d(sf[0] + ilosc_w * 10.f, sf[1] + ilosc * 10.f, sf[2]);
					glVertex3d(se[0] + ilosc_w * 10.f, se[1] + ilosc * 10.f, se[2]);
					glEnd();
				}

				color = color + 0.05f;

				if (color > 0.6f)
				{
					color = 0.0f;
				}
			}

			if (next == 0)
			{
				sa[0] += 5.0f;
				sb[0] += 5.0f;
				sc[0] += 5.0f;
				sd[0] += 5.0f;
				se[0] += 5.0f;
				sf[0] += 5.0f;
				sg[0] += 5.0f;
				sh[0] += 5.0f;

				next = 1;
			}
			else
			{
				sa[0] = 0.0f;
				sb[0] = 10.0f;
				sc[0] = 10.0f;
				sd[0] = 0.0f;
				se[0] = 0.0f;
				sf[0] = 10.0f;
				sg[0] = 10.0f;
				sh[0] = 0.0f;

				next = 0;
			}
		}
	}
}





void szescian(void)
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	{
		// Parametry wierzcholkow

		GLfloat sa[3] = { 0.0f,0.0f,0.0f };
		GLfloat sb[3] = { 10.0f,0.0f,0.0f };
		GLfloat sc[3] = { 10.0f,10.0f,0.0f };
		GLfloat sd[3] = { 0.0f,10.0f,0.0f };
		GLfloat se[3] = { 0.0f,0.0f,-10.0f };
		GLfloat sf[3] = { 10.0f,0.0f,-10.0f };
		GLfloat sg[3] = { 10.0f,10.0f,-10.0f };
		GLfloat sh[3] = { 0.0f,10.0f,-10.0f };


		// Sciany skladowe
		glColor3f(1.0f, 0.0f, 0.0f);
		glBegin(GL_POLYGON);
		glVertex3fv(sa);
		glVertex3fv(sb);
		glVertex3fv(sc);
		glVertex3fv(sd);
		glEnd();

		glColor3f(0.0f, 1.0f, 0.0f);
		glBegin(GL_POLYGON);
		glVertex3fv(sb);
		glVertex3fv(sf);
		glVertex3fv(sg);
		glVertex3fv(sc);
		glEnd();

		glColor3f(0.0f, 0.0f, 1.0f);
		glBegin(GL_POLYGON);
		glVertex3fv(sf);
		glVertex3fv(se);
		glVertex3fv(sh);
		glVertex3fv(sg);
		glEnd();

		glColor3f(1.0f, 1.0f, 0.0f);
		glBegin(GL_POLYGON);
		glVertex3fv(se);
		glVertex3fv(sa);
		glVertex3fv(sd);
		glVertex3fv(sh);
		glEnd();

		glColor3f(0.0f, 1.0f, 1.0f);
		glBegin(GL_POLYGON);
		glVertex3fv(sd);
		glVertex3fv(sc);
		glVertex3fv(sg);
		glVertex3fv(sh);
		glEnd();

		glColor3f(1.0f, 0.0f, 1.0f);
		glBegin(GL_POLYGON);
		glVertex3fv(sa);
		glVertex3fv(sb);
		glVertex3fv(sf);
		glVertex3fv(se);
		glEnd();
	}
}

	void Zadanie1(void)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		{
			// Parametry wierzcholkow

			GLfloat sa[3] = { 0.0f,0.0f,0.0f };
			GLfloat sb[3] = { 10.0f,0.0f,0.0f };
			GLfloat sc[3] = { 10.0f,10.0f,0.0f };
			GLfloat sd[3] = { 0.0f,10.0f,0.0f };
			GLfloat se[3] = { 0.0f,0.0f,-10.0f };
			GLfloat sf[3] = { 10.0f,0.0f,-10.0f };
			GLfloat sg[3] = { 10.0f,10.0f,-10.0f };
			GLfloat sh[3] = { 0.0f,10.0f,-10.0f };


			// Sciany skladowe
		


			glColor3f(1.0f, 0.0f, 0.0f);
			glBegin(GL_POLYGON);
			glVertex3fv(sa);
			glVertex3fv(sb);
			glVertex3fv(sc);
			glVertex3fv(sd);
			glEnd();

			glColor3f(0.0f, 1.0f, 0.0f);
			glBegin(GL_POLYGON);
			glVertex3fv(sb);
			glVertex3fv(sf);
			glVertex3fv(sg);
			glVertex3fv(sc);
			glEnd();

			glColor3f(0.0f, 0.0f, 1.0f);
			glBegin(GL_POLYGON);
			glVertex3fv(sf);
			glVertex3fv(se);
			glVertex3fv(sh);
			glVertex3fv(sg);
			glEnd();

			glColor3f(1.0f, 1.0f, 0.0f);
			glBegin(GL_POLYGON);
			glVertex3fv(se);
			glVertex3fv(sa);
            glVertex3fv(sd);
			glVertex3fv(sh);
			glEnd();

		

		

			glColor3f(0.0f, 1.0f, 1.0f);
			glBegin(GL_POLYGON);
			glVertex3d(sd[0], sd[1] + 10, sd[2]);
			glVertex3d(sc[0], sc[1] + 10, sc[2]);
			glVertex3d(sg[0], sg[1] + 10, sg[2]);
			glVertex3d(sh[0], sh[1] + 10, sh[2]);
			glEnd();

			glColor3f(1.0f, 0.0f, 1.0f);
			glBegin(GL_POLYGON);
			glVertex3fv(sa);
			glVertex3fv(sb);
			glVertex3fv(sf);
			glVertex3fv(se);
			glEnd();
		}
}

	void Zadanie2(void)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		{
			// Parametry wierzcholkow

			GLfloat sa[3] = { 0.0f,0.0f,0.0f };
			GLfloat sb[3] = { 10.0f,0.0f,0.0f };
			GLfloat sc[3] = { 10.0f,10.0f,0.0f };
			GLfloat sd[3] = { 0.0f,10.0f,0.0f };
			GLfloat se[3] = { 0.0f,0.0f,-10.0f };
			GLfloat sf[3] = { 10.0f,0.0f,-10.0f };
			GLfloat sg[3] = { 10.0f,10.0f,-10.0f };
			GLfloat sh[3] = { 0.0f,10.0f,-10.0f };


			// Sciany skladowe
			glColor3f(1.0f, 0.0f, 0.0f);
			glBegin(GL_POLYGON);
			glVertex3fv(sa);
			glVertex3fv(sb);
			glVertex3fv(sc);
			glVertex3fv(sd);
			glEnd();

			glColor3f(0.0f, 1.0f, 0.0f);
			glBegin(GL_POLYGON);
			glVertex3fv(sb);
			glVertex3fv(sf);
			glVertex3fv(sg);
			glVertex3fv(sc);
			glEnd();

			glColor3f(0.0f, 0.0f, 1.0f);
			glBegin(GL_POLYGON);
			glVertex3fv(sf);
			glVertex3fv(se);
			glVertex3fv(sh);
			glVertex3fv(sg);
			glEnd();

			glColor3f(1.0f, 1.0f, 0.0f);
			glBegin(GL_POLYGON);
			glVertex3fv(se);
			glVertex3fv(sa);
			glVertex3fv(sd);
			glVertex3fv(sh);
			glEnd();

			glColor3f(0.0f, 1.0f, 1.0f);
			glBegin(GL_POLYGON);
			glVertex3d(sd[0]+10, sd[1] , sd[2]);
			glVertex3d(sc[0]+10, sc[1] , sc[2]);
			glVertex3d(sg[0]+10, sg[1] , sg[2]);
			glVertex3d(sh[0]+10, sh[1] , sh[2]);
			glEnd();

			glColor3f(1.0f, 0.0f, 1.0f);
			glBegin(GL_POLYGON);
			glVertex3fv(sa);
			glVertex3fv(sb);
			glVertex3fv(sf);
			glVertex3fv(se);
			glEnd();
		}
	}

	void Zadanie3(void)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		{
			GLfloat sa[3] = { 0.0f,0.0f,0.0f };
			GLfloat sb[3] = { 10.0f,0.0f,0.0f };
			GLfloat sc[3] = { 10.0f,10.0f,0.0f };
			GLfloat sd[3] = { 0.0f,10.0f,0.0f };
			GLfloat se[3] = { 0.0f,0.0f,-10.0f };
			GLfloat sf[3] = { 10.0f,0.0f,-10.0f };
			GLfloat sg[3] = { 10.0f,10.0f,-10.0f };
			GLfloat sh[3] = { 0.0f,10.0f,-10.0f };
			GLfloat a[3] = { 5.0f * sqrt(2), 10.0f + 5.0f * sqrt(2), 0.0f };
			GLfloat b[3] = { 5.0f * sqrt(2), 10.0f + 5.0f * sqrt(2), -10.0f };

			glColor3f(1.0f, 0.0f, 0.0f);
			glBegin(GL_POLYGON);
			glVertex3fv(sa);
			glVertex3fv(sb);
			glVertex3fv(sc);
			glVertex3fv(sd);
			glEnd();

			glColor3f(0.0f, 1.0f, 0.0f);
			glBegin(GL_POLYGON);
			glVertex3fv(sb);
			glVertex3fv(sf);
			glVertex3fv(sg);
			glVertex3fv(sc);
			glEnd();

			glColor3f(0.0f, 0.0f, 1.0f);
			glBegin(GL_POLYGON);
			glVertex3fv(sf);
			glVertex3fv(se);
			glVertex3fv(sh);
			glVertex3fv(sg);
			glEnd();

			glColor3f(1.0f, 1.0f, 0.0f);
			glBegin(GL_POLYGON);
			glVertex3fv(se);
			glVertex3fv(sa);
			glVertex3fv(sd);
			glVertex3fv(sh);
			glEnd();

			glColor3f(0.0f, 1.0f, 1.0f);
			glBegin(GL_POLYGON);
			glVertex3d(a[0], a[1], a[2]);
			glVertex3d(sc[0], sc[1], sc[2]);
			glVertex3d(sg[0], sg[1], sg[2]);
			glVertex3d(b[0], b[1], b[2]);
			glEnd();

			glColor3f(1.0f, 0.0f, 1.0f);
			glBegin(GL_POLYGON);
			glVertex3fv(sa);
			glVertex3fv(sb);
			glVertex3fv(sf);
			glVertex3fv(se);
			glEnd();
		}
	}
		
	void Zadanie4(void)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		{
			// Parametry wierzcholkow

			GLfloat sa[3] = { 0.0f,0.0f,0.0f };
			GLfloat sb[3] = { 10.0f,0.0f,0.0f };
			GLfloat sc[3] = { 10.0f,10.0f,0.0f };
			GLfloat sd[3] = { 0.0f,10.0f,0.0f };
			GLfloat se[3] = { 0.0f,0.0f,-10.0f };
			GLfloat sf[3] = { 10.0f,0.0f,-10.0f };
			GLfloat sg[3] = { 10.0f,10.0f,-10.0f };
			GLfloat sh[3] = { 0.0f,10.0f,-10.0f };
			GLfloat a[3] = {-3.f*sqrt(2) , 10.f,-10.f };
			GLfloat b[3] = { 10.f-5.0f * sqrt(2),10.f, -10.0f - 5.0f * sqrt(2)};
			GLfloat c[3] = { 10.f-5.0f * sqrt(2),10.f,   -10.f+5.0f * sqrt(2) };


			// Sciany skladowe
			glColor3f(1.0f, 0.0f, 0.0f);
			glBegin(GL_POLYGON);
			glVertex3fv(sa);
			glVertex3fv(sb);
			glVertex3fv(sc);
			glVertex3fv(sd);
			glEnd();

			glColor3f(0.0f, 1.0f, 0.0f);
			glBegin(GL_POLYGON);
			glVertex3fv(sb);
			glVertex3fv(sf);
			glVertex3fv(sg);
			glVertex3fv(sc);
			glEnd();

			glColor3f(0.0f, 0.0f, 1.0f);
			glBegin(GL_POLYGON);
			glVertex3fv(sf);
			glVertex3fv(se);
			glVertex3fv(sh);
			glVertex3fv(sg);
			glEnd();

			glColor3f(1.0f, 1.0f, 0.0f);
			glBegin(GL_POLYGON);
			glVertex3fv(se);
			glVertex3fv(sa);
			glVertex3fv(sd);
			glVertex3fv(sh);
			glEnd();

			glColor3f(0.9f, 0.7f, 0.0f);
			glBegin(GL_POLYGON);
			glVertex3d(a[0], a[1], a[2]);
			glVertex3d(c[0], c[1], c[2]);
			glVertex3d(sg[0], sg[1], sg[2]);
			glVertex3d(b[0], b[1], b[2]);
			glEnd();

			glColor3f(1.0f, 0.0f, 1.0f);
			glBegin(GL_POLYGON);
			glVertex3fv(sa);
			glVertex3fv(sb);
			glVertex3fv(sf);
			glVertex3fv(se);
			glEnd();
		}
	}
	// PROJEKT
legs(int wsp_x,int wsp_y,int wsp_z,GLfloat scale)
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	{
		double x = 1;
		double y = 1;
		double z = 0;
	//	GLfloat se[3] = { 0.0f,0.0f,-10.0f };
		int i = 0, j=0;
		while (i <= 7)
		{

			if (j == 1)
			{
				y = -1;

			}
			if (j == 2)
			{
				x = -1;

			}
			if (j == 3)
			{

				y = 1;
			}
			if (j == 4)
			{
				x = 1;
				z = z + 5;
				j = 0;
			}

			GLfloat a[3] = { wsp_x+(x*25.0f+scale),wsp_y+z,wsp_z+(y*25.0f+scale) };
			GLfloat b[3] = { wsp_x+(x*65.0f+scale),wsp_y+z,wsp_z+(y*65.0f+scale) };
			GLfloat c[3] = { wsp_x+(x*10.0f+scale),wsp_y+z,wsp_z+(y*35.0f+scale) };
			GLfloat d[3] = { wsp_x+(x*60.0f+scale),wsp_y+z,wsp_z+(y*70.0f+scale) };

			glColor3f(0.9f, 0.8f, 0.8f);
			glBegin(GL_TRIANGLE_STRIP);
			glVertex3fv(a);
			glVertex3fv(b);
			glColor3f(0.6f, 0.4f, 0.5f);
			glVertex3fv(c);
			glVertex3fv(d);
			glEnd();

			glColor3f(0.9f, 0.8f, 0.8f);
			glBegin(GL_TRIANGLE_STRIP);
			glVertex3f(b[0],  wsp_y+ 0, b[2]);
			glVertex3f(a[0], wsp_y + 0, a[2]);
			glColor3f(0.2f,  0.2f, 0.2f);
			glVertex3f(b[0], wsp_y + 5, b[2]);
			glVertex3f(a[0], wsp_y + 5, a[2]);

			glColor3f(0.2f, 0.2f, 0.2f);
			glBegin(GL_TRIANGLE_STRIP);
			glVertex3f(d[0], wsp_y + 0, d[2]);
			glVertex3f(c[0], wsp_y + 0, c[2]);
			glColor3f(0.9f,   0.8f, 0.8f);
			glVertex3f(d[0], wsp_y + 5, d[2]);
			glVertex3f(c[0], wsp_y + 5, c[2]);
			
			glColor3f(0.1f, 0.2f, 0.2f);
			glBegin(GL_TRIANGLE_STRIP);
			glVertex3f(b[0], wsp_y + 0, b[2]);
			glVertex3f(d[0], wsp_y + 0, d[2]);
			glColor3f(0.9f,   0.9f, 0.9f);
			glVertex3f(b[0], wsp_y + 5, b[2]);
			glVertex3f(d[0], wsp_y + 5, d[2]);
			
			glEnd();

			i++;
			j++;

			double angle, q, w;

			glColor3f(0.9f, 0.0f, 0.9f);
			glBegin(GL_TRIANGLE_STRIP);
			for (angle = 0; angle <= 2 * GL_PI; angle += GL_PI / 8.0)
			{
				q = 3 * sin(angle);
				w = 3 * cos(angle);


				glVertex3f(wsp_x+(x*60.0f), wsp_y+5.0f, wsp_z+(y*66.0f));
				glColor3f(0.1f, 0.0f, 0.1f);
				glVertex3f(wsp_x+(x*(q+60)), wsp_y+5.0f, wsp_z+(y*(w+66.0f)));

			}
			glEnd();

			
			glBegin(GL_TRIANGLE_STRIP);
			for (angle = 0; angle <= 2 * GL_PI; angle += GL_PI / 8.0)
			{
				q = 3 * sin(angle);
				w = 3 * cos(angle);

				glColor3f(0.9f, 0.0f, 0.9f);
				glVertex3f(wsp_x+(x*60.0f), wsp_y+15.0f, wsp_z+(y*66.0f));
				glColor3f(0.3f, 0.0f, 0.3f);
				glVertex3f(wsp_x+(x*(q + 60)), wsp_y+15.0f, wsp_z+(y*(w + 66.0f)));
				

			}
			glEnd();

			
			glBegin(GL_TRIANGLE_STRIP);
			for (angle = 0; angle <= 2 * GL_PI; angle += GL_PI / 8.0)
			{
				q = 3 * sin(angle);
				w = 3 * cos(angle);

				glColor3f(0.9f, 0.8f, 0.9f);
				glVertex3f(wsp_x+(x*(q+60.0f)), wsp_y+15.0f, wsp_z+(y*(w+66.0f)));
				glColor3f(0.2f, 0.0f, 0.2f);
				glVertex3f(wsp_x+(x*(q + 60)), wsp_y+5.0f, wsp_z+(y*(w + 66.0f)));

			}
			glEnd();

			
		}
	}
}

gadgets(int wsp_x, int wsp_y, int wsp_z)
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	{
		double w, q;
		double x = 1;
		double y = 1;
		double z = 0;
		//	GLfloat se[3] = { 0.0f,0.0f,-10.0f };
		int i = 0, j = 0;
		while (i <= 7)
		{

			if (j == 1)
			{
				y = -1;

			}
			if (j == 2)
			{
				x = -1;

			}
			if (j == 3)
			{

				y = 1;
			}
			if (j == 4)
			{
				x = 1;
				z = z + 5;
				j = 0;
			}
			i++;
			j++;
			double angle;
			glColor3f(0.1f, 0.2f, 0.2f);
			glBegin(GL_TRIANGLE_STRIP);
			for (angle = 0; angle <= 2 * GL_PI; angle += GL_PI / 8.0)
			{
				q = 3 * sin(angle);
				w = 3 * cos(angle);


				glVertex3f(wsp_x + (x*27.0f), wsp_y + 5.0f, wsp_z + (y*18.0f));
				glColor3f(0.1f, 0.4f, 0.6f);
				glVertex3f(wsp_x + (x*(q + 27)), wsp_y + 5.0f, wsp_z + (y*(w + 18.0f)));

			}
			glEnd();


			glBegin(GL_TRIANGLE_STRIP);
			for (angle = 0; angle <= 2 * GL_PI; angle += GL_PI / 8.0)
			{
				q = 3 * sin(angle);
				w = 3 * cos(angle);

				glColor3f(0.3f, 0.1f, 0.4f);
				glVertex3f(wsp_x + (x*27.0f), wsp_y + 15.0f, wsp_z + (y*18.0f));
				glColor3f(0.1f, 0.2f, 0.2f);
				glVertex3f(wsp_x + (x*(q + 27)), wsp_y + 15.0f, wsp_z + (y*(w + 18.0f)));


			}
			glEnd();


			glBegin(GL_TRIANGLE_STRIP);
			for (angle = 0; angle <= 2 * GL_PI; angle += GL_PI / 8.0)
			{
				q = 3 * sin(angle);
				w = 3 * cos(angle);

				glColor3f(0.0f, 0.4f, 0.3f);
				glVertex3f(wsp_x + (x*(q + 27.0f)), wsp_y + 15.0f, wsp_z + (y*(w + 18.0f)));
				glColor3f(0.0f, 0.1f, 0.2f);
				glVertex3f(wsp_x + (x*(q + 27)), wsp_y + 5.0f, wsp_z + (y*(w + 18.0f)));

			}
			glEnd();

			

			glColor3f(0.0f, 0.6f, 0.0f);
			glBegin(GL_TRIANGLE_STRIP);
			for (angle = 0; angle <= 2 * GL_PI; angle += GL_PI / 8.0)
			{
				{
					q = 3 * sin(angle);
					w = 3 * cos(angle);

					glColor3f(0.1f, 0.9f, 0.3f);
					glVertex3f(wsp_x + (x*(q + 27.0f)), wsp_y + 15.0f, wsp_z + (y*(w + 18.0f)));
					glColor3f(0.5f, 0.8f, 0.7f);
					glVertex3f(wsp_x + (x*(1 + 23)), wsp_y + 20.0f, wsp_z + (y*(1 + 15.0f)));

				}
			}
			glEnd();
		}
	}
}

foots(int wsp_x, int wsp_y, int wsp_z, GLfloat scale)
{


	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	{
		double x = 1;
		double y = 1;
		double z = 0;
		//	GLfloat se[3] = { 0.0f,0.0f,-10.0f };
		int i = 0, j = 0;
		GLfloat a[3] = { wsp_x + (x*25.0f + scale),wsp_y + z,wsp_z + (y*25.0f + scale) };
		GLfloat b[3] = { wsp_x + (x*65.0f + scale),wsp_y + z,wsp_z + (y*65.0f + scale) };
		GLfloat c[3] = { wsp_x + (x*10.0f + scale),wsp_y + z,wsp_z + (y*35.0f + scale) };
		GLfloat d[3] = { wsp_x + (x*60.0f + scale),wsp_y + z,wsp_z + (y*70.0f + scale) };;
		while (i <= 7)
		{

			if (j == 1)
			{
				y = -1;

			}
			if (j == 2)
			{
				x = -1;

			}
			if (j == 3)
			{

				y = 1;
			}
			if (j == 4)
			{
				x = 1;
				z = z + 5;
				j = 0;
			}

			

			i++;
			j++;

			double angle, q, w,t,u;

			glColor3f(0.9f, 0.0f, 0.9f);
			glBegin(GL_TRIANGLE_STRIP);
			for (angle = 0; angle <= 2 * GL_PI; angle += GL_PI / 8.0)
			{
				q = 4 * sin(angle);
				w = 4 * cos(angle);


				glVertex3f(wsp_x + (x*60.0f), wsp_y , wsp_z + (y*66.0f));
				glColor3f(0.1f, 0.0f, 0.1f);
				glVertex3f(wsp_x + (x*(q + 60)), wsp_y , wsp_z + (y*(w + 66.0f)));

			}
			glEnd();


			glBegin(GL_TRIANGLE_STRIP);
			for (angle = 0; angle <= 2 * GL_PI; angle += GL_PI / 8.0)
			{
				q = 4 * sin(angle);
				w = 4 * cos(angle);

				glColor3f(0.9f, 0.0f, 0.9f);
				glVertex3f(wsp_x + (x*60.0f), wsp_y - 5.0f, wsp_z + (y*66.0f));
				glColor3f(0.3f, 0.0f, 0.3f);
				glVertex3f(wsp_x + (x*(q + 60)), wsp_y -5.0f, wsp_z + (y*(w + 66.0f)));


			}
			glEnd();


			glBegin(GL_TRIANGLE_STRIP);
			for (angle = 0; angle <= 2 * GL_PI; angle += GL_PI / 8.0)
			{
				q = 4 * sin(angle);
				w = 4 * cos(angle);

				glColor3f(0.9f, 0.8f, 0.9f);
				glVertex3f(wsp_x + (x*(q + 60.0f)), wsp_y -5.f, wsp_z + (y*(w + 66.0f)));
				glColor3f(0.2f, 0.3f, 0.2f);
				glVertex3f(wsp_x + (x*(q + 60)), wsp_y , wsp_z + (y*(w + 66.0f)));

			}
			glEnd();

			// 2 stopien 

			glColor3f(0.9f, 0.0f, 0.9f);
			glBegin(GL_TRIANGLE_STRIP);
			for (angle = 0; angle <= 2 * GL_PI; angle += GL_PI / 8.0)
			{
				q = 3 * sin(angle);
				w = 3 * cos(angle);


				glVertex3f(wsp_x + (x*60.0f), wsp_y-5.f, wsp_z + (y*66.0f));
				glColor3f(0.1f, 0.0f, 0.1f);
				glVertex3f(wsp_x + (x*(q + 60)), wsp_y-5.f, wsp_z + (y*(w + 66.0f)));

			}
			glEnd();


			glBegin(GL_TRIANGLE_STRIP);
			for (angle = 0; angle <= 2 * GL_PI; angle += GL_PI / 8.0)
			{
				q = 3 * sin(angle);
				w = 3 * cos(angle);

				glColor3f(0.9f, 0.0f, 0.9f);
				glVertex3f(wsp_x + (x*60.0f), wsp_y - 15.0f, wsp_z + (y*66.0f));
				glColor3f(0.3f, 0.0f, 0.3f);
				glVertex3f(wsp_x + (x*(q + 60)), wsp_y - 15.0f, wsp_z + (y*(w + 66.0f)));


			}
			glEnd();


			glBegin(GL_TRIANGLE_STRIP);
			for (angle = 0; angle <= 2 * GL_PI; angle += GL_PI / 8.0)
			{
				q = 3 * sin(angle);
				w = 3 * cos(angle);

				glColor3f(0.9f, 0.5f, 0.9f);
				glVertex3f(wsp_x + (x*(q + 60.0f)), wsp_y - 15.f, wsp_z + (y*(w + 66.0f)));
				glColor3f(0.2f, 0.3f, 0.2f);
				glVertex3f(wsp_x + (x*(q + 60)), wsp_y -5.f, wsp_z + (y*(w + 66.0f)));

			}
			glEnd();
			
			// igielki

			glColor3f(0.9f, 0.0f, 0.9f);
			glBegin(GL_TRIANGLE_STRIP);
			for (angle = 0; angle <= 2 * GL_PI; angle += GL_PI / 8.0)
			{
				q = 3 * sin(angle);
				w = 3 * cos(angle);


				glVertex3f(wsp_x + (x*60.0f), wsp_y - 15.f, wsp_z + (y*66.0f));
				glColor3f(0.1f, 0.0f, 0.1f);
				glVertex3f(wsp_x + (x*(q + 60)), wsp_y - 15.f, wsp_z + (y*(w + 66.0f)));

			}
			glEnd();


			glBegin(GL_TRIANGLE_STRIP);
			for (angle = 0; angle <= 2 * GL_PI; angle += GL_PI / 8.0)
			{
				q = 3 * sin(angle);
				w = 3 * cos(angle);

				t = 1.5 * sin(angle);
				u = 1.5 * cos(angle);

				glColor3f(0.1f, 0.0f, 0.1f);
				glVertex3f(wsp_x + (x*(t+60.0f)), wsp_y - 20.0f, wsp_z + (y*(u+66.0f)));
				glColor3f(0.3f, 0.7f, 0.3f);
				glVertex3f(wsp_x + (x*(q + 60)), wsp_y - 15.0f, wsp_z + (y*(w + 66.0f)));


			}
			glEnd();



		}
		//tr
			//glColor3f(0.2f, 0.2f, 0.2f);
			//glBegin(GL_TRIANGLE_STRIP);
			//glVertex3f(d[0], wsp_y + 0, d[2]);
			//glVertex3f(c[0], wsp_y + 0, c[2]);
			//glColor3f(0.9f, 0.8f, 0.8f);
			//glVertex3f(d[0], wsp_y + 5, d[2]);
			//glVertex3f(c[0], wsp_y + 5, c[2]);

			//glColor3f(0.1f, 0.2f, 0.2f);
			//glBegin(GL_TRIANGLE_STRIP);
			//glVertex3f(b[0], wsp_y + 0, b[2]);
			//glVertex3f(d[0], wsp_y + 0, d[2]);
			//glColor3f(0.9f, 0.9f, 0.9f);
			//glVertex3f(b[0], wsp_y + 5, b[2]);
			//glVertex3f(d[0], wsp_y + 5, d[2]);

			//glEnd();

	
	}
}

body(int wsp_x,int wsp_y,int wsp_z)
{
	int x = 1;
	int y = 1;
	double z = 0;
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	{
		for (int i = 0; i <= 4; i++)
		{
			if (i > 1)
			{
				z = 5;
				if (i == 3)
				{
					y = 1;
				}
			}
			GLfloat a[3] = { 25.f,z,25.f };
			GLfloat b[3] = { 10.f,z,35.f };
			GLfloat c[3] = { -25.f,z,25.f };
			GLfloat d[3] = { -10.f,z,35.f };
			
			glColor3f(0.5f, 0.9f, 0.6f);
			glBegin(GL_POLYGON);
			glVertex3f(wsp_x+(x*a[0]), wsp_y+(a[1]), wsp_z+(y*a[2]));
			glVertex3f(wsp_x+(x*b[0]), wsp_y+(b[1]), wsp_z+(y*b[2]));
			glColor3f(0.7f, 0.8f, 0.8f);
			glVertex3f(wsp_x+(x*d[0]), wsp_y+(d[1]), wsp_z+(y*d[2]));
			glVertex3f(wsp_x+(x*c[0]), wsp_y+(c[1]), wsp_z+(y*c[2]));
			glEnd();
			if (i <= 1)
			{
				glColor3f(0.8f, 0.9f, 0.9f);
				glBegin(GL_POLYGON);
				glVertex3f(wsp_x+(x*d[0]), wsp_y+(d[1]), wsp_z+(y*d[2]));
				glVertex3f(wsp_x+(x*b[0]), wsp_y+(b[1]), wsp_z+(y*b[2]));
				glColor3f(0.7f, 0.5f, 0.7);
				glVertex3f(wsp_x+(x*b[0]), wsp_y+(b[1]) + 5, wsp_z+(y*b[2]));
				glVertex3f(wsp_x+(x*d[0]), wsp_y+(d[1]) + 5, wsp_z+(y*d[2]));
				glEnd();
				
				y = 1;
				glColor3f(0.6f, 0.8f, 0.7f);
				glBegin(GL_POLYGON);
				glVertex3f(wsp_x+(x*a[0]), wsp_y+(a[1]), wsp_z+(y*a[2]));
				glVertex3f(wsp_x+(x*a[0]), wsp_y+(a[1]+5), wsp_z+(y*a[2]));
				glVertex3f(wsp_x+(x*a[0]), wsp_y+(a[1]+5), wsp_z+(-y*a[2]));
				glVertex3f(wsp_x+(x*a[0]), wsp_y+(a[1]), wsp_z+(-y*a[2]));
				glEnd();

				glColor3f(0.6f, 0.8f, 0.7f);
				glBegin(GL_POLYGON);
				glVertex3f(wsp_x+(x*c[0]), wsp_y+(c[1]), wsp_z+(y*c[2]));
				glVertex3f(wsp_x+(x*c[0]), wsp_y+(c[1] + 5), wsp_z+(y*c[2]));
				glVertex3f(wsp_x+(x*c[0]), wsp_y+(c[1] + 5), wsp_z+(-y*c[2]));
				glVertex3f(wsp_x+(x*c[0]), wsp_y+(c[1]), wsp_z+(-y*c[2]));
				glEnd();
			}


			y = 1;
			glColor3f(0.6f, 0.8f, 0.7f);
			glBegin(GL_POLYGON);
			glVertex3f(wsp_x+(x*a[0]), wsp_y+(a[1]), wsp_z+(y*a[2]));
			glVertex3f(wsp_x+(x*c[0]), wsp_y+(c[1]), wsp_z+(y*c[2]));
			glColor3f(0.8f, 0.9f, 0.9f);
			glVertex3f(wsp_x+(x*-a[0]), wsp_y+(a[1]), wsp_z+(-y*a[2]));
			glVertex3f(wsp_x+(x*-c[0]), wsp_y+(c[1]), wsp_z+(-y*c[2]));
			glEnd();

			y = -1;
			

		
		}
	
	}
}

head(int wsp_x,int wsp_y,int wsp_z)
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	{
	

		double z = 0;
		double x = 1;
		double y = 1;
		GLfloat a[3] = { 25.f,z,25.f };
		GLfloat b[3] = { 10.f,z,35.f };
		GLfloat c[3] = { -25.f,z,25.f };
		GLfloat d[3] = { -10.f,z,35.f };
		for (int i = 0; i < 4; i++)
		{
			if (i == 2)
			{
				y = -1;
			}
			if (i == 3)
			{
				x = 1;
			}
			glBegin(GL_POLYGON);
			glColor3f(0.9f, 0.0f, 0.8f);
			glVertex3f(x*(a[0])+wsp_x, (a[1] + 5)+wsp_y, y*(a[2])+wsp_z);
			glVertex3f(x*(a[0] - 3)+wsp_x, (a[1] + 15)+wsp_y, (y*(a[2] - 3)+wsp_z));
			glColor3f(0.4f, 0.0f, 0.1f);
			glVertex3f((x*(b[0] - 3))+wsp_x, (b[1] + 15)+wsp_y, (y*(b[2] - 3)+wsp_z));
			glVertex3f(x*(b[0])+wsp_x, (b[1] + 5)+wsp_y, y*(b[2])+wsp_z);
			glEnd();
			x = -1;
		}

			glBegin(GL_POLYGON);
			glColor3f(0.6f, 0.0f, 0.8f);
			glVertex3f(-a[0]+wsp_x, a[1]+wsp_y + 5, -a[2]+wsp_z);
			glVertex3f(-a[0] + 3+wsp_x, a[1] + 15+wsp_y, -a[2] + 3+wsp_z);
			glColor3f(0.4f, 0.0f, 0.4f);
			glVertex3f(-a[0] + 3+wsp_x, a[1] + 15+wsp_y, a[2] - 3+wsp_z);
			glVertex3f(-a[0]+wsp_x, a[1] + 5+wsp_y, a[2]+wsp_z);
			glEnd();

			
			glBegin(GL_POLYGON);
			glColor3f(0.6f, 0.0f, 0.8f);
			glVertex3f(a[0]+wsp_x, a[1] + 5+wsp_y, -a[2]+wsp_z);
			glVertex3f(a[0] - 3+wsp_x, a[1] + 15+wsp_y, -a[2] + 3+wsp_z);
			glColor3f(0.4f, 0.0f, 0.4f);
			glVertex3f(a[0] - 3+wsp_x, a[1] + 15+wsp_y, a[2] - 3+wsp_z);
			glVertex3f(a[0]+wsp_x, a[1] + 5+wsp_y, a[2]+wsp_z);
			glEnd();

			
			glBegin(GL_POLYGON);
			glColor3f(0.6f, 0.0f, 0.8f);
			glVertex3f(-b[0]+wsp_x, b[1] + 5+wsp_y, -b[2]+wsp_z);
			glVertex3f(-b[0] + 3+wsp_z, b[1] + 15+wsp_y, -b[2] + 3+wsp_z);
			glColor3f(0.4f, 0.0f, 0.6f);
			glVertex3f(b[0] - 3+wsp_x, b[1] + 15+wsp_y, -b[2] + 3+wsp_z);
			glVertex3f(b[0]+wsp_z, b[1] + 5+wsp_y, -b[2]+wsp_z);
			glEnd();

			
			glBegin(GL_POLYGON);
			glColor3f(0.6f, 0.0f, 0.8f);
			glVertex3f(b[0]+wsp_x, b[1] + 5+wsp_y, b[2]+wsp_z);
			glVertex3f(b[0] - 3+wsp_x, b[1] + 15+wsp_y, b[2] - 3+wsp_z);
			glColor3f(0.4f, 0.0f, 0.6f);
			glVertex3f(-b[0] + 3+wsp_x, b[1] + 15+wsp_y, b[2] - 3+wsp_z);
			glVertex3f(-b[0]+wsp_x, b[1] + 5+wsp_y, b[2]+wsp_z);
			glEnd();
		
			x = 1;
			y = 1;
					for (int i = 0; i < 4; i++)
		{
			if (i == 2)
			{
				y = -1;
			}
			if (i == 3)
			{
				x = 1;
			}
			
			glBegin(GL_POLYGON);
			glColor3f(0.9f, 0.8f, 0.8f);
			glVertex3f(x*(a[0] - 3)+wsp_x, a[1] + 15+wsp_y, y*(a[2] - 3)+wsp_z);
			glVertex3f(x*(a[0]-8)+wsp_x, a[1] + 20+wsp_y, y*(a[2]-8)+wsp_z);
			glColor3f(0.6f, 0.4f, 0.5f);
			glVertex3f(x*(b[0]-8)+wsp_x, b[1] + 20+wsp_y, y*(b[2] - 8)+wsp_z);
			glVertex3f(x*(b[0]-3)+wsp_x, b[1] + 15+wsp_y, y*(b[2]-3)+wsp_z);
			glEnd();
			x = -1;
		}

					glShadeModel(GL_SMOOTH);
					glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
					glBegin(GL_POLYGON);
					glColor3f(0.8f, 0.8f, 0.6f);
					glVertex3f(-a[0]+3+wsp_x, a[1] + 15+wsp_y, -a[2]+3+wsp_z);
					glVertex3f(-a[0] + 8+wsp_x, a[1] + 20+wsp_y, -a[2] + 8+wsp_z);
					glColor3f(0.7f, 0.4f, 0.5f);
					glVertex3f(-a[0] + 8+wsp_x, a[1] + 20+wsp_y, a[2] - 8+wsp_z);
					glVertex3f(-a[0]+3+wsp_x, a[1] + 15+wsp_y, a[2]-3+wsp_z);
					glEnd();

					glShadeModel(GL_SMOOTH);
					glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
					glBegin(GL_POLYGON);
					glColor3f(0.8f, 0.8f, 0.6f);
					glVertex3f(a[0]-3+wsp_x, a[1] + 15+wsp_y, -a[2]+3+wsp_z);
					glVertex3f(a[0] - 8+wsp_x, a[1] + 20+wsp_y, -a[2] + 8+wsp_z);
					glColor3f(0.7f, 0.4f, 0.5f);
					glVertex3f(a[0] - 8+wsp_x, a[1] + 20+wsp_y, a[2] - 8+wsp_z);
					glVertex3f(a[0]-3+wsp_x, a[1] + 15+wsp_y, a[2]-3+wsp_z);
					glEnd();

				
					glBegin(GL_POLYGON);
					glColor3f(0.8f, 0.9f, 0.9f);
					glVertex3f(-b[0]+3+wsp_x, b[1] + 15+wsp_y, -b[2]+3+wsp_z);
					glVertex3f(-b[0] + 8+wsp_x, b[1] + 20+wsp_y, -b[2] + 8+wsp_z);
					glColor3f(0.7f, 0.5f, 0.7);
					glVertex3f(b[0] - 8+wsp_x, b[1] + 20+wsp_y, -b[2] + 8+wsp_z);
					glVertex3f(b[0]-3+wsp_x, b[1] + 15+wsp_y, -b[2]+3+wsp_z);
					glEnd();


				
					glBegin(GL_POLYGON);
					glColor3f(0.8f, 0.9f, 0.9f);
					glVertex3f(b[0]-3+wsp_x, b[1] + 15+wsp_y, b[2]-3+wsp_z);
					glVertex3f(b[0] - 8+wsp_x, b[1] + 20+wsp_y, b[2] - 8+wsp_z);
					glColor3f(0.7f, 0.5f, 0.7);
					glVertex3f(-b[0] + 8+wsp_x, b[1] + 20+wsp_y, b[2] - 8+wsp_z);
					glVertex3f(-b[0]+3+wsp_x, b[1] + 15+wsp_y, b[2]-3+wsp_z);
					glEnd();
		
					
		glBegin(GL_POLYGON);
		glColor3f(0.3f, 0.3f, 0.7f);
		glVertex3f(a[0] - 8+wsp_x, a[1] + 20+wsp_y, a[2] - 8+wsp_z);
		glVertex3f(b[0] - 8+wsp_x, b[1] + 20+wsp_y, b[2] - 8+wsp_z);
		glVertex3f(-b[0] + 8+wsp_x, b[1] + 20+wsp_y, b[2] - 8+wsp_z);
		glVertex3f(-a[0] + 8+wsp_x, a[1] + 20+wsp_y, a[2] - 8+wsp_z);
		glColor3f(0.8f, 0.7f, 0.9f);
		glVertex3f(-a[0] + 8+wsp_x, a[1] + 20+wsp_y, -a[2] + 8+wsp_z);
		glVertex3f(-b[0] + 8+wsp_x, b[1] + 20+wsp_y, -b[2] + 8+wsp_z);
		glVertex3f(b[0] - 8+wsp_x, b[1] + 20+wsp_y, -b[2] + 8+wsp_z);
		glVertex3f(a[0] - 8+wsp_x, a[1] + 20+wsp_y, -a[2] + 8+wsp_z);

		

		
		glEnd();

	}
}

	ostr()
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		{
			GLfloat a[3] = {0.f,0.f,0.f};
			GLfloat b[3] = { 10.f,0.f,0.f };
			GLfloat c[3] = { 10.f,0.f,10.f };
			GLfloat d[3] = { 0.f,0.f,10.f };
			GLfloat h[3] = { 5.f,10.f,5.f };
			GLfloat sa[3] = { 0.0f,0.0f,0.0f };

			glColor3f(1.0f, 0.f, 0.f);
			glBegin(GL_POLYGON);
			glVertex3fv(a);
			glVertex3fv(b);
			glVertex3fv(c);
			glVertex3fv(d);
			glEnd();

			glColor3f(0.f, 1.f, 0.f);
			glBegin(GL_POLYGON);
			glVertex3fv(a);
			glVertex3fv(b);
			glVertex3fv(h);
			glEnd();


			glColor3f(0.f, 1.f, 0.f);
			glBegin(GL_POLYGON);
			glVertex3fv(c);
			glVertex3fv(d);
			glVertex3fv(h);
			glEnd();

			glColor3f(0.f, 0.f, 1.f);
			glBegin(GL_POLYGON);
			glVertex3fv(a);
			glVertex3fv(d);
			glVertex3fv(h);
			glEnd();

			glColor3f(0.f, 0.f, 1.f);
			glBegin(GL_POLYGON);
			glVertex3fv(b);
			glVertex3fv(c);
			glVertex3fv(h);
			glEnd();
		}
	}

	Zadanie5()
	{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	{
		// Parametry wierzcholkow

		GLfloat sa[3] = { 0.0f,0.0f,0.0f };
		GLfloat sb[3] = { 10.0f,0.0f,0.0f };
		GLfloat sc[3] = { 10.0f,10.0f,0.0f };
		GLfloat sd[3] = { 0.0f,10.0f,0.0f };
		GLfloat se[3] = { 0.0f,0.0f,-10.0f };
		GLfloat sf[3] = { 10.0f,0.0f,-10.0f };
		GLfloat sg[3] = { 10.0f,10.0f,-10.0f };
		GLfloat sh[3] = { 0.0f,10.0f,-10.0f };


		// Sciany skladowe
		glColor3f(1.0f, 0.0f, 0.0f);
		glBegin(GL_POLYGON);
		glVertex3fv(sa);
		glVertex3fv(sb);
		glVertex3fv(sc);
		glVertex3fv(sd);
		glEnd();

		glColor3f(0.0f, 1.0f, 0.0f);
		glBegin(GL_POLYGON);
		glVertex3fv(sb);
		glVertex3fv(sf);
		glVertex3fv(sg);
		glVertex3fv(sc);
		glEnd();

		glColor3f(0.0f, 0.0f, 1.0f);
		glBegin(GL_POLYGON);
		glVertex3fv(sf);
		glVertex3fv(se);
		glVertex3fv(sh);
		glVertex3fv(sg);
		glEnd();

		glColor3f(1.0f, 1.0f, 0.0f);
		glBegin(GL_POLYGON);
		glVertex3fv(se);
		glVertex3fv(sa);
		glVertex3fv(sd);
		glVertex3fv(sh);
		glEnd();

	/*	glColor3f(0.0f, 1.0f, 1.0f);
		glBegin(GL_POLYGON);
		glVertex3fv(sd);
		glVertex3fv(sc);
		glVertex3fv(sg);
		glVertex3fv(sh);
		glEnd();*/

		glColor3f(1.0f, 0.0f, 1.0f);
		glBegin(GL_POLYGON);
		glVertex3fv(sa);
		glVertex3fv(sb);
		glVertex3fv(sf);
		glVertex3fv(se);
		glEnd();
	}
}
	int angle;
	void Zadanie6(void)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		{

			GLfloat sa[3] = { 0.0f,0.0f,0.0f };
			GLfloat sb[3] = { 10.0f,0.0f,0.0f };
			GLfloat sc[3] = { 10.0f,10.0f,0.0f };
			GLfloat se[3] = { 0.0f,0.0f,-10.0f };
			GLfloat sf[3] = { 10.0f,0.0f,-10.0f };
			GLfloat sg[3] = { 10.0f,10.0f,-10.0f };
			GLfloat sd[3] = { 0.0f,10.0f,0.0f };
			GLfloat sh[3] = { 0.0f,10.0f,-10.0f };
			GLfloat d[3] = { 0.0f,10.0f,0.0f };
			GLfloat h[3] = { 0.0f,10.0f,-10.0f };

			if (angle == 4)
			{
				angle = 0;
			}

			if (angle == 0)
			{
				d[0] = 0.0f;
				d[1] = 10.0f;
				d[2] = 0.0f;

				h[0] = 0.0f;
				h[1] = 10.0f;
				h[2] = -10.0f;
			}

			else if (angle == 1)
			{
				d[0] = 10.0f - 5 * sqrt(3);
				d[1] = 15.0f;
				d[2] = 0.0f;

				h[0] = 10.0f - 5 * sqrt(3);
				h[1] = 15.0f;
				h[2] = -10.0f;
			}

			else if (angle == 2)
			{
				d[0] = 5.0f;
				d[1] = 10.0f + 5.f*sqrt(3);
				d[2] = 0.0f;

				h[0] = 5.0f;
				h[1] = 10.0f + 5.f*sqrt(3);
				h[2] = -10.0f;
			}

			else if (angle == 3)
			{
				d[0] = 10.0f;
				d[1] = 20.0f;
				d[2] = 0.0f;

				h[0] = 10.0f;
				h[1] = 20.0f;
				h[2] = -10.0f;
			}

			glColor3f(0.0f, 1.0f, 1.0f);
			glBegin(GL_POLYGON);
			glVertex3fv(d);
			glVertex3fv(sc);
			glVertex3fv(sg);
			glVertex3fv(h);
			glEnd();

			glColor3f(1.0f, 0.0f, 0.0f);
			glBegin(GL_POLYGON);
			glVertex3fv(sa);
			glVertex3fv(sb);
			glVertex3fv(sc);
			glVertex3fv(sd);
			glEnd();

			glColor3f(0.0f, 1.0f, 0.0f);
			glBegin(GL_POLYGON);
			glVertex3fv(sb);
			glVertex3fv(sf);
			glVertex3fv(sg);
			glVertex3fv(sc);
			glEnd();

			glColor3f(0.0f, 0.0f, 1.0f);
			glBegin(GL_POLYGON);
			glVertex3fv(sf);
			glVertex3fv(se);
			glVertex3fv(sh);
			glVertex3fv(sg);
			glEnd();

			glColor3f(1.0f, 1.0f, 0.0f);
			glBegin(GL_POLYGON);
			glVertex3fv(se);
			glVertex3fv(sa);
			glVertex3fv(sd);
			glVertex3fv(sh);
			glEnd();

			glColor3f(1.0f, 0.0f, 1.0f);
			glBegin(GL_POLYGON);
			glVertex3fv(sa);
			glVertex3fv(sb);
			glVertex3fv(sf);
			glVertex3fv(se);
			glEnd();
		}
	}

	void zadstozek()
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		{
			double angle, x, y;

			glColor3f(0.0f, 0.6f, 0.0f);
			glBegin(GL_TRIANGLE_STRIP);
			for (angle = 0; angle <= 2 * GL_PI; angle += GL_PI / 8.0)
			{
				x = 10 * sin(angle);
				y = 10 * cos(angle);
				
					
					glVertex3f(0.0f, 0.0f, 30.0f);
					glVertex3f(x , y , 0);
					
				
			}
			glEnd();

			glColor3f(1.0f, 0.0f, 0.0f);
			glBegin(GL_TRIANGLE_STRIP);
			for (angle = 0; angle <= 2 * GL_PI; angle += GL_PI / 8.0)
			{
				x = 10 * sin(angle);
				y = 10 * cos(angle);

				glVertex3f(0.0f, 0.0f, 0.0f);
				glVertex3f(x, y, 0);
				

			}
			glEnd();
		}
	}

	void zadwalec()
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		{
			double angle, x, y;

			glColor3f(0.0f, 0.6f, 0.0f);
			glBegin(GL_TRIANGLE_STRIP);
			for (angle = 0; angle <= 2 * GL_PI; angle += GL_PI / 8.0)
			{
				x = 10 * sin(angle);
				y = 10 * cos(angle);


				glVertex3f(0.0f, 0.0f, 0.0f);
				glVertex3f(x, y, 0);


			}
			glEnd();

			glColor3f(1.0f, 0.0f, 0.0f);
			glBegin(GL_TRIANGLE_STRIP);
			for (angle = 0; angle <= 2 * GL_PI; angle += GL_PI / 8.0)
			{
				x = 10 * sin(angle);
				y = 10 * cos(angle);

				glVertex3f(0.0f, 0.0f,20.0f);
				glVertex3f(x, y,20.0f);


			}
			glEnd();

			glColor3f(0.0f, 0.0f, 1.0f);
			glBegin(GL_TRIANGLE_STRIP);
			for (angle = 0; angle <= 2 * GL_PI; angle += GL_PI / 8.0)
			{
				x = 10 * sin(angle);
				y = 10 * cos(angle);

				glVertex3f(x , y , 0.f);
				glVertex3f(x , y , 20.0f);

			}
			glEnd();
		}
	}

	void walec_opt()
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		{
			double angle, x, y;
			for (angle = 0; angle <= 2 * GL_PI; angle += GL_PI / 8.0)
			{
				x = 10 * sin(angle);
				y = 10 * cos(angle);
				glColor3f(0.0f, 0.6f, 0.0f);
				glBegin(GL_TRIANGLE_STRIP);
					glVertex3f(0.f, 0.f, 0.f);
					glVertex3f(x, y, 0.f);
					glEnd();
			}
		}
	}

	void most()
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		{
			double angle, x, y;
			// Tworzenie przedniej sciany z wolnym miejscem na "kontener" walca
			glColor3f(0.0f, 0.5f, 0.0f);   // Lewa
			glBegin(GL_TRIANGLE_STRIP);
			glVertex3f(0.0f, 10.0f, 0.0f);   
			glVertex3f(0.0f, 30.0f, 0.0f); 
			glVertex3f(20.0f, 10.0f, 0.0f);
			glVertex3f(20.0f, 30.0f, 0.0f); 
			glEnd();

			glColor3f(0.0f, 0.5f, 0.0f);  // Prawa
			glBegin(GL_TRIANGLE_STRIP);
			glVertex3f(40.0f, 10.0f, 0.0f); 
			glVertex3f(40.0f, 30.0f, 0.0f); 
			glVertex3f(60.0f, 10.0f, 0.0f); 
			glVertex3f(60.0f, 30.0f, 0.0f); 
			glEnd();

			glColor3f(0.0f, 0.5f, 0.0f);  // Góra
			glBegin(GL_TRIANGLE_STRIP);
			glVertex3f(20.0f, 30.0f, 0.0f); 
			glVertex3f(20.0f, 20.0f, 0.0f);
			glVertex3f(40.0f, 30.0f, 0.0f); 
			glVertex3f(40.0f, 20.0f, 0.0f); 
			glEnd();
			// Zaprogramowanie walca
			glColor3f(0.0f, 0.6f, 0.0f);  // walec
			glBegin(GL_TRIANGLE_STRIP);
			for (angle = 0; angle <= 2 * GL_PI; angle += GL_PI / 50.0)
			{
				x = 10 * sin(angle);
				y = 10 * cos(angle);
				//Ograniczenie pola rysowania do jednej æwiartki uk³adu wspó³rzednych
				if (angle < GL_PI && angle < GL_PI / 2.0f)
				{
					//Rysowanie trójk¹tów w pêtli
					glVertex3f(x + 30, y + 10, 0);
					glVertex3f(40.0f, 20.0f, 0.0f);
				}
			}
			glEnd();

			glColor3f(0.0f, 0.6f, 0.0f);  
			glBegin(GL_TRIANGLE_STRIP);
			for (angle = 0; angle <= 2 * GL_PI; angle += GL_PI / 50.0)
			{
				x = 10 * sin(angle);
				y = 10 * cos(angle);
				//Ograniczenie pola rysowania do jednej æwiartki uk³adu wspó³rzednych
				if (angle < 2 * GL_PI && angle > 3 * GL_PI / 2.0f)
				{
					//Rysowanie trójk¹tów w pêtli
					glVertex3f(x + 30, y + 10, 0);
					glVertex3f(20.0f, 20.0f, 0.0f);
				}
			}
			glEnd();

			// Tworzenie tylnej sciany z wolnym miejscem na "kontener" walca
			glColor3f(0.0f, 0.5f, 0.0f);   // Lewa
			glBegin(GL_TRIANGLE_STRIP);
			glVertex3f(0.0f, 10.0f, 20.0f);
			glVertex3f(0.0f, 30.0f, 20.0f); 
			glVertex3f(20.0f, 10.0f, 20.0f);
			glVertex3f(20.0f, 30.0f, 20.0f); 
			glEnd();

			glColor3f(0.0f, 0.5f, 0.0f);  // Prawa
			glBegin(GL_TRIANGLE_STRIP);
			glVertex3f(40.0f, 10.0f, 20.0f);
			glVertex3f(40.0f, 30.0f, 20.0f); 
			glVertex3f(60.0f, 10.0f, 20.0f);
			glVertex3f(60.0f, 30.0f, 20.0f);
			glEnd();

			glColor3f(0.0f, 0.5f, 0.0f);  // Góra
			glBegin(GL_TRIANGLE_STRIP);
			glVertex3f(20.0f, 30.0f, 20.0f); 
			glVertex3f(20.0f, 20.0f, 20.0f); 
			glVertex3f(40.0f, 30.0f, 20.0f);
			glVertex3f(40.0f, 20.0f, 20.0f); 
			glEnd();

			glColor3f(0.0f, 0.7f, 0.0f);  // walec
			glBegin(GL_TRIANGLE_STRIP);
			for (angle = 0; angle <= 2 * GL_PI; angle += GL_PI / 50.0)
			{
				x = 10 * sin(angle);
				y = 10 * cos(angle);
				//Ograniczenie pola rysowania do jednej æwiartki uk³adu wspó³rzednych
				if (angle < GL_PI && angle < GL_PI / 2.0f)
				{
					//Rysowanie trójk¹tów w pêtli
					glVertex3f(x + 30, y + 10, 20);
					glVertex3f(40.0f, 20.0f, 20.0f);
				}
			}
			glEnd();

			glColor3f(0.0f, 0.7f, 0.0f);  // walec
			glBegin(GL_TRIANGLE_STRIP);
			for (angle = 0; angle <= 2 * GL_PI; angle += GL_PI / 50.0)
			{
				x = 10 * sin(angle);
				y = 10 * cos(angle);
				//Ograniczenie pola rysowania do jednej æwiartki uk³adu wspó³rzednych
				if (angle < 2 * GL_PI && angle > 3 * GL_PI / 2.0f)
				{
					//Rysowanie trójk¹tów w pêtli
					glVertex3f(x + 30, y + 10, 20);
					glVertex3f(20.0f, 20.0f, 20.0f);
				}
			}
			glEnd();

			//Mniejszy prostopad³oscian "kontener" w którym znajduje siê walec
			glColor3f(0.0f, 0.7f, 0.0f); 
			glBegin(GL_TRIANGLE_STRIP);
			glVertex3f(20.0f, 20.0f, 0.0f);
			glVertex3f(20.0f, 20.0f, 20.0f);
			glVertex3f(40.0f, 20.0f, 0.0f);
			glVertex3f(40.0f, 20.0f, 20.0f);
			glEnd();

			
			glColor3f(0.0f, 0.7f, 0.0f);
			glBegin(GL_TRIANGLE_STRIP);
			glVertex3f(20.0f, 10.0f, 0.0f);
			glVertex3f(20.0f, 10.0f, 20.0f);
			glVertex3f(20.0f, 20.0f, 0.0f);
			glVertex3f(20.0f, 20.0f, 20.0f);
			glEnd();

			
			glColor3f(0.0f, 0.7f, 0.0f);
			glBegin(GL_TRIANGLE_STRIP);
			glVertex3f(40.0f, 10.0f, 0.0f);
			glVertex3f(40.0f, 10.0f, 20.0f);
			glVertex3f(40.0f, 20.0f, 0.0f);
			glVertex3f(40.0f, 20.0f, 20.0f);
			glEnd();

			
			glColor3f(0.0f,0.5f, 0.0f);
			glBegin(GL_TRIANGLE_STRIP);
			glVertex3f(0.0f, 30.0f, 0.0f);
			glVertex3f(0.0f, 30.0f, 20.0f);
			glVertex3f(60.0f, 30.0f, 0.0f);
			glVertex3f(60.0f, 30.0f, 20.0f);
			glEnd();

			
			glColor3f(0.0f, 0.5f, 0.0f);
			glBegin(GL_TRIANGLE_STRIP);
			glVertex3f(0.0f, 10.0f, 0.0f);
			glVertex3f(0.0f, 10.0f, 20.0f);
			glVertex3f(0.0f, 30.0f, 0.0f);
			glVertex3f(0.0f, 30.0f, 20.0f);
			glEnd();

			
			glColor3f(0.0f, 0.5f, 0.0f);
			glBegin(GL_TRIANGLE_STRIP);
			glVertex3f(60.0f, 10.0f, 0.0f);
			glVertex3f(60.0f, 10.0f, 20.0f);
			glVertex3f(60.0f, 30.0f, 0.0f);
			glVertex3f(60.0f, 30.0f, 20.0f);
			glEnd();

			glColor3f(0.0f, 0.9f, 0.0f);  
			glBegin(GL_TRIANGLE_STRIP);
			for (angle = 0; angle <= 2 * GL_PI; angle += GL_PI / 190.0)
			{
				x = 10 * sin(angle);
				y = 10 * cos(angle);
				if (angle < 2 * GL_PI && angle > 3 * GL_PI / 2.0f)
				{
					glVertex3f(x+30, y+10, 0.f);
					glVertex3f(x+30, y+10, 20.0f);
					//Rysowanie po³¹czenia miedzy przedmi¹ a tyln¹ scian¹ walca
				}
			}
			glEnd();

			glColor3f(0.0f, 0.9f, 0.0f); 
			glBegin(GL_TRIANGLE_STRIP);
			for (angle = 0; angle <= 2 * GL_PI; angle += GL_PI / 190.0)
			{
				x = 10 * sin(angle);
				y = 10 * cos(angle);
				if (angle < GL_PI && angle < GL_PI / 2.0f)
				{
					glVertex3f(x + 30, y + 10, 0.f);
					glVertex3f(x + 30, y + 10, 20.0f);
					//Rysowanie po³¹czenia miedzy przedmi¹ a tyln¹ scian¹ walca
				}
			}
			glEnd();
			

		}
	}
	
	void zadwalec2()
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		{
			double x, y, alpha;
			glColor3f(1, 0.0, 0);
			glBegin(GL_TRIANGLE_FAN);
			glVertex3d(0, 0, 0);
			for (alpha = 0; alpha <= 2 * GL_PI; alpha += GL_PI / 8.0)
			{
				x = 10 * sin(alpha);
				y = 10 * cos(alpha);
				
				glVertex3d(x, y, 0);
				
				
				
			}
			glEnd();

			glColor3f(0.0, 0.0, 1);
			glBegin(GL_QUAD_STRIP);
			for (alpha = 0.0; alpha <= 2 * GL_PI; alpha += GL_PI / 8.0)
			{
				x = 10*sin(alpha);
				y = 10* cos(alpha);
				glVertex3f(x, y, 0);
				glVertex3f(x, y, 20);
			}
			glEnd();

			glColor3f(0.0, 1.0, 0);
			glBegin(GL_TRIANGLE_FAN);
			glVertex3d(0, 0, 20);
			for (alpha = 0; alpha <= 2 * GL_PI; alpha += GL_PI / 8.0)
			{
				x = 10 * sin(alpha);
				y = 10 * cos(alpha);
			
				glVertex3d(x, y, 20);
				
				
				
			}
			glEnd();
		}
	}

void zadstozek2()
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		{
			double x, y, alpha;
			glColor3f(1, 0.0, 0);
			glBegin(GL_TRIANGLE_FAN);
			glVertex3d(0, 0, 0);
			for (alpha = 0; alpha <= 2 * GL_PI; alpha += GL_PI / 8.0)
			{
				x = 10 * sin(alpha);
				y = 10 * cos(alpha);
				glVertex3d(x, y, 0);

			}
			glEnd();
			glColor3f(0, 1.0, 0);
			glBegin(GL_TRIANGLE_FAN);
			glVertex3d(0, 0, 20);
			for (alpha = 0; alpha <= 2 * GL_PI; alpha += GL_PI / 8.0)
			{
				x = 10 * sin(alpha);
				y = 10 * cos(alpha);
				glVertex3d(x, y,0);

			}
			glEnd();
		}
	}

void cegla(GLfloat x, GLfloat y, GLfloat z)
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	{
		GLfloat q = 15,w=30,e=7.5;
		glColor3f(0.8f, 0.0f, 0.0f);
		glBegin(GL_TRIANGLE_STRIP);
		glVertex3d(x, y, z);
		glVertex3d(x, y + q, z);
		glVertex3d(x + w, y, z);
		glVertex3d(x + w, y +q, z);
		glEnd();

		glColor3f(0.7f, 0.0f, 0.0f);
		glBegin(GL_TRIANGLE_STRIP);
		glVertex3d(x, y, z);
		glVertex3d(x, y + q, z);
		glVertex3d(x, y, z - e);
		glVertex3d(x, y + q, z - e);
		glEnd();

		glBegin(GL_TRIANGLE_STRIP);
		glVertex3d(x, y + q, z);
		glVertex3d(x + w, y + q, z);
		glVertex3d(x, y + q, z - e);
		glVertex3d(x + w, y + q, z - e);
		glEnd();

		glBegin(GL_TRIANGLE_STRIP);
		glVertex3d(x, y, z - e);
		glVertex3d(x, y + q, z - e);
		glVertex3d(x + w, y, z - e);
		glVertex3d(x + w, y + q, z - e);
		glEnd();

		glBegin(GL_TRIANGLE_STRIP);
		glVertex3d(x + w, y, z);
		glVertex3d(x + w, y + q, z);
		glVertex3d(x + w, y, z - e);
		glVertex3d(x + w, y + q, z - e);
		glEnd();

		glBegin(GL_TRIANGLE_STRIP);
		glVertex3d(x, y, z);
		glVertex3d(x + w, y, z);
		glVertex3d(x, y, z - e);
		glVertex3d(x + w, y, z - e);
		glEnd();
	}
}

void mur(int ilec, int ilew)
{
	int i, j;
	GLfloat start[] = { 0.0f, 0.0f, 0.0f };   // Wsp startowe

	if (ilec < 1 || ilew < 1)    // Warunek sprawdzaj¹cy poprawne podanie danych
	{
		return;
	}
	 
	for (i = 0; i < ilew; i++)    // Pêtla odpowiadajaca za rysowanie kolejnych warstw	
	{
		for (j = 0; j < ilec + 1; j++)  // Pêtla odpowiadaj¹ca za rysowanie kolejnych cegiel w warstwie
		{
			if (j == ilec && i % 2 != 0)   
			{
				break;
			}

			cegla(start[0], start[1], start[2]);    // Rysowanie cegiel

			start[0] += 31.0f;   // Przeniesienie dla kazdej kolejnej celgy aby byla miedzy nimi przerwa w osi x
		}

		start[1] += 16.0f;  // Przeniesienie dla kazdej kolejnej cegly aby by³a miêdzy nimi przerwa w osi y

		if (i % 2 == 0)
		{
			start[0] = 16.0f;  // Rysowanie na przemian cegiel o roznym polozeniu osi x
		}
		else
		{
			start[0] = 0.0f;
		}
	}
}


void walec(double r, double h)
{
	double x, y, alpha, PI = 3.14;
	glBegin(GL_TRIANGLE_FAN);
	glColor3d(0.8, 0.0, 0);
	glVertex3d(0, 0, 0);
	for (alpha = 0; alpha <= 2 * PI; alpha += PI / 8.0)
	{
		x = r*sin(alpha);
		y = r*cos(alpha);
		glVertex3d(x, y, 0);
	}
	glEnd();

	glBegin(GL_QUAD_STRIP);
	for (alpha = 0.0; alpha <= 2 * PI; alpha += PI / 8.0)
	{
		x = r*sin(alpha);
		y = r* cos(alpha);
		glVertex3d(x, y, 0);
		glVertex3d(x, y, h);
	}
	glEnd();

	glBegin(GL_TRIANGLE_FAN);
	glVertex3d(0, 0, h);
	for (alpha = 0; alpha >= -2 * PI; alpha -= PI / 8.0)
	{
		x = r*sin(alpha);
		y = r*cos(alpha);
		glVertex3d(x, y, h);
	}
	glEnd();
}
void ramie(double r1, double r2, double h, double d)
{
	double PI = 3.14, alpha, x, y;
	glBegin(GL_TRIANGLE_FAN);
		glColor3d(0.8, 0.0, 0);
		glVertex3d(0, 0, 0);
		for (alpha = PI; alpha <= 2 * PI; alpha += PI / 8.0)
		{
			x = r1*sin(alpha);
			y = r1*cos(alpha);
			glVertex3d(x, y, 0);
		}
	glEnd();

	glBegin(GL_QUAD_STRIP);
		for (alpha = 0; alpha >= -PI; alpha -= PI / 8.0)
		{
			x = r1*sin(alpha);
			y = r1* cos(alpha);
			glVertex3d(x, y, h);
			glVertex3d(x, y, 0);
		}
	glEnd();

	glBegin(GL_TRIANGLE_FAN);
		glVertex3d(0, 0, h);
		for (alpha = 0; alpha >= -PI; alpha -= PI / 8.0)
		{
			x = r1*sin(alpha);
			y = r1*cos(alpha);
			glVertex3d(x, y, h);
		}
	glEnd();

	glBegin(GL_TRIANGLE_FAN);
		glColor3d(0.8, 0.0, 0);
		//glVertex3d(d,r2,0);
		//glVertex3d(d, r2, h);
		for (alpha = 0; alpha <= PI; alpha += PI / 8.0)
		{
			x = d + r2 * sin(alpha);
			y = d + r2 * cos(alpha);
			glVertex3d(x, y, 0);
		}
	glEnd();

	glBegin(GL_QUAD_STRIP);
		//glVertex3d(d, r2, 0);
		for (alpha = 0; alpha <= PI; alpha += PI / 8.0)
		{
			x = d+ r2*sin(alpha);
			y = d +r2* cos(alpha);
			glVertex3d(x, y, h);
			glVertex3d(x, y, 0);
		}
	glEnd();

	glBegin(GL_TRIANGLE_FAN);
		//glVertex3d(d, r2, h);
		for (alpha = 0; alpha <= PI; alpha += PI / 8.0)
		{
			x = d +r2*sin(alpha);
			y = d +r2*cos(alpha);
			glVertex3d(x, y, h);
		}
	glEnd();
}
// Called to draw scene
void RenderScene(void)
	{
	//float normal[3];	// Storeage for calculated surface normal

	// Clear the window with current clearing color
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Save the matrix state and do the rotations
	glPushMatrix();
	glRotatef(xRot, 1.0f, 0.0f, 0.0f);
	glRotatef(yRot, 0.0f, 1.0f, 0.0f);

	/////////////////////////////////////////////////////////////////
	// MIEJSCE NA KOD OPENGL DO TWORZENIA WLASNYCH SCEN:		   //
	/////////////////////////////////////////////////////////////////
	//szescian();
	
	//Sposób na odróŸnienie "przedniej" i "tylniej" œciany wielok¹ta:
	glPolygonMode(GL_BACK,GL_LINE);
	//walec(40, 40);



	glShadeModel(GL_SMOOTH);
	glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);

	//szescian();
	//Zadanie1();
	//Zadanie2();
	//Zadanie3();
	//Zadanie4();
	//Zadanie5();
	//Zadanie6();
	//zadstozek2();
	//mur(5, 4);
	//walec_opt();
	//ostr();
	foots(0, 0, 0,0);
	legs(0,0,0,0);
	body(0,0,0);
	head(0,0,0);
	gadgets(0, 0, 0);
	//most();

	//zad5();

	
		
	//zad8(4,15);
	
	




	//glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);

	//Wyrysowanie prostokata:
	//glRectd(-10.0,-10.0,20.0,20.0);
		
	/////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);

	// Flush drawing commands
	glFlush();
	}


// Select the pixel format for a given device context
void SetDCPixelFormat(HDC hDC)
	{
	int nPixelFormat;

	static PIXELFORMATDESCRIPTOR pfd = {
		sizeof(PIXELFORMATDESCRIPTOR),  // Size of this structure
		1,                                                              // Version of this structure    
		PFD_DRAW_TO_WINDOW |                    // Draw to Window (not to bitmap)
		PFD_SUPPORT_OPENGL |					// Support OpenGL calls in window
		PFD_DOUBLEBUFFER,                       // Double buffered
		PFD_TYPE_RGBA,                          // RGBA Color mode
		24,                                     // Want 24bit color 
		0,0,0,0,0,0,                            // Not used to select mode
		0,0,                                    // Not used to select mode
		0,0,0,0,0,                              // Not used to select mode
		32,                                     // Size of depth buffer
		0,                                      // Not used to select mode
		0,                                      // Not used to select mode
		PFD_MAIN_PLANE,                         // Draw in main plane
		0,                                      // Not used to select mode
		0,0,0 };                                // Not used to select mode

	// Choose a pixel format that best matches that described in pfd
	nPixelFormat = ChoosePixelFormat(hDC, &pfd);

	// Set the pixel format for the device context
	SetPixelFormat(hDC, nPixelFormat, &pfd);
	}



// If necessary, creates a 3-3-2 palette for the device context listed.
HPALETTE GetOpenGLPalette(HDC hDC)
	{
	HPALETTE hRetPal = NULL;	// Handle to palette to be created
	PIXELFORMATDESCRIPTOR pfd;	// Pixel Format Descriptor
	LOGPALETTE *pPal;			// Pointer to memory for logical palette
	int nPixelFormat;			// Pixel format index
	int nColors;				// Number of entries in palette
	int i;						// Counting variable
	BYTE RedRange,GreenRange,BlueRange;
								// Range for each color entry (7,7,and 3)


	// Get the pixel format index and retrieve the pixel format description
	nPixelFormat = GetPixelFormat(hDC);
	DescribePixelFormat(hDC, nPixelFormat, sizeof(PIXELFORMATDESCRIPTOR), &pfd);

	// Does this pixel format require a palette?  If not, do not create a
	// palette and just return NULL
	if(!(pfd.dwFlags & PFD_NEED_PALETTE))
		return NULL;

	// Number of entries in palette.  8 bits yeilds 256 entries
	nColors = 1 << pfd.cColorBits;	

	// Allocate space for a logical palette structure plus all the palette entries
	pPal = (LOGPALETTE*)malloc(sizeof(LOGPALETTE) +nColors*sizeof(PALETTEENTRY));

	// Fill in palette header 
	pPal->palVersion = 0x300;		// Windows 3.0
	pPal->palNumEntries = nColors; // table size

	// Build mask of all 1's.  This creates a number represented by having
	// the low order x bits set, where x = pfd.cRedBits, pfd.cGreenBits, and
	// pfd.cBlueBits.  
	RedRange = (1 << pfd.cRedBits) -1;
	GreenRange = (1 << pfd.cGreenBits) - 1;
	BlueRange = (1 << pfd.cBlueBits) -1;

	// Loop through all the palette entries
	for(i = 0; i < nColors; i++)
		{
		// Fill in the 8-bit equivalents for each component
		pPal->palPalEntry[i].peRed = (i >> pfd.cRedShift) & RedRange;
		pPal->palPalEntry[i].peRed = (unsigned char)(
			(double) pPal->palPalEntry[i].peRed * 255.0 / RedRange);

		pPal->palPalEntry[i].peGreen = (i >> pfd.cGreenShift) & GreenRange;
		pPal->palPalEntry[i].peGreen = (unsigned char)(
			(double)pPal->palPalEntry[i].peGreen * 255.0 / GreenRange);

		pPal->palPalEntry[i].peBlue = (i >> pfd.cBlueShift) & BlueRange;
		pPal->palPalEntry[i].peBlue = (unsigned char)(
			(double)pPal->palPalEntry[i].peBlue * 255.0 / BlueRange);

		pPal->palPalEntry[i].peFlags = (unsigned char) NULL;
		}
		

	// Create the palette
	hRetPal = CreatePalette(pPal);

	// Go ahead and select and realize the palette for this device context
	SelectPalette(hDC,hRetPal,FALSE);
	RealizePalette(hDC);

	// Free the memory used for the logical palette structure
	free(pPal);

	// Return the handle to the new palette
	return hRetPal;
	}


// Entry point of all Windows programs
int APIENTRY WinMain(   HINSTANCE       hInst,
						HINSTANCE       hPrevInstance,
						LPSTR           lpCmdLine,
						int                     nCmdShow)
	{
	MSG                     msg;            // Windows message structure
	WNDCLASS        wc;                     // Windows class structure
	HWND            hWnd;           // Storeage for window handle

	hInstance = hInst;

	// Register Window style
	wc.style                        = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc          = (WNDPROC) WndProc;
	wc.cbClsExtra           = 0;
	wc.cbWndExtra           = 0;
	wc.hInstance            = hInstance;
	wc.hIcon                        = NULL;
	wc.hCursor                      = LoadCursor(NULL, IDC_ARROW);
	
	// No need for background brush for OpenGL window
	wc.hbrBackground        = NULL;         
	
	wc.lpszMenuName         = MAKEINTRESOURCE(IDR_MENU);
	wc.lpszClassName        = lpszAppName;

	// Register the window class
	if(RegisterClass(&wc) == 0)
		return FALSE;


	// Create the main application window
	hWnd = CreateWindow(
				lpszAppName,
				lpszAppName,
				
				// OpenGL requires WS_CLIPCHILDREN and WS_CLIPSIBLINGS
				WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS,
	
				// Window position and size
				50, 50,
				400, 400,
				NULL,
				NULL,
				hInstance,
				NULL);

	// If window was not created, quit
	if(hWnd == NULL)
		return FALSE;


	// Display the window
	ShowWindow(hWnd,SW_SHOW);
	UpdateWindow(hWnd);

	// Process application messages until the application closes
	while( GetMessage(&msg, NULL, 0, 0))
		{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
		}

	return msg.wParam;
	}




// Window procedure, handles all messages for this program
LRESULT CALLBACK WndProc(       HWND    hWnd,
							UINT    message,
							WPARAM  wParam,
							LPARAM  lParam)
	{
	static HGLRC hRC;               // Permenant Rendering context
	static HDC hDC;                 // Private GDI Device context

	switch (message)
		{
		// Window creation, setup for OpenGL
		case WM_CREATE:
			// Store the device context
			hDC = GetDC(hWnd);              

			// Select the pixel format
			SetDCPixelFormat(hDC);          

			// Create palette if needed
			hPalette = GetOpenGLPalette(hDC);

			// Create the rendering context and make it current
			hRC = wglCreateContext(hDC);
			wglMakeCurrent(hDC, hRC);
			SetupRC();
			glGenTextures(2, &texture[0]);                  // tworzy obiekt tekstury			
			
			// ³aduje pierwszy obraz tekstury:
			bitmapData = LoadBitmapFile("Bitmapy\\checker.bmp", &bitmapInfoHeader);
			
			glBindTexture(GL_TEXTURE_2D, texture[0]);       // aktywuje obiekt tekstury

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP );

			// tworzy obraz tekstury
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, bitmapInfoHeader.biWidth,
						 bitmapInfoHeader.biHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, bitmapData);
			
			if(bitmapData)
			free(bitmapData);

			// ³aduje drugi obraz tekstury:
			bitmapData = LoadBitmapFile("Bitmapy\\crate.bmp", &bitmapInfoHeader);
			glBindTexture(GL_TEXTURE_2D, texture[1]);       // aktywuje obiekt tekstury

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP );

			// tworzy obraz tekstury
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, bitmapInfoHeader.biWidth,
						 bitmapInfoHeader.biHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, bitmapData);
			
			if(bitmapData)
			free(bitmapData);

			// ustalenie sposobu mieszania tekstury z t³em
			glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,GL_MODULATE);
			break;

		// Window is being destroyed, cleanup
		case WM_DESTROY:
			// Deselect the current rendering context and delete it
			wglMakeCurrent(hDC,NULL);
			wglDeleteContext(hRC);

			// Delete the palette if it was created
			if(hPalette != NULL)
				DeleteObject(hPalette);

			// Tell the application to terminate after the window
			// is gone.
			PostQuitMessage(0);
			break;

		// Window is resized.
		case WM_SIZE:
			// Call our function which modifies the clipping
			// volume and viewport
			ChangeSize(LOWORD(lParam), HIWORD(lParam));
			break;


		// The painting function.  This message sent by Windows 
		// whenever the screen needs updating.
		case WM_PAINT:
			{
			// Call OpenGL drawing code
			RenderScene();

			SwapBuffers(hDC);

			// Validate the newly painted client area
			ValidateRect(hWnd,NULL);
			}
			break;

		// Windows is telling the application that it may modify
		// the system palette.  This message in essance asks the 
		// application for a new palette.
		case WM_QUERYNEWPALETTE:
			// If the palette was created.
			if(hPalette)
				{
				int nRet;

				// Selects the palette into the current device context
				SelectPalette(hDC, hPalette, FALSE);

				// Map entries from the currently selected palette to
				// the system palette.  The return value is the number 
				// of palette entries modified.
				nRet = RealizePalette(hDC);

				// Repaint, forces remap of palette in current window
				InvalidateRect(hWnd,NULL,FALSE);

				return nRet;
				}
			break;

	
		// This window may set the palette, even though it is not the 
		// currently active window.
		case WM_PALETTECHANGED:
			// Don't do anything if the palette does not exist, or if
			// this is the window that changed the palette.
			if((hPalette != NULL) && ((HWND)wParam != hWnd))
				{
				// Select the palette into the device context
				SelectPalette(hDC,hPalette,FALSE);

				// Map entries to system palette
				RealizePalette(hDC);
				
				// Remap the current colors to the newly realized palette
				UpdateColors(hDC);
				return 0;
				}
			break;

		// Key press, check for arrow keys to do cube rotation.
		case WM_KEYDOWN:
			{
			if (wParam == VK_TAB)
				angle++;
			if(wParam == VK_UP)
				xRot-= 5.0f;

			if(wParam == VK_DOWN)
				xRot += 5.0f;

			if(wParam == VK_LEFT)
				yRot -= 5.0f;

			if(wParam == VK_RIGHT)
				yRot += 5.0f;

			

			xRot = (const int)xRot % 360;
			yRot = (const int)yRot % 360;

			InvalidateRect(hWnd,NULL,FALSE);
			}
			break;

		// A menu command
			
		case WM_COMMAND:
			{
			switch(LOWORD(wParam))
				{
				// Exit the program
				case ID_FILE_EXIT:
					DestroyWindow(hWnd);
					break;

				// Display the about box
				case ID_HELP_ABOUT:
					DialogBox (hInstance,
						MAKEINTRESOURCE(IDD_DIALOG_ABOUT),
						hWnd,
						AboutDlgProc);
					break;
				}
			}
			break;


	default:   // Passes it on if unproccessed
	    return (DefWindowProc(hWnd, message, wParam, lParam));

	}

    return (0L);
	}




// Dialog procedure.
BOOL APIENTRY AboutDlgProc (HWND hDlg, UINT message, UINT wParam, LONG lParam)
	{
	
    switch (message)
	{
		// Initialize the dialog box
	    case WM_INITDIALOG:
			{
			int i;
			GLenum glError;

			// glGetString demo
			SetDlgItemText(hDlg,IDC_OPENGL_VENDOR,glGetString(GL_VENDOR));
			SetDlgItemText(hDlg,IDC_OPENGL_RENDERER,glGetString(GL_RENDERER));
			SetDlgItemText(hDlg,IDC_OPENGL_VERSION,glGetString(GL_VERSION));
			SetDlgItemText(hDlg,IDC_OPENGL_EXTENSIONS,glGetString(GL_EXTENSIONS));

			// gluGetString demo
			SetDlgItemText(hDlg,IDC_GLU_VERSION,gluGetString(GLU_VERSION));
			SetDlgItemText(hDlg,IDC_GLU_EXTENSIONS,gluGetString(GLU_EXTENSIONS));


			// Display any recent error messages
			i = 0;
			do {
				glError = glGetError();
				SetDlgItemText(hDlg,IDC_ERROR1+i,gluErrorString(glError));
				i++;
				}
			while(i < 6 && glError != GL_NO_ERROR);


			return (TRUE);
			}
			break;

		// Process command messages
	    case WM_COMMAND:      
			{
			// Validate and Make the changes
			if(LOWORD(wParam) == IDOK)
				EndDialog(hDlg,TRUE);
		    }
			break;

		// Closed from sysbox
		case WM_CLOSE:
			EndDialog(hDlg,TRUE);
			break;
		}

	return FALSE;
	}
