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
SDL_Surface* background;
bool running=true;
long keystate[1000];
OBJECT ship;
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
void moveship(int speed);
void Draw(int X, int Y, SDL_Surface *img);
void DrawObject(OBJECT object);
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
}
void loadAssets()
{
    background=IMG_Load("assets/images/background.png");
    if(background==NULL) std::cout<<ERR_MSG0<<"assets/images/background.png\n";
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
    SDL_RenderPresent(gRen);
}
void moveship(int speed)
{
    ship.DX+= speed*sinwithdegree(ship.Angle)*-1;
    ship.DY+= speed*coswithdegree(ship.Angle);
    ship.X=round(ship.DX);
    ship.Y=round(ship.DY);
}
void GameLoop()
{
    Uint32 lastTime, currentTime;
    lastTime=SDL_GetTicks();
    while(running)
    {
        currentTime=SDL_GetTicks();
        if(currentTime-lastTime>1000) lastTime=currentTime-60;
        while(currentTime-lastTime>2000/30)
        {
            UpdateGame();
            lastTime=lastTime+60;
        }
        HandleEvents();
        DrawScreen();
    }
}
void UpdateGame()
{
    lastX=ship.X;
    lastY=ship.Y;
    lastAngle=ship.Angle;
    if(keystate[SDLK_w]) {
        ShipState=UTHRUST;
        moveship(-SPEED);
    }
    if(keystate[SDLK_s]) {
        ShipState=DTHRUST;
        moveship(SPEED);
    }
}