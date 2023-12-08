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
		case ' ':
			if(flagColisao == 0)
			{
				personagemPosX = 0;
				personagemPosY = -124;
				camPosY = -135;
				camLookY = 0;
				velY = 40;
				indiceChao = 0;
				r = rand()%13;
				flagColisao = 1;
			}
		break;

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

