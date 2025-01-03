#define _CRT_SECURE_NO_WARNINGS


#include <stdio.h>
#include <stdlib.h>

#define INITIAL_CAPACITY 5
#define MAX_LENGTH 20


typedef struct {
	char firstName[MAX_LENGTH];
	char lastName[MAX_LENGTH];
	char phoneNum[MAX_LENGTH];
} Contact;

typedef struct {
	Contact* array;
	int used;
	int size;
} Array;

void initArray(Array*, int);
void checkArrayCapacity(Array*, int);
void freeArray(Array*);
void addContact(Array*);


int main() {

	Array friends; // Instantiation of dynamic array structure
	initArray(&friends, INITIAL_CAPACITY); // Initializes members of the structures

	int selection = 0;

	while (selection != 6) {
		printf("Please choose from the following options: \n");
		printf("1) Add a contact\n");
		printf("2) Delete a contact\n");
		printf("3) Find a contact\n");
		printf("4) Display contacts\n");
		printf("5) Erase a contact\n");
		printf("6) Close program\n");
		printf("Please make a selection(1-6): \n");
		scanf("%d", &selection);
		getchar();

		switch (selection) {
			case 1: // Adds a contact
				addContact(&friends);
				printf("-----------------------------------------------\n");
				printf((friends.array + friends.used)->firstName);
				printf((friends.array + friends.used)->lastName);
				printf((friends.array + friends.used)->phoneNum);
				printf("-----------------------------------------------\n");

				break;
			case 2:
				break;
			case 3:
				break;
			case 4:
				break;
			case 5:
				break;
			case 6:
				break;
			default:
				printf("Please make a valid selection.");
				scanf("%d", &selection);
				getchar();
		}
	}

}

void initArray(Array* a, int initialSize) {
	a->array = (Contact*)malloc(initialSize * sizeof(Contact));
	a->used = 0;
	a->size = initialSize;
}

void checkArrayCapacity(Array* a, int element) {
	if (a->used == a->size) { // Checks if limit has been reached (used can go up to size)
		a->size *= 2; // Doubles size
		Contact* temp_array = realloc(a->array, a->size * sizeof(Contact)); // Temp variable to check if reallocation is successful

		if (temp_array == NULL) {
			printf("Memory Allocation Failed!");
			printf("Phone Book Full!");
			printf("Please try again.");
			return;
		}
		else {
			a->array = temp_array; // Resizes array if memory allocation is successful
		}
	}
}

void freeArray(Array* a) {
	free(a->array);
	a->array = NULL;
	a->used = a->size = 0;
}

void addContact(Array* a) {
	printf("Enter a first name: ");
	fgets(a->array[a->used]->firstName, MAX_LENGTH, stdin);
	printf("Enter a last name: ");
	fgets((a->array + a->used)->lastName, MAX_LENGTH, stdin);
	printf("Enter a phone number: ");
	fgets((a->array + a->used)->phoneNum, MAX_LENGTH, stdin);
}