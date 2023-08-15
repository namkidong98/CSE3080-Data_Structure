#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void pmatch_all(char* string, char* pat, int* failure) {
	int i = 0;
	int j = 0;
	int lens = strlen(string);
	int lenp = strlen(pat);

	while (i < lens && j < lenp) { //i는 string의 index, j는 pattern의 index
		if (string[i] == pat[j]) { //패턴이 일치하면
			i++, j++; //다음꺼 조사
			if (j == lenp) {
				printf("%d\n", i - lenp);
				j = 0;
				i = i - lenp + 1;
			}
		}
		else if (j == 0) i++; // 패턴의 시작(j==0)부터 일치하지 않으면 string의 다음거(i++)를 조사 
		else j = failure[j - 1] + 1; // pattern이 일치하다가 일치하지 않으면
		// j++이 된 상태인데 패턴이 안맞아 --> 이전꺼(패턴이맞은곳까지)의 failure값(몇번째 인덱스까지 일치했는지)에 +1 한 곳으로 j를 이동
		// 마지막에 +1은 i++된 상태이니 일치했던 index 다음 칸(failure[j-1] +1)과 i++을 비교해야 하니깐 더한 것이다.
	}
	//종료 경우의 수: 1) 패턴이 일치하여 i와 p가 모두 끝에 도달한 경우    2) 일치하는 패턴이 없어서 i = lens에 도달한 경우
	//1번의 경우를 첫번째 if문 안에 넣음으로써 해결
	
}

void fail(char* pat, int* failure) { //pat의 구조를 분석
	int i = 0;
	int j = 0;
	int n = strlen(pat);
	failure[0] = -1;
	for (j = 1; j < n; j++) { //failure[ n ] : n번째 인덱스까지의 값과 일치한다
		i = failure[j - 1]; // 어디까지 일치했는지 알려주는 failure을 i에 넣는다 --> i는 일치한 인덱스를 의미
		while ((pat[j] != pat[i + 1]) && (i >= 0)) { // 새로운 j칸의 글자가 일치했던 index 다음 칸(i+1)이 같지 않아
			i = failure[i]; // 그 인덱스는 어디까지 일치했던 것인치 파악 
			// --> 다음 칸은 일치하지 않아서 이어가지는 못하지만 앞 칸의 패턴들 중 살려서 활용할 수 있는게 얼마나 있는지 판단
		}
		if (pat[j] == pat[i + 1]) { //새로운 j칸의 글자와 기존의 일치했던 index 다음 칸이 같으면
			failure[j] = i + 1; // 일치했던 인덱스 값을 j번째 failure에 넣는다
		}
		else failure[j] = -1; // 시작부터 일치하지 않으면 -1을 대입 (왜냐하면 failure이 0이면 0번 인덱스랑은 일치했다는 의미니깐)
	}
}


int main() {
	char string[31];
	char pattern[31];
	int failure[31];

	//printf("String: ");
	scanf_s("%s", string, (unsigned int)sizeof(string));

	//printf("Pattern: ");
	scanf_s("%s", pattern, (unsigned int)sizeof(pattern));

	fail(pattern, failure);

	pmatch_all (string, pattern, failure);

}