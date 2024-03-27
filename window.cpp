#include "window.h"
SDL_Renderer *gRen;
SDL_Window *gWin;
bool running = true;
bool gReady = false;
SDL_Surface* background , *indicator;
time_t t;
Uint32 timeTemp=0;
int points=0,best = 0;
int currLevel = 1;
Mix_Music *theme = NULL;
Mix_Chunk *sound = NULL, *intro = NULL, *shot = NULL, *expsnd = NULL, *shield = NULL, *crash = NULL;
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
    if (theme == NULL)  std::cout<<"Load sound error!\n" << SDL_GetError(); 
    intro = Mix_LoadWAV("assets/sounds/intro.wav");
    if (intro == NULL)  std::cout<<"Load sound error!\n" << SDL_GetError();
    Mix_VolumeChunk(intro, MIX_MAX_VOLUME ); 
    sound = Mix_LoadWAV("assets/sounds/rockets.wav");
    if (sound == NULL) std::cout<<"Load sound error!\n" << SDL_GetError();
    Mix_VolumeChunk( sound, MIX_MAX_VOLUME );
    shot = Mix_LoadWAV("assets/sounds/shot.wav");
    if (shot == NULL) std::cout<<"Load sound error!\n" << SDL_GetError();   
    Mix_VolumeChunk(shot, MIX_MAX_VOLUME ); 
    expsnd = Mix_LoadWAV("assets/sounds/explosion.wav");
    if (expsnd == NULL) std::cout<<"Load sound error!\n" << SDL_GetError();   
    Mix_VolumeChunk(expsnd, MIX_MAX_VOLUME ); 
    shield = Mix_LoadWAV("assets/sounds/shield.wav");
    if (shield == NULL) std::cout<<"Load sound error!\n" << SDL_GetError();   
    Mix_VolumeChunk(shield, MIX_MAX_VOLUME ); 
    crash = Mix_LoadWAV("assets/sounds/crash.wav");
    if (crash == NULL) std::cout<<"Load sound error!\n" << SDL_GetError();   
    Mix_VolumeChunk(crash, MIX_MAX_VOLUME ); 
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
bool lerp(double *value, Uint32 *time, int ms){
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
// void timer(int *ticks, Uint8 *time, int ms){

//  if (SDL_GetTicks() - *time < ms) {
//     //value = TRUE;
//    //if (Mix_Playing(3) == 0) Mix_PlayChannel(3, expsnd, 0);
//  } else{
//    *time = SDL_GetTicks();
//    if (*ticks < 6) {
//        *ticks = *ticks +1;
// 	//value = TRUE;
//    }else {
//         *ticks = 0;
//  	//value = FALSE;
// 	//currentLevel = 1;
// 	//NewGame(currentLevel);
// 	}
// }
 
// }