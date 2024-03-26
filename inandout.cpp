#include "inandout.h"
bool newgame = false;
void Intro()
{
    std::fstream file("highscores.txt");
    file>>best;
    std::string introStr, helpStr0, helpStr1, helpStr2, helpStr3, helpStr4, bestScores;
    bestScores = "Best scores: ";
    bestScores+= std::to_string(best);
    int posY = 0;
    bool keyflag = false;
    SDL_Event e;
    SDL_RenderClear(gRen);
    DrawImg(0,0, background);
    introStr = "AST3R0ID";
    if (Mix_Playing(1) == 0) Mix_PlayChannel(1, intro, 0);
    do{ 
        SDL_RenderClear(gRen);
        DrawImg(0,0,background);
        DrawText(introStr,"assets/fonts/RubikIso-Regular.ttf", 160, 215 ,posY, 255,0, 0, 0, 0, 0,true); 
        DrawText(introStr,"assets/fonts/RubikIso-Regular.ttf", 160, 215 ,posY+5,255,255, 0, 0, 0, 0,true); 
        SDL_RenderPresent(gRen);
        SDL_Delay(10);
        posY = posY + 3;
   } while (posY < 144);
    helpStr0 = "Coded by DuyTQ";
    helpStr1 = "CONTROLS: ";
    helpStr2 = "^: UP  v: DOWN <- : LEFT  -> : RIGHT | SPACE : SHOOT ";
    helpStr3 = "ESC: EXIT";
    helpStr4 = "PRESS ANY KEY TO START";
    DrawText(helpStr0,"assets/fonts/FreeMonoBold.ttf", 12, 460,300,105,105, 105, 0, 0, 0,true); 
    DrawText(helpStr1,"assets/fonts/FreeMonoBold.ttf", 16, 360,560,255,255, 255, 0, 0, 0,true); 
    DrawText(helpStr2,"assets/fonts/FreeMonoBold.ttf", 18, 360,600,255,255, 255, 0, 0, 0,true); 
    DrawText(helpStr3,"assets/fonts/FreeMonoBold.ttf", 18, 360,640,255,255, 255, 0, 0, 0,true); 
    DrawText(helpStr4,"assets/fonts/FreeMonoBold.ttf", 22, 500,460,255,255, 255, 0, 0, 0,true); 
    DrawText(bestScores,"assets/fonts/FreeMonoBold.ttf", 22, 1000,280,255,255, 255, 0, 0, 0,true, -25);
    SDL_RenderPresent(gRen);

    do {
        if (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                running = false;
                break;
            }    
            if (e.type == SDL_KEYDOWN){
            keyflag = true;
            }
        }

   } while (keyflag ==false);
   SDL_Delay(100);
}
void Outtro()
{
    std::string outtro, tryagain, yes, no;
    SDL_Event e;
    bool keyflag = false;
    SDL_RenderClear(gRen);
    DrawImg(0,0, background);
    outtro = "Game Over";
    yes = "Yes";
    no = "No";
    DrawText(outtro,"assets/fonts/RubikIso-Regular.ttf", 160, 205 ,146, 255,255, 0, 0, 0, 0,true); 
    if(points<best){
        tryagain = "You need "+std::to_string(best-points)+" to beat the highscores. Try again?"; 
    }
    else{
        tryagain = "New record have been set. Wanna play again?";
    }
    DrawText(tryagain,"assets/fonts/FreeMonoBold.ttf", 24, 290,400,255,255, 255, 0, 0, 0,true);
    DrawText(yes,"assets/fonts/FreeMonoBold.ttf", 32, 550,500,255,255, 255, 0, 0, 0,true); 
    DrawText(no,"assets/fonts/FreeMonoBold.ttf", 32, 550,540,255,255, 255, 0, 0, 0,true); 
    SDL_RenderPresent(gRen);
    do{
        if(SDL_PollEvent(&e)){
            if(e.type == SDL_QUIT)
            {
                running=false;
                break;
            }
            else if(e.type == SDL_KEYDOWN)
            {
                switch (e.key.keysym.sym)
                {
                case SDLK_y:
                    newgame = true;
                    DrawText(yes,"assets/fonts/FreeMonoBold.ttf", 32, 550,500,255,0, 0, 0, 0, 0,true); 
                    DrawText(no,"assets/fonts/FreeMonoBold.ttf", 32, 550,540,255,255, 255, 0, 0, 0,true); 
                    SDL_RenderPresent(gRen);
                    break;
                case SDLK_n:
                    newgame = false;
                    DrawText(yes,"assets/fonts/FreeMonoBold.ttf", 32, 550,500,255,255, 255, 0, 0, 0,true); 
                    DrawText(no,"assets/fonts/FreeMonoBold.ttf", 32, 550,540,255,0, 0, 0, 0, 0,true); 
                    SDL_RenderPresent(gRen);
                    break;
                case SDLK_RETURN:
                    keyflag = true;
                    break;
                default:
                    break;
                }
            }
        }
    }while(!keyflag);
}