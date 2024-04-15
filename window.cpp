#include "window.h"
SDL_Renderer *gRen;
SDL_Window *gWin;
bool running = true;
bool gReady = false;
SDL_Surface* background , *indicator;
time_t t;
Uint32 timeTemp=0;
int points=0,best = 0;
int money=0;
int currLevel = 1;
Mix_Music *theme = NULL;
Mix_Chunk *sound = NULL, *intro = NULL, *shot = NULL, *expsnd = NULL, *shield = NULL, *crash = NULL, *hit=NULL, *eshot=NULL;
void loadHUD(){
    background=IMG_Load("assets/images/background.png");
    indicator=IMG_Load("assets/images/indicators.png");
}
bool InitVideo()
{
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);
    TTF_Init();
    gWin=SDL_CreateWindow("ASTEROID",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,SCREEN_W,SCREEN_H,SDL_WINDOW_SHOWN);
    gRen=SDL_CreateRenderer(gWin,-1,SDL_RENDERER_ACCELERATED);
    return (gRen!=NULL) && (gWin!=NULL);
}
bool InitAudio()
{
    if (SDL_Init(SDL_INIT_AUDIO)<0){
        return false;
    }
    Mix_Init(MIX_INIT_MP3);
     if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", SDL_GetError());
     }
    return true;
}
void loadAudio()
{
    theme = Mix_LoadMUS("assets/sounds/theme.ogg");
    intro = Mix_LoadWAV("assets/sounds/intro.wav");
    Mix_VolumeChunk(intro, MIX_MAX_VOLUME ); 
    sound = Mix_LoadWAV("assets/sounds/rockets.wav");
    Mix_VolumeChunk( sound, MIX_MAX_VOLUME );
    shot = Mix_LoadWAV("assets/sounds/shot.wav"); 
    Mix_VolumeChunk(shot, MIX_MAX_VOLUME ); 
    expsnd = Mix_LoadWAV("assets/sounds/explosion.wav"); 
    Mix_VolumeChunk(expsnd, MIX_MAX_VOLUME ); 
    shield = Mix_LoadWAV("assets/sounds/shield.wav");
    Mix_VolumeChunk(shield, MIX_MAX_VOLUME ); 
    crash = Mix_LoadWAV("assets/sounds/crash.wav"); 
    Mix_VolumeChunk(crash, MIX_MAX_VOLUME); 
    hit = Mix_LoadWAV("assets/sounds/astbloom.wav");
    Mix_VolumeChunk(hit, MIX_MAX_VOLUME);
    eshot = Mix_LoadWAV("assets/sounds/bullet_enemy.wav");
    Mix_VolumeChunk(hit,MIX_MAX_VOLUME);
}
void Clean()
{
    SDL_DestroyWindow(gWin);
    gWin=NULL;
    SDL_DestroyRenderer(gRen);
    gRen=NULL;
    Mix_CloseAudio();
    Mix_Quit();
    IMG_Quit();
    TTF_Quit();
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
