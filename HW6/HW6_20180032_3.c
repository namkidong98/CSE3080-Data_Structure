#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0

typedef struct _node* node_pointer;
typedef struct _node {
	int vertex;
	int weight; //����ġ
	node_pointer link;
}node;

int** adj_matrix;
int* visited;
int num_of_vertex;
node_pointer* graph;
node_pointer* group;
int count = 0;

/*
void dfs(int v) {
	node_pointer w;
	visited[v] = TRUE;
	printf("%d ", v);
	for (w = group[v]; w; w = w->link) {
		if (!visited[w->vertex])
			dfs(w->vertex);
	}
}

void connected() {
	int i;
	for (i = 0; i < num_of_vertex; i++) {
		if (!visited[i]) {
			dfs(i);
			printf("\n");
		}
	}
}
*/

void Prim() {
	int i; node_pointer ptr, temp, root;
	int min; int index;

	for (i = 0; i < num_of_vertex; i++) {
		if (!visited[i]) {
			visited[i] = TRUE;
			//printf("%d ", i);
			root = (node_pointer)malloc(sizeof(node));
			root->vertex = i;
			group[count] = root;

			ptr = graph[i];
			index = i;
			while (1) {
				min = 1000;
				
				//minimum cost edge ã��
				for (; ptr; ptr = ptr->link) {
					if (visited[ptr->vertex] == FALSE) {
						if (ptr->weight < min) min = ptr->weight;
					}
				}
				//�ش� vertex�� �̵�
				for (ptr = graph[index]; ptr; ptr = ptr->link) {
					if (ptr->weight == min) break;
				}
				if (ptr == NULL) { //connected�� component�� �� ���� �� ptr�� NULL�� ��
					root->link = NULL;
					break; 
				}

				index = ptr->vertex;
				//printf("%d ", index);
				temp = (node_pointer)malloc(sizeof(node));
				temp->vertex = index;
				temp->weight = min;
				root->link = temp;
				root = temp;
				
				visited[index] = TRUE;
				ptr = graph[index]; //���� ���� �Ѿ
			}
			//printf("\n");
			count++; //1���� connected component�� ����
		}
		
	}
}

int main() {
	FILE* fp; int i, j, num; node_pointer temp, ptr;
	fp = fopen("input.txt", "r");

	fscanf(fp, "%d", &num_of_vertex);
	graph = (node_pointer*)malloc(sizeof(node_pointer) * num_of_vertex);
	group = (node_pointer*)malloc(sizeof(node_pointer) * num_of_vertex);
	for (i = 0; i < num_of_vertex; i++) {
		graph[i] = NULL;
		group[i] = NULL;
	}
	visited = (int*)malloc(sizeof(int) * num_of_vertex);
	for (i = 0; i < num_of_vertex; i++) {
		visited[i] = FALSE;
	}
	adj_matrix = (int**)malloc(sizeof(int*) * num_of_vertex);
	for (i = 0; i < num_of_vertex; i++) {
		adj_matrix[i] = (int*)malloc(sizeof(int) * num_of_vertex);
	}

	//���� ���� �о ���� ��ķ� ����
	for (i = 0; i < num_of_vertex; i++) {
		for (j = 0; j < num_of_vertex; j++) {
			fscanf(fp, "%d", &num);
			adj_matrix[i][j] = num;
		}
	}

	fclose(fp);

	//���� ����� ������ ���� ����Ʈ�� ��ȯ
	for (i = 0; i < num_of_vertex; i++) {
		for (j = 0; j < num_of_vertex; j++) {
			if (adj_matrix[i][j] != -1) {
				temp = (node_pointer)malloc(sizeof(node));
				temp->vertex = j;
				temp->weight = adj_matrix[i][j];
				temp->link = graph[i];
				graph[i] = temp;
			}
		}
	}

	Prim();

	fp = fopen("output.txt", "w");
	for (i = 0; i < count; i++) { //count�� connected group�� ����
		for (ptr = group[i]; ptr; ptr = ptr->link) fprintf(fp, "%d ", ptr->vertex);
		fprintf(fp, "\n");
	}
	fclose(fp);
}