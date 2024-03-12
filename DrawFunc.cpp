#include "DrawFunc.h"
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