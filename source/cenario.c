#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "cenario.h"
#include "camera.h"
#include "colisao.h"

typedef struct BMPImagem
{
    int   width;
    int   height;
    char *data;
}BMPImage;

posicao obstaculosAnt[N_OBS];
posicao obstaculosAtual[N_OBS];
posicao obstaculosProx[N_OBS];
posicao *possiveis[13];

int indiceChao = 0;

int posicoesY[N_OBS];

unsigned int r = 0;

#define MAX_NO_TEXTURES 3

GLuint texture_id[MAX_NO_TEXTURES];
char* filenameArray[MAX_NO_TEXTURES] = {
        "chaoTextura.bmp",
        "gramaTextura.bmp",
		"caixaTextura.bmp"
};

void getBitmapImageData( char *pFileName, BMPImage *pImage )
{
    FILE *pFile = NULL;
    unsigned short nNumPlanes;
    unsigned short nNumBPP;
    int i;

    if( (pFile = fopen(pFileName, "rb") ) == NULL )
        printf("ERROR: getBitmapImageData - %s not found.\n", pFileName);

    // Seek forward to width and height info
    fseek( pFile, 18, SEEK_CUR );

    if( (i = fread(&pImage->width, 4, 1, pFile) ) != 1 )
        printf("ERROR: getBitmapImageData - Couldn't read width from %s.\n ", pFileName);

    if( (i = fread(&pImage->height, 4, 1, pFile) ) != 1 )
        printf("ERROR: getBitmapImageData - Couldn't read height from %s.\n ", pFileName);

    if( (fread(&nNumPlanes, 2, 1, pFile) ) != 1 )
        printf("ERROR: getBitmapImageData - Couldn't read plane count from %s.\n", pFileName);

    if( nNumPlanes != 1 )
        printf("ERROR: getBitmapImageData - Plane count from %s.\n ", pFileName);

    if( (i = fread(&nNumBPP, 2, 1, pFile)) != 1 )
        printf( "ERROR: getBitmapImageData - Couldn't read BPP from %s.\n ", pFileName);

    if( nNumBPP != 24 )
        printf("ERROR: getBitmapImageData - BPP from %s.\n ", pFileName);

    // Seek forward to image data
    fseek( pFile, 24, SEEK_CUR );

    // Calculate the image's total size in bytes. Note how we multiply the
    // result of (width * height) by 3. This is becuase a 24 bit color BMP
    // file will give you 3 bytes per pixel.
    int nTotalImagesize = (pImage->width * pImage->height) * 3;

    pImage->data = (char*) malloc( nTotalImagesize );

    if( (i = fread(pImage->data, nTotalImagesize, 1, pFile) ) != 1 )
        printf("ERROR: getBitmapImageData - Couldn't read image data from %s.\n ", pFileName);

    //
    // Finally, rearrange BGR to RGB
    //

    char charTemp;
    for( i = 0; i < nTotalImagesize; i += 3 )
    {
        charTemp = pImage->data[i];
        pImage->data[i] = pImage->data[i+2];
        pImage->data[i+2] = charTemp;
    }
}

void CarregaTexturas()
{
    BMPImage textura;

    /* Define quantas texturas serão usadas no programa  */
    glGenTextures(MAX_NO_TEXTURES, texture_id); /* 1 = uma textura; */
                                /* texture_id = vetor que guardas os números das texturas */

    int i;
    for ( i=0; i<MAX_NO_TEXTURES; i++ ) {
        getBitmapImageData( filenameArray[i], &textura);
        glBindTexture(GL_TEXTURE_2D, texture_id[i]);
        glTexImage2D(GL_TEXTURE_2D, 0, 3, textura.width, textura.height, 0, GL_RGB, GL_UNSIGNED_BYTE, textura.data);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    }
}

void initTexture (void)
{

    /* Habilita o uso de textura bidimensional  */
    glEnable ( GL_TEXTURE_2D );
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    /*Carrega os arquivos de textura */
  //  CarregaTextura("tunnelTexture.bmp");
    //CarregaTextura("tex2.bmp");
    CarregaTexturas();

}

