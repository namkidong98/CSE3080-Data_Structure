#include <stdio.h>
#include <stdlib.h>
#define MAX_STACK_SIZE 100

typedef struct {
	int key;
}element;

element stack[MAX_STACK_SIZE];
int top = -1;

void stackEmpty() {
	fprintf(stderr, "The stack is empty\n");
	return;
}

void stackFull() {
	printf("The stack is full.\n");
	return;
}

void push(element item) {
	if (top >= MAX_STACK_SIZE - 1) {
		stackFull();
	}
	stack[++top] = item;
	printf("%d is pushed\n", item.key);
	return;
}

void pop() {
	if (top == -1) {
		stackEmpty();
		return;
	}
	else printf("%d is popped out\n", stack[top--].key);
	return;
}

void print() {
	if (top == -1) {
		stackEmpty();
		return;
	}
	for (int i = 0; i <= top; i++) {
		printf("%d ", stack[i].key);
	}
	printf("\n");
	return;
}
int main() {
	int value;
	int num = 0;
	element item;
	while (1) {
		printf("-----------------------\n");
		printf("1. push\n");
		printf("2. pop\n");
		printf("3. print\n");
		printf("4. exit\n");
		printf("-----------------------\n");
		scanf_s("%d", &value);
		switch (value) {
		case 1:
			printf("The value you want to push: ");
			scanf_s("%d", &num);
			item.key = num;
			push(item);
			break;
		case 2:
			pop();
			break;
		case 3:
			print();
			break;
		case 4:
			printf("Program sucessfully ended.\n");
			exit(1);
		default:
			printf("Not proper command entered.\n");
		}
		printf("\n");
	}
	return 0;
}