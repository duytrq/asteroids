#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<iostream>
#include<cmath>
#include<time.h>
#include "list.h"
#include "ship.h"
#include "DrawFunc.h"
#define ASTW0 160
#define ASTH0 160
#define ASTW1 100
#define ASTH1 100
#define ASTW2 60
#define ASTH2 60
#define ERR_MSG0 "Error: "
Ship Player;
SDL_Event ev;
bool KeyPressed=false;
SDL_Surface* background,*ast1,*ast2,*ast3, *bullet;
bool running=true;
long keystate[1000];
OBJECT *asteroids;
int lastX,lastY,lastAngle;
void loadAssets();
void HandleEvents();
void HandleKeys(long sym, bool down);
void NewGame();
void addProjectile(double X, double Y, double DX, double DY, SDL_Surface* img, int life);
void addAsteroid(int X,int Y,int DIRX, int DIRY, int size);
void moveAsteroid();
void moveProjectile();
void Draw(int X, int Y, SDL_Surface *img);
void DrawObject(OBJECT object);
void DrawDynamicObject(OBJECT* object);
void DrawAnimation(int X, int Y, int H, int W, int frame, SDL_Surface *img);
void GameLoop();
void DrawScreen();
void UpdateGame();
int main(int argc, char* argv[])
{
    InitVideo();
    loadAssets();
    NewGame();
    GameLoop();
    Clean();
}
void HandleKey(long sym, bool down)
{
    switch (sym)
    {
        case SDLK_w:
            sym=SDL_SCANCODE_W;
            break;
        case SDLK_d:
            sym=SDL_SCANCODE_D;
            break;
        case SDLK_s:
            sym=SDL_SCANCODE_S;
            break;
        case SDLK_a:
            sym=SDL_SCANCODE_A;
            break;
        case SDLK_SPACE:
            sym=SDL_SCANCODE_SPACE;
            break;
        default:
            break;
    }
    if(sym>=0 && sym<=1000)
    {
        keystate[sym]=down;
    }
}
void HandleEvents()
{
    SDL_Event e;
    if(SDL_PollEvent(&e))
    {
        switch (e.type)
        {
            case SDL_QUIT:
                running=false;
                break;
            case SDL_KEYDOWN:
                HandleKey(e.key.keysym.sym,true);
                KeyPressed=true;
                break;
            case SDL_KEYUP:
                HandleKey(e.key.keysym.sym,false);
                KeyPressed=false;
                break;
            default:
                break;
        }
    }
}
void NewGame()
{
    int a,tDIRX,tDIRY,tSIZE,tX,tY;
    if (asteroids != NULL) deleteList(&asteroids);
    Player.X=200; 
    Player.Y=200;
    lastX=Player.X;
    lastY=Player.Y;
    Player.DX = Player.X;
    Player.DY = Player.Y;
    Player.W = 50;
    Player.H = 70;
    Player.Angle = 0;  
    
    lastAngle = Player.Angle;
    srand((unsigned) time(&t));
    for(int i=0;i<10;i++)
    {
        a = rand() % 2;
        if (a==0) tDIRX = 1;
        else tDIRX = -1;
        a = rand() % 2;
        if (a==0) tDIRY = 1;
        else tDIRY = -1; 
        tX = rand() % 1280;
        tY = rand() % 720;
        tSIZE = rand() % 3;
        addAsteroid(tX,tY,tDIRX, tDIRY, tSIZE);
    }
}
void loadAssets()
{
    background=IMG_Load("assets/images/background.png");
    if(background==NULL) std::cout<<ERR_MSG0<<"assets/images/background.png\n";
    ast1=IMG_Load("assets/images/ast1.png");
    if(ast1==NULL) std::cout<<ERR_MSG0<<"assets/images/ast1.png\n";
    ast2=IMG_Load("assets/images/ast2.png");
    if(ast1==NULL) std::cout<<ERR_MSG0<<"assets/images/ast2.png\n";
    ast3=IMG_Load("assets/images/ast3.png");
    if(ast3==NULL) std::cout<<ERR_MSG0<<"assets/images/ast3.png\n";
    bullet=IMG_Load("assets/images/bullet.png");
    if(bullet==NULL) std::cout<<ERR_MSG0<<"assets/images/bullet.png\n";
    Player.Load();
}
void addAsteroid(int X,int Y,int DIRX, int DIRY, int size)
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
   if (temp.size==0){
     temp.W = ASTH0;
     temp.H = ASTW0;
     temp.Img=ast2;
   } 
   if(temp.size==1) {
     temp.W = ASTH1;
     temp.H = ASTW1;
     temp.Img=ast1;
   }
   if(temp.size==2){
     temp.W = ASTH2;
     temp.H = ASTW2; 
     temp.Img=ast3;
   }
    temp.Angle=0;
    asteroids = addend(asteroids, newelement(temp)); 
}
void DrawScreen()
{
    SDL_RenderClear(gRen);
    Draw(0,0,background);
    
    SDL_Rect rAst;

    Player.DrawToScreen();
    if (asteroids != NULL) {
        for (int i=0;i<length(&asteroids);i++){
            DrawDynamicObject(getObject(asteroids,i));
            rAst=getRect(getObject(asteroids,i));
            SDL_SetRenderDrawColor( gRen, 0x00, 0xFF, 0x00, 0xFF );
            SDL_RenderDrawRect(gRen, &rAst);
        }
    }
    // if (projectiles != NULL) {
    //     for (int i=0;i<length(&projectiles);i++){
    //         DrawDynamicObject(getObject(projectiles,i));
    //     }
    // }
    SDL_RenderPresent(gRen);
}
void moveAsteroid()
{
    OBJECT *p,*q;
    for(int i=0;i<length(&asteroids);i++)
    {
        p=getObject(asteroids,i);
        SDL_Rect rShip, rAst1, rAst2;
        rShip=Player.HitBox();
        rAst1=getRect(p);
        if(Collided(rShip,rAst1))
        {
            Player.Damaged();
            p->DIRX*=-1;
            p->DIRY*=-1;
        }
        for(int j=0;j<length(&asteroids);j++)
        {
            q=getObject(asteroids,j);
            rAst2=getRect(q);
            if(p!=q){           
                if(Collided(rAst1,rAst2))
                {
                        p->DIRX*=-1;
                        p->DIRY*=-1;
                        q->DIRX*=-1;
                        q->DIRX*=-1;  
                }
            }
        }
        p->DX=p->DX + (1.5 * p->DIRX);
        p->DY=p->DY + (1.5 * p->DIRY);
        p->X = round(p->DX);
        p->Y = round(p->DY);
        p->X=p->DX;
        p->Y=p->DY;
        p->Angle+=3;
        if(p->X < -10){p->X = SCREEN_W;p->DX = SCREEN_W;}
        if(p->X > SCREEN_W){p->X=0;p->DX=0;}
        if(p->Y < -10){p->Y = SCREEN_H;p->DY = SCREEN_H;}
        if(p->Y > SCREEN_H){p->Y=0;p->DY=0;}
    }
}
// void moveProjectile()
// {
//     OBJECT *p;
//     for(int i=0;i<length(&projectiles);i++)
//     {
//         p=getObject(projectiles,i);
//         if(p->Life==-1)
//         {
//             p->FX+= (p->DX *coswithdegree(p->Angle));
//             p->FY+= (p->DY *sinwithdegree(p->Angle))*-1;
//             p->X=round(p->FX);
//             p->Y=round(p->FY);
//             if(p->X < -10 || p->X > SCREEN_W +10 || p->Y <-10 || p->Y > SCREEN_H + 10)
//             {
//                 deleteObject(&projectiles,i,true);
//             }
//             SDL_Rect pj=getRect(p);
//             for(int j=0;j<length(&asteroids);j++)
//             {
//                 OBJECT *a;
//                 a=getObject(asteroids,j);
//                 SDL_Rect ast=getRect(a);
//                 if(Collided(pj,ast))
//                 {
//                     deleteObject(&asteroids,j,true);
//                     deleteObject(&projectiles,i,true);
//                 }
//             }
//         }
//     }
// }
// void ShipShoot()
// {
//     //if(SDL_GetTicks()-shipShootTime>=200)
//     //{ 
//         //shipShootTime=SDL_GetTicks();
//         addProjectile(ship.X+16,ship.Y-2,20,20,bullet,-1);
//     //}
// }
void GameLoop()
{
    Uint32 lastTime, currentTime, deltaTime;
    const Uint32 targetFrameTime = 1000 / 60;

    lastTime = SDL_GetTicks();
    while (running)
    {
        currentTime = SDL_GetTicks();
        deltaTime = currentTime - lastTime;
        if (deltaTime > 100) {
            deltaTime = 100;
        }
        while (deltaTime >= targetFrameTime)
        {
            HandleEvents();
            UpdateGame();
            deltaTime -= targetFrameTime;
            lastTime += targetFrameTime;
        }
        DrawScreen();
    }
}

void UpdateGame()
{
    lastX=Player.X;
    lastY=Player.Y;
    lastAngle=Player.Angle;
    if(keystate[SDL_SCANCODE_W]) {
        Player.Up();
    }
    if(keystate[SDL_SCANCODE_S]) {
        Player.Down();
    }
    if(keystate[SDL_SCANCODE_A]) {
        Player.Left();
    }
    if(keystate[SDL_SCANCODE_D]) {
        Player.Right();
    }
    if(keystate[SDL_SCANCODE_SPACE]){
        //ShipShoot();
    }
    if(KeyPressed) Player.momentum=false;
    if(Player.shipstill)
    {
        if (Player.ShipState == Player.UTHRUST) {Player.momentum = true; Player.reversed = false;}
        if (Player.ShipState == Player.DTHRUST) {Player.momentum = true; Player.reversed = true;}
        Player.Halted();

    }
    Player.Update();
    moveAsteroid();
    //moveProjectile();
    if (Player.X != lastX || Player.Y != lastY || Player.Angle != lastAngle) Player.shipstill = false;
    else Player.shipstill = true;
}