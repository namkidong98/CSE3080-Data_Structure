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
	*symbol = expr[(*n)++]; //입력받은 수식에서 char 하나 꺼내서 symbol에 넣고 다음 시행을 위해 1증가
	switch (*symbol) { //입력 받은 char 1개가 어떤 것인가
	case '(': return '(';
	case ')': return ')';
	case '+': return '+';
	case '-': return '-';
	case '*': return '*';
	case '/': return '/';
	case '%': return '%';
	case '\0': return'\0'; //End of String
	case '#': return '#';
	default: return 'o'; //연산자 외에는 피연산자로 간주
	}
}

int eval(char stack[], char expr[], int* top) {
	char token;
	char symbol; //symbol은 수식에서 하나씩 값을 나눠서 받아올 공간
	int op1; int op2; int n = 0; //n은 입력 받은 수식을 읽어나가는 counter
	token = getToken(&symbol, expr, &n);
	while (token != '\0') {
		if (token == 'o') { //피연산자인 경우 출력
			push(stack, &(*top), symbol - '0'); //char형으로 받은 수는 ASCII코드를 기준으로 인식되므로 변환 필요 
		}
		else if (token == '#') {
			op1 = pop(stack, &(*top));
			push(stack, &(*top), -op1);
		}
		else {
			op2 = pop(stack, &(*top)); //pop은 위에꺼부터 하니깐 2번째 연산자가 나중에 들어온 것(우측 피연산자)
			op1 = pop(stack, &(*top)); //두번째 pop된 것이 먼저 들어온 것(좌측 피연산자)
			switch (token) { //연산자를 만난 경우 -> 피연산자 2개 꺼내서 연산하고 연산한 값을 다시 push
			case '+': push(stack, &(*top), op1 + op2); break;
			case '-': push(stack, &(*top), op1 - op2); break;
			case '*': push(stack, &(*top), op1 * op2); break;
			case '/': push(stack, &(*top), op1 / op2); break;
			case '%': push(stack, &(*top), op1 % op2);
			}
		}
		token = getToken(&symbol, expr, &n);
	}
	return pop(stack, &(*top)); //마지막에는 모든 연산이 다 된 이후의 결과값만이 남아 있음
}

int precedence(char token) {
	switch (token) { //입력 받은 char 1개가 어떤 것인가
	case '(': return 0;
	case ')': return 1;
	case '+': return 2;
	case '-': return 3;
	case '*': return 4;
	case '/': return 5;
	case '%': return 6;
	case '\0': return 7; //End of String
	case '#': return 8;
	default: return 9; //연산자 외에는 피연산자로 간주
	}
}

void postfix(char stack[], char expr[], char expr2[], int* top) {
	char symbol; char token;
	int n = 0; 	int i = 0;
	int isp[] = { 0, 19, 12, 12, 13, 13, 13, 0, 18, 0 }; // in stack precedence
	int icp[] = { 20, 19, 12, 12, 13, 13, 13, 0, 18, 0 }; //incoming precedence
	stack[0] = '\0'; //제일 아래에 제일 우선순위가 낮은 eos 두어서 새로 들어올 연산자는 무리 없이 들어오게 한다
	for (token = getToken(&symbol, expr, &n); token != '\0'; token = getToken(&symbol, expr, &n)) {
		if (token == '-') {
			if (*top == 0) token = '#'; // 시작부터 -로 시작하면
		}
		if (token == '(') { //좌괄호이면서
			token = getToken(&symbol, expr, &n);
			if (token == '-') { //그 다음꺼가 바로 -이면
				push(stack, &(*top), '('); //좌괄호를 스택에 넣고
				token = '#'; //이번 토큰은 마이너스가 아니라 negative로 간주한다
			}
			else { //다음 토큰이 -가 아니었으면
				push(stack, &(*top), '(');
			}
		}
		if (token == 'o') expr2[i++] = symbol;
		else if (token == ')') { //우괄호를 만나면 --> 좌괄호 만날 때까지 다 꺼내기
			while (stack[*top] != '(') {
				expr2[i++] = pop(stack, &(*top));
			}
			pop(stack, &(*top)); //좌괄호 빼내기
		}
		else {
			while (isp[precedence(stack[(*top)])] >= icp[precedence(token)]) { //새c로 들어오는 연산자의 우선순위가 스택 안의 연산자보다 작거나 같으면
				//작으면 높은 우선순위부터 해야 하니깐 pop, 같아도 먼저 온거부터 해야 하니깐 pop
				expr2[i++] = pop(stack, &(*top));
			}
			push(stack, &(*top), token); //그렇지 않으면 stack 안에 넣어라
		}
	}
	while ((token = pop(stack, &(*top))) != '\0') { //stack[0]에 넣은 EOS가 나올 때까지 남은 연산자 처리
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