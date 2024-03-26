#include "game.h"
Ship Player;
SDL_Event ev;
bool KeyPressed=false;
long keystate[1000];
int lastX,lastY,lastAngle;
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
                if (asteroids != NULL) deleteList(&asteroids);
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
void ClearKey(){
    for(int i=0;i<1000;i++){
        keystate[i]=0;
    }
    KeyPressed = false;
}
void NewGame(int level)
{
    int a,tDIRX,tDIRY,tSIZE,tX,tY;
    if (asteroids != NULL) deleteList(&asteroids);
    Player.Lives = 3; 
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
    for(int i=0;i<level*3;i++)
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
    Mix_PlayMusic(theme, -1);
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
        ShipShoot(&Player);
    }
    if(KeyPressed) Player.momentum=false;
    if(Player.shipstill)
    {
        if (Player.ShipState == Player.UTHRUST) {Player.momentum = true; Player.reversed = false;}
        if (Player.ShipState == Player.DTHRUST) {Player.momentum = true; Player.reversed = true;}
        Player.Halted();
        if (Mix_Playing(1) != 0) Mix_FadeOutChannel(1,500);	
    }
    Player.Update();
    moveAsteroid(Player);
    moveProjectile();
    if (Player.X != lastX || Player.Y != lastY || Player.Angle != lastAngle) Player.shipstill = false;
    else Player.shipstill = true;
    if(length(&asteroids) == 0){
        Mix_HaltChannel(-1);
        deleteList(&projectiles);
        SDL_Delay(100);
        currLevel+=1;
        NewGame(currLevel);
    }
}