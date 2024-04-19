#include "ship.h"
Ship::Ship()
{ 
}
void Ship::Load()
{
    shipSprite[0].img = IMG_Load("assets/images/ship.png");  
    shipSprite[1].img = IMG_Load("assets/images/ship_plume.png");
    shipSprite[2].img = IMG_Load("assets/images/ship_plume5.png"); 
    shipSprite[3].img = IMG_Load("assets/images/ship_plume6.png");
    shipSprite[4].img = IMG_Load("assets/images/ship_dmg0.png"); 
    shipSprite[5].img = IMG_Load("assets/images/ship_skill.png");
    explosionIMG = IMG_Load("assets/images/exp.png");
    icon = IMG_Load("assets/images/skill_icon.png");
}
void Ship::Draw(SDL_Surface* img)
{
    SDL_Rect R;
    SDL_Texture *text;
    R.x= X;
    R.y= Y;
    R.w= W;
    R.h= H;
    text=SDL_CreateTextureFromSurface(gRen, img);
    SDL_RenderCopyEx(gRen,text, NULL, &R,Angle,NULL,SDL_FLIP_NONE);
    SDL_DestroyTexture(text);
}
void Ship::DrawLife(){
    int X=90,Y=0,W=40,H=40;
    SDL_Texture *text;
    if(!skillIsActive){
        text=SDL_CreateTextureFromSurface(gRen,shipSprite[0].img);
    }
    else text=SDL_CreateTextureFromSurface(gRen,shipSprite[5].img);
    for(int i=1;i<=Lives;i++)
    {
        SDL_Rect r{X,Y,W,H};
        SDL_RenderCopy(gRen, text, NULL, &r);
        X+=40;
    }
    SDL_DestroyTexture(text);
}
void Ship::DisplaySkillTimer()
{
    if(skillIsActive){
        std::stringstream timeText;
        timeText.str("");
        if(skillDuration>(skillAct.getTicks()-skillLastUsed))
            timeText<< (skillDuration-(skillAct.getTicks()-skillLastUsed)) / 1000.f ;
        else timeText<<"0";
        DrawText(timeText.str(),"assets/fonts/FreeMonoBold.ttf", 30, 215, 3, 255, 255, 255, 0, 0, 0, true); 
    }
    else{
        DrawImgRatio(20,630,0.5,icon);
        std::stringstream timeText;
        timeText.str(" ");
        if(skillLastUsed==0){
            if((skillCooldown>(skillAct.getTicks()-skillLastUsed)))
                timeText<<(skillCooldown-(skillAct.getTicks()-skillLastUsed)) / 1000.f;
            else{
                timeText<<"Ready";
            }
        }
        else{
            if((skillOnCooldown && skillCooldown>(skillAct.getTicks()-skillLastUsed))){
                timeText<<(skillCooldown-(skillAct.getTicks()-skillLastUsed)) / 1000.f;
            }
            else{
                timeText<<"Ready";
            }
        }
        DrawText(timeText.str(),"assets/fonts/FreeMonoBold.ttf", 30, 10, 600, 255, 255, 255, 0, 0, 0, true);
    }
}
void Ship::DrawExplosion()
{
    DrawAnimation(X,Y,60,60,expticks,explosionIMG);
    SDL_RenderPresent(gRen);
}
void Ship::DrawToScreen()
{
    int a;
    SDL_Surface* ship;
    switch (ShipState)
    {
        case HALTED: ship = shipSprite[0].img; break;			        
        case UTHRUST: ship = shipSprite[1].img; break;			        	       
        case LTHRUST: ship = shipSprite[2].img; break;			        
        case RTHRUST: ship = shipSprite[3].img; break;			        
        case DAMAGED: ship = shipSprite[4].img; break;
        case SKILL: ship = shipSprite[5].img; break;			        
    }
    SDL_Rect rShip, rAst;

    if(!explosion){
        Draw(ship);

    }
    DrawLife();
    DisplaySkillTimer();
}
void Ship::move()
{
    float xN = static_cast<float>(sinwithdegree(Angle));
    float yN = static_cast<float>(coswithdegree(Angle));
    if(stupidmove){
        VX += xN * accFactor * -1;
        VY -= yN * accFactor * -1;
    }
    else{
        VX += xN * accFactor;
        VY -= yN * accFactor;
    }
}
void Ship::rotateBy(float D){
    float temp;
    if (Mix_Playing(1) == 0) Mix_PlayChannel( 1, sound, 0);
    if(stupidmove) D*=-1;
    if(fabs(Angle + D) < 181) 
    {
        temp = Angle + D;
        Angle = round(temp);
    } 
    else{
        Angle = Angle * -1;  
    }
}
void Ship::SkillActivate(){
    if(skillAct.getTicks()-skillLastUsed >= skillCooldown && !skillOnCooldown){
        skillIsActive = true;
        skillOnCooldown = true;
        skillLastUsed = skillAct.getTicks();
    }
}
void Ship::UpdateSkillState(){
    if(skillIsActive && skillAct.getTicks() - skillLastUsed>= skillDuration){
        skillIsActive = false;
    }
    if(skillOnCooldown && skillAct.getTicks() - skillLastUsed >= skillCooldown){
        skillOnCooldown = false;
    }
}
void Ship::Update()
{
    UpdateSkillState();
    X += VX;
    Y += VY;
    VX = VX - VX * dragFactor;
    VY = VY - VY * dragFactor;
    if (Y < -10) {Y = SCREEN_H;}
    if (Y > SCREEN_H+10) {Y = 0;}
    if (X > SCREEN_W + 10) {X = 0;}
    if (X < -10) {X = SCREEN_W;}
}
SDL_Rect Ship::HitBox()
{
    SDL_Rect t={X+10,Y+10,W-20,H-20};
    return t;
}