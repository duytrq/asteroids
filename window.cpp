#include "window.h"
SDL_Renderer *gRen;
SDL_Window *gWin;
time_t t;
double timeTemp=0;
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
    IMG_Quit();
    SDL_Quit();
}
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
SDL_Rect getRect(OBJECT *obj)
{
    SDL_Rect t={obj->X+10,obj->Y+10,obj->W-20,obj->H-20};
    return t;
}
bool lerp(double *value, double *time, int ms){
    bool res;
    if (SDL_GetTicks() - *time < ms) {
        res = true;
    } else{
        *time = SDL_GetTicks();
        if (*value > 0) {
        *value = *value -3;
        res = true;
        }
        else {
            *value = 0;
        res = false;
        }
    }
    return res;
}