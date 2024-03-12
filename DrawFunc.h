#ifndef DRAWFUNC_H
#define DRAWFUNC_H
#include "window.h"
#include "list.h"
void Draw(int X, int Y, SDL_Surface *img);
void DrawDynamicObject(OBJECT* object);
void DrawAnimation(int X, int Y, int H, int W, int frame, SDL_Surface *img);
#endif