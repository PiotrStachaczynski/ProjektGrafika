#include "Drone.h"
#include <math.h>



Drone::Drone(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}


Drone::~Drone()
{
}

void Drone::draw()
{
	kadlub(0);
	ramiona(0, 0, 0);
	silnik(-2 * 2.8 - 19, 0, 15);//dó³ lewy
	rotor(-2 * 2.8 - 19, 10.2, 15);
	oslona(-24.6f, 10.2f, 15);

	silnik(2 * 2.8 + 8 + 29, 0, 15); //prawy dó³
	rotor(2 * 2.8 + 8 + 29, 10.2, 15);
	oslona(42.6, 10.2f, 15);

	silnik(2 * 2.8 + 8 + 29, 0, -35); //prawy góra
	rotor(2 * 2.8 + 8 + 29, 10.2, -35);
	oslona(42.6, 10.2f, -35);

	silnik(-2 * 2.8 - 19, 0, -35); //lewy góra
	rotor(-2 * 2.8 - 19, 10.2, -35);
	oslona(-24.6, 10.2f, -35);

	kamera(0, 0, -15);

	spoiler(30, 10, -10);
	nogi(10, 0, -10);//nogi na których l¹duje dron; xyz - œrodek spodu kad³ubu
}
void Drone::kadlub(float x)
{
	float y = 0, z = 0; //podstawa prostopadloscian
	glColor3f(0.5f, 0.f, 1.f);
	glBegin(GL_TRIANGLE_STRIP);
	glVertex3f(x + 20, y, z);
	glVertex3f(x, y, z);
	glVertex3f(x + 20, y, z - 20);
	glVertex3f(x, y, z - 20);
	glVertex3f(x + 20, y + 10, z - 20);
	glVertex3f(x, y + 10, z - 20);
	glVertex3f(x + 20, y + 10, z);
	glVertex3f(x, y + 10, z);
	glVertex3f(x + 20, y, z);
	glVertex3f(x, y, z);
	glEnd();
	//trojkaty
	//dol lewy
	glColor3f(1.f, 0.f, 0.f);
	glBegin(GL_TRIANGLE_STRIP);
	glVertex3f(x, y, z - 5);
	glVertex3f(x - 10, y, z - 5);
	glVertex3f(x, y, z);
	glVertex3f(x - 10, y + 10, z - 5);
	glVertex3f(x, y + 10, z);
	glVertex3f(x, y + 10, z - 5);
	glEnd();
	//gora lewy
	glBegin(GL_TRIANGLE_STRIP);
	glVertex3f(x, y, z - 15);
	glVertex3f(x - 10, y, z - 15);
	glVertex3f(x, y, z - 20);
	glVertex3f(x - 10, y + 10, z - 15);
	glVertex3f(x, y + 10, z - 20);
	glVertex3f(x, y + 10, z - 15);
	glEnd();
	//gora prawy
	glBegin(GL_TRIANGLE_STRIP);
	glVertex3f(x + 20, y, z - 15);
	glVertex3f(x + 30, y, z - 15);
	glVertex3f(x + 20, y, z - 20);
	glVertex3f(x + 30, y + 10, z - 15);
	glVertex3f(x + 20, y + 10, z - 20);
	glVertex3f(x + 20, y + 10, z - 15);
	glEnd();
	//dol prawy
	glBegin(GL_TRIANGLE_STRIP);
	glVertex3f(x + 20, y, z - 5);
	glVertex3f(x + 30, y, z - 5);
	glVertex3f(x + 20, y, z);
	glVertex3f(x + 30, y + 10, z - 5);
	glVertex3f(x + 20, y + 10, z);
	glVertex3f(x + 20, y + 10, z - 5);
	glEnd();

	//lewy i prawy 'dziub'
	glBegin(GL_TRIANGLE_STRIP); //lewy
	glColor3f(0.2f, 0.2f, 0.7f);
	glVertex3f(x, y, z - 5);
	glVertex3f(x, y, z - 15);
	glVertex3f(x - 10, y, z - 5);
	glVertex3f(x - 10, y, z - 15);
	glVertex3f(x - 10, y + 10, z - 5);
	glVertex3f(x - 10, y + 10, z - 15);
	glVertex3f(x, y + 10, z - 5);
	glVertex3f(x, y + 10, z - 15);
	glEnd();
	glBegin(GL_TRIANGLE_STRIP); //prawy
	glColor3f(0.2f, 0.2f, 0.7f);
	glVertex3f(x + 20, y, z - 5);
	glVertex3f(x + 20, y, z - 15);
	glVertex3f(x + 30, y, z - 5);
	glVertex3f(x + 30, y, z - 15);
	glVertex3f(x + 30, y + 10, z - 5);
	glVertex3f(x + 30, y + 10, z - 15);
	glVertex3f(x + 20, y + 10, z - 5);
	glVertex3f(x + 20, y + 10, z - 15);
	glEnd();

}

