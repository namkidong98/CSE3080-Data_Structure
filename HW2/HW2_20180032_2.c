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
	for (int i = 0; i < len; i++) { //최솟값 구하기
		if (min > str[i]) min = str[i];
	}
	int index = 0;
	for (int i = 0; i < len; i++) { //최솟값과의 차이를 구하고 그에 맞는 인덱스에 넣기
		index = str[i] - min;
		cmp[index] = index;
	}
	for (int i = 0; i < len; i++) { //자기자신을 빼서 0인것부터 1, 2, 3으로 읽어지면 return 1, 그렇지 않으면 return 0
		if (cmp[i] == i);
		else {
			return 0;
		}
	}
	free(cmp);
	return 1;
}