#include "game.h"
#include "inandout.h"
#include "Shop.h"
void loadAssets();
void HandleEvents();
void GameLoop();
void DrawScreen();
void UpdateGame();
int main(int argc, char* argv[])
{
    InitVideo();
    InitAudio();
    loadAssets();
    Intro();
    if(!loadgame) NewGame(currLevel);
    else LoadGame();
    GameLoop();
    if(Player.Lives!=0) SaveGame();
    Clean();
}

void loadAssets()
{
    loadHUD();
    LoadShopAssets();
    loadProjectileIMG();
    loadAsteroid();
    loadEnemyIMG();
    Player.Load();
    loadAudio();
}
void DrawScreen()
{
    std::string pointText = std::to_string(points);
    SDL_RenderClear(gRen);
    DrawImg(0,0,background);
    
    SDL_Rect rAst;
    Player.DrawToScreen();
    DrawAsteroid();
    drawEnemy();
    DrawProjectile();
    DrawImgRatio(1,1,2,indicator);
    DrawText(pointText,"assets/fonts/FreeMonoBold.ttf", 24, 125, 30, 255, 255, 255, 0, 0, 0, true);
    SDL_RenderPresent(gRen);
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
                if(e.key.keysym.sym == SDLK_ESCAPE){
                    paused = !paused;
                }
                else if(!paused){
                    HandleKey(e.key.keysym.sym,true);
                    KeyPressed=true;
                    gReady=true;
                }
                break;
            case SDL_KEYUP:
                HandleKey(e.key.keysym.sym,false);
                KeyPressed=false;
                break;
            default:
                break;
        }
        if(paused){
            if(e.type == SDL_MOUSEMOTION){
                int mouseX=e.button.x;
                int mouseY=e.button.y;
                clicked = false;
                ProcessingCursorLocation(mouseX,mouseY);
            }
            if(e.type == SDL_MOUSEBUTTONDOWN){
                if(e.button.button == SDL_BUTTON_LEFT){
                    clicked=true;
                }
            }
        }
    }
}
void GameLoop()
{   
    const int FPS = 60;
    const int frameDelay = 1000/FPS;
    Uint32 frameStart;
    int frameTime;
    while (running)
    {
        frameStart = SDL_GetTicks();
        HandleEvents();
        if(!paused)
        {
            if(!Player.explosion){
                UpdateGame();
            }
            DrawScreen();
            if(Player.explosion){
                if (SDL_GetTicks() - timeTemp < 100) {
                    Player.explosion = true;
                    if (Mix_Playing(3) == 0) Mix_PlayChannel(3, expsnd, 0);
                    Player.DrawExplosion();
                } else{
                    timeTemp = SDL_GetTicks();
                    if (Player.expticks < 6) {
                        Player.expticks = Player.expticks +1;
                        Player.explosion = true;
                        Player.DrawExplosion();
                    }else {
                        Player.expticks = 0;
                        Player.explosion = false;
                        Outtro();
                        if(newgame){
                            points = 0;
                            money = 0;
                            Player.shipShootLevel = 1;
                            currLevel = 1;
                            ClearKey();
                            NewGame(currLevel);
                        }
                        else running = false;
                    }            
                }
            }
        }
        else{
            UpdateShop();
            RenderShop();
        }
        frameTime = SDL_GetTicks()-frameStart;
        if(frameDelay > frameTime){
            SDL_Delay(frameDelay - frameTime);
        }
    }
}

