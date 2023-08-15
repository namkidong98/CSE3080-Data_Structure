#include <stdio.h>
#include <string.h>

int nfind(char* string, char* pat) {
	int i = 0;
	int j = 0;
	int start = 0;
	int lasts = (int)strlen(string) - 1; //0���� �����ϴ� �ε����� ������ -1�� �ϴ� ��!!
	int lastp = (int)strlen(pat) - 1;
	int endmatch = lastp;
	for (i = 0; endmatch <= lasts; endmatch++, start++) {
		if (string[endmatch] == pat[lastp]) {
			for (j = 0, i = start; j < lastp && string[i] == pat[j]; i++, j++); //i�� string���� �����̰� j�� pattern���� �����δ�
		}
		if (j == lastp) return start; //������ ã�� ���� �������� ��ȯ(j�� ���� ���� for���� ���ؼ��� lastp�� ������ �� ����
	}
	return -1; //������ �� ã���� ��
}

int main() {
	char string[] = "ababbaabaa";
	char pattern[] = "aab";
	int result = nfind(string, pattern);
	printf("pattern matched: %d", result);

	return 0;
}