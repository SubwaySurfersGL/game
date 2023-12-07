#include "personagens.h"
#include "cenario.h"
#include "stdio.h"
#include "stdlib.h"
#include "movimento.h"

int flag = 1;

int checkBottomCollision() {
    /*
        Função faz a verificação se o personagem faz contato com o topo do obstáculo
    */
    float autura = 1.;

    for (int obstaculoIndex = 0; obstaculoIndex < N_OBS; obstaculoIndex++) {
        posicao posicao = obstaculos[obstaculoIndex];
        int colisaoX = personagemPosX >= posicao.posX && personagemPosX <= posicao.posX + 2.;
        int colisaoY;
        int colisaoZ;
        if (posicao.flag == GRANDE) {
            colisaoY = personagemPosY >= posicao.posY + indiceChao-5.0 && personagemPosY <= posicao.posY + indiceChao + 9.;
            colisaoZ = personagemPosZ - autura <= 3.;
        } else {
            colisaoY = personagemPosY >= posicao.posY + indiceChao-1.25 && personagemPosY <= posicao.posY + indiceChao + 2.;
            colisaoZ = personagemPosZ - autura <= 1.5;
        }
        if (colisaoX && colisaoY && colisaoZ){
	    flag = 0;
            return 1;
	}
    }
    return 0;
}

int checkFrontCollision() {
    /*
        Função faz a verificação se o personagem faz contato com alguma das faces do obstáculo
    */
    for (int obstaculoIndex = 0; obstaculoIndex < N_OBS; obstaculoIndex++) {

    }
    return 0;
}
