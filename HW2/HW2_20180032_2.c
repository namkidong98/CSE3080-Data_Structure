#include <stdio.h>
#include <stdlib.h>

int check_array(int len, int* str);

int main() {
	int len = 0;
	scanf_s("%d", &len);
	int* str = (int*)malloc(sizeof(int) * len);
	int a = 0;
	for (int i = 0; i < len; i++) {
		scanf_s("%d", &a);
		str[i] = a;
	}
	int result = check_array(len, str);

	free(str);
	printf("%d", result);
	return 0;
}

int check_array(int len, int* str) {
	int* cmp = (int*)malloc(sizeof(int) * len);
	for (int i = 0; i < len; i++) {
		cmp[i] = 0;
	}

	int min = str[0];
	for (int i = 0; i < len; i++) { //�ּڰ� ���ϱ�
		if (min > str[i]) min = str[i];
	}
	int index = 0;
	for (int i = 0; i < len; i++) { //�ּڰ����� ���̸� ���ϰ� �׿� �´� �ε����� �ֱ�
		index = str[i] - min;
		cmp[index] = index;
	}
	for (int i = 0; i < len; i++) { //�ڱ��ڽ��� ���� 0�ΰͺ��� 1, 2, 3���� �о����� return 1, �׷��� ������ return 0
		if (cmp[i] == i);
		else {
			return 0;
		}
	}
	free(cmp);
	return 1;
}