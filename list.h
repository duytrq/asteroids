#ifndef _LIST_H_
#define _LIST_H_

#include<iostream>
#include <SDL2/SDL.h>


struct OBJECT
{
    int  index;
   	SDL_Surface *Img;
   	int Angle;
   	int X,Y,W,H,DIRX,DIRY,Life,size,type;
   	float FX,FY,DX,DY;
	double rotFactor,velrate;
	bool skill1 = true, skill2 = false;
	Uint32 lastDirchange;
	OBJECT *next;
};


bool Collided(SDL_Rect a, SDL_Rect b);
OBJECT *newelement(OBJECT temp);
OBJECT *addend (OBJECT *head, OBJECT *newp);
OBJECT *getObject(OBJECT *head, int index);
void RemoveThing(OBJECT **head, int index);
void deleteList(OBJECT **head);
OBJECT *delelement(OBJECT *head, int index);
void deleteObject(OBJECT **head,int index, bool sort);
int length(OBJECT **head);
void reindex(OBJECT **head);
#endif
