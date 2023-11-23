#include <GL/freeglut_std.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <math.h>
#include "cenario.h"
#include "camera.h"

void chao()
{
	glPushMatrix();

		glColor3f(0.3, 0.3, 0.3);
		glScalef(5, 50, 0.05);
		glutSolidCube(1);

	glPopMatrix();

}

void DesenhaCenario()
{
	glPushMatrix();
		chao();
	glPopMatrix();
}

