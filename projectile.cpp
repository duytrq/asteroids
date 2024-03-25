#include "projectile.h"
OBJECT *projectiles = NULL;
SDL_Surface* bullet,*debris;
void loadProjectileIMG()
{
    bullet=IMG_Load("assets/images/bullet.png");
    if(bullet==NULL) std::cout<<"assets/images/bullet.png\n";
    debris=IMG_Load("assets/images/debris.png");
    if(debris==NULL) std::cout<<"asstets/images/debris.png\n";
}
void LaunchProjectile(double X, double Y, double DX, double DY, SDL_Surface *Img, int Life, Ship* ship){
    OBJECT p;
    if (projectiles == NULL) 
        p.index = 0;
    else{
        p.index = length(&projectiles);
    } 
    p.Img = Img;
    p.W = 16;
    p.H = 16;
    if (Life == -1 && ship!=NULL) {
    //ship projectile
        p.Angle = ship->Angle + 90;
        p.FX = (ship->X +(ship->W-10)/2);
        p.FY = (ship->Y +(ship->H-30)/2);
        p.DX = DX;
        p.DY = DY;
        p.X = round(p.FX);
        p.Y = round(p.FY);
    } else{
        p.Angle=30;
        p.X = X;
        p.Y = Y;
        p.FX = X;
        p.FY = Y;
        p.DX = DX;
        p.DY = DY;
    }
    p.Life = Life;
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
void moveProjectile()
{
    OBJECT *p;
    bool bCol=false;
    for(int i=0;i<length(&projectiles);i++)
    {
        p=getObject(projectiles,i);
        if(p->Life==-1)
        {
            p->FX+= (p->DX *coswithdegree(p->Angle))*-1;
            p->FY+= (p->DY *sinwithdegree(p->Angle))*-1;
            p->X=round(p->FX);
            p->Y=round(p->FY);
        }
        else
        {
            p->FX+= p->DX;
            p->FY+= p->DY;
            p->X=round(p->FX);
            p->Y=round(p->FY);
        }
        if(p->Life!=-1) p->Life--;
        if(p->X < -10 || p->X > SCREEN_W +10 || p->Y <-10 || p->Y > SCREEN_H + 10 || p->Life==0)
        {
            deleteObject(&projectiles,i,true);
        }
        SDL_Rect pj=getRect(p);
        for(int j=0;j<length(&asteroids);j++)
        {
            OBJECT *a;
            a=getObject(asteroids,j);
            SDL_Rect ast=getRect(a);
            if(Collided(pj,ast) && p->Life==-1)
            {
                if(a->Life==1)
                {
                    deleteObject(&asteroids, j, true);
                    LaunchPoof(a->X,a->Y, debris, 10);
                    if(p->Img != debris) points+=10;
                    continue;
                }
                if(a->Life==2)
                {
                    addAsteroid(a->X,a->Y, 1, 1, 0);
                    addAsteroid(a->X,a->Y, -1, -1, 0);
                    deleteObject(&asteroids, j, true);
                    if(p->Img != debris) points+=20;
                }
                if(a->Life==3)
                {
                    addAsteroid(a->X, a->Y, 1,1,1);
	                addAsteroid(a->X, a->Y, -1,-1,1);
	                addAsteroid(a->X, a->Y, 1,-1,1);
                    deleteObject(&asteroids, j, true);
                    if(p->Img != debris) points+=30;
                }
                deleteObject(&projectiles,i,true);
                bCol=true;
                break;
                }
            
        }if(bCol) break;
    }
}
void ShipShoot(Ship *ship)
{
    if(SDL_GetTicks()-ship->shipShootTime>=150)
    { 
        ship->shipShootTime=SDL_GetTicks();
        LaunchProjectile(ship->X+16,ship->Y-2,20,20,bullet,-1,ship);
    }
}
void LaunchPoof(int X, int Y, SDL_Surface * Img, int life)
{
      LaunchProjectile(X, Y, -1, -0.4, Img, life);
      LaunchProjectile(X, Y, -0.2, -0.7, Img,life);
      LaunchProjectile(X, Y, 0.3, -0.6, Img,life);
      LaunchProjectile(X, Y, 0.96, -0.3, Img,life);
      LaunchProjectile(X, Y, -0.8, 0.5, Img,life);
      LaunchProjectile(X, Y, -0.3, 0.65, Img,life);
      LaunchProjectile(X, Y, 0.34, 0.67, Img,life);
      LaunchProjectile(X, Y, 0.93, 0.31, Img,life);
}