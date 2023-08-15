#include <stdio.h>
#include <string.h>

int nfind(char* string, char* pat) {
	int i = 0;
	int j = 0;
	int start = 0;
	int lasts = (int)strlen(string) - 1; //0부터 시작하는 인덱스로 쓰려고 -1을 하는 것!!
	int lastp = (int)strlen(pat) - 1;
	int endmatch = lastp;
	for (i = 0; endmatch <= lasts; endmatch++, start++) {
		if (string[endmatch] == pat[lastp]) {
			for (j = 0, i = start; j < lastp && string[i] == pat[j]; i++, j++); //i는 string에서 움직이고 j는 pattern에서 움직인다
		}
		if (j == lastp) return start; //패턴을 찾은 곳의 시작점을 반환(j의 값은 위의 for문을 통해서만 lastp와 같아질 수 있음
	}
	return -1; //패턴을 못 찾았을 때
}

int main() {
	char string[] = "ababbaabaa";
	char pattern[] = "aab";
	int result = nfind(string, pattern);
	printf("pattern matched: %d", result);

	return 0;
}