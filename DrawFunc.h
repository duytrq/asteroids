#ifndef DRAWFUNC_H
#define DRAWFUNC_H
#include "window.h"
#include "list.h"
void DrawImg(int X, int Y, SDL_Surface *img);
void DrawImgRatio(int X, int Y, double ratio, SDL_Surface *img);
void DrawDynamicObject(OBJECT* object);
void DrawAnimation(int X, int Y, int H, int W, int frame, SDL_Surface *img);
void DrawText(std::string string , std::string Font, int size, int x, int y, Uint8 fR, Uint8 fG, Uint8 fB,Uint8 bR, Uint8 bG, Uint8 bB, bool transparent, double angle = 0);
#endif