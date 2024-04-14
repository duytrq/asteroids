#include "projectile.h"
OBJECT *projectiles = NULL;
SDL_Surface* bullet,*debris, *mbullet, *abullet,*blackhole,*repair,*coin;
bool shootspecial=false,bexist=false;
void loadProjectileIMG()
{
    bullet=IMG_Load("assets/images/bullet.png");
    debris=IMG_Load("assets/images/debris.png");
    mbullet=IMG_Load("assets/images/bullet2.png");
    abullet=IMG_Load("assets/images/bullet3.png");
    blackhole=IMG_Load("assets/images/blackhole.png");
    repair=IMG_Load("assets/images/repair.png");
    coin=IMG_Load("assets/images/goldcoin.png");
}
void LaunchProjectile(double X, double Y, double DX, double DY, SDL_Surface *Img, int Life, int type, Ship* ship){
    OBJECT p;
    if (projectiles == NULL) 
        p.index = 0;
    else{
        p.index = length(&projectiles);
    } 
    p.Img = Img;
    p.type = type;
    p.Life = Life;
    if (type == 1) {
    //ship projectile
        p.W = 16;
        p.H = 16;
        if(ship->shipShootLevel==1 || shootspecial){
            p.Angle = ship->Angle + 90;
            p.FX = (ship->X +(ship->W-10)/2);
            p.FY = (ship->Y +(ship->H-30)/2);
            p.DX = DX;
            p.DY = DY;
            p.X = round(p.FX);
            p.Y = round(p.FY);
        }
        else if(ship->shipShootLevel==2 && !shootspecial){
            p.Angle = ship->Angle+80;
            p.FX = (ship->X +(ship->W-10)/2);
            p.FY = (ship->Y +(ship->H-30)/2);
            p.DX = DX;
            p.DY = DY;
            p.X = round(p.FX);
            p.Y = round(p.FY);
            projectiles=addend(projectiles, newelement(p)); 
            p.index++;
            p.Angle = ship->Angle+100;
        }
        else if(ship->shipShootLevel==3 && !shootspecial){
            p.Angle = ship->Angle+80;
            p.FX = (ship->X +(ship->W-10)/2);
            p.FY = (ship->Y +(ship->H-30)/2);
            p.DX = DX;
            p.DY = DY;
            p.X = round(p.FX);
            p.Y = round(p.FY);
            projectiles=addend(projectiles, newelement(p)); 
            p.index++;
            p.Angle = ship->Angle+100;
            projectiles=addend(projectiles, newelement(p)); 
            p.index++;
            p.Angle = ship->Angle + 90;
        }
    } 
    if (type ==0){
        p.W = 16;
        p.H = 16;
        p.X = X;
        p.Y = Y;
        p.FX = X;
        p.FY = Y;
        p.DX = DX;
        p.DY = DY;
    }
    if (type ==2){
        p.W = 20;
        p.H = 20;
        p.X = X;
        p.Y = Y;
        p.FX = X;
        p.FY = Y;
        p.DX = DX;
        p.DY = DY;
    }
    if (type ==3){
        p.W = 16;
        p.H = 16;
        p.X = X;
        p.Y = Y;
        p.FX = X;
        p.FY = Y;
        p.DX = DX;
        p.DY = DY;
    }
    if (type == 4){
        p.W = 32;
        p.H = 32;
        p.X = X;
        p.Y = Y;
        p.FX = X;
        p.FY = Y;
        p.DX = DX;
        p.DY = DY;
    }
    if (type ==5){
        p.W = 200;
        p.H = 200;
        p.X = X;
        p.Y = Y;
        p.Angle = 0;
    }
    projectiles=addend(projectiles, newelement(p)); 
} 
void DrawProjectile()
{
    if (projectiles != NULL) {
        for (int i=0;i<length(&projectiles);i++){
            DrawDynamicObject(getObject(projectiles,i));
        }
    }
}
void moveProjectile(Ship &ship)
{
    OBJECT *p;
    bool bCol=false;
    for(int i=0;i<length(&projectiles);i++)
    {
        p=getObject(projectiles,i);
        if(p->type == 1)
        {
            p->FX+= (p->DX *coswithdegree(p->Angle))*-1;
            p->FY+= (p->DY *sinwithdegree(p->Angle))*-1;
            p->X=round(p->FX);
            p->Y=round(p->FY);
        }
        if(p->type == 0)
        {
            p->FX+= p->DX;
            p->FY+= p->DY;
            p->X=round(p->FX);
            p->Y=round(p->FY);
        }
        if(p->type == 2)
        {
            p->FX+= 10*p->DX;
            p->FY+= 10*p->DY;
            p->X=round(p->FX);
            p->Y=round(p->FY);
        }
        if(p->type ==3)
        {
            p->FX+= 5*p->DX;
            p->FY+= 5*p->DY;
            p->X=round(p->FX);
            p->Y=round(p->FY);
        }
        if(p->type ==4)
        {
            p->FX+= p->DX/2;
            p->FY+= p->DY/2;
            p->X=round(p->FX);
            p->Y=round(p->FY);
            double DIRX,DIRY,distance;
            DIRX=ship.X-p->X;
            DIRY=ship.Y-p->Y;
            distance=sqrt(DIRX*DIRX+DIRY*DIRY);
            if(distance<100){
                p->DX=10*DIRX/distance;
                p->DY=10*DIRY/distance;
            }
        }
        if(p->type ==5){
            p->Angle+=5;
        }
        if(p->Life!=-1) p->Life--;
        if(p->X < -10 || p->X > SCREEN_W +10 || p->Y <-10 || p->Y > SCREEN_H + 10 || p->Life==0)
        {
            deleteObject(&projectiles,i,true);
            if(p->type==5) bexist=false;
        }
        SDL_Rect rShip = ship.HitBox();
        SDL_Rect pj=getRect(p);
        if(p->type >=2 && Collided(pj, rShip)){
            if(p->type!=4){
                if(!ship.skillIsActive){
                    ship.Damaged();
                    if (Mix_Playing(5) == 0) Mix_PlayChannel(5, crash, 0);
                    if(ship.Lives==0){
                        Mix_HaltChannel(-1);
                        ship.explosion=true;
                    }
                }
            }
            else{
                if(p->Img==blackhole) shootspecial=true;
                if(p->Img==repair) ship.Lives++;
                if(p->Img==coin) money++;
            }
            deleteObject(&projectiles,i,true);
        }
        for(int j=0;j<length(&asteroids);j++)
        {
            OBJECT *a;
            a=getObject(asteroids,j);
            if(p->type == 5){
                double DIRX,DIRY,distance;
                DIRX=p->X+100-a->X;
                DIRY=p->Y+100-a->Y;
                distance=sqrt(DIRX*DIRX+DIRY*DIRY);
                
                a->DX=4*DIRX/distance;
                a->DY=4*DIRY/distance;
            }
            SDL_Rect ast=getRect(a);
            if(Collided(pj,ast) && p->type!=0 && p->type!=4)
            {
                if (Mix_Playing(6) == 0) Mix_PlayChannel(6, hit, 0);
                if(a->Life==1)
                {
                    deleteObject(&asteroids, j, true);
                    LaunchPoof(a->X,a->Y, debris, 20, 0);
                    if(p->Img != debris) points+=10;
                }
                if(a->Life==2)
                {
                    addAsteroid(a->X,a->Y, 2, -2, 0, a->rotFactor+0.3, a->type);
                    addAsteroid(a->X,a->Y, -2.5, 2.5, 0, a->rotFactor, a->type);
                    deleteObject(&asteroids, j, true);
                    if(p->Img != debris) points+=20;
                }
                if(a->Life==3)
                {
                    addAsteroid(a->X, a->Y, 2,2,0, a->rotFactor+0.4, a->type);
	                addAsteroid(a->X, a->Y, -2,-2,0, a->rotFactor+0.2, a->type);
	                addAsteroid(a->X, a->Y, 3,-3,0, a->rotFactor, a->type);
                    deleteObject(&asteroids, j, true);
                    if(p->Img != debris) points+=30;
                }
                double rate=shouldDrop();
                if(rate<0.1){
                    LaunchProjectile(p->X,p->Y,1,-1,blackhole,250,4);
                }
                else if(rate<0.2){
                    LaunchProjectile(p->X,p->Y,1,-1,repair,250,4);
                }
                else if(rate<0.5){
                    LaunchProjectile(p->X,p->Y,1,-1,coin,250,4);
                }
                rate=1;
                if(p->type==1 && p->Img==blackhole)
                {
                    LaunchProjectile(p->X,p->Y,0,0,blackhole,100,5);
                }
                if(p->type!=5) deleteObject(&projectiles,i,true);
                bCol=true;
                break;
            }
            
        }if(bCol) break;
    }
}
void ShipShoot(Ship *ship)
{
    if(SDL_GetTicks()-ship->shipShootTime>=200 )
    { 
        Mix_PlayChannel(2, shot, 0);
        if(!shootspecial){          
            LaunchProjectile(ship->X+16,ship->Y-2,15,15,bullet,-1,1,ship);
            std::cout<<ship->shipShootLevel<<std::endl;
        }
        else{
            LaunchProjectile(ship->X+16,ship->Y-2,20,20,blackhole,-1,1,ship);
            shootspecial=false;
        }
        ship->shipShootTime=SDL_GetTicks();
    }
}
void LaunchPoof(int X, int Y, SDL_Surface * Img, int life, int type)
{
    LaunchProjectile(X, Y, -1, -0.4, Img, life,type);
    LaunchProjectile(X, Y, -0.2, -0.7, Img,life,type);
    LaunchProjectile(X, Y, 0.3, -0.6, Img,life,type);
    LaunchProjectile(X, Y, 0.96, -0.3, Img,life,type);
    LaunchProjectile(X, Y, -0.8, 0.5, Img,life,type);
    LaunchProjectile(X, Y, -0.3, 0.65, Img,life,type);
    LaunchProjectile(X, Y, 0.34, 0.67, Img,life,type);
    LaunchProjectile(X, Y, 0.93, 0.31, Img,life,type);
}
void LaunchBulletCircular(int X, int Y, SDL_Surface* Img, int life, int type)
{
    LaunchProjectile(X, Y, 1, 0, Img, life,type);
    LaunchProjectile(X, Y, 0.71, 0.71, Img,life,type);
    LaunchProjectile(X, Y, 0, 1, Img,life,type);
    LaunchProjectile(X, Y, -0.71, 0.71, Img,life,type);
    LaunchProjectile(X, Y, -1, 0, Img,life,type);
    LaunchProjectile(X, Y, -0.71, -0.71, Img,life,type);
    LaunchProjectile(X, Y, 0, -1, Img,life,type);
    LaunchProjectile(X, Y, 0.71, -0.71, Img,life,type);
}
double shouldDrop()
{
    srand((unsigned) time(&t));
    double randValue = (double) (rand()%100);
    return randValue/100;
}