#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STACK_SIZE 30
#define MAX_EXPR_SIZE 30

void stackFull() {
	printf("The stack is full.\n");
	exit(1);
}
void stackEmpty() {
	printf("The stack is empty.\n");
	exit(1);
}
void push_ch(char stack[][30], int* top, char token) {
	if ((*top) >= MAX_STACK_SIZE - 1) stackFull();
	stack[++(*top)][0] = token;
	stack[*top][1] = '\0';
} //push_str�� ������?
void push_op(char stack[], int* top, char token) {
	if ((*top) >= MAX_STACK_SIZE - 1) stackFull();
	stack[++(*top)] = token;
}
void push_str(char stack[][30], int* top, char* token) {
	if ((*top) >= MAX_STACK_SIZE - 1) stackFull();
	strcpy(stack[++(*top)], token);
}
char pop(char stack[], int* top) {
	if ((*top) == -1) stackEmpty();
	return stack[(*top)--];
}
char* pop_str(char stack[][30], int* top) {
	if ((*top) == -1) stackEmpty();
	return stack[(*top)--];
}

char getToken(char* symbol, char expr[], int* n) {
	*symbol = expr[(*n)++]; //�Է¹��� ���Ŀ��� char �ϳ� ������ symbol�� �ְ� ���� ������ ���� 1����
	return *symbol;
}

int precedence(char symbol) {
	if (symbol == '+' || symbol == '-') return 1;
	else if (symbol == '*' || symbol == '/' || symbol == '%') return 2;
	else if (symbol == '(' || symbol == ')') return 3;
	else return 0; //operand�� 0���� ����
}

void clear(char temp[], char op1[], char op2[]) {
	for (int i = 0; i < 30; i++) {
		temp[i] = '\0';
		op1[i] = '\0';
		op2[i] = '\0';
	}
}

void prefix(char expr[], char operator[], char operand[][30]) {
	char symbol; char token;
	int n = 0; 	int i = 0;
	int top_operator = 0; int top_operand = -1;
	char op2[30]; char op1[30]; char temp[30];
	operator[0] = '\0';
	for (token = getToken(&symbol, expr, &n); token != '\0'; token = getToken(&symbol, expr, &n)) {
		if (precedence(token) == 2) {
			op2[0] = getToken(&symbol, expr, &n);
			if (precedence(op2[0]) == 0) {
				op2[1] = '\0';
				strcpy(op1, pop_str(operand, &top_operand));
				temp[0] = token;
				temp[1] = '\0';
				strcat(temp, op1);
				strcat(temp, op2);
				push_str(operand, &top_operand, temp);
				clear(temp, op1, op2);
				continue;
			}
			else {
				push_op(operator, &top_operator, op2[0]);
				push_op(operator, &top_operator, token);
			}
		}
		//������ ������ �°�ȣ �ڿ� ���� *�� /�� ���Ǿ operand�� push���� ��
		//���ȣ�� ������ --> �°�ȣ ���� ������ �� ������
		else if (token == ')') { 
			for (token = pop(operator, &top_operator); token != '('; token = pop(operator, &top_operator)) {
				strcpy(op2, pop_str(operand, &top_operand));
				strcpy(op1, pop_str(operand, &top_operand));
				temp[0] = token;
				temp[1] = '\0';
				strcat(temp, op1);
				strcat(temp, op2);
				push_str(operand, &top_operand, temp);
				clear(temp, op1, op2);
			}
		}

		else {
			if (precedence(token) == 0) push_ch(operand, &top_operand, token);
			else push_op(operator, &top_operator, token);
		}
	}
	
	for (token = pop(operator, &top_operator); token != '\0'; token = pop(operator, &top_operator)) {
		strcpy(op2, pop_str(operand, &top_operand));
		strcpy(op1, pop_str(operand, &top_operand));
		temp[0] = token;
		temp[1] = '\0';
		strcat(temp, op1);
		strcat(temp, op2);
		push_str(operand, &top_operand, temp);
		clear(temp, op1, op2);
	}
	
	strcpy(op1, pop_str(operand, &top_operand));
	printf("%s", op1);
}

int main() {
	char expr[MAX_EXPR_SIZE];
	char operator[MAX_STACK_SIZE]; //�����ڸ� �ִ� stack
	char operand[MAX_STACK_SIZE][30]; //�ǿ����ڸ� �ִ� stack

	printf("Infix: ");
	scanf("%s", expr);

	printf("Prefix: ");
	prefix(expr, operator, operand);
	printf("\n");
}
