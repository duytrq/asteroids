#ifndef WINDOW_H
#define WINDOW_H
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<iostream>
#include<cmath>
#include<time.h>
#include "list.h"
#define SCREEN_W 1280
#define SCREEN_H 720
#define PI 3.14159265
extern SDL_Renderer *gRen;
extern SDL_Window *gWin;
extern double timeTemp;
extern time_t t;
bool InitVideo();
void Clean();
double sinwithdegree(int degree);
double coswithdegree(int degree);
SDL_Rect getRect(OBJECT *obj);
bool lerp(double *value, double *time, int ms);
#endif