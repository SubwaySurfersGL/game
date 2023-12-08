#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <math.h>
#include <stdlib.h>
#include "cenario.h"
#include "camera.h"
#include "colisao.h"

posicao obstaculosAnt[N_OBS];
posicao obstaculosAtual[N_OBS];
posicao obstaculosProx[N_OBS];
posicao *possiveis[13];

int indiceChao = 0;

int posicoesY[N_OBS];

unsigned int r = 0;

void IniciaObstaculos()
{
	int i, j;
	int tipo[2] = { 0, 1 };
	float posicoesX[3] = { -2.5, 0, 2.5 };

	int posChao = -160;

	for(j = 0; j < N_OBS; j++)
	{
		posicoesY[j] = posChao;
		posChao += 20;
	}

	for(i = 0; i < 13; i++) { possiveis[i] = malloc(N_OBS*sizeof(posicao)); }

	for(i = 0; i < 13; i++)
	{
		for(j = 0; j < N_OBS; j++)
		{
			possiveis[i][j].flag = tipo[rand()%2];
			possiveis[i][j].posX = posicoesX[rand()%3];
		}
	}

}

void SetObstaculos(posicao *obstaculos, int indiceChao)
{
	int j;

	for(j = 0; j < N_OBS; j++)
	{
		obstaculos[j].flag = possiveis[r][j].flag;
		obstaculos[j].posX = possiveis[r][j].posX;
		obstaculos[j].posY = posicoesY[j] + indiceChao;
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

		DesenhaPlanta(-9, -242);
		DesenhaPlanta(9, -219.5);
		DesenhaPlanta(-9, -197);
		DesenhaPlanta(9, -174.5);
		DesenhaPlanta(-9, -152);
		DesenhaPlanta(9, -130);
		DesenhaPlanta(-9, -107.5);
		DesenhaPlanta(9, -85);
		DesenhaPlanta(-9, -62.5);
		DesenhaPlanta(8, -40);
		DesenhaPlanta(-8, -40);
		DesenhaPlanta(8, -17.5);
		DesenhaPlanta(-8, -17.5);
		DesenhaPlanta(7, 22.5);
		DesenhaPlanta(-7, 22.5);
		DesenhaPlanta(7, 67.5);
		DesenhaPlanta(-7, 45);
		DesenhaPlanta(-8, 90);
		DesenhaPlanta(8, 112.5);
		DesenhaPlanta(-8, 125);
		DesenhaPlanta(8, 147.5);
		DesenhaPlanta(-8, 170);
		DesenhaPlanta(8, 192.5);
		DesenhaPlanta(-8, 215);

		glPushMatrix();
			glColor3f(0.45, 0.35, 0.27);
			glScalef(9, 450, 0.5);
			glutSolidCube(1);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(-10.5, 0, 0);
			glColor3f(0.11, 0.39, 0.05);
			glScalef(12, 450, 0.9);
			glutSolidCube(1);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(10.5, 0, 0);
			glColor3f(0.11, 0.39, 0.05);
			glScalef(12, 450, 0.9);
			glutSolidCube(1);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(15, 0, 0);
			glColor3f(0.11, 0.39, 0.05);
			glScalef(1, 450, 10);
			glutSolidCube(1);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(-15, 0, 0);
			glColor3f(0.11, 0.39, 0.05);
			glScalef(1, 450, 10);
			glutSolidCube(1);
		glPopMatrix();
	glPopMatrix();
}

void DesenhaCenario(int i)
{
	int j;

	glPushMatrix();
		glColor3f(0.11, 0.19, 0.05);
		glTranslatef(0, camLookY-100, 0);
		glScalef(33, 1, 9);
		glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(0, 0, -0.4);
		glScalef(1, 1, 1.1);
		DesenhaPlanta(-15, camLookY-207.5);
		DesenhaPlanta(-15, camLookY-185);
		DesenhaPlanta(-15, camLookY-162.5);
		DesenhaPlanta(-15, camLookY-140);
		DesenhaPlanta(-15, camLookY-117.5);
		DesenhaPlanta(15, camLookY-117.5);
		DesenhaPlanta(15, camLookY-140);
		DesenhaPlanta(15, camLookY-162.5);
		DesenhaPlanta(15, camLookY-185);
		DesenhaPlanta(15, camLookY-207.5);
	glPopMatrix();
	glPushMatrix();
		DesenhaPlanta(-3, camLookY-110);
		DesenhaPlanta(3, camLookY-110);
		DesenhaPlanta(-4, camLookY-105);
		DesenhaPlanta(4, camLookY-105);
		DesenhaPlanta(-8, camLookY-105);
		DesenhaPlanta(8, camLookY-105);
		glScalef(1, 1, 1.2);
		DesenhaPlanta(-12, camLookY-105);
		DesenhaPlanta(12, camLookY-105);
		DesenhaPlanta(0, camLookY);
	glPopMatrix();

	glPushMatrix();
		SetObstaculos(obstaculosAnt, i-450);
		SetObstaculos(obstaculosAtual, i);
		SetObstaculos(obstaculosProx, i+450);
		for(j = 0; j < N_OBS; j++)
		{
			Obstaculos(obstaculosAnt[j].flag, obstaculosAnt[j].posX, obstaculosAnt[j].posY);
			Obstaculos(obstaculosAtual[j].flag, obstaculosAtual[j].posX, obstaculosAtual[j].posY);
			Obstaculos(obstaculosProx[j].flag, obstaculosProx[j].posX, obstaculosProx[j].posY);
		}
		Chao(i-450);
		Chao(i);
		Chao(i+450);
	glPopMatrix();
}

