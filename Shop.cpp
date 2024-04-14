#include "Shop.h"
bool paused=false,clicked=false;
int cursorState=0,price1=10,price2=10,price3=10;
SDL_Surface *shop,*cursor;
int ProcessingCursorLocation(int mouseX, int mouseY)
{
    if(128<mouseX && mouseX<428 && mouseY>220 && mouseY<595) cursorState=1;
    else if(485<mouseX && mouseX<790 && mouseY>220 && mouseY<595) cursorState=2;
    else if(845<mouseX && mouseX<1145 && mouseY>220 && mouseY<595) cursorState=3;
    else cursorState = 0;
}
void LoadShopAssets(){
    shop=IMG_Load("assets/images/shop.png");
    cursor=IMG_Load("assets/images/cursor.png");
}
void RenderShop(){
    std::string smoney;
    smoney+=std::to_string(money)+"$";
    DrawImg(0,0,shop);
    DrawText(smoney,"assets/fonts/FreeMonoBold.ttf",36,1200,3,255,255,255,0,0,0,true);
    if(cursorState==1){
        DrawImgRatio(260,620,0.5,cursor);
        std::string pmoney;
        pmoney+=("-"+std::to_string(price1)+"$");
        DrawText(pmoney,"assets/fonts/FreeMonoBold.ttf",36,1176,40,0,255,0,0,0,0,true);
    }
    if(cursorState==2){
        DrawImgRatio(630,620,0.5,cursor);
        std::string pmoney;
        pmoney+=("-"+std::to_string(price2)+"$");
        DrawText(pmoney,"assets/fonts/FreeMonoBold.ttf",36,1176,40,0,255,0,0,0,0,true);
    }
    if(cursorState==3){
        DrawImgRatio(990,620,0.5,cursor);
        std::string pmoney;
        pmoney+=("-"+std::to_string(price3)+"$");
        DrawText(pmoney,"assets/fonts/FreeMonoBold.ttf",36,1176,40,0,255,0,0,0,0,true);
    }
    SDL_RenderPresent(gRen);
}
void HandleShopEvent(){
}
void UpdateShop(){
    if(cursorState==1 && clicked){
        if(money-price1>=0){
            money-=price1;
            price1+=20;
            Player.shipShootLevel+=1;
            clicked=false;
        }
    }
    if(cursorState==2 && clicked){
        if(money-price2>=0){
            money-=price2;
            price2+=20;
            maxLives +=1;
            clicked=false;
        }  
    }
    if(cursorState==3 && clicked){
        if(money-price3>=0){   
            money-=price3;
            price3+=20;
            Player.skillDuration+=500;
            clicked=false;
        }
    }
}
