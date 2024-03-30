#include "enemy.h"
OBJECT* enemy =NULL;
SDL_Surface* monster,*alien;
void loadEnemyIMG(){
    monster = IMG_Load("assets/images/enemy.png");
    alien = IMG_Load("assets/images/enemy1.png");
}

void addEnemy(int X,int Y,int DIRX, int DIRY,int type)
{
    OBJECT temp;
    temp.index = length(&enemy);
    temp.DIRX = DIRX;
    temp.DIRY = DIRY;
    temp.X = X;
    temp.Y = Y;
    temp.DX = temp.X;
    temp.DY = temp.Y;
    //std::cout<<temp.velrate<<std::endl;
    if(type == 1) {
        temp.Img=alien;
        temp.W = 80;
        temp.H = 80;
    }
    if(type == 2) {
        temp.Img=monster;
        temp.W = 50;
        temp.H = 50;
    }
    temp.type=type;
    enemy = addend(enemy, newelement(temp)); 
}
void drawEnemy()
{
    if (enemy != NULL) {
        for (int i=0;i<length(&enemy);i++){
            DrawDynamicObject(getObject(enemy,i));
            SDL_Rect a= getRect(getObject(enemy,i));
        }
    }
}
void moveEnemy(Ship &ship)
{
    OBJECT *p,*q;
    for(int i=0;i<length(&enemy);i++)
    {
        p=getObject(enemy,i);
        SDL_Rect rEnemy,rShip;
        rEnemy=getRect(p);
        rShip=ship.HitBox();
        if(Collided(rShip,rEnemy) && gReady)
        {
            if(!ship.skillIsActive){
                Uint32 currentTime = SDL_GetTicks();
                if(currentTime - lastCollided > collisionCooldown){
                    ship.Damaged();
                    if (Mix_Playing(5) == 0) Mix_PlayChannel(5, crash, 0);
                    
                    if(ship.Lives==0){
                        Mix_HaltChannel(-1);
                        ship.explosion=true;
                    }
                    lastCollided = currentTime;
                }
            }
            deleteObject(&enemy, i, true);
        }
        for(int j=0;j<length(&projectiles);j++){
            q=getObject(projectiles,j);
            if(q->Life==-1){
                SDL_Rect pj = getRect(q);
                if(Collided(pj,rEnemy)){
                    deleteObject(&enemy, i, true);
                    deleteObject(&projectiles, j, true);
                    break;
                }
            }
        }
        if(p){
            p->DX=p->DX + p->DIRX;
            p->DY=p->DY + p->DIRY;
            p->DIRX*=-1;
            p->DIRY*=-1;
            if(p->type==2) p->Angle+=5;
            p->X = round(p->DX);
            p->Y = round(p->DY);
            if(p->X < -10){p->X = SCREEN_W;p->DX = SCREEN_W;}
            if(p->X > SCREEN_W){p->X=0;p->DX=0;}
            if(p->Y < -10){p->Y = SCREEN_H;p->DY = SCREEN_H;}
            if(p->Y > SCREEN_H){p->Y=0;p->DY=0;}
        }
    }

}