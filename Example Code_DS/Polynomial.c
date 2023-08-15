#include <stdio.h>
#include <stdlib.h>
#define MAX_DEGREE 5 //0차부터 n차까지 --> 총 n+1개

typedef struct {
	int degree; //최고 차수
	int coef[MAX_DEGREE]; //각 차수에 해당하는 계수
}polynomial;

int COMPARE(int a, int b) {
	if (a > b) return 1;
	else if (a == b) return 0;
	else return -1;
}

polynomial Zero() { // 0짜리 다항식을 만듦
	polynomial a;
	a.degree = 0;
	for (int i = 0; i < MAX_DEGREE; i++) {
		a.coef[i] = 0;
	}
	return a;
}

int IsZero(polynomial a) { //다항식이 0인지 판단
	if (a.degree == 0 && a.coef[0] == 0) return 1; //true, zero
	else return 0; //false, not zero polynomial
}

int Coef(polynomial a, int expo) { //해당 지수의 계수 반환
	if (expo < MAX_DEGREE) {
		return a.coef[expo];
	}
	else {
		printf("Error: Improper expoenet.\n");
		return -1;
	}
}

int LeadExp(polynomial a) { //최고 차수 반환
	for (int i = MAX_DEGREE -1; i >=0 ; i--) {
		if (a.coef[i] != 0) {
			a.degree = i;
			return a.degree;
		}
	}
	return 0;
}

polynomial Attach(polynomial a, int coef, int expo) {
	if (expo < MAX_DEGREE && expo >= 0 && a.coef[expo] == 0) {
		a.coef[expo] = coef;
	}
	else if (expo < MAX_DEGREE && expo >= 0 && a.coef[expo] != 0) {
		printf("That exponents already has its coefficents.\n");
	}
	else printf("Error: Improper exponents.\n");

	a.degree = LeadExp(a);

	return a;
}

polynomial Remove(polynomial a, int expo) {
	//if (a.coef[expo] != 0) {
		a.coef[expo] = 0;
		//printf("Exponent is deleted.\n");
	//}
	//else printf("Error: Not existing Expoenent.\n");

	a.degree = LeadExp(a);
	return a;
}

polynomial Add(polynomial a, polynomial b) {
	polynomial d = Zero();
	int sum = 0;
	while (!IsZero(a) || !IsZero(b)) {
		switch ( COMPARE(LeadExp(a), LeadExp(b)) ) {
		case -1:
			d = Attach( d, Coef( b, LeadExp(b) ), LeadExp(b) );
			b = Remove(b, LeadExp(b));
			break;
		case 0:
			sum = Coef(a, LeadExp(a)) + Coef(b, LeadExp(b));
			if (sum) d = Attach(d, sum, LeadExp(a));
			a = Remove(a, LeadExp(a));
			b = Remove(b, LeadExp(b));
			break;
		case 1:
			d = Attach(d, Coef(a, LeadExp(a)), LeadExp(a));
			a = Remove(a, LeadExp(a));
		}
	} 
	return d;
}

polynomial Subtract(polynomial a, polynomial b) {

}

polynomial Mult(polynomial a, polynomial b) {

}

void Print_Polynomial(polynomial a) {
	int i;
	printf("%dx^%d ", a.coef[a.degree], a.degree);
	for (i = a.degree -1; i > 0; i--) {
		if(a.coef[i] !=0) printf("+ %dx^%d ", a.coef[i], i);
	}
	if (a.coef[0] != 0) printf("+ %d", a.coef[0]);
	printf("\n");
	return;
}

int main() {
	int coef, expo;
	polynomial a;
	polynomial b = { 4, {0, 1, 2, 3, 4 } };
	polynomial d = Zero();
	a = Zero();
	//b = Zero();
	int value;
	int num = 0;
	while (1) {
		printf("-----------------------\n");
		printf("1. Attach\n");
		printf("2. Remove\n");
		printf("3. Add\n");
		printf("4. Subtract\n");
		printf("5. Multiply\n");
		printf("6. Print polynomial\n");
		printf("7. exit\n");
		printf("-----------------------\n");
		scanf_s("%d", &value);
		switch (value) {
		case 1:
			printf("Put the coefficient and exponent: ");
			scanf_s("%d %d", &coef, &expo);
			a = Attach(a, coef, expo);
			break;
		case 2:
			printf("Put the exponent to delete: ");
			scanf_s("%d", &expo);
			a = Remove(a, expo);
			break;
		case 3:
			d = Add(a, b);
			Print_Polynomial(d);
			printf("Add Success.\n");
			break;
		case 4:
			
			break;
		case 5:

			break;
		case 6:
			Print_Polynomial(a);
			Print_Polynomial(b);
			break;
		case 7:
			printf("Program sucessfully ended.\n");
			exit(1);
		default:
			printf("Not proper command entered.\n");
		}
		printf("\n");
	}
	return 0;
}