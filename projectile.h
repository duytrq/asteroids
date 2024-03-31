#ifndef PROJECTILE_H
#define PROJECTILE_H
#include "window.h"
#include "asteroid.h"
extern OBJECT* projectiles;
extern SDL_Surface *bullet, *debris, *mbullet;
void loadProjectileIMG();
void LaunchProjectile(double X, double Y, double DX, double DY, SDL_Surface *Img, int Life, int type, Ship *ship=NULL); 
void DrawProjectile();
void moveProjectile(Ship &ship);
void ShipShoot(Ship *ship);
void LaunchPoof(int X, int Y, SDL_Surface * Img, int life, int type);
void LaunchBulletCircular(int X, int Y, SDL_Surface* Img, int life, int type);
#endif