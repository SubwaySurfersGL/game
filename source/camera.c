#include <GL/gl.h>
#include <stdio.h>
#include <math.h>
#include "camera.h"
#include "gravidade.h"
#include "personagens.h"

#define H 1000.0
#define W 1000.0

int zoom = 45;

float camPosY = -235, camLookY = 0;

float dt = 0.0, oldt = 0.0;

void Iluminacao()
{
    GLfloat light0_pos[4]={1.0, 0.5, 1.0, 0.0};
    GLfloat white[4]={1.0, 1.0, 1.0, 1.0};
    GLfloat black[4]={0.0, 0.0, 0.0, 1.0};

    glLightfv(GL_LIGHT0, GL_POSITION, light0_pos);
    glLightfv(GL_LIGHT0, GL_AMBIENT, black);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, white);
    glLightfv(GL_LIGHT0, GL_SPECULAR, white);

	GLfloat global_ambient[] = {0.7, 0.7, 0.7, 1.0};
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);
}

void Camera()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
    gluPerspective(zoom, W/H, 1, 461);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0, camPosY, 5, 0, camLookY, 0, 0, 0, 1);
}

void TimeMove()
{
	int t;

	t = glutGet(GLUT_ELAPSED_TIME);

	dt = (t - oldt) / 2000.0;

	oldt = t;
}

