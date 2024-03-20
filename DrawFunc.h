#ifndef DRAWFUNC_H
#define DRAWFUNC_H
#include "window.h"
#include "list.h"
void DrawImg(int X, int Y, SDL_Surface *img);
void DrawDynamicObject(OBJECT* object);
void DrawAnimation(int X, int Y, int H, int W, int frame, SDL_Surface *img);
void DrawText(char* string,int size, int x, int y,int fR, int fG, int fB,int bR, int bG, int bB, bool transparent);
#endif