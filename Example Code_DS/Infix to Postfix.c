#include <stdio.h>
#include <stdlib.h>
#define MAX_STACK_SIZE 10
#define MAX_EXPR_SIZE 100
char expr[MAX_EXPR_SIZE];

typedef enum { lparen, rparen, plus, minus, times, divide, mod, eos, operand } precedence; //0���� 8���� ���� �ű�(case���� ���� ���� �غ�)
precedence stack[MAX_STACK_SIZE];
int isp[] = { 0, 19, 12, 12, 13, 13, 13, 0 }; // in stack precedence
int icp[] = { 20, 19, 12, 12, 13, 13, 13, 0 }; //incoming precedence
int top = -1; //ó���� stack[0]�� eos�� �ְ� �����ϴϱ�

void stackFull() {
	printf("The stack is full.\n");
	exit(1);
}
precedence stackEmpty() {
	printf("The stack is empty.\n");
	exit(1);
}
void push(precedence token) {
	if (top >= MAX_STACK_SIZE - 1) stackFull();
	stack[++top] = token;
	return;
}
precedence pop() {
	if (top == -1) return stackEmpty();
	return stack[top--];
}
precedence getToken(char* symbol, int* n) {
	*symbol = expr[(*n)++]; //�Է¹��� ���Ŀ��� char �ϳ� ������ symbol�� �ְ� ���� ������ ���� 1����
	switch (*symbol) { //�Է� ���� char 1���� � ���ΰ�
	case '(': return lparen;
	case ')': return rparen;
	case '+': return plus;
	case '-': return minus;
	case '*': return times;
	case '/': return divide;
	case '%': return mod;
	case '\0': return eos; //End of String
	default: return operand; //������ �ܿ��� �ǿ����ڷ� ����
	}
}

void printToken(precedence token) {
	switch (token) {
	case plus: printf("+"); break;
	case minus: printf("-"); break;
	case times: printf("*"); break;
	case divide: printf("/"); break;
	case mod: printf("%%"); break;
	default: exit(1);
	}
}

void postfix() {
	char symbol;
	int n = 0;
	precedence token;
	stack[0] = eos; //���� �Ʒ��� ���� �켱������ ���� eos �ξ ���� ���� �����ڴ� ���� ���� ������ �Ѵ�
	for (token = getToken(&symbol, &n); token != eos; token = getToken(&symbol, &n)) {
		if (token == operand) printf("%c", symbol);
		else if (token == rparen) { //���ȣ�� ������ --> �°�ȣ ���� ������ �� ������
			while (stack[top] != lparen) {
				printToken(pop());
			}
			pop(); //�°�ȣ ������
		}
		else {
			while (isp[stack[top]] >= icp[token]) { //���� ������ �������� �켱������ ���� ���� �����ں��� �۰ų� ������
													//������ ���� �켱�������� �ؾ� �ϴϱ� pop, ���Ƶ� ���� �°ź��� �ؾ� �ϴϱ� pop
				printToken(pop());
			}
			push(token); //�׷��� ������ stack �ȿ� �־��
		}
	}
	while ((token = pop()) != eos) { //stack[0]�� ���� EOS�� ���� ������ ���� ������ ó��
		printToken(token);
	}
	printf("\n");
}

int main() {
	scanf_s("%s", expr, (unsigned int)sizeof(expr));
	postfix();
}