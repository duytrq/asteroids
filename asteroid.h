#ifndef ASTEROID_H
#define ASTEROID_H
#include "window.h"
#include "list.h"
#include "ship.h"
#include "DrawFunc.h"
#define ASTW0 200
#define ASTH0 200
#define ASTW1 160
#define ASTH1 160
#define ASTW2 100
#define ASTH2 100
extern OBJECT* asteroids;
extern SDL_Surface *ast;
void loadAsteroid();
void DrawAsteroid();
void moveAsteroid(Ship &ship);
void addAsteroid(int X,int Y,int DIRX, int DIRY, int size);
#endif