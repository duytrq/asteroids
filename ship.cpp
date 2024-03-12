#include "ship.h"
Ship::Ship()
{
    // //ship = new OBJECT();
    // ship.X=200;
    // ship.Y=200;
    // ship.DX = ship.X;
    // ship.DY = ship.Y;
    // ship.W = 50;
    // ship.H = 70;
    // ship.Angle = 0;  
}
void Ship::Load()
{
    shipSprite[0].img = IMG_Load("assets/images/ship.png");  
    shipSprite[1].img = IMG_Load("assets/images/ship_plume.png");
    shipSprite[2].img = IMG_Load("assets/images/ship_plume2.png"); 
    shipSprite[3].img = IMG_Load("assets/images/ship_plume3.png"); 
    shipSprite[4].img = IMG_Load("assets/images/ship_plume4.png");
    shipSprite[5].img = IMG_Load("assets/images/ship_plume5.png"); 
    shipSprite[6].img = IMG_Load("assets/images/ship_plume6.png");
    shipSprite[7].img = IMG_Load("assets/images/ship_dmg0.png");
    shipSprite[8].img = IMG_Load("assets/images/ship_dmg1.png");
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
void Ship::DrawToScreen()
{
    int a;
    SDL_Surface* ship;
    switch (ShipState)
    {
        case HALTED: ship = shipSprite[0].img; break;			        
        case UTHRUST: a=rand() & 1; ship = shipSprite[a+1].img; break;			        
        case DTHRUST: a=rand() & 1; ship = shipSprite[a+3].img; break;		       
        case LTHRUST: ship = shipSprite[6].img; break;			        
        case RTHRUST: ship = shipSprite[5].img; break;			        
        case DAMAGED: a=rand() & 1; ship = shipSprite[a+7].img; break;			        
    }
    SDL_Rect rShip, rAst;

    if(!explosion){
        //rShip=getRect(&ship);
        SDL_SetRenderDrawColor( gRen, 0x00, 0xFF, 0x00, 0xFF );
        //SDL_RenderDrawRect(gRen, &rShip);
        Draw(ship);

    }
}
void Ship::move(int speed)
{
    DX+= speed*sinwithdegree(Angle)*-1;
    DY+= speed*coswithdegree(Angle);
    X=round(DX);
    Y=round(DY);
}
void Ship::rotateBy(float D){
   float temp;
    if(fabs(Angle + D) < 181) 
    {
     temp = Angle + D;
     Angle = round(temp);
    } 
    else{
      Angle = Angle * -1;  
    }
}
void Ship::Update()
{
    if(momentum==true) 
    {
        momentum=lerp(&velocity,&timeTemp,100);
        if(reversed==false) move(-velocity);
        else move(velocity);
    }
    else{
        velocity=SPEED;
    }
    if (Y < -10) {Y = SCREEN_H; DY = SCREEN_H;}
    if (Y > SCREEN_H+10) {Y = 0; DY = 0;}
    if (X > SCREEN_W + 10) {X = 0; DX = 0;}
    if (X < -10) {X = SCREEN_W; DX = SCREEN_W;}
    
}
SDL_Rect Ship::HitBox()
{
    SDL_Rect t={X+10,Y+10,W-20,H-20};
    return t;
}