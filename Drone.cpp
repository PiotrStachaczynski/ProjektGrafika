#include "Drone.h"
#include <math.h>

Drone::Drone(float x, float y, float z)
{
	xParam = x;
	yParam = y;
	zParam = z;
}

Drone::~Drone()
{
}

void Drone::draw()
{
	flashlight(xParam, yParam, zParam);
	legs(xParam, yParam, zParam,0);
	gadgets(xParam, yParam, zParam);
	foots(xParam, yParam, zParam,0);
	body(xParam, yParam, zParam);
	head(xParam, yParam, zParam);
}

void Drone::flashlight(float wsp_x, float wsp_y, float wsp_z)
{
	float GL_PI = 3.14;
	GLfloat a[3] = { 25.f,0,25.f };
	GLfloat b[3] = { 10.f,0,35.f };
	GLfloat c[3] = { -25.f,0,25.f };
	GLfloat d[3] = { -10.f,0,35.f };

	glShadeModel(GL_SMOOTH);
	glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
	glBegin(GL_POLYGON);
	glColor3f(0.4f, 0.2f, 0.2f);
	glVertex3f(-a[0] - 10 + wsp_x, a[1] + 25 + wsp_y, -a[2] + 28 + wsp_z);
	glVertex3f(-a[0] - 10 + wsp_x, a[1] + 30 + wsp_y, -a[2] + 28 + wsp_z);
	glColor3f(0.7f, 0.4f, 0.5f);
	glVertex3f(-a[0] + 7 + wsp_x, a[1] + 20 + wsp_y, a[2] - 22 + wsp_z);
	glVertex3f(-a[0] + 7 + wsp_x, a[1] + 15 + wsp_y, a[2] - 22 + wsp_z);
	glEnd();

	glShadeModel(GL_SMOOTH);
	glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
	glBegin(GL_POLYGON);
	glColor3f(0.4f, 0.2f, 0.2f);
	glVertex3f(a[0] - 7 + wsp_x, a[1] + 15 + wsp_y, -a[2] + 28 + wsp_z);
	glVertex3f(a[0] - 7 + wsp_x, a[1] + 20 + wsp_y, -a[2] + 28 + wsp_z);
	glColor3f(0.7f, 0.4f, 0.5f);
	glVertex3f(a[0] + 10 + wsp_x, a[1] + 30 + wsp_y, a[2] - 22 + wsp_z);
	glVertex3f(a[0] + 10 + wsp_x, a[1] + 25 + wsp_y, a[2] - 22 + wsp_z);
	glEnd();

	glShadeModel(GL_SMOOTH);
	glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
	glBegin(GL_POLYGON);
	glColor3f(0.4f, 0.2f, 0.2f);
	glVertex3f(-a[0] - 10 + wsp_x, a[1] + 25 + wsp_y, -a[2] + 22 + wsp_z);
	glVertex3f(-a[0] - 10 + wsp_x, a[1] + 30 + wsp_y, -a[2] + 22 + wsp_z);
	glColor3f(0.7f, 0.4f, 0.5f);
	glVertex3f(-a[0] + 7 + wsp_x, a[1] + 20 + wsp_y, a[2] - 28 + wsp_z);
	glVertex3f(-a[0] + 7 + wsp_x, a[1] + 15 + wsp_y, a[2] - 28 + wsp_z);
	glEnd();

	glShadeModel(GL_SMOOTH);
	glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
	glBegin(GL_POLYGON);
	glColor3f(0.4f, 0.2f, 0.2f);
	glVertex3f(a[0] - 7 + wsp_x, a[1] + 15 + wsp_y, -a[2] + 22 + wsp_z);
	glVertex3f(a[0] - 7 + wsp_x, a[1] + 20 + wsp_y, -a[2] + 22 + wsp_z);
	glColor3f(0.7f, 0.4f, 0.5f);
	glVertex3f(a[0] + 10 + wsp_x, a[1] + 30 + wsp_y, a[2] - 28 + wsp_z);
	glVertex3f(a[0] + 10 + wsp_x, a[1] + 25 + wsp_y, a[2] - 28 + wsp_z);
	glEnd();


	glShadeModel(GL_SMOOTH);
	glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
	glBegin(GL_POLYGON);
	glColor3f(0.4f, 0.2f, 0.2f);

	glVertex3f(a[0] - 7 + wsp_x, a[1] + 20 + wsp_y, -a[2] + 22 + wsp_z);
	glVertex3f(a[0] - 7 + wsp_x, a[1] + 20 + wsp_y, -a[2] + 28 + wsp_z);
	glColor3f(0.7f, 0.4f, 0.5f);
	glVertex3f(a[0] + 10 + wsp_x, a[1] + 30 + wsp_y, a[2] - 22 + wsp_z);
	glVertex3f(a[0] + 10 + wsp_x, a[1] + 30 + wsp_y, a[2] - 28 + wsp_z);

	glEnd();

	glShadeModel(GL_SMOOTH);
	glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
	glBegin(GL_POLYGON);
	glColor3f(0.4f, 0.2f, 0.2f);
	glVertex3f(-a[0] - 10 + wsp_x, a[1] + 30 + wsp_y, -a[2] + 22 + wsp_z);
	glVertex3f(-a[0] - 10 + wsp_x, a[1] + 30 + wsp_y, -a[2] + 28 + wsp_z);
	glVertex3f(-a[0] + 7 + wsp_x, a[1] + 20 + wsp_y, -a[2] + 28 + wsp_z);
	glVertex3f(-a[0] + 7 + wsp_x, a[1] + 20 + wsp_y, -a[2] + 22 + wsp_z);
	glColor3f(0.7f, 0.4f, 0.5f);
	glEnd();

	double angle, q, w;
	// Jedna latarka
	glColor3f(0.9f, 0.0f, 0.9f);
	glBegin(GL_TRIANGLE_STRIP);
	for (angle = 0; angle <= 2 * GL_PI; angle += GL_PI / 8.0)
	{
		q = 5 * sin(angle);
		w = 5 * cos(angle);
		glVertex3f(wsp_x + (a[0] + 10), wsp_y + 30.0f, wsp_z + (a[2] - 30));
		glColor3f(0.1f, 0.0f, 0.1f);
		glVertex3f(wsp_x + ((q + a[0] + 10)), wsp_y + w + 30.0f, wsp_z + ((a[2] - 30)));
	}
	glEnd();

	glBegin(GL_TRIANGLE_STRIP);
	for (angle = 0; angle <= 2 * GL_PI; angle += GL_PI / 8.0)
	{
		q = 5 * sin(angle);
		w = 5 * cos(angle);
		glVertex3f(wsp_x + (a[0] + 10), wsp_y + 30.0f, wsp_z + (a[2] - 19));
		glColor3f(0.7f, 0.0f, 0.1f);
		glVertex3f(wsp_x + ((q + a[0] + 10)), wsp_y + w + 30.0f, wsp_z + ((a[2] - 19)));

	}
	glEnd();


	glBegin(GL_TRIANGLE_STRIP);
	for (angle = 0; angle <= 2 * GL_PI; angle += GL_PI / 8.0)
	{
		q = 3 * sin(angle);
		w = 3 * cos(angle);
		glVertex3f(wsp_x + (a[0] + 10), wsp_y + 30.0f, wsp_z + (a[2] - 15));
		glColor3f(1.f, 1.f, 0.0f);
		glVertex3f(wsp_x + ((q + a[0] + 10)), wsp_y + w + 30.0f, wsp_z + ((a[2] - 15)));
	}
	glEnd();


	glBegin(GL_TRIANGLE_STRIP);
	for (angle = 0; angle <= 2 * GL_PI; angle += GL_PI / 8.0)
	{
		q = 5 * sin(angle);
		w = 5 * cos(angle);
		glColor3f(0.4f, 0.2f, 0.0f);
		glVertex3f(wsp_x + (q + a[0] + 10), wsp_y + w + 30.0f, wsp_z + (a[2] - 30));
		glColor3f(0.2f, 0.1f, 0.0f);
		glVertex3f(wsp_x + ((q + a[0] + 10)), wsp_y + w + 30.0f, wsp_z + ((a[2] - 19)));
	}

	glEnd();
	glBegin(GL_TRIANGLE_STRIP);
	for (angle = 0; angle <= 2 * GL_PI; angle += GL_PI / 8.0)
	{
		q = 3 * sin(angle);
		w = 3 * cos(angle);
		glColor3f(0.4f, 0.2f, 0.0f);
		glVertex3f(wsp_x + (q + a[0] + 10), wsp_y + w + 30.0f, wsp_z + (a[2] - 19));
		glColor3f(0.6f, 0.1f, 0.0f);
		glVertex3f(wsp_x + ((q + a[0] + 10)), wsp_y + w + 30.0f, wsp_z + ((a[2] - 15)));
	}
	glEnd();

	//Druga latarka
	glColor3f(0.9f, 0.0f, 0.9f);
	glBegin(GL_TRIANGLE_STRIP);
	for (angle = 0; angle <= 2 * GL_PI; angle += GL_PI / 8.0)
	{
		q = 5 * sin(angle);
		w = 5 * cos(angle);
		glVertex3f(wsp_x + (-a[0] - 10), wsp_y + 30.0f, wsp_z + (a[2] - 30));
		glColor3f(0.1f, 0.0f, 0.1f);
		glVertex3f(wsp_x + ((q - a[0] - 10)), wsp_y + w + 30.0f, wsp_z + ((a[2] - 30)));
	}
	glEnd();

	glBegin(GL_TRIANGLE_STRIP);
	for (angle = 0; angle <= 2 * GL_PI; angle += GL_PI / 8.0)
	{
		q = 5 * sin(angle);
		w = 5 * cos(angle);
		glVertex3f(wsp_x + (-a[0] - 10), wsp_y + 30.0f, wsp_z + (a[2] - 19));
		glColor3f(0.7f, 0.0f, 0.1f);
		glVertex3f(wsp_x + ((q - a[0] - 10)), wsp_y + w + 30.0f, wsp_z + ((a[2] - 19)));
	}
	glEnd();


	glBegin(GL_TRIANGLE_STRIP);
	for (angle = 0; angle <= 2 * GL_PI; angle += GL_PI / 8.0)
	{
		q = 3 * sin(angle);
		w = 3 * cos(angle);
		glVertex3f(wsp_x - a[0] - 10, wsp_y + 30.0f, wsp_z + (a[2] - 15));
		glColor3f(1.f, 1.f, 0.0f);
		glVertex3f(wsp_x + ((q - a[0] - 10)), wsp_y + w + 30.0f, wsp_z + ((a[2] - 15)));
	}
	glEnd();


	glBegin(GL_TRIANGLE_STRIP);
	for (angle = 0; angle <= 2 * GL_PI; angle += GL_PI / 8.0)
	{
		q = 5 * sin(angle);
		w = 5 * cos(angle);
		glColor3f(0.4f, 0.2f, 0.0f);
		glVertex3f(wsp_x + (q - a[0] - 10), wsp_y + w + 30.0f, wsp_z + (a[2] - 30));
		glColor3f(0.2f, 0.1f, 0.0f);
		glVertex3f(wsp_x + ((q - a[0] - 10)), wsp_y + w + 30.0f, wsp_z + ((a[2] - 19)));
	}

	glEnd();
	glBegin(GL_TRIANGLE_STRIP);
	for (angle = 0; angle <= 2 * GL_PI; angle += GL_PI / 8.0)
	{
		q = 3 * sin(angle);
		w = 3 * cos(angle);
		glColor3f(0.4f, 0.2f, 0.0f);
		glVertex3f(wsp_x + (q - a[0] - 10), wsp_y + w + 30.0f, wsp_z + (a[2] - 19));
		glColor3f(0.6f, 0.1f, 0.0f);
		glVertex3f(wsp_x + ((q - a[0] - 10)), wsp_y + w + 30.0f, wsp_z + ((a[2] - 15)));
	}
	glEnd();
}

