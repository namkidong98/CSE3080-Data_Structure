#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 50

typedef struct _node* tree_pointer;
typedef struct _node {
	int key;
	tree_pointer leftchild;
	tree_pointer rightchild;
	tree_pointer parent;
}tree_node;

int input[MAX_SIZE];
int stack[MAX_SIZE];
int top = -1;
tree_pointer root = NULL;

void push(int key) {
	if (top == MAX_SIZE - 1) {
		fprintf(stderr, "Stack is full.");
		exit(1);
	}
	stack[++top] = key;
}

void pop() {
	if (top == -1) {
		fprintf(stderr, "Stack is empty.");
		exit(1);
	}
	top--;
}

void make_tree_preorder(int num) {
	int i = 0; tree_pointer temp, ptr;
	
	temp = (tree_pointer)malloc(sizeof(tree_node));
	temp->key = input[0];
	temp->leftchild = NULL;
	temp->rightchild = NULL;
	push(input[0]);
	root = temp;
	ptr = root;
	for (i = 1; i < num; i++) {
		if (stack[top] > input[i]) {
			temp = (tree_pointer)malloc(sizeof(tree_node));
			temp->key = input[i];
			temp->leftchild = NULL;
			temp->rightchild = NULL;
			push(input[i]);
			ptr->leftchild = temp;
			temp->parent = ptr;
			ptr = ptr->leftchild;
		}
		else if (stack[top] < input[i]) {
			while (stack[top] < input[i]) {
				pop();
				if (top != -1) ptr = ptr->parent;
				if (top == -1) break;
			}
			temp = (tree_pointer)malloc(sizeof(tree_node));
			temp->key = input[i];
			temp->leftchild = NULL;
			temp->rightchild = NULL;
			push(input[i]);
			ptr->rightchild = temp;
			temp->parent = ptr;
			ptr = ptr->rightchild;
		}
	}


}

void inorder(tree_pointer ptr) {
	if (ptr) {
		inorder(ptr->leftchild);
		printf("%d ", ptr->key);
		inorder(ptr->rightchild);
	}
}

void postorder(tree_pointer ptr) {
	if (ptr) {
		postorder(ptr->leftchild);
		postorder(ptr->rightchild);
		printf("%d ", ptr->key);
	}
}

int main() {
	int num, i, j, flag = 0; 
	scanf("%d", &num);
	for (i = 0; i < num; i++) {
		scanf("%d", &input[i]);
	}
	for (i = 0; i < num - 1; i++) {
		for (j = i + 1; j < num; j++) {
			if (input[i] == input[j]) flag = 1;
		}
	}
	if (flag == 1) {
		printf("cannot construct BST\n");
	}
	else {
		make_tree_preorder(num);

		printf("Inorder: ");
		inorder(root);
		printf("\n");
		printf("Postorder: ");
		postorder(root);
		printf("\n");
	}
}
