#ifndef SHIP_H
#define SHIP_H
#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
#include "list.h"
#include "window.h"
#include "DrawFunc.h"
#include "timer.h"
#define SPEED 12
#define ROTATION 5.5
struct Sprite
{
    SDL_Surface *img;
};
struct Ship{
   	int X,Y,W,H,Lives,size;
    double VX,VY;
    const double accFactor = 0.2;
    const double dragFactor = 0.02;
   	int Angle;
    Sprite shipSprite[10];
    SDL_Surface* explosionIMG,*icon;
    enum SHIPSTATE {HALTED, UTHRUST, DTHRUST, LTHRUST, RTHRUST, DAMAGED, SKILL};
    enum SHIPSTATE ShipState;
    bool momentum=false;
    bool reversed=false;
    bool shipstill=false;
    bool explosion=false;
    bool skillOnCooldown = false, skillIsActive =false;
    int expticks=0; 
    Timer skillAct,skillCool;
    const Uint32 skillDuration=2000;
    const Uint32 skillCooldown=5000;
    Uint32 skillLastUsed = 0;
    double shipShootTime;
    Ship();
    void Load();
    void move();
    void Update();
    void ShipShoot();
    void Draw(SDL_Surface *img);
    void DrawToScreen();
    void DrawLife();
    void DrawExplosion();
    void rotateBy(float D);
    void SkillActivate();
    void UpdateSkillState();
    void DisplaySkillTimer();
    void Damaged(){ShipState=DAMAGED; Lives--;}
    void Up(){ShipState=UTHRUST; move();}
    void Down(){ShipState=DTHRUST; move();}
    void Right(){ShipState=RTHRUST; rotateBy(ROTATION);}
    void Left(){ShipState=LTHRUST; rotateBy(-ROTATION);}
    void Halted(){ShipState=HALTED;}
    SDL_Rect HitBox();
};
#endif
