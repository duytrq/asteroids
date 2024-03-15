#ifndef PROJECTILE_H
#define PROJECTILE_H
#include "window.h"
#include "asteroid.h"
extern OBJECT* projectiles;
extern SDL_Surface *bullet, *debris;
void loadProjectileIMG();
void LaunchProjectile(double X, double Y, double DX, double DY, SDL_Surface *Img, int Life, Ship *ship=NULL); 
void DrawProjectile();
void moveProjectile();
void ShipShoot(Ship *ship);
void LaunchPoof(int X, int Y, SDL_Surface * Img, int life);
#endif