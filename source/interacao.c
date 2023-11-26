#include <GL/gl.h>
#include <stdio.h>
#include <math.h>
#include "camera.h"
#include "gravidade.h"
#include "personagens.h"
#include "movimento.h"

#define H 1000.0
#define W 1000.0

int pulo = 0, lado = 0;

void Keyboard(unsigned char c, int x, int y)
{
	switch(c)
	{
		case 'a':
			if(personagemPosX <= 0) { metade = ESQUERDA; }
			else if(personagemPosX > 0) { metade = DIREITA; }
			lado = 1;
		break;

		case 'd':
			if(personagemPosX < 0) { metade = ESQUERDA; }
			else if(personagemPosX >= 0) { metade = DIREITA; }
			lado = 2;
		break;

		case 'w':
			velZ = 0;
			pulo = 1;
		break;

		default:
		break;

	}
	glutPostRedisplay();
}
