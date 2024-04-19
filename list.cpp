#include "list.h"

OBJECT *newelement(OBJECT temp)
{
	OBJECT *newp;
	newp = new OBJECT;
	newp->index = temp.index;
	newp->Img = temp.Img;
	newp->X = temp.X;
	newp->Y = temp.Y;
	newp->W = temp.W;
	newp->H = temp.H;
	newp->DIRX = temp.DIRX;
	newp->DIRY = temp.DIRY;
	newp->Life = temp.Life;
	newp->DX = temp.DX;
	newp->DY = temp.DY;
	newp->FX = temp.FX;
	newp->FY = temp.FY;
	newp->Angle = temp.Angle;
	newp->size = temp.size;
	newp->velrate = temp.velrate;
	newp->rotFactor = temp.rotFactor;
	newp->type = temp.type;
    newp -> next = NULL;
	return newp;
}
void RemoveThing(OBJECT **head, int index)
{
	bool present = false;
	OBJECT *old;
	OBJECT **tracer = head;
	if ((*tracer)->index==index) present=true;
	while((*tracer) && !(present)){
		if ((*tracer)->index==index) present=true;
		tracer = &(*tracer)->next;
	}

	if(present)
	{
		old = *tracer;
		*tracer = (*tracer)->next;
		free(old); 
	}
}
void deleteList(OBJECT **head) 
{ 

   OBJECT *current = *head; 
   OBJECT *next = NULL;
   OBJECT **tracer=head; 
   while (current != NULL)  
   { 
       next = current->next; 
       free(current);
       current = next; 
   } 
    
   *tracer = NULL;
} 
// getObject 
OBJECT *getObject(OBJECT *head, int index)
{
	OBJECT *p;
	for (p = head; p != NULL; p = p -> next) {
            if (p -> index == index) {
		break;
	   }
	}
	 //p-> index = temp.index;	
	 return p;
	
}
OBJECT *delelement(OBJECT *head, int index)
{
	OBJECT *p, *prev;
	prev = NULL;
	for (p = head; p != NULL; p = p -> next) {
            if (p -> index == index) {
		if(prev == NULL)
		   head = p-> next;
		else
		   prev -> next = p -> next;
		free(p);	
		return head;
	   }
	   prev = p;	
	}
  return NULL;
}
OBJECT *addend (OBJECT *head, OBJECT *newp)
{
	OBJECT *p2; 	
	if (head == NULL)
		return newp;
	for (p2 = head; p2 -> next != NULL; p2 = p2 -> next)
		;
	p2 -> next = newp;
	return head;
}
int length(OBJECT **head)
{

	int count=0;
	OBJECT **tracer = head;
	while ((*tracer) != NULL) {
		count = count +1;	
		tracer = &(*tracer)->next;
	}
       return count;
}
void reindex(OBJECT **head)
{
	int count=0;	
	OBJECT *p=NULL;
	OBJECT **tracer = head;
	while ((*tracer) != NULL) {
		p = *tracer;
		p->index=count;
		count = count +1;
		tracer = &(*tracer)->next;
	}           
}

void deleteObject(OBJECT **head,int index, bool sort){
   OBJECT *p=*head;
  if (index == 0 || length(head) <=1 || p->index == index )
    RemoveThing(head,index);
  else 
    delelement(*head,index);
  if (sort == true) reindex(head); 
}
bool Collided(SDL_Rect a, SDL_Rect b)
{
    int leftA,rightA,bottomA,topA;
    int leftB,rightB,bottomB,topB;
    leftA = a.x;
    rightA= a.x+a.w;
    topA = a.y;
    bottomA= a.y+a.h;

    leftB = b.x;
    rightB= b.x+b.w;
    topB = b.y;
    bottomB= b.y+b.h;
    return bottomA>topB && topA<bottomB && rightA>leftB && leftA<rightB;
}