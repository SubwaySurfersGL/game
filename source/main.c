#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdio.h>
#include "cenario.h"
#include "camera.h"
#include "gravidade.h"
#include "personagens.h"

#define H 1000.0
#define W 1000.0

int indiceChao = 0;

void Inicia()
{
	glEnable(GL_DEPTH_TEST);

	glClearColor(0.0, 0.0, 0.0, 1.0);
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
		Posicao();
		if(posY > (indiceChao+22.5)) { indiceChao += 45; }
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

