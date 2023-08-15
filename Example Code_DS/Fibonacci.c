#include <stdio.h>

// g, h, f ������ ����, g + h = f�� ����
int fibo_iterative(int n) { //n�� 0���� ���� ���� ���, 1���� ������ ����� �޶���
	int g, h, i;
	int f = 0;
	if (n > 1) {
		g = 0;
		h = 1;
		for (i = 2; i <= n; i++) {
			f = g + h; //���� ������Ű��
			g = h; //���� ������ ���� ���� ��ĭ�� �̵���Ŵ
			h = f;
		}
	}
	else f = n;
	return f;
}

int fibo_recursive(int n) { //n�� 0���� ���� ���� ���, 1���� ������ ����� �޶���
	if (n > 1) {
		return fibo_recursive(n - 1) + fibo_recursive(n - 2);
	}
	else return n;
}

int main() { //�Ǻ���ġ�� 1���� 0��°�� �� ��, 1��°�� �� ���� �߿��ϴ�
	int n = 0; 
	scanf_s("%d", &n);
	printf("Fibonacci_iterative: \n");
	for (int i = 0; i < n; i++) { // i=0;i<n�� i=1;i<=n�� ���������� ���� �Ǻ���ġ�� �ڵ尡 �޶�����
		printf("%d ", fibo_iterative(i));
	}
	printf("\n\n");
	printf("Fibonacci_recursive: \n");
	for (int i = 0; i < n; i++) {
		printf("%d ", fibo_recursive(i));
	}
}