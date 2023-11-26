#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <math.h>
#include "cenario.h"
#include "camera.h"

#define PEQUENO 0
#define GRANDE 1

#define N_OBS 5

typedef struct posicao
{
	int flag;
	float posX, posY;
} posicao;

float cenarioPosY = 0.0;

posicao obstaculos[N_OBS];

void IniciaObstaculos()
{
	int i;

	for(i = 0; i < N_OBS; i++)
	{
		obstaculos[i].flag = (i*i*i)%2;

		if((i)%3 == 1) { obstaculos[i].posX = -2.5; }
		else if((i)%3 == 2) { obstaculos[i].posX = 2.5; }
		else { obstaculos[i].posX = 0; }

		if(i == 0) { obstaculos[i].posY = 0; }
		else { obstaculos[i].posY = powf(-1, (i+1))*(45.0/i); }
	}
}

void ObstaculoGrande()
{
	glPushMatrix();
		glColor3f(0.63, 0.63, 0.4);
		glScalef(2, 9, 3);
		glTranslatef(0, 0, 1);
		glutSolidCube(1);
	glPopMatrix();
}

void ObstaculoPequeno()
{ glPushMatrix();
		glColor3f(0.5, 0.5, 0.5);
		glScalef(2, 2, 1.5);
		glTranslatef(0, 0, 1);
		glutSolidCube(1);
	glPopMatrix();
}

void Obstaculos(int flag, float posX, float posY)
{
	glPushMatrix();
		glTranslatef(posX, posY, 0);
		if(flag == GRANDE) { ObstaculoGrande(); }
		if(flag == PEQUENO) { ObstaculoPequeno(); }
	glPopMatrix();
}

void Planta(int it)
{
	if(it > ITERACOES) { return; }

	glPushMatrix();
		glTranslatef(-0.1, 0.2, 0.0);
		glRotatef(45, 0, 0, 1);
		glScalef(ESCALA_X, ESCALA_Y, ESCALA_Z);
		Planta(it+1);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(0.1, 0.2, 0);
		glRotatef(-45, 0, 0, 1);
		glScalef(ESCALA_X, ESCALA_Y, ESCALA_Z);
		Planta(it+1);
	glPopMatrix();

	glColor3f(0.4-(0.5/10)*it, 0.2+(0.75/10)*it, 0);
	glutSolidCube(0.25);
}

void DesenhaPlanta(float posX, float posY)
{
	glPushMatrix();
		glTranslatef(posX, posY, 2);
		glRotatef(90, 1, 0, 0);
		glScalef(9, 9, 9);
		Planta(0);
	glPopMatrix();
}

void Chao(float posY)
{
	glPushMatrix();
		glTranslatef(0, posY, 0);

		DesenhaPlanta(-8, -22.5);
		DesenhaPlanta(-7, 22.5);
		DesenhaPlanta(8, 0);
		DesenhaPlanta(7, 22.5);
		DesenhaPlanta(-8, -22.5);

		glPushMatrix();
			glColor3f(0.45, 0.35, 0.27);
			glScalef(9, 90, 0.5);
			glutSolidCube(1);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(-10.5, 0, 0);
			glColor3f(0.11, 0.39, 0.05);
			glScalef(12, 90, 0.9);
			glutSolidCube(1);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(10.5, 0, 0);
			glColor3f(0.11, 0.39, 0.05);
			glScalef(12, 90, 0.9);
			glutSolidCube(1);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(15, 0, 0);
			glColor3f(0.11, 0.39, 0.05);
			glScalef(1, 90, 10);
			glutSolidCube(1);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(-15, 0, 0);
			glColor3f(0.11, 0.39, 0.05);
			glScalef(1, 90, 10);
			glutSolidCube(1);
		glPopMatrix();
	glPopMatrix();
}

void DesenhaCenario(int i)
{
	int j;

	glPushMatrix();
		glColor3f(0.11, 0.19, 0.05);
		glTranslatef(0, camLookY+40, 0);
		glScalef(33, 1, 9);
		glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(0, 0, -0.4);
		glScalef(1, 1, 1.1);
		DesenhaPlanta(-15, camLookY-22.5);
		DesenhaPlanta(-15, camLookY);
		DesenhaPlanta(-15, camLookY+22.5);
		DesenhaPlanta(15, camLookY-22.5);
		DesenhaPlanta(15, camLookY);
		DesenhaPlanta(15, camLookY+22.5);
	glPopMatrix();

	glPushMatrix();
		DesenhaPlanta(-3, camLookY+30);
		DesenhaPlanta(3, camLookY+30);
		DesenhaPlanta(-4, camLookY+35);
		DesenhaPlanta(4, camLookY+35);
		DesenhaPlanta(-8, camLookY+35);
		DesenhaPlanta(8, camLookY+35);
		glScalef(1, 1, 1.2);
		DesenhaPlanta(-12, camLookY+30);
		DesenhaPlanta(12, camLookY+30);
		DesenhaPlanta(0, camLookY+40);
	glPopMatrix();

	glPushMatrix();
		for(j = 0; j < N_OBS; j++)
		{
			Obstaculos(obstaculos[j].flag, obstaculos[j].posX, obstaculos[j].posY+i);
			Obstaculos(obstaculos[j].flag, obstaculos[j].posX, obstaculos[j].posY+i+90);
		}
		Chao(i-90);
		Chao(i);
		Chao(i+90);
	glPopMatrix();
}

