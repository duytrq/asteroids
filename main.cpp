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
//...................//
/*Function prototypes*/
//...................//
/*SDL_Related*/
bool InitVideo();
bool InitAudio();
void Clean();
void Draw(int X, int Y, SDL_Surface *img);
void DrawAnimation(int X, int Y, int H, int W, int frame, SDL_Surface *img);
int main(int argc, char* argv[])
{
    InitVideo();
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
void DrawAnimation(int X, int Y, int H, int W, int frame, SDL_Surface *img) {
  SDL_Rect R, D;
  SDL_Texture *text;
  
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
