#include <stdio.h>
#include <stdlib.h>
#define MAX_STACK_SIZE 100

typedef struct {
	int buf[MAX_STACK_SIZE]; //값을 넣을 공간
	int top; //현재 위치를 나타낼 index값
}stack; //stack의 자료구조를 typedef로 구현

void stackEmpty() {
	fprintf(stderr,"The stack is empty\n");
	return;
}

void stackFull() {
	printf("The stack is full.\n");
	return;
}

void push(stack *stack, int value) {
	if (stack->top >= MAX_STACK_SIZE - 1) {
		stackFull();
	}
	stack->top += 1;
	stack->buf[stack->top] = value;
	printf("%d is pushed\n", value);
	return;
}

void pop(stack *stack) {
	if (stack->top == -1) {
		stackEmpty();
		return;
	}
	else printf("%d is popped out\n", stack->buf[stack->top]); //stack->top에서 top이 -1값이 있어서 버퍼오버런?
	stack->top -=1;
	return;
}

void print(stack* stack) {
	if (stack->top == -1) {
		stackEmpty();
		return;
	}
	for (int i = 0; i <= stack->top; i++) {
		printf("%d ", stack->buf[i]);
	}
	printf("\n");
	return;
}
int main() {
	stack stack;
	stack.top = -1;
	int value;
	int num = 0;
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
			push(&stack, num);
			break;
		case 2:
			pop(&stack);
			break;
		case 3:
			print(&stack);
			break;
		case 4:
			printf("Program sucessfully ended.\n");
			exit(1);
		default :
			printf("Not proper command entered.\n");
		}
		printf("\n");
	}
	return 0;
}