void Drone::legs(float wsp_x, float wsp_y, float wsp_z, GLfloat scale)
{
	float GL_PI = 3.14;
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	{
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
			GLfloat a[3] = { wsp_x + (x*25.0f + scale),wsp_y + z,wsp_z + (y*25.0f + scale) };
			GLfloat b[3] = { wsp_x + (x*65.0f + scale),wsp_y + z,wsp_z + (y*65.0f + scale) };
			GLfloat c[3] = { wsp_x + (x*10.0f + scale),wsp_y + z,wsp_z + (y*35.0f + scale) };
			GLfloat d[3] = { wsp_x + (x*60.0f + scale),wsp_y + z,wsp_z + (y*70.0f + scale) };

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
			glVertex3f(b[0], wsp_y + 0, b[2]);
			glVertex3f(a[0], wsp_y + 0, a[2]);
			glColor3f(0.2f, 0.2f, 0.2f);
			glVertex3f(b[0], wsp_y + 5, b[2]);
			glVertex3f(a[0], wsp_y + 5, a[2]);

			glColor3f(0.2f, 0.2f, 0.2f);
			glBegin(GL_TRIANGLE_STRIP);
			glVertex3f(d[0], wsp_y + 0, d[2]);
			glVertex3f(c[0], wsp_y + 0, c[2]);
			glColor3f(0.9f, 0.8f, 0.8f);
			glVertex3f(d[0], wsp_y + 5, d[2]);
			glVertex3f(c[0], wsp_y + 5, c[2]);

			glColor3f(0.1f, 0.2f, 0.2f);
			glBegin(GL_TRIANGLE_STRIP);
			glVertex3f(b[0], wsp_y + 0, b[2]);
			glVertex3f(d[0], wsp_y + 0, d[2]);
			glColor3f(0.9f, 0.9f, 0.9f);
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
				glVertex3f(wsp_x + (x*60.0f), wsp_y + 5.0f, wsp_z + (y*66.0f));
				glColor3f(0.1f, 0.0f, 0.1f);
				glVertex3f(wsp_x + (x*(q + 60)), wsp_y + 5.0f, wsp_z + (y*(w + 66.0f)));

			}
			glEnd();

			glBegin(GL_TRIANGLE_STRIP);
			for (angle = 0; angle <= 2 * GL_PI; angle += GL_PI / 8.0)
			{
				q = 3 * sin(angle);
				w = 3 * cos(angle);
				glColor3f(0.9f, 0.0f, 0.9f);
				glVertex3f(wsp_x + (x*60.0f), wsp_y + 15.0f, wsp_z + (y*66.0f));
				glColor3f(0.3f, 0.0f, 0.3f);
				glVertex3f(wsp_x + (x*(q + 60)), wsp_y + 15.0f, wsp_z + (y*(w + 66.0f)));
			}
			glEnd();

			glBegin(GL_TRIANGLE_STRIP);
			for (angle = 0; angle <= 2 * GL_PI; angle += GL_PI / 8.0)
			{
				q = 3 * sin(angle);
				w = 3 * cos(angle);
				glColor3f(0.9f, 0.8f, 0.9f);
				glVertex3f(wsp_x + (x*(q + 60.0f)), wsp_y + 15.0f, wsp_z + (y*(w + 66.0f)));
				glColor3f(0.2f, 0.0f, 0.2f);
				glVertex3f(wsp_x + (x*(q + 60)), wsp_y + 5.0f, wsp_z + (y*(w + 66.0f)));
			}
			glEnd();
		}
	}
}

