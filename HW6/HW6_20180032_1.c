#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0

typedef struct _node* node_pointer;
typedef struct _node {
	int vertex;
	node_pointer link;
}node;

int** adj_matrix;
int* visited;
int num_of_vertex;
node_pointer* graph;

void dfs(FILE*fp, int v) {
	node_pointer w;
	visited[v] = TRUE;
	fprintf(fp, "%d ", v);
	for (w = graph[v]; w; w = w->link) {
		if (!visited[w->vertex])
			dfs(fp, w->vertex);
	}
}

void connected(FILE* fp) {
	int i;
	for (i = 0; i < num_of_vertex; i++) {
		if (!visited[i]) {
			dfs(fp, i);
			fprintf(fp, "\n");
		}
	}
}

int main() {
	FILE* fp; int i, j, num; node_pointer temp, ptr;
	fp = fopen("input.txt", "r");

	fscanf(fp, "%d", &num_of_vertex);
	graph = (node_pointer*)malloc(sizeof(node_pointer) * num_of_vertex);
	for (i = 0; i < num_of_vertex; i++) {
		graph[i] = NULL;
	}
	visited = (int*)malloc(sizeof(int) * num_of_vertex);
	for (i = 0; i < num_of_vertex; i++) {
		visited[i] = FALSE;
	}
	adj_matrix = (int**)malloc(sizeof(int*) * num_of_vertex);
	for (i = 0; i < num_of_vertex; i++) {
		adj_matrix[i] = (int*)malloc(sizeof(int) * num_of_vertex);
	}

	//파일 정보 읽어서 인접 행렬로 저장
	for (i = 0; i < num_of_vertex; i++) {
		for (j = 0; j < num_of_vertex; j++) {
			fscanf(fp, "%d", &num);
			adj_matrix[i][j] = num;
		}
	}

	fclose(fp);
	
	//인접 행렬의 정보를 인접 리스트로 전환
	for (i = 0; i < num_of_vertex; i++) {
		for (j = 0; j < num_of_vertex; j++) {
			if (adj_matrix[i][j] == 1) {
				temp = (node_pointer)malloc(sizeof(node));
				temp->vertex = j;
				temp->link = graph[i];
				graph[i] = temp;
			}
		}
	}

	fp = fopen("output.txt", "w");

	connected(fp);

	fclose(fp);
}