void Drone::ramiona(float x, float y, float z)
{
	glBegin(GL_QUAD_STRIP); //lewy góra
	glColor3f(0.7f, 0.7f, 0.7f);
	glVertex3f(x - 2.8, y + 3, z - 15 - 0.47*(sqrt(125) - 3) + 1);
	glVertex3f(x - 2 * 2.8 - 18, y + 3, z - 35);//
	glVertex3f(x - 3 * 2.8, y + 3, z - 15 - 0.47*(sqrt(125) - 3 * 3) + 1);
	glVertex3f(x - 2 * 2.8 - 20, y + 3, z - 35);//

	glVertex3f(x - 3 * 2.8, y + 6.5, z - 15 - 0.47*(sqrt(125) - 3 * 3) + 1);
	glVertex3f(x - 2 * 2.8 - 20, y + 6.5, z - 35);//

	glVertex3f(x - 2.8, y + 6.5, z - 15 - 0.47*(sqrt(125) - 3) + 1);
	glVertex3f(x - 2 * 2.8 - 18, y + 6.5, z - 35);//

	glVertex3f(x - 2.8, y + 3, z - 15 - 0.47*(sqrt(125) - 3) + 1);
	glVertex3f(x - 2 * 2.8 - 18, y + 3, z - 35);//
	glEnd();

	glBegin(GL_QUAD_STRIP); //prawy góra
	glColor3f(0.7f, 0.7f, 0.7f);
	glVertex3f(x + 2.8 + 20, y + 3, z - 15 - 0.47*(sqrt(125) - 3) + 1);
	glVertex3f(x + 2 * 2.8 + 8 + 28, y + 3, z - 35);//
	glVertex3f(x + 3 * 2.8 + 20, y + 3, z - 15 - 0.47*(sqrt(125) - 3 * 3) + 1);
	glVertex3f(x + 2 * 2.8 + 8 + 30, y + 3, z - 35);//

	glVertex3f(x + 3 * 2.8 + 20, y + 6.5, z - 15 - 0.47*(sqrt(125) - 3 * 3) + 1);
	glVertex3f(x + 2 * 2.8 + 8 + 30, y + 6.5, z - 35);//

	glVertex3f(x + 2.8 + 20, y + 6.5, z - 15 - 0.47*(sqrt(125) - 3) + 1);
	glVertex3f(x + 2 * 2.8 + 8 + 28, y + 6.5, z - 35);//

	glVertex3f(x + 2.8 + 20, y + 3, z - 15 - 0.47*(sqrt(125) - 3) + 1);
	glVertex3f(x + 2 * 2.8 + 8 + 28, y + 3, z - 35);//
	glEnd();

	glBegin(GL_QUAD_STRIP); //lewy dó³
	glColor3f(0.7f, 0.7f, 0.7f);
	glVertex3f(x - 2.8, y + 3, z + 0.47*(sqrt(125) - 3) - 6);
	glVertex3f(x - 2 * 2.8 - 18, y + 3, z + 15);//
	glVertex3f(x - 3 * 2.8, y + 3, z + 0.47*(sqrt(125) - 3 * 3) - 6);
	glVertex3f(x - 2 * 2.8 - 20, y + 3, z + 15);//

	glVertex3f(x - 3 * 2.8, y + 6.5, z + 0.47*(sqrt(125) - 3 * 3) - 6);
	glVertex3f(x - 2 * 2.8 - 20, y + 6.5, z + 15);//

	glVertex3f(x - 2.8, y + 6.5, z + 0.47*(sqrt(125) - 3) - 6);
	glVertex3f(x - 2 * 2.8 - 18, y + 6.5, z + 15);//

	glVertex3f(x - 2.8, y + 3, z + 0.47*(sqrt(125) - 3) - 6);
	glVertex3f(x - 2 * 2.8 - 18, y + 3, z + 15);//
	glEnd();

	glBegin(GL_QUAD_STRIP); //prawy dó³
	glColor3f(0.7f, 0.7f, 0.7f);
	glVertex3f(x + 2.8 + 20, y + 3, z + 0.47*(sqrt(125) - 3) - 6);
	glVertex3f(x + 2 * 2.8 + 8 + 28, y + 3, z + 15);//
	glVertex3f(x + 3 * 2.8 + 20, y + 3, z + 0.47*(sqrt(125) - 3 * 3) - 6);
	glVertex3f(x + 2 * 2.8 + 8 + 30, y + 3, z + 15);//

	glVertex3f(x + 3 * 2.8 + 20, y + 6.5, z + 0.47*(sqrt(125) - 3 * 3) - 6);
	glVertex3f(x + 2 * 2.8 + 8 + 30, y + 6.5, z + 15);//

	glVertex3f(x + 2.8 + 20, y + 6.5, z + 0.47*(sqrt(125) - 3) - 6);
	glVertex3f(x + 2 * 2.8 + 8 + 28, y + 6.5, z + 15);//

	glVertex3f(x + 2.8 + 20, y + 3, z + 0.47*(sqrt(125) - 3) - 6);
	glVertex3f(x + 2 * 2.8 + 8 + 28, y + 3, z + 15);//
	glEnd();
}
void Drone::silnik(float x, float y, float z)
{
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(1.f, 0.f, 0.4f);
	glVertex3f(x, y, z);
	for (float angle = 0; angle < 2 * GL_PI; angle += GL_PI / 8.f) //podstawa
	{
		glVertex3f(2 * sin(angle) + x, y, 2 * cos(angle) + z);
	}
	glEnd();

	glBegin(GL_TRIANGLE_STRIP);
	for (float angle = 0; angle < 2 * GL_PI; angle += GL_PI / 8.f) //³¹czenie-sciany
	{
		glVertex3f(2 * sin(angle) + x, y, 2 * cos(angle) + z);
		glVertex3f(2 * sin(angle) + x, y + 10, 2 * cos(angle) + z);
	}
	glEnd();
}
void Drone::rotor(float x, float y, float z)
{
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(0.f, 0, 0);
	glVertex3f(x, y + 3, z);
	for (float angle = 0.f; angle < 2 * GL_PI; angle += GL_PI / 8.f) //podstawa pod uchwyt na œmig³o
	{
		glVertex3f(2 * sin(angle) + x, y, 2 * cos(angle) + z);
	}
	glEnd();
	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(x, y + 4, z);
	for (float angle = 0.f; angle < 2 * GL_PI; angle += GL_PI / 8.f) //sto¿ek trzymaj¹cy od góry smiglo
	{
		glVertex3f(2 * sin(angle) + x, y + 2, 2 * cos(angle) + z);
	}
	glEnd();

	//lewy p³at œmig³a
	glBegin(GL_TRIANGLE_STRIP); //góra œmig³a
	glColor3f(0.4, 0.4, 0.8);
	glVertex3f(x, y + 2, z);
	glVertex3f(x - 3, y + 2, z - 3);
	glVertex3f(x - 3, y + 2, z + 3);
	glVertex3f(x - 15, y + 2, z - 3);
	glVertex3f(x - 15, y + 1.5, z + 3);
	glVertex3f(x - 15, y + 0.5, z - 3);
	glVertex3f(x - 15, y + 1, z + 3);
	glEnd();

	glBegin(GL_TRIANGLE_STRIP); //dó³ œmig³a
	glColor3f(0.7, 0.8, 0.4);
	glVertex3f(x - 15, y + 0.5, z - 3);
	glVertex3f(x - 15, y + 1, z + 3);
	glVertex3f(x - 3, y + 0, z - 3);
	glVertex3f(x - 3, y + 1, z + 3);
	glVertex3f(x, y + 2, z);
	glEnd();

	//przednia sciana œmiga³
	glBegin(GL_TRIANGLE_STRIP);
	glColor3f(0.1, 0.1, 0.1);
	glVertex3f(x, y + 2, z);
	glVertex3f(x - 3, y + 2, z + 3);
	glVertex3f(x - 3, y + 1, z + 3);
	glVertex3f(x - 15, y + 1.5, z + 3);
	glVertex3f(x - 15, y + 1, z + 3);
	glEnd();

	glBegin(GL_TRIANGLE_STRIP);
	glColor3f(0.8, 0.f, 0.4); //tylna œciana œmig³a
	glVertex3f(x, y + 2, z);
	glVertex3f(x - 3, y + 2, z - 3);
	glVertex3f(x - 3, y + 0, z - 3);
	glVertex3f(x - 15, y + 2, z - 3);
	glVertex3f(x - 15, y + 0.5, z - 3);
	glEnd();


	//prawy p³at œmig³a
	glBegin(GL_TRIANGLE_STRIP); //góra œmig³a
	glColor3f(0.4, 0.4, 0.4);
	glVertex3f(x, y + 2, z);
	glVertex3f(x + 3, y + 2, z - 3);
	glVertex3f(x + 3, y + 2, z + 3);
	glVertex3f(x + 15, y + 1.5, z - 3);
	glVertex3f(x + 15, y + 2, z + 3);
	glVertex3f(x + 15, y + 1, z - 3);
	glVertex3f(x + 15, y + 0.5, z + 3);
	glEnd();

	glBegin(GL_TRIANGLE_STRIP); //dó³ œmig³a
	glColor3f(0.7, 0.8, 0.4);
	glVertex3f(x + 15, y + 1, z - 3);
	glVertex3f(x + 15, y + 0.5, z + 3);
	glVertex3f(x + 3, y + 1, z - 3);
	glVertex3f(x + 3, y + 0, z + 3);
	glVertex3f(x, y + 2, z);
	glEnd();

	//przednia sciana œmig³a
	glBegin(GL_TRIANGLE_STRIP); glColor3f(0.7, 0.1, 0.8);
	glVertex3f(x, y + 2, z);
	glVertex3f(x + 3, y + 0, z + 3);
	glVertex3f(x + 3, y + 2, z + 3);
	glVertex3f(x + 15, y + 0.5, z + 3);
	glVertex3f(x + 15, y + 2, z + 3);
	glEnd();

	glBegin(GL_TRIANGLE_STRIP);	glColor3f(0.8, 0.f, 0.4); //tylna œciana œmig³a
	glVertex3f(x, y + 2, z);
	glVertex3f(x + 3, y + 1, z - 3);
	glVertex3f(x + 3, y + 2, z - 3);
	glVertex3f(x + 15, y + 1, z - 3);
	glVertex3f(x + 15, y + 1.5, z - 3);
	glEnd();
}

