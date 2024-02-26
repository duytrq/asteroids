#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<iostream>
#include "list.h"
#define PI 3.14159265
//GAME CONSTANTS
#define SCREEN_W 640
#define SCREEN_H 480
#define ERR_MSG0 "Failed to load asset. \n"

//GLOBAL
SDL_Event ev;
SDL_Renderer *gRen;
SDL_Window *gWin;
SDL_Surface* background;
bool running=true;
long keystate[1000];
OBJECT ship;
//...................//
/*Function prototypes*/
//...................//
/*SDL_Related*/
bool InitVideo();
bool InitAudio();
void Clean();
void loadAssets();
void HandleEvents();
void HandleKeys(long sym, bool down);
void UpdateGame();
void Draw(int X, int Y, SDL_Surface *img);
void DrawAnimation(int X, int Y, int H, int W, int frame, SDL_Surface *img);
void GameLoop();
void DrawScreen();
int main(int argc, char* argv[])
{
    InitVideo();
    loadAssets();
    GameLoop();
    Clean();
}

/* Function */
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
void loadAssets()
{
    background=IMG_Load("assets/images/background.png");
    if(background==NULL) std::cout<<ERR_MSG0<<"assets/images/background.png\n";
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
    SDL_RenderClear(gRen);
    Draw(0,0,background);
    SDL_RenderPresent(gRen);
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
            //UpdateGame();
            lastTime=lastTime+60;
        }
        HandleEvents();
        DrawScreen();
    }

}