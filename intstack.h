#ifndef COMMON_HEADERS
	#define COMMON_HEADERS
	#include <stdlib.h>
#endif

typedef struct stakrec {
	long element;
	struct stakrec *prev;
} mystack;
typedef mystack *stack;

void copyobj (long *element1, long element2) { *element1 = element2; }
void initialize (stack *s) { (*s) = NULL; }
long stackempty (stack s) { return s == NULL; }

void push (stack *s, long element) {
	mystack *a;
	a = (mystack *) malloc(sizeof(mystack));
	a->prev = *s;
	copyobj (&a->element, element);
	*s = a;
}

long pop (stack *s){
	if (stackempty(*s)) return 0;
	mystack *ptr;
	long top;
	if(stackempty(*s)) return 0;
	else {
		ptr = *s;
		(*s) = (*s)->prev;
		top = ptr->element;
		free(ptr);
		return top;
	}
}

long top(stack s) {
	return (stackempty(s)) ? 0 : s->element;
}
