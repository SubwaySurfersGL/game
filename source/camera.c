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

void Textura()
{
}

void Iluminacao()
{
    GLfloat posicaoLuz[4]={0.0, 0.5, 1.0, 0.0};
    GLfloat luzAmbiente[4]={0.1, 0.1, 0.1, 1.0};
    GLfloat luzDifusa[4]={0.8, 0.8, 0.8, 1.0};
    GLfloat luzEspecular[4]={1.0, 1.0, 1.0, 1.0};

    GLfloat objeto_ambiente[4] = {0.05,0.05,0.05,1.0};
    GLfloat objeto_difusa[4] = {0.05,0.05,0.05,1.0};

    GLfloat especularidade[4]={0.1,0.1,0.1,1.0};
    GLint especMaterial = 1;

    glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz );
    glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa );
    glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular );
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 90.0);

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, objeto_ambiente);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, objeto_difusa);
    glMaterialfv(GL_FRONT,GL_SPECULAR, especularidade);
    glMateriali(GL_FRONT,GL_SHININESS,especMaterial);
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

