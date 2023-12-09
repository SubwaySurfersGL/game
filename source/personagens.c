#include <GL/freeglut_std.h>
#include "personagens.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdio.h>

float personagemPosX = 0;
float personagemPosY = -223;
float personagemPosZ = 1.0;
float personagemRotX = 0;
float personagemRotY = 0;
int isAlive = 1;
int vida = 2;

void DesenhaEsfera()
{
	glPushMatrix();
		glColor3f(0.7, 0.8, 0.7);
		glTranslatef(personagemPosX, personagemPosY, personagemPosZ + 0.5);
		glutSolidSphere(0.3, 50, 50);
	glPopMatrix();

	glPushMatrix();
		glColor3f(0.9, 1, 0.9);
		glTranslatef(personagemPosX, personagemPosY, personagemPosZ);
		glPushMatrix();
			glRotatef(personagemRotX, 1, 0, 0);
			glRotatef(personagemRotY, 0, 1, 0);
			glutSolidSphere(0.5, 50, 50);
		glPopMatrix();
	glPopMatrix();
}

void onCollision(posicao *objeto) {
	if (objeto->flag == GRANDE) {
		vida -= 2;
	}
	else {
		vida--;
	}
	if (vida <= 0) {
		isAlive = 0;
	}
}
