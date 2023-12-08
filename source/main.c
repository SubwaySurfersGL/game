#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "cenario.h"
#include "camera.h"
#include "gravidade.h"
#include "movimento.h"
#include "personagens.h"
#include "interacao.h"
#include "colisao.h"

#define H 1000.0
#define W 1000.0

void Inicia()
{
	glEnable (GL_COLOR_MATERIAL);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);

	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
    glEnable(GL_LIGHTING);

	glEnable(GL_NORMALIZE);

	glClearColor(0.53, 0.81, 0.92, 1.0);

	srand(time(NULL));

	r = rand()%13;

	IniciaObstaculos();

	Iluminacao();
}

void Timer(int v)
{
	glutPostRedisplay();

	glutTimerFunc(40, Timer, v);
}

void Desenha()
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	glPushMatrix();
		Camera();
		DesenhaCenario(indiceChao);
		DesenhaEsfera();
		CheckBottomCollision();
		if(flagColisao)
		{
			TimeMove();
			PosicaoX();
			PosicaoY();
			PosicaoZ();
		}
		if(personagemPosY > (indiceChao+125)) { indiceChao += 250; }
	glPopMatrix();

	glutSwapBuffers();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(W, H);
	glutCreateWindow("Subway Surfers");
	glutDisplayFunc(Desenha);
	glutKeyboardFunc(Keyboard);
	glutTimerFunc(0, Timer, 0);
	Inicia();
	glutMainLoop();

	return 0;
}

