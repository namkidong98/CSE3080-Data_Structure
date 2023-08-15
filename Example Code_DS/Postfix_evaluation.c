#include <stdio.h>
#include <stdlib.h>
#define MAX_STACK_SIZE 100
#define MAX_EXPR_SIZE 100

typedef enum { lparen, rparen, plus, minus, times, divide, mod, eos, operand } precedence; //0���� 8���� ���� �ű�(case���� ���� ���� �غ�)
int stack[MAX_STACK_SIZE]; char expr[MAX_EXPR_SIZE];
int top = -1;

void stackFull() {
	printf("The stack is full.\n");
	exit(1);
}
int stackEmpty() {
	printf("The stack is empty.\n");
	exit(1);
}
void push(int value) {
	if (top >= MAX_STACK_SIZE - 1) stackFull();
	stack[++top] = value;
	return;
}
int pop() {
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

int eval() {
	precedence token;
	char symbol; //symbol�� ���Ŀ��� �ϳ��� ���� ������ �޾ƿ� ����
	int op1; int op2; int n = 0; //n�� �Է� ���� ������ �о���� counter
	token = getToken(&symbol, &n); 
	while (token != eos) {
		if (token == operand) { //�ǿ������� ��� ���
			push(symbol - '0'); //char������ ���� ���� ASCII�ڵ带 �������� �νĵǹǷ� ��ȯ �ʿ� 
		}
		else {
			op2 = pop(); //pop�� ���������� �ϴϱ� 2��° �����ڰ� ���߿� ���� ��(���� �ǿ�����)
			op1 = pop(); //�ι�° pop�� ���� ���� ���� ��(���� �ǿ�����)
			switch (token) { //�����ڸ� ���� ��� -> �ǿ����� 2�� ������ �����ϰ� ������ ���� �ٽ� push
			case plus: push(op1 + op2); break;
			case minus: push(op1 - op2); break;
			case times: push(op1 * op2); break;
			case divide: push(op1 / op2); break;
			case mod: push(op1 % op2);
			}
		}
		token = getToken(&symbol, &n);
	}
	return pop(); //���������� ��� ������ �� �� ������ ��������� ���� ����
}

int main() {
	scanf_s("%s", expr, (unsigned int)sizeof(expr));
	int result = eval();
	printf("The result is %d", result);
}