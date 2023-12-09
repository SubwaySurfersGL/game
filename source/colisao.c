#include "personagens.h"
#include "movimento.h"
#include "cenario.h"
#include "colisao.h"
#include "stdlib.h"
#include "stdio.h"

posicao *colisao;

posicao *checkCollision() {
    float altura = 1.;

    for(int obstaculoIndex = 0; obstaculoIndex < N_OBS; obstaculoIndex++) {
        posicao posicaoObject = obstaculosAtual[obstaculoIndex];
        if (
            colisao &&
            posicaoObject.flag == colisao->flag &&
            posicaoObject.posX == colisao->posX &&
            posicaoObject.posY == colisao->posY
        ) continue;
        int colisaoX = personagemPosX >= posicaoObject.posX && personagemPosX <= posicaoObject.posX + 2.;
        int colisaoY;
        int colisaoZ;
        
        if(posicaoObject.flag == GRANDE) {
            colisaoY = personagemPosY >= posicaoObject.posY - 5. && personagemPosY <= posicaoObject.posY  + 9.;
            colisaoZ = personagemPosZ - altura <= 3.;
        }
        else {
            colisaoY = personagemPosY >= posicaoObject.posY - 1.25 && personagemPosY <= posicaoObject.posY + 2.;
            colisaoZ = personagemPosZ - altura <= 1.5;
        }

        if (colisaoX && colisaoY && colisaoZ) {
            colisao = (posicao *) malloc(sizeof(posicaoObject));
            colisao->flag = posicaoObject.flag;
            colisao->posX = posicaoObject.posX;
            colisao->posY = posicaoObject.posY;
            return colisao;
		}
    }
    return NULL;
}

