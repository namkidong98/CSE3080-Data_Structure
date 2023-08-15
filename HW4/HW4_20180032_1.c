#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 50

typedef enum {head, entry} tagfield;
typedef struct _entry_node {
	int row;
	int col;
	int value;
} entry_node;

typedef struct _matrix_node* matrix_pointer;
typedef struct _matrix_node {
	matrix_pointer down;
	matrix_pointer right;
	tagfield tag;
	union {
		matrix_pointer next;
		entry_node entry;
	} u;
} matrix_node;

matrix_pointer hdnode[MAX_SIZE];
matrix_pointer hdnode_t[MAX_SIZE];

matrix_pointer mread() {
	int num_rows, num_cols, num_terms, num_heads, i;
	int row, col, value, current_row;
	matrix_pointer temp, last, node;
	FILE* fp;
	fp = fopen("input.txt", "r");
	fscanf(fp, "%d %d %d\n", &num_rows, &num_cols, &num_terms);
	num_heads = (num_cols > num_rows) ? num_cols : num_rows;

	node = (matrix_pointer)malloc(sizeof(matrix_node));
	node->tag = entry;
	node->u.entry.row = num_rows;
	node->u.entry.col = num_cols;
	node->u.entry.value = num_terms;
	if (!num_heads) node->right = node;
	else {
		for (i = 0; i < num_heads; i++) {
			temp = (matrix_pointer)malloc(sizeof(matrix_node));
			hdnode[i] = temp;
			hdnode[i]->tag = head;
			hdnode[i]->right = temp;
			hdnode[i]->u.next = temp;
		}
		current_row = 0;
		last = hdnode[0]; //last는 매트릭스 포인터
		for (i = 0; i < num_terms; i++) {
			fscanf(fp, "%d %d %d\n", &row, &col, &value);
			if (row > current_row) { //close current row
				last->right = hdnode[current_row];
				current_row = row;
				last = hdnode[row];
			}
			temp = (matrix_pointer)malloc(sizeof(matrix_node));
			temp->u.entry.row = row; temp->tag = entry;
			temp->u.entry.col = col; temp->u.entry.value = value;
			last->right = temp; //link into row list
			last = temp;
			hdnode[col]->u.next->down = temp; //link into column list
			hdnode[col]->u.next = temp;
		}
		//close last row
		last->right = hdnode[current_row];
		//close all column lists
		for (i = 0; i < num_cols; i++) {
			hdnode[i]->u.next->down = hdnode[i];
		}
		//link all header nodes together
		for (i = 0; i < num_heads - 1; i++) {
			hdnode[i]->u.next = hdnode[i + 1];
		}
		hdnode[num_heads - 1]->u.next = node;
		node->right = hdnode[0];
	}

	fclose(fp);
	return node;
}

void mwrite(matrix_pointer node) {
	int i; FILE* fp;
	matrix_pointer temp, head;
	head = node->right;

	fp = fopen("output.txt", "w");
	fprintf(fp, "%d %d %d\n", node->u.entry.row, node->u.entry.col, node->u.entry.value); //첫 번째 줄 
	
	for(i = 0; i < node->u.entry.row; i++) {
		for (temp = head->right; temp != head; temp = temp->right) {
			fprintf(fp, "%d %d %d\n", temp->u.entry.row, temp->u.entry.col, temp->u.entry.value);
		}
		head = head->u.next;
	}

	fclose(fp);
}


void merase(matrix_pointer node) {
	matrix_pointer x, y; matrix_pointer head;
	head = node->right; int i;

	for (i = 0; i < node->u.entry.row; i++) {
		y = head->right;
		while (y != head) {
			x = y;
			y = y->right;
			free(x);
		}
		x = head; head = head->u.next; free(x);
	}

	//free remaining head nodes
	y = head;
	while (y != node) {
		x = y;
		y = y->u.next;
		free(x);
	}
	free(node); node = NULL;

}


matrix_pointer mtranspose(matrix_pointer matrix) {
	int num_heads, i, j;
	matrix_pointer temp, last, node, ptr;
	node = (matrix_pointer)malloc(sizeof(matrix_node));
	node->tag = entry;
	// 첫 번째 줄 처리(열과 행 바꾸기)
	node->u.entry.row = matrix->u.entry.col;
	node->u.entry.col = matrix->u.entry.row;
	node->u.entry.value = matrix->u.entry.value;
	num_heads = (matrix->u.entry.col > matrix->u.entry.row) ? matrix->u.entry.col : matrix->u.entry.row;

	if (!num_heads) node->right = node;
	else {
		//헤드 노드 만들기
		for (i = 0; i < num_heads; i++) {
			temp = (matrix_pointer)malloc(sizeof(matrix_node));
			hdnode_t[i] = temp;
			hdnode_t[i]->tag = head;
			hdnode_t[i]->right = temp;
			hdnode_t[i]->u.next = temp;
		}

		for (j = 0; j < matrix->u.entry.col; j++) {
			for (ptr = hdnode[j]->down, last = hdnode_t[j]; ptr != hdnode[j]; ptr = ptr->down) {
				temp = (matrix_pointer)malloc(sizeof(matrix_node));
				temp->tag = entry;
				temp->u.entry.row = ptr->u.entry.col;
				temp->u.entry.col = ptr->u.entry.row;
				temp->u.entry.value = ptr->u.entry.value;
				last->right = temp; //link into row list
				last = temp;
				hdnode_t[ptr->u.entry.col]->u.next->down = temp; //link into column list
				hdnode_t[ptr->u.entry.col]->u.next = temp;
			}
			last->right = hdnode_t[j];
		}
		
		//close all column lists
		for (i = 0; i < node->u.entry.col; i++) {
			hdnode_t[i]->u.next->down = hdnode_t[i];
		}
		//link all header nodes together
		for (i = 0; i < num_heads - 1; i++) {
			hdnode_t[i]->u.next = hdnode_t[i + 1];
		}
		hdnode_t[num_heads - 1]->u.next = node;
		node->right = hdnode_t[0];
		
	}
	
	return node;
}

int main() {
	matrix_pointer matrix;
	matrix = mread();
	matrix_pointer t_matrix;
	t_matrix = mtranspose(matrix);
	mwrite(t_matrix);
	
	merase(matrix);
	merase(t_matrix);
	return 0;
}