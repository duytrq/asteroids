#ifndef ENEMY_H
#define ENEMY_H
#include "window.h"
#include "DrawFunc.h"
#include "projectile.h"
extern OBJECT* enemy;
extern SDL_Surface* monster,*alien;
void loadEnemyIMG();
void addEnemy(int X,int Y,int DIRX, int DIRY, int type);
void drawEnemy();
void moveEnemy(Ship &ship);
#endif