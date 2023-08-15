#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_SIZE 50
#define MAX_NAME 20

typedef struct _node* node_pointer;
typedef struct _node{
	char name[MAX_NAME];
	node_pointer link; //friend linking
}node;

node_pointer stack[MAX_SIZE]; //각각의 index에는 새로 들어오는 이름의 node들이 할당됨
int top = -1;

void push(char* name) {
	if (top == MAX_SIZE) {
		fprintf(stderr, "Stack is full.");
		exit(1);
	}
	node_pointer temp;
	temp = (node_pointer)malloc(sizeof(node));
	strcpy(temp->name, name);
	temp->link = NULL;
	stack[++top] = temp;
}
void pop() {
	if (top == -1) {
		fprintf(stderr, "Stack is empty");
		exit(1);
	}
	node_pointer ptr, trail;
	for (ptr = stack[top]; ptr != NULL;) {
		trail = ptr;
		ptr = ptr->link;
		free(trail);
	}
	top--;
}

int main() {
	FILE* fp; FILE* fp2;
	char name1[MAX_NAME]; char name2[MAX_NAME]; char command; int i; int flag = 0;
	node_pointer ptr = NULL; node_pointer temp = NULL; node_pointer trail = NULL;

	fp = fopen("input.txt", "r");
	fp2 = fopen("output.txt", "w");
	for (;;) {
		fscanf(fp, "%c", &command);
		if (command == '\r') fscanf(fp, "%c", &command);
		if (command == '\n') fscanf(fp, "%c", &command);

		if (command == 'P' || command == 'L') {
			fscanf(fp, "%s", name1);

			if (command == 'P') { //create person
				for (i = 0; i <= top; i++) {
					if (strcmp(stack[top]->name, name1) == 0) {
						fprintf(stderr, "%s is already is in the list", name1);
						exit(1);
					}
				}
				push(name1);
			}

			else { //command == 'L' (list)
				for (i = 0; i <= top; i++) {
					if (strcmp(stack[i]->name, name1) == 0) break;
				}
				
				for (ptr =  stack[i]->link; ptr != NULL; ptr = ptr->link) {
					if (ptr == NULL) break; //친구가 없는 경우
					fprintf(fp2, "%s ", ptr->name);
				}
				fprintf(fp2, "\n");
			}
		}

		else if (command == 'F' || command == 'U' || command == 'Q') {
			fscanf(fp, "%s %s", name1, name2);


			if (command == 'F') { //record friend
				if (strcmp(name1, name2) == 0) break; //동일 인물이 스스로의 친구인 경우
				flag = 0; //이미 친구 목록에 있는지 확인하는 flag

				for (i = 0; i <= top; i++) {
					if (strcmp(stack[i]->name, name1) == 0) break;
				}
				for (ptr = stack[i]; ptr != NULL; ptr = ptr->link) {
					if (strcmp(ptr->name, name2) == 0) flag = 1; //이미 친구로 등록되어 있는 경우
				}
				
				if (flag == 0) {
					temp = (node_pointer)malloc(sizeof(node));
					strcpy(temp->name, name2);
					temp->link = NULL;
					if (stack[i]->link == NULL) stack[i]->link = temp;
					else {
						for (ptr = stack[i]; ptr->link != NULL; ptr = ptr->link);
						ptr->link = temp;
					}

					for (i = 0; i <= top; i++) {
						if (strcmp(stack[i]->name, name2) == 0) break;
					}
					temp = (node_pointer)malloc(sizeof(node));
					strcpy(temp->name, name1);
					temp->link = NULL;
					if (stack[i]->link == NULL) stack[i]->link = temp;
					else {
						for (ptr = stack[i]; ptr->link != NULL; ptr = ptr->link);
						ptr->link = temp;
					}
				}
			}

			else if (command == 'U') { //no longer friend
				if (strcmp(name1, name2) == 0) break; //동일 인물을 친구 해제 하려는 경우

				for (i = 0; i <= top; i++) {
					if (strcmp(stack[i]->name, name1) == 0) break;
				}
				for (ptr = stack[i]; ptr != NULL; ) {
					if (strcmp(ptr->name, name2) == 0) {
						trail->link = ptr->link;
						free(ptr);
						break;
					}
					trail = ptr;
					ptr = ptr->link;
				}

				for (i = 0; i <= top; i++) {
					if (strcmp(stack[i]->name, name2) == 0) break;
				}
				for (ptr = stack[i]; ptr != NULL; ) {
					if (strcmp(ptr->name, name1) == 0) {
						trail->link = ptr->link;
						free(ptr);
						break;
					}
					trail = ptr;
					ptr = ptr->link;
				}

			}

			else { //command == 'Q'
				for (i = 0; i <= top; i++) {
					if (strcmp(stack[i]->name, name1) == 0) break;
				}
				for (ptr = stack[i]->link; ptr != NULL;) { //name1과 name2에 같은 값이 들어오면? No
					if (ptr == NULL) break;
					if (strcmp(ptr->name, name2) == 0) {
						fprintf(fp2, "Yes\n");
						break;
					}
					ptr = ptr->link;
				}
				if(ptr == NULL) fprintf(fp2, "No\n");
			}
		}

		else if (command == 'X') {
			break;
		}

		else { //Error handling
			fprintf(stderr, "Wrong Information in input.txt");
			exit(1);
		}
	}

	for (i = top; i >= 0; i--) {
		pop();
	}
	
	fclose(fp2);
	fclose(fp);
}