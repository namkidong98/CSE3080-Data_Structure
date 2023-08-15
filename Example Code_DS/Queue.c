#include <stdio.h>
#include <string.h>
#define MAX_QUEUE_SIZE 100

typedef struct {
	int key;
	//other fields
} element;
element queue[MAX_QUEUE_SIZE];
int front = -1;
int rear = -1;

element queueEmpty() {
	printf("Queue is empty.\n");
	return;
}

void queueFull() {
	printf("Queue is full.\n");
	return;
}

void queue_add(element item) {
	if (rear == MAX_QUEUE_SIZE - 1) queueFull();
	else {
		queue[++rear] = item;
		printf("%d is added to queue.\n", item.key);
	}
	return;
}

element queue_delete() {
	if (front == rear) return queueEmpty();
	else return queue[++front];
}

void print_queue() {
	for (int i = front + 1; i <= rear; i++) {
		printf("%d ", queue[i].key);
	}
	printf("\n\n");
}

int main() {
	char str[10] = { 0 };
	int num = 0;
	element item;
	while (1) {
		printf("Do you want to add or delete? (add / delete)\n");
		scanf_s("%s", str, 10);
		if (strcmp(str, "add") == 0) {
			printf("Value to add: ");
			scanf_s("%d", &num);
			item.key = num;
			queue_add(item);
			printf("\n");
		}
		else if (strcmp(str, "delete") == 0) {
			item = queue_delete();
			//printf("%d is deleted from queue.\n", item.key);
			printf("\n");
		}
		else printf("Not proper command.\n");

		printf("'print' to see queue, 'exit' to end program.\n");
		scanf_s("%s", str, 10);
		if (strcmp(str, "print") == 0) {
			print_queue();
		}
		else if (strcmp(str, "exit") == 0) {
			break;
		}
	}
	return;
}