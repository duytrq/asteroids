#include "list.h"
#include "ship.h"
#include "DrawFunc.h"
#include "asteroid.h"
Ship Player;
SDL_Event ev;
bool KeyPressed=false;
bool running=true;
SDL_Surface* background, *bullet;
long keystate[1000];
int lastX,lastY,lastAngle;
void loadAssets();
void HandleEvents();
void HandleKeys(long sym, bool down);
void NewGame();
void addProjectile(double X, double Y, double DX, double DY, SDL_Surface* img, int life);
void moveProjectile();
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
    if(background==NULL) std::cout<<"assets/images/background.png\n";
    bullet=IMG_Load("assets/images/bullet.png");
    if(bullet==NULL) std::cout<<"assets/images/bullet.png\n";
    loadAsteroid();
    Player.Load();
}
void DrawScreen()
{
    SDL_RenderClear(gRen);
    Draw(0,0,background);
    
    SDL_Rect rAst;

    Player.DrawToScreen();
    DrawAsteroid();
    // if (projectiles != NULL) {
    //     for (int i=0;i<length(&projectiles);i++){
    //         DrawDynamicObject(getObject(projectiles,i));
    //     }
    // }
    SDL_RenderPresent(gRen);
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
    moveAsteroid(Player);
    Player.Update();
    //moveProjectile();
    if (Player.X != lastX || Player.Y != lastY || Player.Angle != lastAngle) Player.shipstill = false;
    else Player.shipstill = true;
}