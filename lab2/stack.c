#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node
{
	int value;
	struct Node* prev;
} Node;


Node* ntop = NULL;
int count = 0;

void push(int val)
{
	Node* nobj = malloc(sizeof(*nobj));
	nobj->value = val;
	nobj->prev = ntop;
	ntop = nobj;
	count++;
}

void pop()
{
	if(!ntop)
	{
		printf("Stack is empty!\n");
	}
	Node* temp = ntop;
	ntop = ntop->prev;
	free(temp);
	count--;
}

int top()
{
	if (!ntop)
	{
		printf("Stack is empty!!\n");
		return -1;
	}
	return ntop->value;
}

bool empty()
{
	return ntop == NULL;
}

int size()
{
	return count;
}

int main()
{
	printf("Is it empty 1(yes)/0(no): %d\n", empty());
	push(25);
	push(15);
	push(30);
	pop();
	printf("top: %d\n", top());
	printf("Is it empty 1(yes)/0(no): %d\n", empty());
	printf("The size of stack is: %d\n", size());

	return 0;
}
