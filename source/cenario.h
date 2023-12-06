#ifndef CENARIO
#define CENARIO

#define ESCALA_X 1.0/sqrt(2)
#define ESCALA_Y 1.0/sqrt(2)
#define ESCALA_Z 1.0/sqrt(0.7)
#define ITERACOES 4
#define PEQUENO 0
#define GRANDE 1
#define N_OBS 5

typedef struct posicao
{
	int flag;
	float posX, posY;
} posicao;

extern posicao obstaculos[N_OBS];
extern int indiceChao;

void DesenhaCenario(int i);
void IniciaObstaculos();

#endif
