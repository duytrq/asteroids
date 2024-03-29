#ifndef ASTEROID_H
#define ASTEROID_H
#include "window.h"
#include "list.h"
#include "ship.h"
#include "DrawFunc.h"
#define ASTW0 100
#define ASTH0 100
#define ASTW1 160
#define ASTH1 160
#define ASTW2 200
#define ASTH2 200
extern OBJECT* asteroids;
extern SDL_Surface *ast,*ast1,*ast2;
extern bool gReady;
extern Uint32 collisionCooldown,lastCollided;
void loadAsteroid();
void DrawAsteroid();
void moveAsteroid(Ship &ship);
void addAsteroid(int X,int Y,int DIRX, int DIRY, int size, double vel, int type);
#endif