#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<iostream>
#include<cmath>
#include "list.h"
#define PI 3.14159265

//GAME CONSTANTS
#define SCREEN_W 1280
#define SCREEN_H 720
#define SPEED 18
#define ROTATION 7.5
#define ASTW0 160
#define ASTH0 160
#define ASTW1 100
#define ASTH1 100
#define ASTW2 60
#define ASTH2 60
#define ERR_MSG0 "Failed to load asset. \n"

//GLOBAL
struct Sprite
{
    SDL_Surface *img;
};
enum SHIPSTATE {HALTED, UTHRUST, DTHRUST, LTHRUST, RTHRUST, DAMAGED};
enum SHIPSTATE ShipState;
SDL_Event ev;
SDL_Renderer *gRen;
SDL_Window *gWin;
SDL_Surface* background,*ast1,*ast2,*ast3;
bool running=true;
long keystate[1000];
OBJECT ship;
OBJECT *asteroids;
Sprite shipSprite[9];
bool explosion=false;
int lastX,lastY,lastAngle;
//...................//
/*Function prototypes*/
//...................//
double sinwithdegree(int degree);
double coswithdegree(int degree);
/*SDL_Related*/
bool InitVideo();
bool InitAudio();
void Clean();
void loadAssets();
void HandleEvents();
void HandleKeys(long sym, bool down);
void NewGame();
void addAsteroid(int X,int Y,int DIRX, int DIRY, int size);
void moveship(int speed);
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

