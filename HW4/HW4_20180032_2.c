#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct _poly_node* poly_pointer;
typedef struct _poly_node {
	int coef;
	int expon;
	poly_pointer link;
}poly_node;

poly_pointer getpoly_a() {
	FILE* fp; int i; int coef, expo; int num;
	poly_pointer temp; poly_pointer ptr = NULL; poly_pointer start = NULL;

	fp = fopen("a.txt", "r");
	if (fp == NULL) {
		fprintf(stderr, "FILE OPEN ERROR");
		exit(1);
	}
	fscanf(fp, "%d\n", &num);

	
	for (i = 0; i < num; i++) {
		fscanf(fp, "%d %d\n", &coef, &expo);
		temp = (poly_pointer)malloc(sizeof(poly_node));
		temp->expon = expo;
		temp->coef = coef;
		temp->link = NULL;
		if (i == 0) {
			ptr = temp;
			start = temp;
		}
		else {
			ptr->link = temp;
			ptr = ptr->link;
		}
	}

	fclose(fp);
	return start;
}

poly_pointer getpoly_b() {
	FILE* fp; int i; int coef, expo; int num;
	poly_pointer temp; poly_pointer ptr = NULL; poly_pointer start = NULL;

	fp = fopen("b.txt", "r");
	if (fp == NULL) {
		fprintf(stderr, "FILE OPEN ERROR");
		exit(1);
	}
	fscanf(fp, "%d\n", &num);

	for (i = 0; i < num; i++) {
		fscanf(fp, "%d %d\n", &coef, &expo);
		temp = (poly_pointer)malloc(sizeof(poly_node));
		temp->expon = expo;
		temp->coef = coef;
		temp->link = NULL;
		if (i == 0) {
			ptr = temp;
			start = temp;
		}
		else {
			ptr->link = temp;
			ptr = ptr->link;
		}
	}

	fclose(fp);
	return start;
}

void perase(poly_pointer ptr) {
	poly_pointer temp; poly_pointer trail;
	for (temp = ptr, trail = ptr; temp != NULL; ) {
		temp = temp->link;
		free(trail);
		trail = temp;
	}
}

poly_pointer pmult(poly_pointer a, poly_pointer b, int* num_d) {
	int i = 0; int j = 0; int coef_a, expo_a, coef_b, expo_b, coef_c, expo_c;
	int num_c = 0; int max = 0; int result = 0;
	poly_pointer c = NULL; poly_pointer d = NULL; poly_pointer temp; poly_pointer ptr = NULL;
	poly_pointer ptr_a = NULL; poly_pointer ptr_b = NULL;

	for (ptr_a = a; ptr_a != NULL;ptr_a = ptr_a->link) {
		coef_a = ptr_a->coef; expo_a = ptr_a->expon;
		for (ptr_b = b; ptr_b != NULL; ptr_b = ptr_b->link) {
			coef_b = ptr_b->coef; expo_b = ptr_b->expon;
			
			expo_c = expo_a + expo_b;
			coef_c = coef_a * coef_b;

			temp = (poly_pointer)malloc(sizeof(poly_node));
			temp->expon = expo_c;
			temp->coef = coef_c;
			temp->link = NULL;
			if (i++ == 0) {
				ptr = temp;
				c = temp;
			}
			else {
				ptr->link = temp;
				ptr = ptr->link;
			}
		}
	}

	
	for (ptr = c; ptr != NULL;ptr=ptr->link) {
		if (ptr->expon >= max) max = ptr->expon;
	}

	ptr_b = d;
	for (i = max; i >= 0; i--) {
		for (ptr_a = c; ptr_a != NULL; ptr_a=ptr_a->link) {
			if (ptr_a->expon == i) result += ptr_a->coef;
		}
		if (result != 0) {
			temp = (poly_pointer)malloc(sizeof(poly_node));
			temp->expon = i;
			temp->coef = result;
			temp->link = NULL;
			if (j++ == 0) {
				ptr = temp;
				d = temp;
			}
			else {
				ptr->link = temp;
				ptr = ptr->link;
			}
			result = 0;
			(*num_d)++;
		}
	}
	perase(c);
	
	return d;
}


void pwrite(poly_pointer d, int num_d) {
	FILE* fp;
	poly_pointer ptr = NULL;
	fp = fopen("d.txt", "w");
	if (fp == NULL) {
		fprintf(stderr, "FILE OPEN ERROR");
		exit(1);
	}
	fprintf(fp, "%d\n", num_d);
	for (ptr = d; ptr != NULL; ptr = ptr->link) {
		fprintf(fp, "%d %d\n", ptr->coef, ptr->expon);
	}

	fclose(fp);
}

int main() {
	poly_pointer a; poly_pointer b; poly_pointer d; poly_pointer ptr;
	a = getpoly_a();
	b = getpoly_b();
	
	d = (poly_pointer)malloc(sizeof(poly_node));
	int num_d = 0;
	d = pmult(a, b, &num_d);
	
	pwrite(d, num_d);

	perase(a);
	perase(b);
	perase(d);
	
	return 0;
}