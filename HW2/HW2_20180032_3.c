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

int string_Compare(char* c1, char* c2) { //-1�̸� 1��° ���ڰ� ������, 1�̸� 2��° ���ڰ� ���� ��
	while (*c1 != '\0' && *c2 != '\0') {
		//���� �ҹ��� Ȥ�� �빮�ڳ����� �񱳶�� --> �����ϴ� ��� �ϸ� ��
		//�ҹ��ڿ� �빮�ڳ����� �񱳶�� --> �ҹ��ڸ� �빮�ڷ� ��ȯ�ϰ� ���ϸ� �ȴ�(������ �ҹ��ڸ� ���� ������ ����)
		if (*c1 < *c2) {
			if (*c2 - *c1 < 32 && *c2 >= 97 && *c1 <= 90) return 1; //�ҹ��� �빮�� ���̸鼭(ū�� �ҹ�����(97�̻�)) �ҹ��ڰ� �빮�ں��� �޼��̸�(���� 32�̻�) �ݴ��
			else return -1; 
		}
		else if (*c1 > *c2) {
			if (*c1 - *c2 < 32 && *c1 >= 97 && *c2 <= 90) return -1; //�ҹ��� �빮�� �񱳶��
			else return 1;
		}
		else {
			c1++;
			c2++;
		}

		//�� ��(��ĭ�� ��������)
		if (*c1 == ' ' && *c2 != ' ') return -1; //ª�� ���� ��찡 �� ���� ����
		else if (*c1 != ' ' && *c2 == ' ') return 1;
		else if (*c1 == ' ' && *c2 == ' ') {
			c1++;
			c2++;
		}
		
	}
	//�̸����� �� �� �� ���� �� ª�� ���
	if (*c1 == '\0' && *c2 == '\0') return 0; //������ ���� �̸�
	else if (*c1 == '\0' && *c2 != '\0') return -1; //ª�� ���� ��찡 �� ���� ����
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
	if (fp == NULL) { //���� ó��
		fprintf(stderr, "File open error.\n");
		exit(1);
	}

	for (int i = 0; i < num; i++) { //���Ͽ��� �о����
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