/* Function */
double sinwithdegree(int degree)
{
    double rad=degree*PI/180;
    return sin(rad);
}
double coswithdegree(int degree)
{
    double rad=degree*PI/180;
    return cos(rad);
}
bool InitVideo()
{
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);
    gWin=SDL_CreateWindow("ASTEROID",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,SCREEN_W,SCREEN_H,SDL_WINDOW_SHOWN);
    gRen=SDL_CreateRenderer(gWin,-1,SDL_RENDERER_ACCELERATED);
    return (gRen!=NULL) && (gWin!=NULL);
}
void Clean()
{
    SDL_DestroyWindow(gWin);
    gWin=NULL;
    SDL_DestroyRenderer(gRen);
    gRen=NULL;
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
                break;
            case SDL_KEYUP:
                HandleKey(e.key.keysym.sym,false);
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
    ship.X=200;
    ship.Y=200;
    lastX=ship.X;
    lastY=ship.Y;
    ship.DX = ship.X;
    ship.DY = ship.Y;
    ship.W = 50;
    ship.H = 70;
    ship.Angle = 0;  
    lastAngle = ship.Angle;
    for(int i=0;i<2;i++)
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
    shipSprite[0].img = IMG_Load("assets/images/ship.png");
    if (shipSprite[0].img == NULL) {std::cout<<ERR_MSG0<<"assets/images/ship.png\n";}   
    shipSprite[1].img = IMG_Load("assets/images/ship_plume.png");
    if (shipSprite[1].img == NULL) {std::cout<<ERR_MSG0<<"assets/images/ship_plume.png\n";}   
    shipSprite[2].img = IMG_Load("assets/images/ship_plume2.png");
    if (shipSprite[2].img == NULL) {std::cout<<ERR_MSG0<<"assets/images/ship_plume2.png\n";}   
    shipSprite[3].img = IMG_Load("assets/images/ship_plume3.png");
    if (shipSprite[3].img == NULL) {std::cout<<ERR_MSG0<<"assets/images/ship_plume3.png\n";}   
    shipSprite[4].img = IMG_Load("assets/images/ship_plume4.png");
    if (shipSprite[4].img == NULL) {std::cout<<ERR_MSG0<<"assets/images/ship_plume4.png\n";}   
    shipSprite[5].img = IMG_Load("assets/images/ship_plume5.png");
    if (shipSprite[5].img == NULL) {std::cout<<ERR_MSG0<<"assets/images/ship_plume5.png\n";}   
    shipSprite[6].img = IMG_Load("assets/images/ship_plume6.png");
    if (shipSprite[6].img == NULL) {std::cout<<ERR_MSG0<<"assets/images/ship_plume6.png\n";}
    shipSprite[7].img = IMG_Load("assets/images/ship_dmg0.png");
    if (shipSprite[7].img == NULL) {std::cout<<ERR_MSG0<<"assets/images/ship_dmg0.png\n";}
    shipSprite[8].img = IMG_Load("assets/images/ship_dmg1.png");
    if (shipSprite[8].img == NULL) {std::cout<<ERR_MSG0<<"assets/images/ship_dmg1.png\n";}
  
    ship.Img = shipSprite[0].img;
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
   if (size==0){
     temp.W = ASTH0;
     temp.H = ASTW0;
     temp.Img=ast2;
   } 
   if(size==1) {
     temp.W = ASTH1;
     temp.H = ASTW1;
     temp.Img=ast1;
   }
   if(size==2){
     temp.W = ASTH2;
     temp.H = ASTW2; 
     temp.Img=ast3;
   }
    temp.Angle=0;
    asteroids = addend(asteroids, newelement(temp)); 
}
/* Draw Function*/
void Draw(int X, int Y, SDL_Surface *img)
{
    SDL_Rect r;
    SDL_Texture *tex;
    r.x=X;
    r.y=Y;
    r.w=img->w;
    r.h=img->h;
    tex=SDL_CreateTextureFromSurface(gRen,img);
    SDL_RenderCopy(gRen,tex,NULL,&r);
    SDL_DestroyTexture(tex);
}
void DrawObject(OBJECT object)
{
    SDL_Rect R;
    SDL_Texture *text;
    R.x= object.X;
    R.y= object.Y;
    R.w= object.W;
    R.h= object.H;
    text=SDL_CreateTextureFromSurface(gRen,object.Img);
    SDL_RenderCopyEx(gRen,text, NULL, &R,object.Angle,NULL,SDL_FLIP_NONE);
    SDL_DestroyTexture(text);
}
void DrawDynamicObject(OBJECT* object)
{
    SDL_Rect R;
    SDL_Texture *text;
    
    R.x = object->X;
    R.y = object->Y;
    R.w = object->W;
    R.h = object->H;
    text = SDL_CreateTextureFromSurface(gRen,object->Img);
    SDL_RenderCopyEx(gRen, text, NULL, &R, object->Angle,NULL, SDL_FLIP_NONE);
    SDL_DestroyTexture(text);
}
void DrawAnimation(int X, int Y, int H, int W, int frame, SDL_Surface *img) 
{
  SDL_Texture *text;
  SDL_Rect R,D;
  R.x = X;
  R.y = Y;
  R.w = H;
  R.h = W;
  D.x = H*frame;
  D.y = 0;
  D.w = W;
  D.h = W;
  text = SDL_CreateTextureFromSurface(gRen,img);
  SDL_RenderCopy(gRen, text, &D, &R);
  SDL_DestroyTexture(text);
}
void DrawScreen()
{
    int a;
    SDL_RenderClear(gRen);
    Draw(0,0,background);
    switch (ShipState)
    {
        case HALTED: ship.Img = shipSprite[0].img; break;			        
        case UTHRUST: a=rand() & 1; ship.Img = shipSprite[a+1].img; break;			        
        case DTHRUST: a=rand() & 1; ship.Img = shipSprite[a+3].img; break;		       
        case LTHRUST: ship.Img = shipSprite[6].img; break;			        
        case RTHRUST: ship.Img = shipSprite[5].img; break;			        
        case DAMAGED: a=rand() & 1; ship.Img = shipSprite[a+7].img; break;			        
    }
    if(!explosion) DrawObject(ship);
    if (asteroids != NULL) {
        for (int i=0;i<length(&asteroids);i++){
            DrawDynamicObject(getObject(asteroids,i));
        }
    }
    SDL_RenderPresent(gRen);
}
void moveship(int speed)
{
    ship.DX+= speed*sinwithdegree(ship.Angle)*-1;
    ship.DY+= speed*coswithdegree(ship.Angle);
    ship.X=round(ship.DX);
    ship.Y=round(ship.DY);
}
void rotateBy(OBJECT *Object, float D){
   float temp;
   if(fabs(Object->Angle + D) < 181) {
     temp = Object->Angle + D;
     Object->Angle = round(temp);
   } else{
      Object->Angle = Object->Angle * -1;  
    }
}
void moveAsteroid()
{
    OBJECT *p;
    for(int i=0;i<length(&asteroids);i++)
    {
        p=getObject(asteroids,i);
        p->DX=p->DX + (1 * p->DIRX);
        p->DY=p->DY + (1 * p->DIRY);
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
    lastX=ship.X;
    lastY=ship.Y;
    lastAngle=ship.Angle;
    if(keystate[SDL_SCANCODE_W]) {
        ShipState=UTHRUST;
        moveship(-SPEED);
    }
    if(keystate[SDL_SCANCODE_S]) {
        ShipState=DTHRUST;
        moveship(SPEED);
    }
    if(keystate[SDL_SCANCODE_A]) {
        ShipState=LTHRUST;
        rotateBy(&ship,-ROTATION);
    }
    if(keystate[SDL_SCANCODE_D]) {
        ShipState=RTHRUST;
        rotateBy(&ship,ROTATION);
    }
    moveAsteroid();
}