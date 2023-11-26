#ifndef CAMERA
#define CAMERA

#include <GL/gl.h>
#include <GL/glut.h>
#include "cenario.h"

extern int zoom;
extern float dt;
extern float oldt;
extern float camPosY;
extern float camLookY;

void Textura();
void Iluminacao();
void Camera();
void TimeMove();
void Keyboard(unsigned char c, int x, int y);

#endif
