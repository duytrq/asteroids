#ifndef SHIP_H
#define SHIP_H
#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
#include "list.h"
#include "window.h"
#define SPEED 12
#define ROTATION 5.5
struct Sprite
{
    SDL_Surface *img;
};
struct Ship{
   	int X,Y,W,H,DX,DY,DIRX,DIRY,Life,size;
   	int Angle;
    Sprite shipSprite[9];
    enum SHIPSTATE {HALTED, UTHRUST, DTHRUST, LTHRUST, RTHRUST, DAMAGED};
    enum SHIPSTATE ShipState;
    bool momentum=false;
    bool reversed=false;
    bool shipstill=false;
    bool explosion=false;
    double velocity = SPEED;
    double shipShootTime;
    Ship();
    void Load();
    void move(int speed);
    void Update();
    void ShipShoot();
    void Draw(SDL_Surface *img);
    void DrawToScreen();
    void rotateBy(float D);
    void Damaged(){ShipState=DAMAGED;}
    void Up(){ShipState=UTHRUST; move(-SPEED);}
    void Down(){ShipState=DTHRUST; move(SPEED);}
    void Right(){ShipState=RTHRUST; rotateBy(ROTATION);}
    void Left(){ShipState=LTHRUST; rotateBy(-ROTATION);}
    void Halted(){ShipState=HALTED;}
    SDL_Rect HitBox();
};
#endif
