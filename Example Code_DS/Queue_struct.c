#include <stdio.h>
#include <string.h>
#define MAX_QUEUE_SIZE 100

typedef struct {
	int buf[MAX_QUEUE_SIZE];
	int front;
	int rear;
} queue;

void queueEmpty() {
	printf("Queue is empty.\n");
	return;
}

void queueFull() {
	printf("Queue is full.\n");
	return;
}

void queue_add(queue *queue, int value) {
	if (queue->rear == MAX_QUEUE_SIZE -1) queueFull();
	else {
		queue->rear += 1;
		queue->buf[queue->rear] = value;
		printf("%d is added to queue.\n", value);
	}
	return;
}

void queue_delete(queue *queue) {
	if (queue->front == queue->rear) queueEmpty();
	else {
		queue->front += 1;
		printf("%d is deleted from queue.\n", queue->buf[queue->front]);
	}
	return;
}

void print_queue(queue* queue) {
	for (int i = queue->front + 1; i <= queue->rear; i++) {
		printf("%d ", queue->buf[i]);
	}
	printf("\n\n");
}

int main() {
	queue queue;
	queue.front = -1;
	queue.rear = -1;
	char str[10] = { 0 };
	int num = 0;
	while (1) {
		printf("Do you want to add or delete? (add / delete)\n");
		scanf_s("%s", str, 10);
		if (strcmp(str, "add") == 0) {
			printf("Value to add: ");
			scanf_s("%d", &num);
			queue_add(&queue, num);
			printf("\n");
		}
		else if (strcmp(str, "delete") == 0) {
			queue_delete(&queue);
			printf("\n");
		}
		else printf("Not proper command.\n");

		printf("'print' to see queue, 'exit' to end program.\n");
		scanf_s("%s", str, 10);
		if (strcmp(str, "print") == 0) {
			print_queue(&queue);
		}
		else if (strcmp(str, "exit") == 0) {
			break;
		}
	}
	return;
}