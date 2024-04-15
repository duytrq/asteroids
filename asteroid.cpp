#include "asteroid.h"
OBJECT* asteroids=NULL;
SDL_Surface* ast,*ast1,*ast2;
Uint32 collisionCooldown=1000,lastCollided=0;
void loadAsteroid()
{
    ast=IMG_Load("assets/images/asteroid.png");
    if(ast==NULL) std::cout<<"Can't load from: assets/images/asteroid.png \n";
    ast1=IMG_Load("assets/images/asteroid1.png");
    if(ast1==NULL) std::cout<<"Can't load from: assets/images/asteroid1.png \n";
    ast2=IMG_Load("assets/images/asteroid2.png");
    if(ast1==NULL) std::cout<<"Can't load from: assets/images/asteroid2.png \n";
}
void DrawAsteroid()
{
    if (asteroids != NULL) {
        for (int i=0;i<length(&asteroids);i++){
            DrawDynamicObject(getObject(asteroids,i));
        }
    }
}
void addAsteroid(int X,int Y,int DX, int DY, int size, double rotation,int type)
{
    OBJECT temp;
    temp.index = length(&asteroids);
    temp.X = X;
    temp.Y = Y;
    temp.DX = DX;
    temp.DY = DY;
    temp.size=size;
    temp.rotFactor = rotation;
    if (temp.size==0){
        temp.W = ASTH0;
        temp.H = ASTW0;
        temp.Life = 1;
    } 
    if(temp.size==1) {
        temp.W = ASTH1;
        temp.H = ASTW1;
        temp.Life = 2;
    }
    if(temp.size==2){
        temp.W = ASTH2;
        temp.H = ASTW2; 
        temp.Life = 3;
    }
    if(type == 0) temp.Img=ast;
    if(type == 1) temp.Img=ast1;
    if(type == 2) temp.Img=ast2;
    temp.Angle=0;
    temp.type=type;
    asteroids = addend(asteroids, newelement(temp)); 
}
void moveAsteroid(Ship &ship)
{
    OBJECT *p,*q;
    for(int i=0;i<length(&asteroids);i++)
    {
        p=getObject(asteroids,i);
        SDL_Rect rAst1, rAst2, rShip;
        rAst1=getRect(p);
        rShip=ship.HitBox();
        rAst1=getRect(p);
        if(Collided(rShip,rAst1) && gReady)
        {
            if(!ship.skillIsActive){
                Uint32 currentTime = SDL_GetTicks();
                if(currentTime - lastCollided > collisionCooldown){
                    ship.Damaged();
                    if (Mix_Playing(5) == 0) Mix_PlayChannel(5, crash, 0);
                    p->DIRX*=-1;
                    p->DIRY*=-1;
                    if(ship.Lives==0){
                        Mix_HaltChannel(-1);
                        ship.explosion=true;
                    }
                    lastCollided = currentTime;
                }
            }
            else{
                deleteObject(&asteroids, i, true);
            }
        }
        p->X = round(p->X+p->DX);
        p->Y = round(p->Y+p->DY);
        p->Angle+=p->rotFactor;
        if(p->X < -10){p->X = SCREEN_W;}
        if(p->X > SCREEN_W){p->X=0;}
        if(p->Y < -10){p->Y = SCREEN_H;}
        if(p->Y > SCREEN_H){p->Y=0;}
    }
    
}