#ifndef COMMON_HEADERS
	#define COMMON_HEADERS
	#include <stdlib.h>
#endif

typedef struct comp {
	long element;
	struct comp *next;
} component;
typedef component *list;

void copy(long *a, long b) { *a = b; }
void display(long a) { printf("%i", a); }

long displayoperator(long c) {
	switch (c) {
		case 43: printf("+"); return 1; break;
		case 45: printf("-"); return 1; break;
		case 42: printf("*"); return 1; break;
		case 47: printf("/"); return 1; break;
		case 37: printf("%%"); return 1; break;
		case 94: printf("^"); return 1; break;
		default: return 0;
	}
}

void init (list *l) {
	(*l) = (component *)malloc(sizeof(component));
	(*l)->next = NULL;
}

long empty (list l) { return l->next == NULL; }

void insert_in_list (long a, long position, list *l) {
	component *ptr, *ptr1;
	ptr = *l;
	while (position>1 && ptr->next!=NULL){
		--position;
		ptr=ptr->next;
	}
	if (position == 1){
		if (ptr->next == NULL) {
			ptr->next = (component *)malloc(sizeof(component));
			copy(&(ptr->next->element), a);
			ptr->next->next = NULL;
		}
		else {
			ptr1 = (component *)malloc(sizeof(component));
			copy(&ptr1->element, a);
			ptr1->next = ptr->next;
			ptr->next = ptr1;
		}
	}
}

void delete (long position, list *l) {
	component *ptr, *ptr1;
	ptr = (*l);
	while (position>1 && ptr->next!=NULL){
		--position;
		ptr=ptr->next;
	}
	if(ptr->next!=NULL){
		ptr1=ptr->next;
		ptr->next = ptr->next->next;
		free(ptr1);
	}
}

long getatpos (long position, list *l) {
	component *ptr, *objectptr;
	ptr = *l;
	while (position>1 && ptr->next!=NULL){
		--position;
		ptr=ptr->next;
	}
	if (position == 1 && (ptr->next) != NULL) {
		ptr->next->element;
	}
	else return 0;
}

/*void printlist(list l) {
	component *ptr;
	if (empty(l)) printf ("List is empty");
	else {
		ptr = l->next;
		while (ptr->next != NULL) {
			display (ptr->element);
			ptr = ptr->next;
		}
		display (ptr->element);
	}
}*/

void printlist(list l) {
	component *ptr;
	if (empty(l)) printf ("List is empty");
	else {
		ptr = l->next;
		while (ptr->next != NULL) {
			if(!displayoperator(ptr->element)) display (ptr->element);
			ptr = ptr->next;
		}
		if(!displayoperator(ptr->element)) display (ptr->element);
	}
}

component *prevcomp (int pos, list l) {
	component *ptr, *prv;
	if (empty(l) || l->next->next == NULL || pos < 2) return NULL;
	ptr = l;
	while (pos>1 && ptr->next!=NULL){
		prv = ptr->next;
		ptr = ptr->next;
		--pos;
	}
	if (pos>1) return NULL;
	return prv;
}

component *nextcomp (int pos, list l) {
	component *ptr;
	if (empty(l) || l->next->next == NULL || pos < 1) return NULL;
	ptr = l->next;
	while (pos>1 && ptr->next!=NULL){
		ptr = ptr->next;
		--pos;
	}
	if (ptr->next != NULL) return ptr->next;
	else return NULL;
}
