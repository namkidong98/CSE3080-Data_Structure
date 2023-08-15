#include <stdio.h>
#include <stdlib.h>


typedef struct NODE{
	int data;
	struct NODE* link;
}list_node;

/*list_node* create2() {
	list_node* first;
	list_node* second;
	first = (list_node*)malloc(sizeof(list_node));
	second = (list_node*)malloc(sizeof(list_node));
	second->link = NULL;
	second->data = 20;
	first->data = 10;
	first->link = second;
	return first;
}*/

/*void insert(list_node* ptr, list_node node) {
	list_node* temp;
	temp = (list_node*)malloc(sizeof(list_node));
	temp->data = 0;

}*/

int main() {
	list_node* head = (list_node*)malloc(sizeof(list_node));

	list_node* node1 = (list_node*)malloc(sizeof(list_node));
	head->link = node1;
	node1->data = 10;

	list_node* node2 = (list_node*)malloc(sizeof(list_node));
	node1->link = node2;
	node2->data = 20;

	node2->link = NULL;

	list_node* curr = head->link;
	while (curr != NULL) {
		printf("%d", curr->data);
		curr = curr->link;
	}

	free(node2);
	free(node1);
	free(head);
}