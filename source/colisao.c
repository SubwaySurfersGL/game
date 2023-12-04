#include "personagens.h"

int checkCollision() {
    float personagemPosX = -44;
    float personagemPosY = -44;
    float personagemPosZ = 1.0;
    int collisionX = one.Position.x + one.Size.x >= two.Position.x &&
        two.Position.x + two.Size.x >= one.Position.x;

    int collisionY = one.Position.y + one.Size.y >= two.Position.y &&
        two.Position.y + two.Size.y >= one.Position.y;

    return collisionX && collisionY;
}  
