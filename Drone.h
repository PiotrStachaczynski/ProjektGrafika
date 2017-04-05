#pragma once
#include<glut.h>
class Drone
{
private:
	float xParam, yParam, zParam;
public:
	Drone(float x,float y,float z);
	~Drone();

	void flashlight(float wsp_x, float wsp_y, float wsp_z);
	void legs(float wsp_x, float wsp_y, float wsp_z, GLfloat scale);
	void gadgets(float wsp_x, float wsp_y, float wsp_z);
	void foots(float wsp_x, float wsp_y, float wsp_z, GLfloat scale);
	void wing(float xParam, float yParam, float zParam);
	void body(float wsp_x, float wsp_y, float wsp_z);
	void head(float wsp_x, float wsp_y, float wsp_z);
	void draw();
};

