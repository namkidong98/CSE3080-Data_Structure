#include <stdio.h>
#include <stdlib.h>
//��ũ�� Ȯ�� #define COMPARE (x,y) ((x) < (y)) ? -1:((x)==(y)) ? 0 : 1)


void SWAP(int* a, int* b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

void sort(int list[], int n) {
	int i, j, min;
	for (i = 0; i < n - 1; i++) {
		min = i;
		for (j = i + 1; j < n; j++) {
			if (list[min] > list[j]) min = j;
			SWAP(&list[i], &list[min]); //swap�Լ� �ѱ� �� �ּҰ�(������)�� �Ѱܾ� �ϴ� �� ����!
		}
	}
}

int COMPARE(int x, int y) {
	if (x > y) return -1;
	else if (x == y) return 0;
	else return 1;
}

int binsearch(int list[], int searchnum, int left, int right) {
	int middle;
	while (left <= right) {
		middle = (left + right) / 2;
		switch (COMPARE(list[middle], searchnum)) {
		case -1: //�߰������� ������ ã�°��� ��ġ
			right = middle -1;
			break;
		case 0:
			return middle;
		case 1: //�߰������� ������ ã�°��� ��ġ
			left = middle + 1;
			break;
		}
	}
	return -1; //������ ��
}

//recursive�� ��� while���� ���� ���� �����ϰ� return�ϴ� ���� �ƴ϶�, �Լ� ���ο��� binsearch�� ��ȣ���ϴ� ������ �̷���� �ִ�.
int binsearch_recursive(int list[], int searchnum, int left, int right) {
	int middle = (left + right) / 2;
	switch (COMPARE(list[middle], searchnum)) {
	case -1: //�߰������� ������ ã�°��� ��ġ
		return binsearch_recursive(list, searchnum, left, middle - 1);
	case 0:
		return middle;
	case 1: //�߰������� ������ ã�°��� ��ġ
		return binsearch_recursive(list, searchnum, middle + 1, right);
	}
	return -1; //������ ��
}

int main() {
	int n = 0;
	int searchnum = 0;

	//get set of numbers
	scanf_s("%d", &n);
	int* list = (int*)malloc(sizeof(int) * n);
	for (int i = 0; i < n; i++) {
		scanf_s("%d", &list[i]); //�Է� ���� ���� �ּҰ�����!
	}

	//Sorting for binary search
	sort(list, n);
	printf("Sorting completed\n");
	for (int i = 0; i < n; i++) {
		printf("%d ", list[i]);
	}
	printf("\n");

	//Binary Search
	printf("Put the number you want to find: ");
	scanf_s("%d", &searchnum);
	int result = binsearch(list, searchnum, 0, n);
	printf("(Binary Search)Index you want to search: %d", result + 1);
	printf("\n");

	//Binary Search recursively
	result = binsearch_recursive(list, searchnum, 0, n);
	printf("(Binary Search_recursive)Index you want to search: %d", result + 1);
	free(list);
}