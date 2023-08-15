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

typedef struct _edge {
	int weight;
	int initial;
	int terminal;
}edge;
int count = 0;
edge* edge_set;

int** adj_matrix;
int* visited;
int num_of_vertex;
node_pointer* graph; //adj_list
node_pointer* group; //Kruskal algorithm으로 만든 MST(adj_list의 형식으로)

int* parent;

void set_union(int i, int j) {
	int k, std;
	if (parent[i] < parent[j]) {
		std = parent[j];
		for (k = 0; k < count; k++) {
			if (parent[k] == std) parent[k] = parent[i];
		}
	}
	else { //parnet[i] > parent[j]
		std = parent[i];
		for (k = 0; k < count; k++) {
			if (parent[k] == std) parent[k] = parent[j];
		}
	}
}

void sort_edge() { //edge함수 weight 기준으로 sorting
	int i, j, min, index; edge save;
	
	for (i = 0; i < count - 1; i++) {
		min = edge_set[i].weight;
		index = i;
		for (j = i + 1; j < count; j++) {
			if (edge_set[j].weight < min) {
				min = edge_set[j].weight;
				index = j;
			}
		}
		//swap
		if (index != i) { //min이 다른 값이면
			save = edge_set[i];
			edge_set[i] = edge_set[index];
			edge_set[index] = save;
		}
	}
}

void dfs(FILE* fp, int v) {
	node_pointer w;
	visited[v] = TRUE;
	fprintf(fp, "%d ", v);
	for (w = group[v]; w; w = w->link) {
		if (!visited[w->vertex])
			dfs(fp, w->vertex);
	}
}

int Kruskal() {
	int i, j; node_pointer temp;
	int cost = 0;
	for (i = 0; i < count; i++) {
		//서로 다른 집합일 때(parent가 다르거나 둘다 -1일 때)-->연결해도 circle이 안 만들어지는 경우
		if (parent[edge_set[i].initial] == parent[edge_set[i].terminal]) continue;
		set_union(edge_set[i].initial, edge_set[i].terminal);

		temp = (node_pointer)malloc(sizeof(node));
		temp->vertex = edge_set[i].terminal;
		temp->link = group[edge_set[i].initial];
		group[edge_set[i].initial] = temp;

		temp = (node_pointer)malloc(sizeof(node));
		temp->vertex = edge_set[i].initial;
		temp->link = group[edge_set[i].terminal];
		group[edge_set[i].terminal] = temp;

		cost += edge_set[i].weight; //tree의 cost를 누적 계산
	}
	return cost;
}

int main() {
	FILE* fp; int i, j, k, num; node_pointer temp, ptr; 
	int flag = 0; int cost;
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
	edge_set = (edge*)malloc(sizeof(edge) * num_of_vertex * (num_of_vertex - 1));

	parent = (int*)malloc(sizeof(int) * num_of_vertex);
	for (i = 0; i < num_of_vertex; i++) {
		parent[i] = i;
	}

	//파일 정보 읽어서 인접 행렬로 저장
	for (i = 0; i < num_of_vertex; i++) {
		for (j = 0; j < num_of_vertex; j++) {
			fscanf(fp, "%d", &num);
			adj_matrix[i][j] = num;
		}
	}

	fclose(fp);

	//인접 행렬의 정보를 인접 리스트로 전환, edge함수 만들기
	for (i = 0; i < num_of_vertex; i++) {
		for (j = 0; j < num_of_vertex; j++) {
			if (adj_matrix[i][j] != -1) {
				temp = (node_pointer)malloc(sizeof(node));
				temp->vertex = j;
				temp->link = graph[i];
				graph[i] = temp;
				
				for (k = 0; k <= count; k++) {
					if (edge_set[k].weight == adj_matrix[i][j]) flag = 1;
				}
				if (flag == 0) {
					edge_set[count].initial = i;
					edge_set[count].terminal = j;
					edge_set[count].weight = adj_matrix[i][j];
					count++;
				}
				else flag = 0;
			}
		}
	}

	sort_edge();
	
	cost = Kruskal();
	
	fp = fopen("output.txt", "w");
	dfs(fp, 0); //kruskal algorithm으로 만든 MST에 dfs를 적용
	fprintf(fp, "\n");
	fprintf(fp, "%d\n", cost);
	fclose(fp);
}
