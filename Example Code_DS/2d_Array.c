#include <stdio.h>
#include <stdlib.h>

int** make2dArray(int rows, int cols) {
	int** x;
	x = (int**)malloc(sizeof(int*) * rows);
	for (int i = 0; i < rows; i++) {
		x[i] = (int*)malloc(sizeof(int) * cols);
	}
	return x; //�������� �̸��� base�� �ּҰ��� ��Ÿ����
}

void put_element(int** arr, int rows, int cols) {
	int i, j;
	for (i = 0; i < rows; i++) {
		for (j = 0; j < cols; j++) {
			arr[i][j] = 10 * i + j;
		}
	}
}

void print2dArray(int** arr, int rows, int cols) {
	int i, j;
	for (i = 0; i < rows; i++) {
		for (j = 0; j < cols; j++) {
			printf("%d ", arr[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

int main() {
	int** arr;
	int rows, cols;
	printf("Put the rows and colums to make a 2 dimensional Array\n");
	scanf_s("%d %d", &rows, &cols);

	arr = make2dArray(rows, cols); //2���� �迭 �����

	put_element(arr, rows, cols); //2���� �迭 �� �Ҵ��ϱ�

	print2dArray(arr, rows, cols); //2���� �迭 �� ����ϱ�
	
	for (int i = 0; i < rows; i++) {
		free(arr[i]);
	}
	free(arr);
	return 0;
}