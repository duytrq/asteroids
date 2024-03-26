#include "game.h"
#include "inandout.h"
void loadAssets();
void GameLoop();
void DrawScreen();
void UpdateGame();
int main(int argc, char* argv[])
{
    InitVideo();
    loadAssets();
    Intro();
    NewGame(currLevel);
    GameLoop();
    Clean();
}

void loadAssets()
{
    loadHUD();
    loadProjectileIMG();
    loadAsteroid();
    Player.Load();
}
void DrawScreen()
{
    std::string pointText = std::to_string(points);
    SDL_RenderClear(gRen);
    DrawImg(0,0,background);
    
    SDL_Rect rAst;

    Player.DrawToScreen();
    DrawAsteroid();
    DrawProjectile();
    DrawImg(1,1,indicator);
    DrawText(pointText,"assets/fonts/FreeMonoBold.ttf", 13, 70, 15, 255, 255, 255, 0, 0, 0, true);
    SDL_RenderPresent(gRen);
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
        if(Player.explosion){
            if (SDL_GetTicks() - timeTemp < 100) {
                Player.explosion = true;
            //if (Mix_Playing(3) == 0) Mix_PlayChannel(3, expsnd, 0);
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
                        currLevel = 1;
                        Player.explosion=false;
                        ClearKey();
                        NewGame(currLevel);
                    }
                    else running = false;
                }            
            }
            // Outtro();
            // if(newgame){
            //     points = 0;
            //     currLevel = 1;
            //     Player.explosion=false;
            //     ClearKey();
            //     NewGame(currLevel);
            // }
            // else running = false;
        }
    }
}

