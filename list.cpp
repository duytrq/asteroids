#include "list.h"

OBJECT *newelement(OBJECT temp)
{
	OBJECT *newp;
	newp = (OBJECT *) malloc (sizeof(OBJECT));
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
		free(old); // free up remainder of list element 
	}
}
void deleteList(OBJECT **head) 
{ 
   /* deref head_ref to get the real head */
   OBJECT *current = *head; 
   OBJECT *next = NULL;
   OBJECT **tracer=head; 
   while (current != NULL)  
   { 
       next = current->next; 
       free(current);
       current = next; 
   } 
    
   /* deref head_ref to affect the real head back 
      in the caller. */

   *tracer = NULL;
} 


// updatelement: remove from list the first instance of an element 
OBJECT *update(OBJECT *head, int index, OBJECT temp)
{
	OBJECT *p;
	for (p = head; p != NULL; p = p -> next) {
            if (p -> index == index) {
		break;
	   }
	}
	 p-> index = temp.index;	
	 return head;
	
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

OBJECT *addfront(OBJECT *head, OBJECT *newp)
{
	newp -> next = head;
	return newp;
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

void printlist(OBJECT **head)
{
	OBJECT **tracer = head;
	  while ((*tracer) != NULL) {
		printf("%d \n",(*tracer)->index);
		tracer = &(*tracer)->next;
	  }  
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