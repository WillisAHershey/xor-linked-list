#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#ifndef LIST_START
#define LIST_START 0
#endif

#ifndef LIST_END
#define LIST_END 100
#endif

#if LIST_START >= LIST_END
#error "LIST_START must be less than LIST_END"
#endif

struct xorList{
  int data;
  intptr_t nexxt; //This is a signed int type that is guaranteed to be wide enough to hold an entire pointer
};

void printAll(struct xorList *pt){
  intptr_t prev = (intptr_t)NULL;  //We're assuming the node passed to us is either the head or tail
  while(pt){
	printf("%d\n",pt->data);
	struct xorList *this = pt;
	pt = (struct xorList*)(pt->nexxt ^ prev);  //Decode xored pointers with last node's address to find next
	prev = (intptr_t)this; //Remember where we came from so we don't get lost
  }
}

void freeXorList(struct xorList *pt){
  intptr_t prev = (intptr_t)NULL;
  while(pt){
	struct xorList *this = pt;
	pt = (struct xorList*)(pt->nexxt ^ prev);
	prev = (intptr_t)this;
	free(this);
  }
}

int main(){
  struct xorList *head=malloc(sizeof(struct xorList));
  struct xorList *tail;
  struct xorList *pt=head;
  intptr_t lastNode = (intptr_t)NULL;	//Technically NULL is not guaranteed to be (void*)0 but it is guaranteed to be unique so this is safe
  for(int c=LIST_START;c<LIST_END;++c){
	struct xorList *newNode = malloc(sizeof(struct xorList));
	*pt = (struct xorList){.data = c,.nexxt = (intptr_t)newNode ^ lastNode};
	lastNode = (intptr_t)pt;
	pt = newNode;
  }
  *pt = (struct xorList){.data = LIST_END,.nexxt = lastNode ^ (intptr_t)NULL};
  tail = pt;
  printAll(head); //Despite this being two calls to the same function with opposite ends of the list, they will print all the data in the xor linked list in opposite directions
  printAll(tail);
  freeXorList(head); //To appease valgrind the observer
}
