#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 50

typedef struct _node* treePointer;
typedef struct _node {
	int key;
	treePointer parent;
	treePointer leftChild;
	treePointer rightChild;
}node;
treePointer root;
int number = 0;
int stack[MAX_SIZE];
int top = -1;

void push(int command) {
	if (top == MAX_SIZE - 1) {
		fprintf(stderr, "The stack is full.");
		exit(EXIT_FAILURE);
	}
	stack[++top] = command;
}

int pop() {
	if (top == -1) {
		fprintf(stderr, "The stack is empty.");
		exit(EXIT_FAILURE);
	}
	return stack[top--];
}

void Insert(int key) {
	int i; int command; int save;
	treePointer temp, ptr;
	if (number == MAX_SIZE - 1) {
		printf("The heap is full\n");
		return;
	}

	temp = (treePointer)malloc(sizeof(node));
	temp->key = key;
	temp->leftChild = NULL;
	temp->rightChild = NULL;
	i = ++number;

	if (i == 1) {
		root = temp;
		return;
	}

	while (i != 1) {
		if (i % 2 == 0) push(-1); //leftChild
		else push(1); //rightChild
		i /= 2;
	}//어느 위치에 놓여야 하는지 root에서부터 가는 방향을 stack에 넣은 상태

	//시작은 root에서
	ptr = root;

	while (top != -1) {
		if (top == 0) {
			command = pop();
			if (command == -1) {
				if (temp->key > ptr->key) { //parent와 child 중 더 큰 값을 가진 것을 parent로 SWAP
					save = ptr->key;
					ptr->key = temp->key;
					temp->key = save;
				}
				ptr->leftChild = temp;
				temp->parent = ptr;
			}
			else if (command == 1) {
				if (temp->key > ptr->key) { //parent와 child 중 더 큰 값을 가진 것을 parent로 SWAP
					save = ptr->key;
					ptr->key = temp->key;
					temp->key = save;
				}
				ptr->rightChild = temp;
				temp->parent = ptr;
			}
		}
		else {
			command = pop();
			if (command == -1) {
				if (temp->key > ptr->key) { //parent와 child 중 더 큰 값을 가진 것을 parent로 SWAP
					save = ptr->key;
					ptr->key = temp->key;
					temp->key = save;
				}
				ptr = ptr->leftChild;
			}
			else if (command == 1) {
				if (temp->key > ptr->key) { //parent와 child 중 더 큰 값을 가진 것을 parent로 SWAP
					save = ptr->key;
					ptr->key = temp->key;
					temp->key = save;
				}
				ptr = ptr->rightChild;
			}
		}
	}

}

void Delete() {
	treePointer a = NULL; treePointer b = NULL; treePointer c = NULL;
	treePointer temp = NULL; int i, item, command, save;
	if (number != 0) item = root->key;

	if (number == 0) {
		printf("The heap is empty\n");
		return;
	}
	i = number; //1개 감소할 예정이기 때문
	if (i == 1) {
		temp = root;
		free(temp); root = NULL;
		number--;
		printf("Delete %d\n", item);
		return;
	}

	while (i != 1) { //마지막 노드까지의 경로를 구하기
		if (i % 2 == 0) push(-1); //leftChild
		else push(1); //rightChild
		i /= 2;
	}

	//초기 설정
	a = root;
	b = a->leftChild;
	c = a->rightChild;

	while (top != -1) {
		if (top == 0) { //tree의 leaf(마지막 경우 처리)
			command = pop();
			if (command == -1) {
				temp = b;
				a->key = temp->key;
				free(temp);
			}
			else if (command == 1) {
				temp = c;
				if (b->key > c->key) {
					a->key = b->key;
					b->key = c->key;
					free(temp);
				}
				else if (b->key < c->key) {
					a->key = c->key;
					free(temp);
				}
			}
			break;
		}

		if (b->key > c->key) a->key = b->key;
		else if (b->key < c->key) a->key = c->key;

		//다음 시행을 위한 준비 작업(a, b, c를 한칸 내려서 설정한다)
		command = pop();
		if (command == -1 && b->key > c->key) {
			a = a->leftChild;
			b = a->leftChild;
			c = a->rightChild;
		}
		else if (command == -1 && b->key < c->key) {
			c->key = b->key;
			if (c->key < c->leftChild->key || c->key < c->rightChild->key) {
				if (c->leftChild->key > c->rightChild->key) {
					save = c->key;
					c->key = c->leftChild->key;
					c->leftChild->key = save;
				}
				else {
					save = c->key;
					c->key = c->rightChild->key;
					c->rightChild->key = save;
				}
			}
			a = a->leftChild;
			b = a->leftChild;
			c = a->rightChild;
		}
		else if (command == 1 && b->key > c->key) {
			b->key = c->key;
			if (b->key < b->leftChild->key || b->key < b->rightChild->key) {
				if (b->leftChild->key > b->rightChild->key) {
					save = b->key;
					b->key = b->leftChild->key;
					b->leftChild->key = save;
				}
				else {
					save = b->key;
					b->key = b->rightChild->key;
					b->rightChild->key = save;
				}
			}
			a = a->rightChild;
			b = a->leftChild;
			c = a->rightChild;
		}
		else if (command == 1 && b->key < c->key) {
			a = a->rightChild;
			b = a->leftChild;
			c = a->rightChild;
		}

	}
	number--;
	printf("Delete %d\n", item);
}

void Search(treePointer ptr, int key, int* result) {
	if (!ptr) return;
	if (ptr->key == key) *result = 1;
	Search(ptr->leftChild, key, &(*result));
	Search(ptr->rightChild, key, &(*result));
}

int main() {
	char command; int key; int result = 0;

	for (;;) {
		scanf("%c", &command);
		switch (command) {
		case 'i':
			scanf("%d", &key);
			Search(root, key, &result);
			if (result == 1) {
				printf("Exist number\n");
				result = 0; //reset for next step
			}
			else {
				Insert(key);
				printf("Insert %d\n", key);
			}
			break;

		case 'd':
			Delete();
			break;

		case 'q':
			exit(EXIT_FAILURE);
		}

	}
}