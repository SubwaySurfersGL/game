#include <GL/freeglut_std.h>
#include "personagens.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdio.h>

typedef struct BMPImagem
{
    int   width;
    int   height;
    char *data;
}BMPImage;

/* Qtd máxima de texturas a serem usadas no programa */
#define MAX_NO_TEXTURES 2

/* vetor com os números das texturas */
GLuint texture_id_personagem[MAX_NO_TEXTURES];

char* filenameArray_personagem[MAX_NO_TEXTURES] = {
        "corpoTextura.bmp",
        "cabecaTextura.bmp"
};

GLUquadricObj *obj;

//-----------------------------------------------------------------------------
// Name: getBitmapImageData_personagem()
// Desc: Simply image loader for 24 bit BMP files.
//-----------------------------------------------------------------------------
void getBitmapImageData_personagem( char *pFileName, BMPImage *pImage )
{
    FILE *pFile = NULL;
    unsigned short nNumPlanes;
    unsigned short nNumBPP;
    int i;

    if( (pFile = fopen(pFileName, "rb") ) == NULL )
        printf("ERROR: getBitmapImageData_personagem - %s not found.\n", pFileName);

    // Seek forward to width and height info
    fseek( pFile, 18, SEEK_CUR );

    if( (i = fread(&pImage->width, 4, 1, pFile) ) != 1 )
        printf("ERROR: getBitmapImageData_personagem - Couldn't read width from %s.\n ", pFileName);

    if( (i = fread(&pImage->height, 4, 1, pFile) ) != 1 )
        printf("ERROR: getBitmapImageData_personagem - Couldn't read height from %s.\n ", pFileName);

    if( (fread(&nNumPlanes, 2, 1, pFile) ) != 1 )
        printf("ERROR: getBitmapImageData_personagem - Couldn't read plane count from %s.\n", pFileName);

    if( nNumPlanes != 1 )
        printf("ERROR: getBitmapImageData_personagem - Plane count from %s.\n ", pFileName);

    if( (i = fread(&nNumBPP, 2, 1, pFile)) != 1 )
        printf( "ERROR: getBitmapImageData_personagem - Couldn't read BPP from %s.\n ", pFileName);

    if( nNumBPP != 24 )
        printf("ERROR: getBitmapImageData_personagem - BPP from %s.\n ", pFileName);

    // Seek forward to image data
    fseek( pFile, 24, SEEK_CUR );

    // Calculate the image's total size in bytes. Note how we multiply the
    // result of (width * height) by 3. This is becuase a 24 bit color BMP
    // file will give you 3 bytes per pixel.
    int nTotalImagesize = (pImage->width * pImage->height) * 3;

    pImage->data = (char*) malloc( nTotalImagesize );

    if( (i = fread(pImage->data, nTotalImagesize, 1, pFile) ) != 1 )
        printf("ERROR: getBitmapImageData_personagem - Couldn't read image data from %s.\n ", pFileName);

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


/*Função para Carregar uma imagem .BMP */
void CarregaTexturas_personagem()
{
    BMPImage textura;

    /* Define quantas texturas serão usadas no programa  */
    glGenTextures(MAX_NO_TEXTURES, texture_id_personagem); /* 1 = uma textura; */
                                /* texture_id_personagem = vetor que guardas os números das texturas */

    int i;
    for ( i=0; i<MAX_NO_TEXTURES; i++ ) {
        getBitmapImageData_personagem( filenameArray_personagem[i], &textura);
        glBindTexture(GL_TEXTURE_2D, texture_id_personagem[i]);
        glTexImage2D(GL_TEXTURE_2D, 0, 3, textura.width, textura.height, 0, GL_RGB, GL_UNSIGNED_BYTE, textura.data);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    }
}

void esfera(GLdouble radius, GLint slices, GLint stacks, int textura)
{
	//glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture_id_personagem[textura]);
	obj = gluNewQuadric();
	gluQuadricTexture(obj,GL_TRUE);
	gluSphere(obj,radius,slices,stacks);
}


/* **********************************************************************
  void initTexture(void)
        Define a textura a ser usada

 ********************************************************************** */
void initTextureEsfera (void)
{

    /* Habilita o uso de textura bidimensional  */
    glEnable ( GL_TEXTURE_2D );
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    /*Carrega os arquivos de textura */
  //  CarregaTextura("tunnelTexture.bmp");
    //CarregaTextura("tex2.bmp");
    CarregaTexturas_personagem();

}

float personagemPosX = 0;
float personagemPosY = -223;
float personagemPosZ = 1.0;
float personagemRotX = 0;
float personagemRotY = 0;
int isAlive = 1;
int vida = 2;

void DesenhaEsfera()
{
	glPushMatrix();
		glColor3f(0.7, 0.8, 0.7);
		glTranslatef(personagemPosX, personagemPosY, personagemPosZ + 0.5);
		esfera(0.3, 50, 50, 1);
	glPopMatrix();

	glPushMatrix();
		glColor3f(0.9, 1, 0.9);
		glTranslatef(personagemPosX, personagemPosY, personagemPosZ);
		glPushMatrix();
			glRotatef(personagemRotX, 1, 0, 0);
			glRotatef(personagemRotY, 0, 1, 0);
			esfera(0.5, 50, 50, 0);
		glPopMatrix();
	glPopMatrix();
}

void onCollision(posicao *objeto) {
	if (objeto->flag == GRANDE) {
		vida -= 2;
	}
	else {
		vida--;
	}
	if (vida <= 0) {
		isAlive = 0;
	}
}