void Drone::kamera(float x, float y, float z)
{
	glColor3f(0.0f, 1.0f, 0.0f);
	glBegin(GL_TRIANGLE_STRIP);
	glVertex3d(x, y, z);
	glVertex3d(x, y, z + 5);
	for (float angle = 0; angle < GL_PI; angle += GL_PI / 10)
	{

		glVertex3d(cos(angle) * (x + 8), sin(angle)*(y - 8), z);
		glVertex3d(cos(angle) * (x + 8), sin(angle)*(y - 8), z + 10);
	}

	glEnd();
	glColor3f(1.0f, 0.0f, 1.0f);
	glBegin(GL_TRIANGLE_FAN);
	glVertex3d(x + 5, y, z);
	for (float angle = 0; angle < GL_PI; angle += GL_PI / 10)
	{
		glVertex3d(cos(angle) * (x + 8), sin(angle)*(y - 8), z);
	}
	glEnd();

	glBegin(GL_TRIANGLE_FAN);
	glVertex3d(x + 5, y, z + 10);
	for (float angle = 0; angle < GL_PI; angle += GL_PI / 10)
	{
		glVertex3d(cos(angle) * (x + 8), sin(angle)*(y - 8), z + 10);
	}
	glEnd();

	glColor3f(0, 0, 0);
	glBegin(GL_QUAD_STRIP);
	glVertex3d(cos(GL_PI / 10)*(x - 10), sin(GL_PI / 10)*(y - 10), z + 4);
	glVertex3d(cos(GL_PI / 10)*(x - 8), sin(GL_PI / 10)*(y - 8), z + 4);
	glVertex3d(cos(GL_PI / 10)*(x - 10), sin(GL_PI / 10)*(y - 10), z + 7);
	glVertex3d(cos(GL_PI / 10)*(x - 8), sin(GL_PI / 10)*(y - 8), z + 7);

	glVertex3d(cos(GL_PI / 5)*(x - 10), sin(GL_PI / 5)*(y - 10), z + 7);
	glVertex3d(cos(GL_PI / 5)*(x - 8), sin(GL_PI / 5)*(y - 8), z + 7);
	glVertex3d(cos(GL_PI / 5)*(x - 10), sin(GL_PI / 5)*(y - 10), z + 4);
	glVertex3d(cos(GL_PI / 5)*(x - 8), sin(GL_PI / 5)*(y - 8), z + 4);

	glVertex3d(cos(GL_PI / 10)*(x - 10), sin(GL_PI / 10)*(y - 10), z + 4);
	glVertex3d(cos(GL_PI / 10)*(x - 8), sin(GL_PI / 10)*(y - 8), z + 4);
	glEnd();

	glColor3f(0, 1, 1);
	glBegin(GL_TRIANGLE_STRIP);
	glVertex3d(cos(GL_PI / 10)*(x - 10), sin(GL_PI / 10)*(y - 10), z + 4);
	glVertex3d(cos(GL_PI / 10)*(x - 10), sin(GL_PI / 10)*(y - 10), z + 7);
	glVertex3d(cos(GL_PI / 5)*(x - 10), sin(GL_PI / 5)*(y - 10), z + 4);
	glVertex3d(cos(GL_PI / 5)*(x - 10), sin(GL_PI / 5)*(y - 10), z + 7);
	glEnd();

}

