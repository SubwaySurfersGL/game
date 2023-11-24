#include <GL/gl.h>
#include <stdio.h>
#include <math.h>
#include "camera.h"
#include "gravidade.h"
#include "personagens.h"

#define H 1000.0
#define W 1000.0

int zoom = 45;

float camPosY = -55, camLookY = 0;

void Camera()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
    gluPerspective(zoom, W/H, 10, 100);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0, camPosY, 5, 0, camLookY, 0, 0, 0, 1);
}

void Keyboard(unsigned char c, int x, int y)
{
	switch(c)
	{
		case 'a':
			if(posX >= -2.5) { posX -= 2.5; }
			rotY += 10;
		break;

		case 'd':
			if(posX <= 2.5) { posX += 2.5; }
			rotY -= 10;
		break;

		case 'p':
			vel = 0;
			if(posZ <= 2.5) { posZ += 2; }
		break;

		case 'w':
			posY += 1;
			rotX += 10;
			camPosY += 1;
			camLookY += 1;
		break;

		case 's':
			posY -= 1;
			rotX -= 10;
			camPosY -= 1;
			camLookY -= 1;
		break;

		case 'i':
			if(zoom > 15)
				zoom -= 5;
		break;

		case 'o':
			if(zoom <= 150)
				zoom += 5;
		break;

		default:
		break;

	}
	Camera();
	glutPostRedisplay();
}

