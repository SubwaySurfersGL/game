#include <GL/freeglut_std.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <math.h>
#include "cenario.h"
#include "camera.h"

float cenarioPosY = 0.0;

void Chao(float posY)
{
	glPushMatrix();

		glTranslatef(0, posY, 0);
		glColor3f(0.3, 0.3, 0.3);
		glScalef(9, 90, 0.5);
		glutSolidCube(1);

	glPopMatrix();
}

void DesenhaCenario(int i)
{
	glPushMatrix();
		Chao(i-90);
		Chao(i);
		Chao(i+90);
	glPopMatrix();
}

