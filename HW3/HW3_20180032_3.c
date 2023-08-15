#include <stdio.h>
#include <stdlib.h>
#define MAX_QUEUE_SIZE 100
#define FALSE 0
#define TRUE 1

void queueEmpty() {
	printf("Queue is empty.\n");
}

void queueFull() {
	printf("Queue is full.\n");
}

void queue_add(int* rear, int** queue, int x, int y, int dir) {
	if ((*rear) == MAX_QUEUE_SIZE - 1) queueFull();
	else {
		queue[++(*rear)][0] = x;
		queue[*rear][1] = y;
		queue[*rear][2] = dir;
	}
}

void queue_delete(int* front, int* rear, int** queue, int* row, int* col) {
	if (*front == *rear) queueEmpty();
	*row = queue[++(*front)][0];
	*col = queue[(*front)][1];
}

void path(int** field, int row_field, int col_field) {
	int front = -1; int rear = -1; int pos = 0; int count = 0;
	int i, row, col, nextRow, nextCol; 
	int dir = 0;
	int** queue = (int**)malloc(sizeof(int*) * MAX_QUEUE_SIZE);
	for (i = 0; i < MAX_QUEUE_SIZE; i++) queue[i] = (int*)malloc(sizeof(int) * 3);
	int** stack = (int**)malloc(sizeof(int*) * MAX_QUEUE_SIZE);
	for (i = 0; i < MAX_QUEUE_SIZE; i++) stack[i] = (int*)malloc(sizeof(int) * 2);
	int** move = (int**)malloc(sizeof(int*) * 8);
	for (i = 0; i < 8; i++) move[i] = (int*)malloc(sizeof(int) * 2);
	move[0][0] = -1; move[0][1] = 0;
	move[1][0] = -1; move[1][1] = 1;
	move[2][0] = 0; move[2][1] = 1;
	move[3][0] = 1; move[3][1] = 1;
	move[4][0] = 1; move[4][1] = 0;
	move[5][0] = 1; move[5][1] = -1;
	move[6][0] = 0; move[6][1] = -1;
	move[7][0] = -1; move[7][1] = -1;

	int found = FALSE;
	int EXIT_ROW = row_field; int EXIT_COL = col_field;
	
	//1,1을 시작점으로 queue에 넣기
	queue_add(&rear, queue, 1, 1, 0);
	field[1][1] = 1;

	while (!found && front != rear) {
		queue_delete(&front, &rear, queue, &row, &col);
		while (dir < 8 && !found) {
			nextRow = row + move[dir][0];
			nextCol = col + move[dir][1];
			if (nextRow == EXIT_ROW && nextCol == EXIT_COL) {
				found = TRUE;
				queue_add(&rear, queue, nextRow, nextCol, (dir + 4) % 8);
				pos = rear;
			}
			else if (field[nextRow][nextCol] == 0) {
				queue_add(&rear, queue, nextRow, nextCol, (dir + 4) % 8);
				field[nextRow][nextCol] = 1;
				++dir;
			}
			else ++dir;
		}
		dir = 0;
	}

	if (found) {
		row = EXIT_ROW; col = EXIT_COL;
		printf("The path is: \n");
		printf("row col \n");

		while (pos != 0) {
			row = queue[pos][0]; col = queue[pos][1];
			stack[count][0] = row; stack[count][1] = col;
			dir = queue[pos][2];
			nextRow = row + move[dir][0];
			nextCol = col + move[dir][1];

			for (i = pos; i >= 0; i--) {
				if (queue[i][0] == nextRow && queue[i][1] == nextCol) {
					pos = i;
					break;
				} 
			}
			count++;
		}
		printf("%2d%5d\n", queue[0][0], queue[0][1]);
		for (i = count - 1; i >= 0; i--) {
			printf("%2d%5d\n", stack[i][0], stack[i][1]);
		}
	}
	else printf("The maze does not have a path\n");

	for (i = 0; i < MAX_QUEUE_SIZE; i++) free(queue[i]);
	free(queue);
	for (i = 0; i < MAX_QUEUE_SIZE; i++) free(stack[i]);
	free(stack);
	for (i = 0; i < 8; i++) free(move[i]);
	free(move);
}


int main() {
	int i, j;
	FILE* fp;
	fp = fopen("input.txt", "r");
	if (fp == NULL) { //에러 처리
		fprintf(stderr, "File open error.\n");
		exit(1);
	}

	char a, b;
	a = fgetc(fp);
	b = fgetc(fp);
	int row = a - '0';
	int col = a - '0';
	char** temp = (char**)malloc(row * sizeof(char*));
	int** maze = (int**)malloc(row * sizeof(int*));
	for (i = 0; i < row; i++) {
		temp[i] = (char*)malloc(sizeof(char) * col);
		maze[i] = (int*)malloc(sizeof(int) * col);
	}
	for (i = 0; i< row; i++) {
		for (j = 0; j < col; j++) {
			temp[i][j] = fgetc(fp);
			if (temp[i][j] == '\r') temp[i][j] = fgetc(fp);
			if (temp[i][j] == '\n') temp[i][j] = fgetc(fp);
		}
	}
	for (i = 0; i < row; i++) {
		for (j = 0; j < col; j++) {
			maze[i][j] = temp[i][j] - '0';
		}
	}
	/* input.txt에서 읽어온 maze 출력
	for (i = 0; i < row; i++) {
		for (j = 0; j < col; j++) {
			printf("%d", maze[i][j]);
		}
		printf("\n");
	}*/
	
	int** field = (int**)malloc((row + 2) * sizeof(int*));
	for (i = 0; i < row + 2; i++) {
		field[i] = (int*)malloc(sizeof(int) * (col + 2));
	}
	for (i = 0; i < row + 2; i++) {
		for (j = 0; j < col + 2; j++) {
			if (i == 0 || i == row + 1 || j == 0 || j == col + 1) field[i][j] = 1;
		}
	}
	for (i = 0; i < row; i++) {
		for (j = 0; j < col; j++) {
			field[i + 1][j + 1] = maze[i][j];
		}
	}

	/* maze에 테두리를 쌓아서 만든 field 출력
	for (i = 0; i < row+2; i++) {
		for (j = 0; j < col+2; j++) {
			printf("%d", field[i][j]);
		}
		printf("\n");
	}*/
	
	path(field, row, col);

	fclose(fp);

	for (i = 0; i < row + 2; i++) free(field[i]);
	free(field);
	for (i = 0; i < row; i++) free(temp[i]);
	free(temp);
	for (i = 0; i < row; i++) free(maze[i]);
	free(maze);
}
