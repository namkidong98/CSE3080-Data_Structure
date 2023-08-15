#include <stdio.h>
#include <stdlib.h>
//매크로 확인 #define SWAP(x,y,t) ((t) = (x), (x) = (y), (y) = (t))

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

int main() {
	int n = 0;
	scanf_s("%d", &n);
	int* list = (int*)malloc(sizeof(int) * n);
	for (int i = 0; i < n; i++) {
		scanf_s("%d", &list[i]); //입력 받을 때는 주소값으로!
	}
	sort(list, n);
	for (int i = 0; i < n; i++) {
		printf("%d ", list[i]);
	}
	free(list);
}