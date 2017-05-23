#pragma once
#include<glut.h>
class Drone
{
private:
	GLfloat GL_PI = 3.1415;
	float x, y, z;
public:
	Drone(float x,float y,float z);
	~Drone();
	void draw();
	void kadlub(float x);
	void ramiona(float x, float y, float z);
	void silnik(float x, float y, float z);//d� lewy
	void rotor(float x, float y, float z);
	void oslona(float x, float y, float z);

	void kamera(float x, float y, float z);

	void spoiler(float x, float y, float z);
	void nogi(float x, float y, float z);//nogi na kt�rych l�duje dron; xyz - �rodek spodu kad�ubu
	void podloga();
};