void drawBox(GLfloat size, GLenum type, int textura)
{
	GLfloat n[6][3] =
	{
		{-1.0, 0.0, 0.0},
		{0.0, 1.0, 0.0},
		{1.0, 0.0, 0.0},
		{0.0, -1.0, 0.0},
		{0.0, 0.0, 1.0},
		{0.0, 0.0, -1.0}
	};
	GLint faces[6][4] =
	{
		{0, 1, 2, 3},
		{3, 2, 6, 7},
		{7, 6, 5, 4},
		{4, 5, 1, 0},
		{5, 6, 2, 1},
		{7, 4, 0, 3}
	};
	GLfloat v[8][3];
	GLint i;

	v[0][0] = v[1][0] = v[2][0] = v[3][0] = -size / 2;
	v[4][0] = v[5][0] = v[6][0] = v[7][0] = size / 2;
	v[0][1] = v[1][1] = v[4][1] = v[5][1] = -size / 2;
	v[2][1] = v[3][1] = v[6][1] = v[7][1] = size / 2;
	v[0][2] = v[3][2] = v[4][2] = v[7][2] = -size / 2;
	v[1][2] = v[2][2] = v[5][2] = v[6][2] = size / 2;

	for (i = 5; i >= 0; i--) {
		glBindTexture(GL_TEXTURE_2D, texture_id[textura]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
		glBegin(type);
			glNormal3fv(&n[i][0]);
			glTexCoord2f(0.0f,0.0f);
			glVertex3fv(&v[faces[i][0]][0]);
			glTexCoord2f(1.0f,0.0f);
			glVertex3fv(&v[faces[i][1]][0]);
			glTexCoord2f(1.0f,1.0f);
			glVertex3fv(&v[faces[i][2]][0]);
			glTexCoord2f(0.0f,1.0f);
			glVertex3fv(&v[faces[i][3]][0]);
		glEnd();
	}
}

void glutSolidCube1(GLdouble size, int textura)
{
	drawBox(size, GL_QUADS, textura);
}



void IniciaObstaculos()
{
	int i, j;
	int tipo[2] = { 0, 1 };
	float posicoesX[3] = { -2.5, 0, 2.5 };

	int posChao = -160;

	for(j = 0; j < N_OBS; j++)
	{
		posicoesY[j] = posChao;
		posChao += 20;
	}

	for(i = 0; i < 13; i++) { possiveis[i] = malloc(N_OBS*sizeof(posicao)); }

	for(i = 0; i < 13; i++)
	{
		for(j = 0; j < N_OBS; j++)
		{
			possiveis[i][j].flag = tipo[rand()%2];
			possiveis[i][j].posX = posicoesX[rand()%3];
		}
	}

}

void SetObstaculos(posicao *obstaculos, int indiceChao)
{
	int j;

	for(j = 0; j < N_OBS; j++)
	{
		obstaculos[j].flag = possiveis[r][j].flag;
		obstaculos[j].posX = possiveis[r][j].posX;
		obstaculos[j].posY = posicoesY[j] + indiceChao;
	}
}

void ObstaculoGrande()
{
	glPushMatrix();
		// glColor3f(0.63, 0.63, 0.4);
		glScalef(2, 9, 3);
		glTranslatef(0, 0, 1);
		glutSolidCube1(1, 2);
	glPopMatrix();
}

void ObstaculoPequeno()
{ glPushMatrix();
		// glColor3f(0.5, 0.5, 0.5);
		glScalef(2, 2, 1.5);
		glTranslatef(0, 0, 1);
		glutSolidCube1(1, 2);
	glPopMatrix();
}

void Obstaculos(int flag, float posX, float posY)
{
	glPushMatrix();
		glTranslatef(posX, posY, 0);
		if(flag == GRANDE) { ObstaculoGrande(); }
		if(flag == PEQUENO) { ObstaculoPequeno(); }
	glPopMatrix();
}

void Planta(int it)
{
	if(it > ITERACOES) { return; }

	glPushMatrix();
		glTranslatef(-0.1, 0.2, 0.0);
		glRotatef(45, 0, 0, 1);
		glScalef(ESCALA_X, ESCALA_Y, ESCALA_Z);
		Planta(it+1);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(0.1, 0.2, 0);
		glRotatef(-45, 0, 0, 1);
		glScalef(ESCALA_X, ESCALA_Y, ESCALA_Z);
		Planta(it+1);
	glPopMatrix();

	glColor3f(0.4-(0.5/10)*it, 0.2+(0.75/10)*it, 0);
	glutSolidCube(0.25);
}

void DesenhaPlanta(float posX, float posY)
{
	glPushMatrix();
		glTranslatef(posX, posY, 2);
		glRotatef(90, 1, 0, 0);
		glScalef(9, 9, 9);
		Planta(0);
	glPopMatrix();
}

void Chao(float posY)
{
	glPushMatrix();
		glTranslatef(0, posY, 0);

		DesenhaPlanta(-9, -242);
		DesenhaPlanta(9, -219.5);
		DesenhaPlanta(-9, -197);
		DesenhaPlanta(9, -174.5);
		DesenhaPlanta(-9, -152);
		DesenhaPlanta(9, -130);
		DesenhaPlanta(-9, -107.5);
		DesenhaPlanta(9, -85);
		DesenhaPlanta(-9, -62.5);
		DesenhaPlanta(8, -40);
		DesenhaPlanta(-8, -40);
		DesenhaPlanta(8, -17.5);
		DesenhaPlanta(-8, -17.5);
		DesenhaPlanta(7, 22.5);
		DesenhaPlanta(-7, 22.5);
		DesenhaPlanta(7, 67.5);
		DesenhaPlanta(-7, 45);
		DesenhaPlanta(-8, 90);
		DesenhaPlanta(8, 112.5);
		DesenhaPlanta(-8, 125);
		DesenhaPlanta(8, 147.5);
		DesenhaPlanta(-8, 170);
		DesenhaPlanta(8, 192.5);
		DesenhaPlanta(-8, 215);

		glPushMatrix();
			glColor3f(0.45, 0.35, 0.27);
			glScalef(9, 450, 0.5);
			glutSolidCube1(1, 0);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(-10.5, 0, 0);
			glColor3f(0.11, 0.39, 0.05);
			glScalef(12, 450, 0.9);
			glutSolidCube1(1, 1);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(10.5, 0, 0);
			glColor3f(0.11, 0.39, 0.05);
			glScalef(12, 450, 0.9);
			glutSolidCube1(1, 1);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(15, 0, 0);
			glColor3f(0.11, 0.39, 0.05);
			glScalef(1, 450, 10);
			glutSolidCube(1);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(-15, 0, 0);
			glColor3f(0.11, 0.39, 0.05);
			glScalef(1, 450, 10);
			glutSolidCube(1);
		glPopMatrix();
	glPopMatrix();
}

void DesenhaCenario(int i) {
	int j;

	glPushMatrix();
		glColor3f(0.11, 0.19, 0.05);
		glTranslatef(0, camLookY-100, 0);
		glScalef(33, 1, 9);
		glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(0, 0, -0.4);
		glScalef(1, 1, 1.1);
		DesenhaPlanta(-15, camLookY-207.5);
		DesenhaPlanta(-15, camLookY-185);
		DesenhaPlanta(-15, camLookY-162.5);
		DesenhaPlanta(-15, camLookY-140);
		DesenhaPlanta(-15, camLookY-117.5);
		DesenhaPlanta(15, camLookY-117.5);
		DesenhaPlanta(15, camLookY-140);
		DesenhaPlanta(15, camLookY-162.5);
		DesenhaPlanta(15, camLookY-185);
		DesenhaPlanta(15, camLookY-207.5);
	glPopMatrix();
	glPushMatrix();
		DesenhaPlanta(-3, camLookY-110);
		DesenhaPlanta(3, camLookY-110);
		DesenhaPlanta(-4, camLookY-105);
		DesenhaPlanta(4, camLookY-105);
		DesenhaPlanta(-8, camLookY-105);
		DesenhaPlanta(8, camLookY-105);
		glScalef(1, 1, 1.2);
		DesenhaPlanta(-12, camLookY-105);
		DesenhaPlanta(12, camLookY-105);
		DesenhaPlanta(0, camLookY);
	glPopMatrix();

	glPushMatrix();
		SetObstaculos(obstaculosAnt, i-450);
		SetObstaculos(obstaculosAtual, i);
		SetObstaculos(obstaculosProx, i+450);
		for(j = 0; j < N_OBS; j++)
		{
			Obstaculos(obstaculosAnt[j].flag, obstaculosAnt[j].posX, obstaculosAnt[j].posY);
			Obstaculos(obstaculosAtual[j].flag, obstaculosAtual[j].posX, obstaculosAtual[j].posY);
			Obstaculos(obstaculosProx[j].flag, obstaculosProx[j].posX, obstaculosProx[j].posY);
		}
		Chao(i-450);
		Chao(i);
		Chao(i+450);
	glPopMatrix();
}

