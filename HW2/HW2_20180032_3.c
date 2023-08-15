#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

void SWAP(char* c1, char* c2) {
	int i = 0;
	char* temp = (char*)malloc(sizeof(char) * 30);
	if (temp != NULL) {
		for (i = 0; i < 30; i++) {
			temp[i] = '\0';
		}
		for (i = 0; i < 30; i++) {
			temp[i] = c1[i];
			if (c1[i] == '\n') break;
		}
		for (i = 0; i < 30; i++) {
			c1[i] = '\0';
		}
		for (i = 0; i < 30; i++) {
			c1[i] = c2[i];
			if (c2[i] == '\n') break;
		}
		for (i = 0; i < 30; i++) {
			c2[i] = '\0';
		}
		for (i = 0; i < 30; i++) {
			c2[i] = temp[i];
			if (temp[i] == '\n') break;
		}
		free(temp);
	}
	else exit(EXIT_FAILURE);
	return;
}

int string_Compare(char* c1, char* c2) { //-1이면 1번째 인자가 빠른것, 1이면 2번째 인자가 빠른 것
	while (*c1 != '\0' && *c2 != '\0') {
		//같은 소문자 혹은 대문자끼리의 비교라면 --> 원래하던 대로 하면 됨
		//소문자와 대문자끼리의 비교라면 --> 소문자를 대문자로 변환하고 비교하면 된다(같으면 소문자를 작은 것으로 간주)
		if (*c1 < *c2) {
			if (*c2 - *c1 < 32 && *c2 >= 97 && *c1 <= 90) return 1; //소문자 대문자 비교이면서(큰게 소문자쪽(97이상)) 소문자가 대문자보다 뒷순이면(차가 32이상) 반대로
			else return -1; 
		}
		else if (*c1 > *c2) {
			if (*c1 - *c2 < 32 && *c1 >= 97 && *c2 <= 90) return -1; //소문자 대문자 비교라면
			else return 1;
		}
		else {
			c1++;
			c2++;
		}

		//성 비교(빈칸을 기준으로)
		if (*c1 == ' ' && *c2 != ' ') return -1; //짧게 끝난 경우가 더 빠른 순서
		else if (*c1 != ' ' && *c2 == ' ') return 1;
		else if (*c1 == ' ' && *c2 == ' ') {
			c1++;
			c2++;
		}
		
	}
	//이름까지 비교 후 한 쪽이 더 짧은 경우
	if (*c1 == '\0' && *c2 == '\0') return 0; //완전히 같은 이름
	else if (*c1 == '\0' && *c2 != '\0') return -1; //짧게 끝난 경우가 더 빠른 순서
	else if (*c1 != '\0' && *c2 == '\0') return 1;
	else return -2;
}

void sorting(char* str[], int num) {
	int i, j;
	int min = 0;
	for (i = 0; i < num - 1; i++) {
		min = i;
		for (j = i + 1; j < num; j++) {
			if (string_Compare(str[min], str[j]) == -1);
			else if (string_Compare(str[min], str[j]) == 1) min = j;
		}
		SWAP(str[i], str[min]);
	}
}

int main() {
	FILE* fp;
	int num = 0;
	int j = 0;
	scanf_s("%d", &num);
	char** str = (char**)malloc(sizeof(char*) * num);
	if (str == NULL) exit(EXIT_FAILURE);
	for (int i = 0; i < num; i++) {
		str[i] = (char*)malloc(sizeof(char) * 30);
		if (str[i] == NULL) exit(EXIT_FAILURE);
	}
	
	fp = fopen("student.txt", "r");
	if (fp == NULL) { //에러 처리
		fprintf(stderr, "File open error.\n");
		exit(1);
	}

	for (int i = 0; i < num; i++) { //파일에서 읽어오기
		fgets(str[i], 30, fp);
		for (j = 0; j < 30; j++) {
			if (str[i][j] == '\0') str[i][j] = '\n';
		}
	}

	sorting(str, num);

	for (int i = 0; i < num; i++) {
		printf("%s", str[i]);
	}

	fclose(fp);
	
	for (int i = 0; i < num; i++) {
		free(str[i]);
	}
	free(str);
}