#include <GL/gl.h>
#include <stdio.h>
#include <math.h>
#include "gravidade.h"
#include "camera.h"
#include "cenario.h"
#include "personagens.h"
#include "interacao.h"

#define DESCER 0
#define SUBIR 1

float velZ = 0.0, peso = 400.0, forca = 200.0;

void VelocidadeZ(int flag)
{
	if(flag == DESCER) { velZ -= peso * dt; }
	else if(flag == SUBIR) { velZ += forca * dt; }
}

void PosicaoZ()
{
	if(pulo == 1 && personagemPosZ < 3.5) { VelocidadeZ(SUBIR); personagemPosZ += velZ*dt; }

	else if(personagemPosZ >= 3.5) { pulo = 0; velZ = 0; }

	if(pulo == 0 && personagemPosZ > 1.5) { VelocidadeZ(DESCER); personagemPosZ += velZ*dt; }
}
