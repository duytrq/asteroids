#ifndef GAME_H
#define GAME_H
#include "list.h"
#include "ship.h"
#include "DrawFunc.h"
#include "asteroid.h"
#include "projectile.h"
#include "enemy.h"
extern Ship Player;
extern SDL_Event ev;
extern bool KeyPressed;
extern long keystate[1000];
extern int lastX,lastY,lastAngle;
void HandleEvents();
void HandleKeys(long sym, bool down);
void NewGame(int level);
void UpdateGame();
void ClearKey();
#endif