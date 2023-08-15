#include <stdio.h>
#include <stdlib.h>
#define MAX_STACK_SIZE 100
#define MAX_EXPR_SIZE 100

typedef enum { lparen, rparen, plus, minus, times, divide, mod, eos, operand } precedence; //0부터 8까지 값을 매김(case문에 쓰기 위한 준비)
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
	*symbol = expr[(*n)++]; //입력받은 수식에서 char 하나 꺼내서 symbol에 넣고 다음 시행을 위해 1증가
	switch (*symbol) { //입력 받은 char 1개가 어떤 것인가
		case '(': return lparen;
		case ')': return rparen;
		case '+': return plus;
		case '-': return minus;
		case '*': return times;
		case '/': return divide;
		case '%': return mod;
		case '\0': return eos; //End of String
		default: return operand; //연산자 외에는 피연산자로 간주
	}
}

int eval() {
	precedence token;
	char symbol; //symbol은 수식에서 하나씩 값을 나눠서 받아올 공간
	int op1; int op2; int n = 0; //n은 입력 받은 수식을 읽어나가는 counter
	token = getToken(&symbol, &n); 
	while (token != eos) {
		if (token == operand) { //피연산자인 경우 출력
			push(symbol - '0'); //char형으로 받은 수는 ASCII코드를 기준으로 인식되므로 변환 필요 
		}
		else {
			op2 = pop(); //pop은 위에꺼부터 하니깐 2번째 연산자가 나중에 들어온 것(우측 피연산자)
			op1 = pop(); //두번째 pop된 것이 먼저 들어온 것(좌측 피연산자)
			switch (token) { //연산자를 만난 경우 -> 피연산자 2개 꺼내서 연산하고 연산한 값을 다시 push
			case plus: push(op1 + op2); break;
			case minus: push(op1 - op2); break;
			case times: push(op1 * op2); break;
			case divide: push(op1 / op2); break;
			case mod: push(op1 % op2);
			}
		}
		token = getToken(&symbol, &n);
	}
	return pop(); //마지막에는 모든 연산이 다 된 이후의 결과값만이 남아 있음
}

int main() {
	scanf_s("%s", expr, (unsigned int)sizeof(expr));
	int result = eval();
	printf("The result is %d", result);
}