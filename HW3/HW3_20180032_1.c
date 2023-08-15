#include <stdio.h>
#include <stdlib.h>
#define MAX_STACK_SIZE 100
#define MAX_EXPR_SIZE 100

void stackFull() {
	printf("The stack is full.\n");
	exit(1);
}
int stackEmpty() {
	printf("The stack is empty.\n");
	exit(1);
}
void push(char stack[], int* top, int value) {
	if ((*top) >= MAX_STACK_SIZE - 1) stackFull();
	stack[++(*top)] = value;
	return;
}
int pop(char stack[], int* top) {
	if ((*top) == -1) return stackEmpty();
	return stack[(*top)--];
}
char getToken(char* symbol, char expr[], int* n) {
	*symbol = expr[(*n)++]; //�Է¹��� ���Ŀ��� char �ϳ� ������ symbol�� �ְ� ���� ������ ���� 1����
	switch (*symbol) { //�Է� ���� char 1���� � ���ΰ�
	case '(': return '(';
	case ')': return ')';
	case '+': return '+';
	case '-': return '-';
	case '*': return '*';
	case '/': return '/';
	case '%': return '%';
	case '\0': return'\0'; //End of String
	case '#': return '#';
	default: return 'o'; //������ �ܿ��� �ǿ����ڷ� ����
	}
}

int eval(char stack[], char expr[], int* top) {
	char token;
	char symbol; //symbol�� ���Ŀ��� �ϳ��� ���� ������ �޾ƿ� ����
	int op1; int op2; int n = 0; //n�� �Է� ���� ������ �о���� counter
	token = getToken(&symbol, expr, &n);
	while (token != '\0') {
		if (token == 'o') { //�ǿ������� ��� ���
			push(stack, &(*top), symbol - '0'); //char������ ���� ���� ASCII�ڵ带 �������� �νĵǹǷ� ��ȯ �ʿ� 
		}
		else if (token == '#') {
			op1 = pop(stack, &(*top));
			push(stack, &(*top), -op1);
		}
		else {
			op2 = pop(stack, &(*top)); //pop�� ���������� �ϴϱ� 2��° �����ڰ� ���߿� ���� ��(���� �ǿ�����)
			op1 = pop(stack, &(*top)); //�ι�° pop�� ���� ���� ���� ��(���� �ǿ�����)
			switch (token) { //�����ڸ� ���� ��� -> �ǿ����� 2�� ������ �����ϰ� ������ ���� �ٽ� push
			case '+': push(stack, &(*top), op1 + op2); break;
			case '-': push(stack, &(*top), op1 - op2); break;
			case '*': push(stack, &(*top), op1 * op2); break;
			case '/': push(stack, &(*top), op1 / op2); break;
			case '%': push(stack, &(*top), op1 % op2);
			}
		}
		token = getToken(&symbol, expr, &n);
	}
	return pop(stack, &(*top)); //���������� ��� ������ �� �� ������ ��������� ���� ����
}

int precedence(char token) {
	switch (token) { //�Է� ���� char 1���� � ���ΰ�
	case '(': return 0;
	case ')': return 1;
	case '+': return 2;
	case '-': return 3;
	case '*': return 4;
	case '/': return 5;
	case '%': return 6;
	case '\0': return 7; //End of String
	case '#': return 8;
	default: return 9; //������ �ܿ��� �ǿ����ڷ� ����
	}
}

void postfix(char stack[], char expr[], char expr2[], int* top) {
	char symbol; char token;
	int n = 0; 	int i = 0;
	int isp[] = { 0, 19, 12, 12, 13, 13, 13, 0, 18, 0 }; // in stack precedence
	int icp[] = { 20, 19, 12, 12, 13, 13, 13, 0, 18, 0 }; //incoming precedence
	stack[0] = '\0'; //���� �Ʒ��� ���� �켱������ ���� eos �ξ ���� ���� �����ڴ� ���� ���� ������ �Ѵ�
	for (token = getToken(&symbol, expr, &n); token != '\0'; token = getToken(&symbol, expr, &n)) {
		if (token == '-') {
			if (*top == 0) token = '#'; // ���ۺ��� -�� �����ϸ�
		}
		if (token == '(') { //�°�ȣ�̸鼭
			token = getToken(&symbol, expr, &n);
			if (token == '-') { //�� �������� �ٷ� -�̸�
				push(stack, &(*top), '('); //�°�ȣ�� ���ÿ� �ְ�
				token = '#'; //�̹� ��ū�� ���̳ʽ��� �ƴ϶� negative�� �����Ѵ�
			}
			else { //���� ��ū�� -�� �ƴϾ�����
				push(stack, &(*top), '(');
			}
		}
		if (token == 'o') expr2[i++] = symbol;
		else if (token == ')') { //���ȣ�� ������ --> �°�ȣ ���� ������ �� ������
			while (stack[*top] != '(') {
				expr2[i++] = pop(stack, &(*top));
			}
			pop(stack, &(*top)); //�°�ȣ ������
		}
		else {
			while (isp[precedence(stack[(*top)])] >= icp[precedence(token)]) { //��c�� ������ �������� �켱������ ���� ���� �����ں��� �۰ų� ������
				//������ ���� �켱�������� �ؾ� �ϴϱ� pop, ���Ƶ� ���� �°ź��� �ؾ� �ϴϱ� pop
				expr2[i++] = pop(stack, &(*top));
			}
			push(stack, &(*top), token); //�׷��� ������ stack �ȿ� �־��
		}
	}
	while ((token = pop(stack, &(*top))) != '\0') { //stack[0]�� ���� EOS�� ���� ������ ���� ������ ó��
		expr2[i++] = token;
	}
	expr2[i] = '\0';
}

int main() {
	char expr1[MAX_EXPR_SIZE];
	char expr2[MAX_EXPR_SIZE];
	char stack[MAX_STACK_SIZE];
	int top = 0;

	printf("Input: ");
	scanf("%s", expr1);

	postfix(stack, expr1, expr2, &top);
	printf("Postfix: ");
	for (int i = 0; expr2[i] != '\0'; i++) {
		printf("%c", expr2[i]);
	}
	printf("\n");
	top = -1;
	int result = eval(stack, expr2, &top);
	printf("Result: %d", result);
	printf("\n");
}