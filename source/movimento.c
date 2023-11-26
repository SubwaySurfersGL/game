#include <GL/gl.h>
#include <stdio.h>
#include <math.h>
#include "movimento.h"
#include "camera.h"
#include "cenario.h"
#include "personagens.h"
#include "interacao.h"

float velY = 40.0, velX = 20.0;

int metade = -1;

void VelocidadeX() { velX += 1*dt; }

void VelocidadeY() { velY += 1*dt; }

void PosicaoX()
{
	if(metade == ESQUERDA)
	{
		if(lado == 1) { VelocidadeX(); personagemPosX -= velX*dt; }
		if(lado == 1 && personagemPosX <= -2.5) { personagemPosX = -2.5; lado = 0; metade = -1; }

		if(lado == 2) { VelocidadeX(); personagemPosX += velX*dt; }
		if(lado == 2 && personagemPosX >= 0) { personagemPosX = 0; lado = 0; metade = -1; }
	}

	if(metade == DIREITA)
	{
		if(lado == 1) { VelocidadeX(); personagemPosX -= velX*dt; }
		if(lado == 1 && personagemPosX <= 0) { personagemPosX = 0; lado = 0; metade = -1; }

		if(lado == 2) { VelocidadeX(); personagemPosX += velX*dt; }
		if(lado == 2 && personagemPosX >= 2.5) { personagemPosX = 2.5; lado = 0; metade = -1; }
	}
}

void PosicaoY()
{
	VelocidadeY();

	personagemPosY += velY*dt;
	personagemRotX -= 10*velY*dt;
	camPosY += velY*dt;
	camLookY += velY*dt;
}
