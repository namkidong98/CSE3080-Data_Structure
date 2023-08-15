#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_QUEUE_SIZE 6

typedef struct {
	int key;
	//other fields
} element;
element queue[MAX_QUEUE_SIZE];
int front = 0;
int rear = 0;

element queueEmpty() {
	printf("Queue is empty.\n");
	exit(1);
	return;
}

void queueFull() {
	printf("Queue is full.\n");
	exit(1);
	return;
}

void queue_add(element item) {
	rear = (rear + 1) % MAX_QUEUE_SIZE;
	if (rear == front) queueFull();  //마지막 칸은 비워둬서 rear를 하나 더했을 때 front와 같아지면 full로 판단
	else {
		queue[rear] = item;
		printf("%d is added to queue.\n", item.key);
	}
	return;
}

element queue_delete() {
	if (front == rear) return queueEmpty(); //이미 front와 rear가 같은지 판단해서 같으면 empty(이전 시행에서 넘어온것)
	front = (front + 1) % MAX_QUEUE_SIZE; //front 한칸 증가
	return queue[front]; //이동 후 front의 값이 삭제되기에 리턴하여 표시
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