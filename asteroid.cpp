#include "asteroid.h"
OBJECT* asteroids=NULL;
SDL_Surface* ast;
void loadAsteroid()
{
    ast=IMG_Load("assets/images/asteroid.png");
    if(ast==NULL) std::cout<<"Can't load from: assets/images/asteroid.png \n";
}
void DrawAsteroid()
{
    if (asteroids != NULL) {
        for (int i=0;i<length(&asteroids);i++){
            DrawDynamicObject(getObject(asteroids,i));
            // rAst=getRect(getObject(asteroids,i));
            // SDL_SetRenderDrawColor( gRen, 0x00, 0xFF, 0x00, 0xFF );
            // SDL_RenderDrawRect(gRen, &rAst);
        }
    }
}
void addAsteroid(int X,int Y,int DIRX, int DIRY, int size, double vel)
{
    OBJECT temp;
    temp.index = length(&asteroids);
    temp.DIRX = DIRX;
    temp.DIRY = DIRY;
    temp.X = X;
    temp.Y = Y;
    temp.DX = temp.X;
    temp.DY = temp.Y;
    temp.size=size;
    temp.velrate = vel;
    //std::cout<<temp.velrate<<std::endl;
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
        temp.Img=ast;
        temp.Angle=0;
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
                ship.Damaged();
                p->DIRX*=-1;
                p->DIRY*=-1;
                if(ship.Lives==0){
                    Mix_HaltChannel(-1);
                    ship.explosion=true;
                }
            }
            else{
                deleteObject(&asteroids, i, true);
            }
        }
        p->DX=p->DX + (p->velrate * p->DIRX);
        p->DY=p->DY + (p->velrate * p->DIRY);
        p->X = round(p->DX);
        p->Y = round(p->DY);
        // p->X=p->DX;
        // p->Y=p->DY;
        p->Angle+=3;
        if(p->X < -10){p->X = SCREEN_W;p->DX = SCREEN_W;}
        if(p->X > SCREEN_W){p->X=0;p->DX=0;}
        if(p->Y < -10){p->Y = SCREEN_H;p->DY = SCREEN_H;}
        if(p->Y > SCREEN_H){p->Y=0;p->DY=0;}
    }
    
}