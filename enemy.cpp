#include "enemy.h"
OBJECT* enemy =NULL;
SDL_Surface* monster,*alien,*alienskill;
void loadEnemyIMG(){
    monster = IMG_Load("assets/images/enemy.png");
    alien = IMG_Load("assets/images/enemy1.png");
    alienskill = IMG_Load("assets/images/enemy3.png");
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
        temp.velrate = 1.2;
    }
    if(type == 2) {
        temp.Img=monster;
        temp.W = 50;
        temp.H = 50;
        temp.velrate = 2.5;
    }
    temp.type=type;
    temp.lastDirchange = 0;
    temp.Angle = 0;
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
                    if(p->type==1) ship.stupidmove=false;
                    deleteObject(&enemy, i, true);
                    deleteObject(&projectiles, j, true);
                    break;
                }
            }
        }
        if(p->type==1){
            if(SDL_GetTicks()-(p->lastDirchange)>4000){
                if(rand()%2) p->DIRY*=-1;
                double drX = ship.X - p->X;
                double drY = ship.Y - p->Y;
                double distance = sqrt(drX*drX+drY*drY);
                if(distance > 0){
                    drX/=distance;
                    drY/=distance;
                }
                if(gReady && p->skill1) {
                    if(Mix_Playing(7)==0) Mix_PlayChannel(7,eshot,0);
                    LaunchProjectile(p->X,p->Y+p->H/2,drX,drY,mbullet,100,2);
                }
                if(gReady && p->skill2) {
                    ship.stupidmove = true;
                    p->Img = alienskill;
                }
                p->skill1=!p->skill1;
                p->skill2=!p->skill2;
                p->lastDirchange = SDL_GetTicks();
            }
            if(SDL_GetTicks()-(p->lastDirchange)>2000){
                ship.stupidmove = false;
                p->Img = alien;
            }
            if(p->Img == alien)
                {p->DX=p->DX + p->velrate*p->DIRX;
                p->DY=p->DY + p->velrate*p->DIRY;
                p->X = round(p->DX);
                p->Y = round(p->DY);
                if(p->X < -10){p->X = SCREEN_W;p->DX = SCREEN_W;}
                if(p->X > SCREEN_W){p->X=0;p->DX=0;}
                if(p->Y < -10){p->Y = SCREEN_H;p->DY = SCREEN_H;}
                if(p->Y > SCREEN_H){p->Y=0;p->DY=0;}}
        }
        if(p->type==2 && gReady){
            double drX = ship.X - p->X;
            double drY = ship.Y - p->Y;
            double distance = sqrt(drX*drX+drY*drY);
            if(distance > 0){
                drX/=distance;
                drY/=distance;
            }
            p->Angle+=5;
            p->DX = p->DX + p->velrate*drX;
            p->DY = p->DY + p->velrate*drY;
            p->X = round(p->DX);
            p->Y = round(p->DY);
            if(distance < 150){
                int blowPosX= p->X;
                int blowPosY= p->Y;
                if(Mix_Playing(7)==0) Mix_PlayChannel(7,eshot,0);
                LaunchBulletCircular(blowPosX,blowPosY,abullet,100,3);
                deleteObject(&enemy,i,true);
            }
        }
    }

}