#include <GL/gl.h>
#include <stdio.h>
#include <math.h>
#include "gravidade.h"
#include "camera.h"
#include "cenario.h"
#include "personagens.h"

#define gravidade 9.81
#define massa 5

float vel = 0.0, peso = 0.0;

float dt = 0.0, oldt = 0.0;

void TimeMove()
{
	int t;

	t = glutGet(GLUT_ELAPSED_TIME);

	dt = (t - oldt) / 2000.0;

	oldt = t;
}

void Aceleracao()
{
	peso = massa * gravidade;
}

void Velocidade()
{
	Aceleracao();
	vel += peso*dt;
}

void Posicao()
{
	TimeMove();
	Velocidade();

	if(posZ >= 0.5) { posZ -= vel*dt; }
}