void Drone::gadgets(float wsp_x, float wsp_y, float wsp_z)
{
	float GL_PI = 3.14;
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
		x = 1;
		y = 1;
		GLfloat a[3] = { 25.f,0,25.f };
		GLfloat b[3] = { 10.f,0,35.f };
		GLfloat c[3] = { -25.f,0,25.f };
		GLfloat d[3] = { -10.f,0,35.f };
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
			glColor3f(0.2f, 0.0f, 0.2f);
			glVertex3f(x*(a[0]) + wsp_x, (a[1] + 5) + wsp_y, y*(a[2]) + wsp_z);
			glVertex3f(x*(a[0] + 3) + wsp_x, (a[1] + 10) + wsp_y, (y*(a[2] + 3) + wsp_z));
			glColor3f(0.4f, 0.0f, 0.1f);
			glVertex3f((x*(b[0] + 3)) + wsp_x, (b[1] + 10) + wsp_y, (y*(b[2] + 3) + wsp_z));
			glVertex3f(x*(b[0]) + wsp_x, (b[1] + 5) + wsp_y, y*(b[2]) + wsp_z);
			glEnd();
			x = -1;
		}
	}
}

void Drone::foots(float wsp_x, float wsp_y, float wsp_z, GLfloat scale)
{
	float GL_PI = 3.14;
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

			double angle, q, w, t, u;
			glColor3f(0.9f, 0.0f, 0.9f);
			glBegin(GL_TRIANGLE_STRIP);
			for (angle = 0; angle <= 2 * GL_PI; angle += GL_PI / 8.0)
			{
				q = 4 * sin(angle);
				w = 4 * cos(angle);
				glVertex3f(wsp_x + (x*60.0f), wsp_y, wsp_z + (y*66.0f));
				glColor3f(0.1f, 0.0f, 0.1f);
				glVertex3f(wsp_x + (x*(q + 60)), wsp_y, wsp_z + (y*(w + 66.0f)));
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
				glVertex3f(wsp_x + (x*(q + 60)), wsp_y - 5.0f, wsp_z + (y*(w + 66.0f)));
			}
			glEnd();

			glBegin(GL_TRIANGLE_STRIP);
			for (angle = 0; angle <= 2 * GL_PI; angle += GL_PI / 8.0)
			{
				q = 4 * sin(angle);
				w = 4 * cos(angle);
				glColor3f(0.9f, 0.8f, 0.9f);
				glVertex3f(wsp_x + (x*(q + 60.0f)), wsp_y - 5.f, wsp_z + (y*(w + 66.0f)));
				glColor3f(0.2f, 0.3f, 0.2f);
				glVertex3f(wsp_x + (x*(q + 60)), wsp_y, wsp_z + (y*(w + 66.0f)));
			}
			glEnd();

			// 2 stopien 
			glColor3f(0.9f, 0.0f, 0.9f);
			glBegin(GL_TRIANGLE_STRIP);
			for (angle = 0; angle <= 2 * GL_PI; angle += GL_PI / 8.0)
			{
				q = 3 * sin(angle);
				w = 3 * cos(angle);
				glVertex3f(wsp_x + (x*60.0f), wsp_y - 5.f, wsp_z + (y*66.0f));
				glColor3f(0.1f, 0.0f, 0.1f);
				glVertex3f(wsp_x + (x*(q + 60)), wsp_y - 5.f, wsp_z + (y*(w + 66.0f)));
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
				glVertex3f(wsp_x + (x*(q + 60)), wsp_y - 5.f, wsp_z + (y*(w + 66.0f)));
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
				glVertex3f(wsp_x + (x*(t + 60.0f)), wsp_y - 20.0f, wsp_z + (y*(u + 66.0f)));
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

void Drone::wing(float xParam, float yParam, float zParam)
{
	float GL_PI = 3.14;
	GLfloat a[3] = { -2.f + xParam, 0.5f + yParam, 2.f + zParam };
	GLfloat b[3] = { 2.f + xParam, 0.5f + yParam, 2.f + zParam };
	GLfloat c[3] = { 2.f + xParam, 0.5f + yParam, -2.f + zParam };
	GLfloat d[3] = { -2.f + xParam, 0.5f + yParam, -2.f + zParam };
	GLfloat e[3] = { -10.f + xParam, 0.f + yParam, -1.f + zParam };
	GLfloat g[3] = { 10.f + xParam, 0.5f + yParam, -4.f + zParam };
	GLfloat h[3] = { 10.f + xParam, 0.f + yParam, 1.f + zParam };
	GLfloat i[3] = { a[0], a[1] - 1.f, a[2] };
	GLfloat j[3] = { b[0], b[1] - 1.f, b[2] };
	GLfloat k[3] = { d[0], d[1] - 1.f, d[2] };
	GLfloat l[3] = { c[0], c[1] - 1.f, c[2] };
	GLfloat n[3] = { -10.f + xParam, 0.5f + yParam, 4.f + zParam };
	GLfloat r[3] = { n[0] + 6.f, a[1], n[2] - 1.f };
	GLfloat s[3] = { g[0] - 6.f, a[1], g[2] + 1.f };

	float x, y, z, angle, range = 2.f;
	GLfloat twicePi = 2.f * GL_PI,
		angleInc = GL_PI / 16.f;

	//czysto testowo zwi�kszenie parametr�w
	for (int is = 0; is < 3; is++)
	{
		int amount = 2;
		range = 4.f;
		a[is] *= amount;
		b[is] *= amount;
		c[is] *= amount;
		d[is] *= amount;
		e[is] *= amount;
		g[is] *= amount;
		h[is] *= amount;
		i[is] *= amount;
		j[is] *= amount;
		k[is] *= amount;
		l[is] *= amount;
		n[is] *= amount;
		r[is] *= amount;
		s[is] *= amount;
	}

	////pierwsze p� g�rnego otworu na n�k� drona, �rodek otworu ma wsp�rz�dne podane przez parametry
	//glColor3d(0.f, 1.0f, 1.0f);
	//glBegin(GL_TRIANGLE_STRIP);
	//for (angle = 0; angle <= twicePi; angle += angleInc)
	//{
	//	x = range * sin(angle);
	//	z = range * cos(angle);

	//	if (x >= 0.f)
	//	{
	//		glVertex3d(c[0], c[1], zParam + z);
	//		glVertex3d(xParam + x, c[1], zParam + z);
	//	}
	//}
	//glEnd();

	////drugie p� g�rnego otworu na n�k� drona, �rodek otworu ma wsp�rz�dne podane przez parametry
	//glBegin(GL_TRIANGLE_STRIP);
	//for (angle = 0; angle <= twicePi; angle += angleInc)
	//{
	//	x = range * sin(angle);
	//	z = range * cos(angle);

	//	if (x < 0.f)
	//	{
	//		glVertex3d(a[0], a[1], zParam + z);
	//		glVertex3d(xParam + x, a[1], zParam + z);
	//	}
	//}
	//glEnd();

	////pierwsze p� dolnego otworu na n�k� drona, �rodek otworu ma wsp�rz�dne podane przez parametry
	//glColor3d(0.f, 1.0f, 1.0f);
	//glBegin(GL_TRIANGLE_STRIP);
	//for (angle = 0; angle <= twicePi; angle += angleInc)
	//{
	//	x = range * sin(angle);
	//	z = range * cos(angle);

	//	if (x >= 0.f)
	//	{
	//		glVertex3d(l[0], l[1], zParam + z);
	//		glVertex3d(xParam + x, l[1], zParam + z);
	//	}
	//}
	//glEnd();

	////drugie p� dolnego otworu na n�k� drona, �rodek otworu ma wsp�rz�dne podane przez parametry
	//glBegin(GL_TRIANGLE_STRIP);
	//for (angle = 0; angle <= twicePi; angle += angleInc)
	//{
	//	x = range * sin(angle);
	//	z = range * cos(angle);

	//	if (x < 0.f)
	//	{
	//		glVertex3d(i[0], i[1], zParam + z);
	//		glVertex3d(xParam + x, i[1], zParam + z);
	//	}
	//}
	//glEnd();

	//tylna �ciana �rodka
	glColor3d(0.9f, 0.4f, 0.4f);
	glBegin(GL_TRIANGLE_STRIP);
	glVertex3fv(d);
	glVertex3fv(c);
	glVertex3fv(k);
	glVertex3fv(l);
	glEnd();

	//przednia �ciana �rodka
	glColor3d(0.9f, 0.4f, 0.4f);
	glBegin(GL_TRIANGLE_STRIP);
	glVertex3fv(a);
	glVertex3fv(b);
	glColor3d(0.9f, 1.0f, 1.0f);
	glVertex3fv(i);
	glVertex3fv(j);
	glEnd();

	//g�rna �ciana lewego p�atka wiatraka
	glColor3d(0.f, 0.3f, 0.7f);
	glBegin(GL_TRIANGLE_STRIP);
	glVertex3fv(e);
	glVertex3fv(d);
	glColor3d(0.f, 1.0f, 1.0f);
	glVertex3d(n[0], n[1], n[2] - 2.f);
	glVertex3fv(a);
	glEnd();
	glBegin(GL_TRIANGLE_STRIP);
	glVertex3fv(a);
	glVertex3fv(r);
	glVertex3d(n[0], n[1], n[2] - 2.f);
	glVertex3fv(n);
	glEnd();

	//g�rna �ciana prawego p�atka wiatraka
	glBegin(GL_TRIANGLE_STRIP);
	glVertex3fv(h);
	glVertex3fv(b);
	glColor3d(0.f, 0.3f, 0.7f);
	glVertex3d(g[0], g[1], g[2] + 2.f);
	glVertex3fv(c);
	glEnd();
	glBegin(GL_TRIANGLE_STRIP);
	glVertex3fv(c);
	glVertex3fv(s);
	glVertex3d(g[0], g[1], g[2] + 2.f);
	glVertex3fv(g);
	glEnd();

	//dolna �ciana lewego p�atka wiatraka
	glColor3d(1.f, 0.3f, 0.7f);
	glBegin(GL_TRIANGLE_STRIP);
	glVertex3fv(k);
	glVertex3fv(e);
	glVertex3fv(i);
	glVertex3d(n[0], n[1], n[2] - 2.f);
	glEnd();
	glBegin(GL_TRIANGLE_STRIP);
	glVertex3fv(i);
	glVertex3d(r[0], r[1], r[2]);
	glVertex3d(n[0], n[1] - 0.01f, n[2] - 2.f);
	glVertex3fv(n);
	glEnd();

	//dolna �ciana prawego p�atka wiatraka
	glBegin(GL_TRIANGLE_STRIP);
	glVertex3fv(j);
	glVertex3fv(h);
	glVertex3fv(l);
	glVertex3d(g[0], g[1], g[2] + 2.f);
	glEnd();
	glBegin(GL_TRIANGLE_STRIP);
	glVertex3fv(l);
	glVertex3d(s[0], s[1], s[2]);
	glVertex3d(g[0], g[1] - 0.01f, g[2] + 2.f);
	glVertex3fv(g);
	glEnd();

	//tylna �ciana lewego skrzyd�a
	glColor3d(0.4f, 0.f, 0.4f);
	glBegin(GL_TRIANGLE_STRIP);
	glVertex3fv(d);
	glVertex3fv(e);
	glVertex3fv(k);
	glEnd();

	//przednia �ciana prawego skrzyd�a
	glBegin(GL_TRIANGLE_STRIP);
	glVertex3fv(b);
	glColor3d(0.f, 0.3f, 0.7f);
	glVertex3fv(h);
	glVertex3fv(j);
	glEnd();

	//przednia �ciana lewego skrzyd�a
	glBegin(GL_TRIANGLE_STRIP);
	glVertex3fv(a);
	glVertex3fv(i);
	glColor3d(0.4f, 0.f, 0.4f);
	glVertex3fv(r);
	glVertex3fv(n);
	glEnd();

	//tylnia �ciana lewego skrzyd�a
	glBegin(GL_TRIANGLE_STRIP);
	glVertex3fv(c);
	glVertex3fv(s);
	glVertex3fv(l);
	glVertex3fv(g);
	glEnd();
}

void Drone::body(float wsp_x, float wsp_y, float wsp_z)
{
	float GL_PI = 3.14;
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
			glVertex3f(wsp_x + (x*a[0]), wsp_y + (a[1]), wsp_z + (y*a[2]));
			glVertex3f(wsp_x + (x*b[0]), wsp_y + (b[1]), wsp_z + (y*b[2]));
			glColor3f(0.7f, 0.8f, 0.8f);
			glVertex3f(wsp_x + (x*d[0]), wsp_y + (d[1]), wsp_z + (y*d[2]));
			glVertex3f(wsp_x + (x*c[0]), wsp_y + (c[1]), wsp_z + (y*c[2]));
			glEnd();
			if (i <= 1)
			{
				glColor3f(0.8f, 0.9f, 0.9f);
				glBegin(GL_POLYGON);
				glVertex3f(wsp_x + (x*d[0]), wsp_y + (d[1]), wsp_z + (y*d[2]));
				glVertex3f(wsp_x + (x*b[0]), wsp_y + (b[1]), wsp_z + (y*b[2]));
				glColor3f(0.7f, 0.5f, 0.7);
				glVertex3f(wsp_x + (x*b[0]), wsp_y + (b[1]) + 5, wsp_z + (y*b[2]));
				glVertex3f(wsp_x + (x*d[0]), wsp_y + (d[1]) + 5, wsp_z + (y*d[2]));
				glEnd();

				y = 1;
				glColor3f(0.6f, 0.8f, 0.7f);
				glBegin(GL_POLYGON);
				glVertex3f(wsp_x + (x*a[0]), wsp_y + (a[1]), wsp_z + (y*a[2]));
				glVertex3f(wsp_x + (x*a[0]), wsp_y + (a[1] + 5), wsp_z + (y*a[2]));
				glVertex3f(wsp_x + (x*a[0]), wsp_y + (a[1] + 5), wsp_z + (-y*a[2]));
				glVertex3f(wsp_x + (x*a[0]), wsp_y + (a[1]), wsp_z + (-y*a[2]));
				glEnd();

				glColor3f(0.6f, 0.8f, 0.7f);
				glBegin(GL_POLYGON);
				glVertex3f(wsp_x + (x*c[0]), wsp_y + (c[1]), wsp_z + (y*c[2]));
				glVertex3f(wsp_x + (x*c[0]), wsp_y + (c[1] + 5), wsp_z + (y*c[2]));
				glVertex3f(wsp_x + (x*c[0]), wsp_y + (c[1] + 5), wsp_z + (-y*c[2]));
				glVertex3f(wsp_x + (x*c[0]), wsp_y + (c[1]), wsp_z + (-y*c[2]));
				glEnd();
			}
			y = 1;
			glColor3f(0.6f, 0.8f, 0.7f);
			glBegin(GL_POLYGON);
			glVertex3f(wsp_x + (x*a[0]), wsp_y + (a[1]), wsp_z + (y*a[2]));
			glVertex3f(wsp_x + (x*c[0]), wsp_y + (c[1]), wsp_z + (y*c[2]));
			glColor3f(0.8f, 0.9f, 0.9f);
			glVertex3f(wsp_x + (x*-a[0]), wsp_y + (a[1]), wsp_z + (-y*a[2]));
			glVertex3f(wsp_x + (x*-c[0]), wsp_y + (c[1]), wsp_z + (-y*c[2]));
			glEnd();
			y = -1;
		}
	}
}

