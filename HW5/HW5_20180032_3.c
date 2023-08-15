#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct _node* node_pointer;
typedef struct _node {
	int key;
	node_pointer parent;
	node_pointer leftchild;
	node_pointer rightchild;
}node;
node_pointer root = NULL; //binary search tree�� root

node_pointer search(int key) {
	node_pointer ptr;
	if (root == NULL) return NULL;
	for (ptr = root; ;) {
		if (ptr->key == key) {
			return ptr;
		}
		else {
			if (ptr->leftchild != NULL) ptr = ptr->leftchild;
			else if (ptr->rightchild != NULL) ptr = ptr->rightchild;
			else return ptr; //ptr->leftchild, rightchild ��� NULL�� ���, �� leaf�� ���
		}
	}
}

void insert(int key) {
	node_pointer temp, ptr;
	
	ptr = search(key); //���� key�� tree�� �����ٸ� ptr�� ������ ���(tree�� leaf)�� ��ġ
	
	if (ptr != NULL) {
		if (ptr->key == key) {
			printf("Exist number\n");
			return;
		}
	}

	temp = (node_pointer)malloc(sizeof(node));
	temp->key = key;
	temp->leftchild = NULL;
	temp->rightchild = NULL;
	
	if (root) { //tree�� ��尡 �ִ� ���
		if (temp->key < ptr->key) {
			ptr->leftchild = temp;
			temp->parent = ptr;
			printf("Push %d\n", key);
		}
		else {
			ptr->rightchild = temp;
			temp->parent = ptr;
			printf("Push %d\n", key);
		}
	}
	else { //tree�� ��尡 ���� ���(root == NULL)
		temp->parent = NULL;
		root = temp;
		printf("Push %d\n", key);
	}
}

void pop() {
	node_pointer ptr, trail;
	
	if (root == NULL) {
		printf("The queue is empty\n");
		return;
	}
	int max = root->key;
	
	//�ִ��� ����
	for (ptr = root; ;) {
		if (ptr->key > max) max = ptr->key;
		if (ptr->leftchild != NULL) ptr = ptr->leftchild;
		else if (ptr->rightchild != NULL) ptr = ptr->rightchild;
		else break; //ptr->leftchild, rightchild ��� NULL�� ���, �� leaf�� ���
	}

	//�ִ��� ���� ��忡�� ����(ptr)
	for (ptr = root; ;) {
		if (ptr->key == max) break;
		if (ptr->leftchild != NULL) ptr = ptr->leftchild;
		else if (ptr->rightchild != NULL) ptr = ptr->rightchild;
	}

	if (ptr == root) { //�ִ��� root�� ���
		if (ptr->leftchild != NULL) { //leftchild�� ���� ����
			root = root->leftchild;
			printf("Pop %d\n", ptr->key);
			ptr->parent == NULL;
			free(ptr);
		}
		else if (ptr->rightchild != NULL) { //rightchild�� ���� ����
			root = root->rightchild;
			printf("Pop %d\n", ptr->key);
			ptr->parent == NULL;
			free(ptr);
		}
		else { //root 1���� �ִ� ���
			printf("Pop %d\n", root->key);
			free(ptr);
			root = NULL;
		}
	}
	else { //�ִ��� root�� �ƴ� ���
		if (ptr->leftchild == NULL && ptr->rightchild == NULL) { //���� ū ��尡 leaf�� ���
			printf("Pop %d\n", ptr->key);
			ptr->parent->leftchild = NULL;
			ptr->parent->rightchild = NULL;
			free(ptr);
		}
		else if (ptr->leftchild == NULL) { //rightchild�� ���� ����
			trail = ptr->parent;
			if (ptr->rightchild->key > trail->key) {
				trail->rightchild = ptr->rightchild;
				trail->leftchild = NULL;
				ptr->rightchild->parent = trail;
				printf("Pop %d\n", ptr->key);
				free(ptr);
			}
			else { //ptr->rightchild->key < trail->key
				trail->leftchild = ptr->rightchild;
				trail->rightchild = NULL;
				ptr->rightchild->parent = trail;
				printf("Pop %d\n", ptr->key);
				free(ptr);
			}
		}
		else if (ptr->rightchild == NULL) { //leftchild�� ���� ����
			trail = ptr->parent;
			if (ptr->leftchild->key > trail->key) {
				trail->rightchild = ptr->leftchild;
				trail->leftchild = NULL;
				ptr->leftchild->parent = trail;
				printf("Pop %d\n", ptr->key);
				free(ptr);
			}
			else { //ptr->rightchild->key < trail->key
				trail->leftchild = ptr->leftchild;
				trail->rightchild = NULL;
				ptr->leftchild->parent = trail;
				printf("Pop %d\n", ptr->key);
				free(ptr);
			}
		}
	}
}

void top() {
	node_pointer ptr;
	if (root == NULL) {
		printf("The queue is empty\n");
		return; //����
	}
	int max = root->key;
	for (ptr = root; ;) {
		if (ptr->key > max) max = ptr->key;
		if (ptr->leftchild != NULL) ptr = ptr->leftchild;
		else if (ptr->rightchild != NULL) ptr = ptr->rightchild;
		else break; //ptr->leftchild, rightchild ��� NULL�� ���, �� leaf�� ���
	}
	printf("The top is %d\n", max);
	return; //����
}


int main() {
	char command[10]; int key; int* max = 0;

	for (;;) {
		scanf("%s", command);
		if (strcmp(command, "push") == 0) {
			scanf("%d", &key);
			insert(key);
		}
		else if (strcmp(command, "top") == 0) {
			top();
		}
		else if (strcmp(command, "pop") == 0) {
			pop();
		}
		else { //q�� ���
			break;
		}
	}
	return 0;
}