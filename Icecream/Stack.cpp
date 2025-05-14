#include "Stack.h"
#include "stdlib.h"


void init_cup(Stack* icecream_cup) {
	icecream_cup->capacity = MAX_CUPSIZE;
	icecream_cup->top = -1;
	icecream_cup->icecream_number = (int*)malloc(icecream_cup->capacity * sizeof(int));
}

int is_full(Stack* icecream_cup) {
	return (icecream_cup->top == (icecream_cup->capacity - 1));
}

void push(int choice, Stack* icecream_cup) {
	if (is_full(icecream_cup)) {
		icecream_cup->capacity *= 2;
		icecream_cup->icecream_number = (int*)realloc(icecream_cup->icecream_number, icecream_cup->capacity * sizeof(int));
	}
	icecream_cup->icecream_number[++icecream_cup->top] = choice;
}

int is_empty(Stack* icecream_cup) {
	return (icecream_cup->top == -1);
}

int pop(Stack* icecream_cup) {
	if (is_empty(icecream_cup))
		return -1;
	else
		return icecream_cup->icecream_number[icecream_cup->top--];
}