void Drone::head(float wsp_x, float wsp_y, float wsp_z)
{
	float GL_PI = 3.14;
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
			glVertex3f(x*(a[0]) + wsp_x, (a[1] + 5) + wsp_y, y*(a[2]) + wsp_z);
			glVertex3f(x*(a[0] - 3) + wsp_x, (a[1] + 15) + wsp_y, (y*(a[2] - 3) + wsp_z));
			glColor3f(0.4f, 0.0f, 0.1f);
			glVertex3f((x*(b[0] - 3)) + wsp_x, (b[1] + 15) + wsp_y, (y*(b[2] - 3) + wsp_z));
			glVertex3f(x*(b[0]) + wsp_x, (b[1] + 5) + wsp_y, y*(b[2]) + wsp_z);
			glEnd();
			x = -1;
		}

		glBegin(GL_POLYGON);
		glColor3f(0.6f, 0.0f, 0.8f);
		glVertex3f(-a[0] + wsp_x, a[1] + wsp_y + 5, -a[2] + wsp_z);
		glVertex3f(-a[0] + 3 + wsp_x, a[1] + 15 + wsp_y, -a[2] + 3 + wsp_z);
		glColor3f(0.4f, 0.0f, 0.4f);
		glVertex3f(-a[0] + 3 + wsp_x, a[1] + 15 + wsp_y, a[2] - 3 + wsp_z);
		glVertex3f(-a[0] + wsp_x, a[1] + 5 + wsp_y, a[2] + wsp_z);
		glEnd();

		glBegin(GL_POLYGON);
		glColor3f(0.6f, 0.0f, 0.8f);
		glVertex3f(a[0] + wsp_x, a[1] + 5 + wsp_y, -a[2] + wsp_z);
		glVertex3f(a[0] - 3 + wsp_x, a[1] + 15 + wsp_y, -a[2] + 3 + wsp_z);
		glColor3f(0.4f, 0.0f, 0.4f);
		glVertex3f(a[0] - 3 + wsp_x, a[1] + 15 + wsp_y, a[2] - 3 + wsp_z);
		glVertex3f(a[0] + wsp_x, a[1] + 5 + wsp_y, a[2] + wsp_z);
		glEnd();

		glBegin(GL_POLYGON);
		glColor3f(0.6f, 0.0f, 0.8f);
		glVertex3f(-b[0] + wsp_x, b[1] + 5 + wsp_y, -b[2] + wsp_z);
		glVertex3f(-b[0] + 3 + wsp_z, b[1] + 15 + wsp_y, -b[2] + 3 + wsp_z);
		glColor3f(0.4f, 0.0f, 0.6f);
		glVertex3f(b[0] - 3 + wsp_x, b[1] + 15 + wsp_y, -b[2] + 3 + wsp_z);
		glVertex3f(b[0] + wsp_z, b[1] + 5 + wsp_y, -b[2] + wsp_z);
		glEnd();

		glBegin(GL_POLYGON);
		glColor3f(0.6f, 0.0f, 0.8f);
		glVertex3f(b[0] + wsp_x, b[1] + 5 + wsp_y, b[2] + wsp_z);
		glVertex3f(b[0] - 3 + wsp_x, b[1] + 15 + wsp_y, b[2] - 3 + wsp_z);
		glColor3f(0.4f, 0.0f, 0.6f);
		glVertex3f(-b[0] + 3 + wsp_x, b[1] + 15 + wsp_y, b[2] - 3 + wsp_z);
		glVertex3f(-b[0] + wsp_x, b[1] + 5 + wsp_y, b[2] + wsp_z);
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
			glVertex3f(x*(a[0] - 3) + wsp_x, a[1] + 15 + wsp_y, y*(a[2] - 3) + wsp_z);
			glVertex3f(x*(a[0] - 8) + wsp_x, a[1] + 20 + wsp_y, y*(a[2] - 8) + wsp_z);
			glColor3f(0.6f, 0.4f, 0.5f);
			glVertex3f(x*(b[0] - 8) + wsp_x, b[1] + 20 + wsp_y, y*(b[2] - 8) + wsp_z);
			glVertex3f(x*(b[0] - 3) + wsp_x, b[1] + 15 + wsp_y, y*(b[2] - 3) + wsp_z);
			glEnd();
			x = -1;
		}

		glShadeModel(GL_SMOOTH);
		glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
		glBegin(GL_POLYGON);
		glColor3f(0.8f, 0.8f, 0.6f);
		glVertex3f(-a[0] + 3 + wsp_x, a[1] + 15 + wsp_y, -a[2] + 3 + wsp_z);
		glVertex3f(-a[0] + 8 + wsp_x, a[1] + 20 + wsp_y, -a[2] + 8 + wsp_z);
		glColor3f(0.7f, 0.4f, 0.5f);
		glVertex3f(-a[0] + 8 + wsp_x, a[1] + 20 + wsp_y, a[2] - 8 + wsp_z);
		glVertex3f(-a[0] + 3 + wsp_x, a[1] + 15 + wsp_y, a[2] - 3 + wsp_z);
		glEnd();

		glShadeModel(GL_SMOOTH);
		glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
		glBegin(GL_POLYGON);
		glColor3f(0.8f, 0.8f, 0.6f);
		glVertex3f(a[0] - 3 + wsp_x, a[1] + 15 + wsp_y, -a[2] + 3 + wsp_z);
		glVertex3f(a[0] - 8 + wsp_x, a[1] + 20 + wsp_y, -a[2] + 8 + wsp_z);
		glColor3f(0.7f, 0.4f, 0.5f);
		glVertex3f(a[0] - 8 + wsp_x, a[1] + 20 + wsp_y, a[2] - 8 + wsp_z);
		glVertex3f(a[0] - 3 + wsp_x, a[1] + 15 + wsp_y, a[2] - 3 + wsp_z);
		glEnd();

		glBegin(GL_POLYGON);
		glColor3f(0.8f, 0.9f, 0.9f);
		glVertex3f(-b[0] + 3 + wsp_x, b[1] + 15 + wsp_y, -b[2] + 3 + wsp_z);
		glVertex3f(-b[0] + 8 + wsp_x, b[1] + 20 + wsp_y, -b[2] + 8 + wsp_z);
		glColor3f(0.7f, 0.5f, 0.7);
		glVertex3f(b[0] - 8 + wsp_x, b[1] + 20 + wsp_y, -b[2] + 8 + wsp_z);
		glVertex3f(b[0] - 3 + wsp_x, b[1] + 15 + wsp_y, -b[2] + 3 + wsp_z);
		glEnd();

		glBegin(GL_POLYGON);
		glColor3f(0.8f, 0.9f, 0.9f);
		glVertex3f(b[0] - 3 + wsp_x, b[1] + 15 + wsp_y, b[2] - 3 + wsp_z);
		glVertex3f(b[0] - 8 + wsp_x, b[1] + 20 + wsp_y, b[2] - 8 + wsp_z);
		glColor3f(0.7f, 0.5f, 0.7);
		glVertex3f(-b[0] + 8 + wsp_x, b[1] + 20 + wsp_y, b[2] - 8 + wsp_z);
		glVertex3f(-b[0] + 3 + wsp_x, b[1] + 15 + wsp_y, b[2] - 3 + wsp_z);
		glEnd();

		glBegin(GL_POLYGON);
		glColor3f(0.3f, 0.3f, 0.7f);
		glVertex3f(a[0] - 8 + wsp_x, a[1] + 20 + wsp_y, a[2] - 8 + wsp_z);
		glVertex3f(b[0] - 8 + wsp_x, b[1] + 20 + wsp_y, b[2] - 8 + wsp_z);
		glVertex3f(-b[0] + 8 + wsp_x, b[1] + 20 + wsp_y, b[2] - 8 + wsp_z);
		glVertex3f(-a[0] + 8 + wsp_x, a[1] + 20 + wsp_y, a[2] - 8 + wsp_z);
		glColor3f(0.8f, 0.7f, 0.9f);
		glVertex3f(-a[0] + 8 + wsp_x, a[1] + 20 + wsp_y, -a[2] + 8 + wsp_z);
		glVertex3f(-b[0] + 8 + wsp_x, b[1] + 20 + wsp_y, -b[2] + 8 + wsp_z);
		glVertex3f(b[0] - 8 + wsp_x, b[1] + 20 + wsp_y, -b[2] + 8 + wsp_z);
		glVertex3f(a[0] - 8 + wsp_x, a[1] + 20 + wsp_y, -a[2] + 8 + wsp_z);
		glEnd();
	}
}