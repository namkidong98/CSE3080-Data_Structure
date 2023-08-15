#include <stdio.h>
#include <stdlib.h>
//매크로 확인 #define COMPARE (x,y) ((x) < (y)) ? -1:((x)==(y)) ? 0 : 1)


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
			SWAP(&list[i], &list[min]); //swap함수 넘길 때 주소값(포인터)로 넘겨야 하는 것 주의!
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
		case -1: //중간값보다 좌측에 찾는값이 위치
			right = middle -1;
			break;
		case 0:
			return middle;
		case 1: //중간값보다 우측에 찾는값이 위치
			left = middle + 1;
			break;
		}
	}
	return -1; //오류일 때
}

//recursive의 경우 while문을 통해 값을 산출하고 return하는 것이 아니라, 함수 내부에서 binsearch를 재호출하는 구조로 이루어져 있다.
int binsearch_recursive(int list[], int searchnum, int left, int right) {
	int middle = (left + right) / 2;
	switch (COMPARE(list[middle], searchnum)) {
	case -1: //중간값보다 좌측에 찾는값이 위치
		return binsearch_recursive(list, searchnum, left, middle - 1);
	case 0:
		return middle;
	case 1: //중간값보다 우측에 찾는값이 위치
		return binsearch_recursive(list, searchnum, middle + 1, right);
	}
	return -1; //오류일 때
}

int main() {
	int n = 0;
	int searchnum = 0;

	//get set of numbers
	scanf_s("%d", &n);
	int* list = (int*)malloc(sizeof(int) * n);
	for (int i = 0; i < n; i++) {
		scanf_s("%d", &list[i]); //입력 받을 때는 주소값으로!
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