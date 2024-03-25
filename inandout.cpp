#include "inandout.h"
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