#include "game.h"
Ship Player;
SDL_Event ev;
bool KeyPressed=false,addMonster;
long keystate[1000];
int lastX,lastY,lastAngle,maxLives=3;
int price1=10,price2=10,price3=10;
void HandleKey(long sym, bool down)
{
    switch (sym)
    {
        case SDLK_w:
            sym=SDL_SCANCODE_W;
            break;
        case SDLK_d:
            sym=SDL_SCANCODE_D;
            break;
        case SDLK_s:
            sym=SDL_SCANCODE_S;
            break;
        case SDLK_a:
            sym=SDL_SCANCODE_A;
            break;
        case SDLK_SPACE:
            sym=SDL_SCANCODE_SPACE;
            break;
        case SDLK_e:
            sym=SDL_SCANCODE_E;
            break;
        default:
            break;
    }
    if(sym>=0 && sym<=1000)
    {
        keystate[sym]=down;
    }
}
void ClearKey(){
    for(int i=0;i<1000;i++){
        keystate[i]=0;
    }
    KeyPressed = false;
}
void NewGame(int level)
{
    gReady = false; addMonster=false;
    int a,e,tDIRX,tDIRY,tSIZE,tX,tY,tType;
    double tRotate,tDX,tDY;
    if (asteroids != NULL) deleteList(&asteroids);
    if (enemy != NULL) deleteList(&enemy);
    if (projectiles != NULL) deleteList(&projectiles);
    if(!Player.skillAct.isStarted()) Player.skillAct.start();
    Player.explosion=false;
    Player.Lives = maxLives; 
    Player.X=200; 
    Player.Y=200;
    lastX=Player.X;
    lastY=Player.Y;
    Player.VX = 0;
    Player.VY = 0;
    Player.W = 50;
    Player.H = 70;
    Player.Angle = 0;  
    lastAngle = Player.Angle;
    srand((unsigned) time(&t));
    for(int i=0;i<level*2;i++)
    {
        tX = rand() % 1280;
        tY = rand() % 720;
        tDX = (rand()%70)/10 -3.5;
        tDY = (rand()%70)/10 -3.5;
        if(tDX>=-2 && tDX<=0) tDX=-2;
        if(tDY>=-2 && tDY<=0) tDY=-2;
        if(tDX<= 2 && tDX>=0) tDX= 2;
        if(tDY<= 2 && tDY>=0) tDY= 2;
        tSIZE = rand() % 3;
        tRotate = (rand()%100)/30 + 2;
        a = rand() % 3;
        tType = a;
        addAsteroid(tX,tY,tDX, tDY, tSIZE, tRotate, tType);
    }
    if(currLevel>=3)
        {e = rand() % 2;
        if(e==0) tDIRX = 1;
        else tDIRX = -1;
        e = rand() % 2;
        if(e==0) tDIRY = 1;
        else tDIRY = -1;
        tX = rand() % 1280;
        tY = rand() % 720;
        e = rand()%2 +1;
        addEnemy(tX,tY,tDIRX,tDIRY,1);}
    Mix_PlayMusic(theme, -1);
}
void UpdateGame()
{
    lastX=Player.X;
    lastY=Player.Y;
    lastAngle=Player.Angle;
    if(keystate[SDL_SCANCODE_W]) {
        Player.Up();
    }
    if(keystate[SDL_SCANCODE_A]) {
        Player.Left();
    }
    if(keystate[SDL_SCANCODE_D]) {
        Player.Right();
    }
    if(keystate[SDL_SCANCODE_SPACE]){
        ShipShoot(&Player);
    }
    if(keystate[SDL_SCANCODE_E]){
        Player.SkillActivate();
    }
    if(Player.shipstill)
    {
        Player.Halted();
        if (Mix_Playing(1) != 0) Mix_FadeOutChannel(1,500);	
    }
    if(Player.skillIsActive){
        Player.ShipState = Player.SKILL;
        if (Mix_Playing(4) == 0) Mix_PlayChannel(4, shield, 0);
    }
    Player.Update();
    moveAsteroid(Player);
    moveEnemy(Player);
    moveProjectile(Player);
    if (Player.X != lastX || Player.Y != lastY || Player.Angle != lastAngle) Player.shipstill = false;
    else Player.shipstill = true;
    if(length(&asteroids) == currLevel && !addMonster)
    {
        int e,tX,tY,tDIRX,tDIRY;
        double dirX,dirY,distance;
        for(int i=0;i<currLevel/2;i++){
            e = rand() % 2;
            if(e==0) tDIRX = 1;
            else tDIRX = -1;
            e = rand() % 2;
            if(e==0) tDIRY = 1;
            else tDIRY = -1;
            tX = rand() % 1280;
            tY = rand() % 720;
            dirX=Player.X-tX;
            dirY=Player.Y-tY;
            distance=sqrt(dirX*dirX+dirY*dirY);
            while(distance<300){
                tX = rand() % 1280;
                tY = rand() % 720;
                dirX=Player.X-tX;
                dirY=Player.Y-tY;
                distance=sqrt(dirX*dirX+dirY*dirY);
            }
            addEnemy(tX,tY,tDIRX,tDIRY,2);
        }
        addMonster = true;
    }
    if(length(&asteroids) == 0 && length(&enemy)==0 && length(&projectiles)==0){
        Mix_HaltChannel(-1);
        deleteList(&projectiles);
        SDL_Delay(100);
        currLevel+=1;
        NewGame(currLevel);
    }
}
void SaveGame(){
    std::ofstream game("game.txt", std::ios::out | std::ios::trunc);
    if(game.is_open()){
        game << currLevel << " "<<points<< " "<<money<<" "<<price1<<" "<<price2<<" "<<price3<<" "<<maxLives;
        game.close();
    }
    std::ofstream ship("ship.txt", std::ios::out | std::ios::trunc);
    if(ship.is_open())
    {
        ship << Player.X <<" "<< Player.Y<<" "<< Player.VX<<" " << Player.VY<<" " << Player.W<<" "
        <<Player.H<<" "<<Player.Angle<<" "<<Player.Lives<<" "<<Player.shipShootLevel<<" "<<Player.skillDuration;
        ship.close();
    }
    std::ofstream asteroid("asteroids.txt", std::ios::out | std::ios::trunc);
    if(asteroid.is_open())
    {
        for(int i=0;i<length(&asteroids);i++){
            OBJECT *p;
            p=getObject(asteroids,i);
            //addAsteroid(tX,tY,tDX, tDY, tSIZE, tRotate, tType);
            asteroid << p->X << " "<<p->Y<<" "<<p->DX<<" "<<p->DY<<" "<<p->size<<" "<<p->rotFactor<<" "<<p->type<<'\n';
        }
        asteroid.close();
    }
    std::ofstream enemies("enemy.txt", std::ios::out | std::ios::trunc);
    if(enemies.is_open())
    {
        for(int i=0;i<length(&enemy);i++){
            OBJECT *p;
            p=getObject(enemy,i);
            //std::cout<<i<<" ";
            // void addEnemy(int X,int Y,int DIRX, int DIRY,int type)
            enemies << p->X << " "<<p->Y<<" "<<p->DIRX<<" "<<p->DIRY<<" "<<p->type<<'\n';
        }
        enemies.close();
    }
}
void LoadGame(){
    gReady = false; Uint32 skillTime;
    Player.skillAct.start();
    std::fstream game("game.txt");
    if(game.is_open()){
        game >> currLevel >>points >> money >>price1 >>price2 >>price3>>maxLives;
        game.close();
    }
    std::fstream ship("ship.txt");
    if(ship.is_open()){
        ship >>Player.X>>Player.Y>>Player.VX>>Player.VY>>Player.W>>Player.H
        >>Player.Angle>>Player.Lives>>Player.shipShootLevel>>Player.skillDuration;
        ship.close();
    }
    std::fstream asteroid("asteroids.txt");
    if(asteroid.is_open()){
        int tX,tY,tSize,tType;
        double tDX, tDY, tRotate;
        while(asteroid >> tX >> tY >> tDX >> tDY>> tSize >> tRotate>> tType)
        {
            addAsteroid(tX,tY,tDX, tDY, tSize, tRotate, tType);
        }
        asteroid.close();
    }
    std::fstream enemies("enemy.txt");
    if (enemies.is_open()) {
        int tX, tY, tDIRX, tDIRY, tType;
        while (enemies >> tX >> tY >> tDIRX >> tDIRY >> tType) {
            addEnemy(tX, tY, tDIRX, tDIRY, tType);
        }
        enemies.close();
    }
}
void GameClean()
{
    if(asteroids!=NULL) deleteList(&asteroids);
    if(projectiles!=NULL) deleteList(&projectiles);
    if(enemy!=NULL) deleteList(&enemy);
}