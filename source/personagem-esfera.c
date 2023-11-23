#include <GL/freeglut_std.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include "personagens.h"

float posY = -20;
float posZ = 0.5;
float rotX = 0;

void DesenhaEsfera()
{
	glPushMatrix();
		glColor3f(0.7, 0.8, 0.7);
		glTranslatef(0, posY, posZ + 0.5);
		glutSolidSphere(0.3, 50, 50);
	glPopMatrix();

	glPushMatrix();
		glColor3f(0.9, 1, 0.9);
		glTranslatef(0, posY, posZ);
		glPushMatrix();
			glRotatef(rotX, 1, 0, 0);
			glutSolidSphere(0.5, 50, 50);
		glPopMatrix();
	glPopMatrix();
}
