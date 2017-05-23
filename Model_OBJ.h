#pragma once
#include <glut.h>
#include <windows.h>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>

class Model_OBJ
{
public:
	Model_OBJ();
	float* Model_OBJ::calculateNormal(float* coord1, float* coord2, float* coord3);
	int Model_OBJ::Load(char *filename);	
	void Model_OBJ::Draw();
	void Draw(float red, float green, float blue);
	void Model_OBJ::Release();				

	float* normals;							
	float* Faces_Triangles;					
	float* vertexBuffer;					
	long TotalConnectedPoints;			
	long TotalConnectedTriangles;			

};

