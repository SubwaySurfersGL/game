#include <GL/gl.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "camera.h"
#include "cenario.h"
#include "gravidade.h"
#include "personagens.h"
#include "movimento.h"
#include "colisao.h"

#define H 1000.0
#define W 1000.0

int pulo = 0, lado = 0;

void Keyboard(unsigned char c, int x, int y)
{
	switch(c)
	{
		case'R':
		case 'r':
			if(isAlive == 0) {
				personagemPosX = 0;
				personagemPosY = -223;
				personagemPosZ = 1.0;
				camPosY = -235;
				camLookY = 0;
				velY = 40;
				indiceChao = 0;
				r = rand()%13;
				vida = 2;
				isAlive = 1;
			}
		break;

		case 'A':
		case 'a':
			if(personagemPosX <= 0) { metade = ESQUERDA; }
			else if(personagemPosX > 0) { metade = DIREITA; }
			lado = 1;
		break;

		case 'D':
		case 'd':
			if(personagemPosX < 0) { metade = ESQUERDA; }
			else if(personagemPosX >= 0) { metade = DIREITA; }
			lado = 2;
		break;

		case 'W':
		case 'w':
			velZ = 0;
			pulo = 1;
		break;

		default:
		break;

	}
	glutPostRedisplay();
}