void Drone::oslona(float x, float y, float z)
{
	glColor3f(1, 0, 0);
	glBegin(GL_LINE_LOOP);

	for (float angle = 0.0; angle <= GL_PI * 2.0; angle += GL_PI / 10.0)
	{

		glVertex3f(sin(angle)*20.0 + x, y + 2, cos(angle)*20.0 + z);

	}
	glEnd();

	glColor3f(0.3f, 0.7f, 0.1f);
	glBegin(GL_LINE_STRIP);
	glVertex3d(x, y - 4, z);
	glVertex3d(x + 15, y - 4, z);
	glVertex3d(x + 20, y + 2, z);
	glEnd();

	glBegin(GL_LINE_STRIP);
	glVertex3d(x, y - 4, z);
	glVertex3d(x - 15, y - 4, z);
	glVertex3d(x - 20, y + 2, z);
	glEnd();

	glBegin(GL_LINE_STRIP);
	glVertex3d(x, y - 4, z);
	glVertex3d(x, y - 4, z - 15);
	glVertex3d(x, y + 2, z - 20);
	glEnd();

	glBegin(GL_LINE_STRIP);
	glVertex3d(x, y - 4, z);
	glVertex3d(x, y - 4, z + 15);
	glVertex3d(x, y + 2, z + 20);
	glEnd();

}
void Drone::spoiler(float x, float y, float z)
{//ta czêœæ co "trzyma" spoiler z kad³ubem
	glBegin(GL_QUADS);//z perspektywy lotu ptaka: czêœæ gorna
	glColor3f(0.3, 0.7, 0.2);
	glVertex3f(x - 2, y, z - 5);
	glVertex3f(x, y, z - 5);
	glVertex3f(x + 20, y + 20, z - 5);
	glVertex3f(x + 25, y + 20, z - 5);
	glEnd();
	glBegin(GL_QUADS);
	glVertex3f(x - 2, y, z - 2);
	glVertex3f(x, y, z - 2);
	glVertex3f(x + 20, y + 20, z - 2);
	glVertex3f(x + 25, y + 20, z - 2);
	glEnd();
	glBegin(GL_QUADS);
	glVertex3f(x, y, z - 2);
	glVertex3f(x, y, z - 5);
	glVertex3f(x + 25, y + 20, z - 5);
	glVertex3f(x + 25, y + 20, z - 2);
	glEnd();
	glBegin(GL_QUADS);
	glVertex3f(x - 2, y, z - 2);
	glVertex3f(x - 2, y, z - 5);
	glVertex3f(x + 20, y + 20, z - 5);
	glVertex3f(x + 20, y + 20, z - 2);
	glEnd();
	//czêœæ dolna
	glBegin(GL_QUADS);
	glVertex3f(x - 2, y, z + 5);
	glVertex3f(x, y, z + 5);
	glVertex3f(x + 20, y + 20, z + 5);
	glVertex3f(x + 25, y + 20, z + 5);
	glEnd();
	glBegin(GL_QUADS);
	glVertex3f(x - 2, y, z + 2);
	glVertex3f(x, y, z + 2);
	glVertex3f(x + 20, y + 20, z + 2);
	glVertex3f(x + 25, y + 20, z + 2);
	glEnd();
	glBegin(GL_QUADS);
	glColor3f(0.3, 0.7, 0.2);
	glVertex3f(x, y, z + 2);
	glVertex3f(x, y, z + 5);
	glVertex3f(x + 25, y + 20, z + 5);
	glVertex3f(x + 25, y + 20, z + 2);
	glEnd();
	glBegin(GL_QUADS);
	glVertex3f(x - 2, y, z + 2);
	glVertex3f(x - 2, y, z + 5);
	glVertex3f(x + 20, y + 20, z + 5);
	glVertex3f(x + 20, y + 20, z + 2);
	glEnd();
	glBegin(GL_TRIANGLE_STRIP);
	glColor3f(0.6, 0.7, 0.8);
	//p³at
	glVertex3f(x + 30, y + 25, z - 20);
	glVertex3f(x + 20, y + 20, z - 20);
	glVertex3f(x + 30, y + 20, z - 20);
	glVertex3f(x + 20, y + 20, z + 20);
	glVertex3f(x + 30, y + 20, z + 20);
	glColor3f(0.2, 0.2, 0.1);
	glVertex3f(x + 30, y + 25, z + 20);
	glVertex3f(x + 20, y + 20, z + 20);

	glVertex3f(x + 20, y + 20, z + 0);
	glVertex3f(x + 20, y + 20, z - 20);
	glVertex3f(x + 30, y + 25, z - 20);
	glEnd();

}
void Drone::nogi(float x, float y, float z)
{
	glColor3f(0.4, 1.f, 0.1f);//ramie lewy dó³
	glBegin(GL_QUAD_STRIP);
	glVertex3f(x - 5, y, z + 10);
	glVertex3f(x - 5, y - 10, z + 20);
	glVertex3f(x - 3, y, z + 10);
	glVertex3f(x - 3, y - 10, z + 20);
	glVertex3f(x - 3, y, z + 7);
	glVertex3f(x - 3, y - 10, z + 17);
	glVertex3f(x - 5, y, z + 7);
	glVertex3f(x - 5, y - 10, z + 17);
	glVertex3f(x - 5, y, z + 10);
	glVertex3f(x - 5, y - 10, z + 20);
	glEnd();
	glBegin(GL_QUAD_STRIP);//ramie prawy dó³
	glVertex3f(x + 5, y, z + 10);
	glVertex3f(x + 5, y - 10, z + 20);
	glVertex3f(x + 3, y, z + 10);
	glVertex3f(x + 3, y - 10, z + 20);
	glVertex3f(x + 3, y, z + 7);
	glVertex3f(x + 3, y - 10, z + 17);
	glVertex3f(x + 5, y, z + 7);
	glVertex3f(x + 5, y - 10, z + 17);
	glVertex3f(x + 5, y, z + 10);
	glVertex3f(x + 5, y - 10, z + 20);
	glEnd();
	//p³oza dó³
	glBegin(GL_TRIANGLE_STRIP);
	glVertex3f(x + 15, y - 10, z + 15);
	glVertex3f(x - 15, y - 10, z + 15);
	glVertex3f(x + 15, y - 10, z + 20);
	glVertex3f(x - 15, y - 10, z + 20);
	glVertex3f(x + 15, y - 12, z + 20);
	glVertex3f(x - 15, y - 12, z + 20);
	glVertex3f(x + 15, y - 12, z + 15);
	glVertex3f(x - 15, y - 12, z + 15);
	glVertex3f(x + 15, y - 10, z + 15);
	glVertex3f(x - 15, y - 10, z + 15);
	glEnd();

	//ramie lewy góra
	glBegin(GL_QUAD_STRIP);
	glVertex3f(x - 5, y, z - 10);
	glVertex3f(x - 5, y - 10, z - 20);
	glVertex3f(x - 3, y, z - 10);
	glVertex3f(x - 3, y - 10, z - 20);
	glVertex3f(x - 3, y, z - 7);
	glVertex3f(x - 3, y - 10, z - 17);
	glVertex3f(x - 5, y, z - 7);
	glVertex3f(x - 5, y - 10, z - 17);
	glVertex3f(x - 5, y, z - 10);
	glVertex3f(x - 5, y - 10, z - 20);
	glEnd();


	glBegin(GL_QUAD_STRIP);//ramie prawy góra
	glVertex3f(x + 5, y, z - 10);
	glVertex3f(x + 5, y - 10, z - 20);
	glVertex3f(x + 3, y, z - 10);
	glVertex3f(x + 3, y - 10, z - 20);
	glVertex3f(x + 3, y, z - 7);
	glVertex3f(x + 3, y - 10, z - 17);
	glVertex3f(x + 5, y, z - 7);
	glVertex3f(x + 5, y - 10, z - 17);
	glVertex3f(x + 5, y, z - 10);
	glVertex3f(x + 5, y - 10, z - 20);
	glEnd();
	//p³oza góra
	glBegin(GL_TRIANGLE_STRIP);
	glVertex3f(x + 15, y - 10, z - 15);
	glVertex3f(x - 15, y - 10, z - 15);
	glVertex3f(x + 15, y - 10, z - 20);
	glVertex3f(x - 15, y - 10, z - 20);
	glVertex3f(x + 15, y - 12, z - 20);
	glVertex3f(x - 15, y - 12, z - 20);
	glVertex3f(x + 15, y - 12, z - 15);
	glVertex3f(x - 15, y - 12, z - 15);
	glVertex3f(x + 15, y - 10, z - 15);
	glVertex3f(x - 15, y - 10, z - 15);
	glEnd();
}

void Drone::podloga()
{
	glColor3f(0.1, 0.8, 0.5);
	glBegin(GL_POLYGON);
	glVertex3f(500, -50, -500); //prawy gorny;
	glVertex3f(500, -50, 500); //prawy dolny
	glVertex3f(-500, -50, 500); //lewy dolny
	glVertex3f(-500, -50, -500); //lewy gorny
	glEnd();
}
