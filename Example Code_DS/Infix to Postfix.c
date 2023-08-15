#include <stdio.h>
#include <stdlib.h>
#define MAX_STACK_SIZE 10
#define MAX_EXPR_SIZE 100
char expr[MAX_EXPR_SIZE];

typedef enum { lparen, rparen, plus, minus, times, divide, mod, eos, operand } precedence; //0부터 8까지 값을 매김(case문에 쓰기 위한 준비)
precedence stack[MAX_STACK_SIZE];
int isp[] = { 0, 19, 12, 12, 13, 13, 13, 0 }; // in stack precedence
int icp[] = { 20, 19, 12, 12, 13, 13, 13, 0 }; //incoming precedence
int top = -1; //처음에 stack[0]에 eos를 넣고 시작하니깐

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
	stack[0] = eos; //제일 아래에 제일 우선순위가 낮은 eos 두어서 새로 들어올 연산자는 무리 없이 들어오게 한다
	for (token = getToken(&symbol, &n); token != eos; token = getToken(&symbol, &n)) {
		if (token == operand) printf("%c", symbol);
		else if (token == rparen) { //우괄호를 만나면 --> 좌괄호 만날 때까지 다 꺼내기
			while (stack[top] != lparen) {
				printToken(pop());
			}
			pop(); //좌괄호 빼내기
		}
		else {
			while (isp[stack[top]] >= icp[token]) { //새로 들어오는 연산자의 우선순위가 스택 안의 연산자보다 작거나 같으면
													//작으면 높은 우선순위부터 해야 하니깐 pop, 같아도 먼저 온거부터 해야 하니깐 pop
				printToken(pop());
			}
			push(token); //그렇지 않으면 stack 안에 넣어라
		}
	}
	while ((token = pop()) != eos) { //stack[0]에 넣은 EOS가 나올 때까지 남은 연산자 처리
		printToken(token);
	}
	printf("\n");
}

int main() {
	scanf_s("%s", expr, (unsigned int)sizeof(expr));
	postfix();
}