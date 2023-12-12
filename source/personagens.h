#ifndef PERSONAGENS
#define PERSONAGENS

#include "cenario.h"


extern float personagemPosX;
extern float personagemPosY;
extern float personagemPosZ;
extern float personagemRotX;
extern float personagemRotY;
extern int isAlive;
extern int vida;

void DesenhaEsfera();
void onCollision(posicao *objeto);
void initTextureEsfera();
#endif

