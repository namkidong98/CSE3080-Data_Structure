#include <stdio.h>

// g, h, f 순으로 증가, g + h = f의 구조
int fibo_iterative(int n) { //n이 0부터 들어올 때의 경우, 1부터 들어오면 모양이 달라짐
	int g, h, i;
	int f = 0;
	if (n > 1) {
		g = 0;
		h = 1;
		for (i = 2; i <= n; i++) {
			f = g + h; //값을 증가시키고
			g = h; //다음 시행을 위해 값을 한칸씩 이동시킴
			h = f;
		}
	}
	else f = n;
	return f;
}

int fibo_recursive(int n) { //n이 0부터 들어올 때의 경우, 1부터 들어오면 모양이 달라짐
	if (n > 1) {
		return fibo_recursive(n - 1) + fibo_recursive(n - 2);
	}
	else return n;
}

int main() { //피보나치의 1항을 0번째로 볼 지, 1번째로 볼 지가 중요하다
	int n = 0; 
	scanf_s("%d", &n);
	printf("Fibonacci_iterative: \n");
	for (int i = 0; i < n; i++) { // i=0;i<n과 i=1;i<=n은 동일하지만 위에 피보나치의 코드가 달라진다
		printf("%d ", fibo_iterative(i));
	}
	printf("\n\n");
	printf("Fibonacci_recursive: \n");
	for (int i = 0; i < n; i++) {
		printf("%d ", fibo_recursive(i));
	}
}