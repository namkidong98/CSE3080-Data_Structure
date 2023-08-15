#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int pmatch(char* string, char* pat, int* failure) {
	int i = 0;
	int j = 0;
	int lens = strlen(string);
	int lenp = strlen(pat);
	while (i < lens && j < lenp) { //i�� string�� index, j�� pattern�� index
		if (string[i] == pat[j]) { //������ ��ġ�ϸ�
			i++, j++; //������ ����
		}
		else if (j == 0) i++; // ������ ����(j==0)���� ��ġ���� ������ string�� ������(i++)�� ���� 
		else j = failure[j - 1] + 1; // pattern�� ��ġ�ϴٰ� ��ġ���� ������
		// j++�� �� �����ε� ������ �ȸ¾� --> ������(�����̸���������)�� failure��(���° �ε������� ��ġ�ߴ���)�� +1 �� ������ j�� �̵�
		// �������� +1�� i++�� �����̴� ��ġ�ߴ� index ���� ĭ(failure[j-1] +1)�� i++�� ���ؾ� �ϴϱ� ���� ���̴�.
	}
	//���� ����� ��: 1) ������ ��ġ�Ͽ� i�� p�� ��� ���� ������ ���    2) ��ġ�ϴ� ������ ��� i = lens�� ������ ���
	return((j == lenp) ? (i - lenp) : -1); //1���� ��쿡�� ������ �����ϴ� �κ��� �ε���(i - lenp)�� ��ȯ
	//2���� ��쿡�� -1(��ġ�ϴ� ������ ����)�� ��ȯ
}

void fail(char* pat, int* failure) { //pat�� ������ �м�
	int i = 0;
	int j = 0;
	int n = strlen(pat);
	failure[0] = -1;
	for (j = 1; j < n; j++) { //failure[ n ] : n��° �ε��������� ���� ��ġ�Ѵ�
		i = failure[j - 1]; // ������ ��ġ�ߴ��� �˷��ִ� failure�� i�� �ִ´� --> i�� ��ġ�� �ε����� �ǹ�
		while ((pat[j] != pat[i + 1]) && (i >= 0)) { // ���ο� jĭ�� ���ڰ� ��ġ�ߴ� index ���� ĭ(i+1)�� ���� �ʾ�
			i = failure[i]; // �� �ε����� ������ ��ġ�ߴ� ����ġ �ľ� 
			// --> ���� ĭ�� ��ġ���� �ʾƼ� �̾���� �������� �� ĭ�� ���ϵ� �� ����� Ȱ���� �� �ִ°� �󸶳� �ִ��� �Ǵ�
		}
		if (pat[j] == pat[i + 1]) { //���ο� jĭ�� ���ڿ� ������ ��ġ�ߴ� index ���� ĭ�� ������
			failure[j] = i + 1; // ��ġ�ߴ� �ε��� ���� j��° failure�� �ִ´�
		}
		else failure[j] = -1; // ���ۺ��� ��ġ���� ������ -1�� ���� (�ֳ��ϸ� failure�� 0�̸� 0�� �ε������� ��ġ�ߴٴ� �ǹ̴ϱ�)
	}
}

int main() {
	char string[31];
	char pattern[31];
	int failure[31];

	printf("String: ");
	scanf_s("%s", string, (unsigned int)sizeof(string));

	printf("Pattern: ");
	scanf_s("%s", pattern, (unsigned int)sizeof(pattern));

	fail(pattern, failure);

	int result = pmatch(string, pattern, failure);

	printf("%d", result);
}