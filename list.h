#ifndef _LIST_H_
#define _LIST_H_

#include<iostream>
#include <SDL2/SDL.h>


struct OBJECT
{
    int  index;
   	SDL_Surface *Img;
   	int X,Y,W,H,DIRX,DIRY,Life;
   	float FX,FY,DX,DY;
   	int Angle;
	OBJECT *next;
};




OBJECT *addfront(OBJECT *head, OBJECT *newp);
OBJECT *addend (OBJECT *head, OBJECT *newp);
OBJECT *addmiddle (OBJECT *head, OBJECT *newp);
OBJECT *update(OBJECT *head, int index, OBJECT temp);
OBJECT *getObject(OBJECT *head, int index);
void RemoveThing(OBJECT **head, int index);
void deleteList(OBJECT **head);
OBJECT *delelement(OBJECT *head, int index);
void deleteObject(OBJECT **head,int index, bool sort);
int length(OBJECT **head);
void printlist(OBJECT **head);
void reindex(OBJECT **head);
#endif