#include <stdio.h>

#define INITIAL_CAPACITY 5

struct Contact {
	char* firstName;
	char* lastName;
	char* phoneNum;
};

struct Array {
	Contact* array;
	size_t used; // Unisigned ints since we only need positive nums
	size_t size;
};

void initArray(Array*, size_t);
void insertInArray(Array*, int);
void freeArray(Array*);


int main() {

	Array friends; // Instantiation of dynamic array structure
	initArray(&friends, INITIAL_CAPACITY); // Initializes members of the structures

	int selection = -1;

	while (selection != 6) {
		printf("Please choose from the following options: ");
		printf("1) Add a contact");
		printf("2) Delete a contact");
		printf("3) Find a contact");
		printf("4) Display contacts");
		printf("5) Erase a contact");
		printf("6) Close program");
	}

	switch (selection) {
	    case 1: // Adds a contact

			break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			break;
		case 5:
			break;
		default:
			printf("Please make a valid selection.");
	}



}

void initArray(Array* a, size_t initalSize) {
	a->array = malloc(initialSize * sizezof(Contact));
	a->used = 0;
	a->size = initialSize;
}

void insertInArray(Array* a, int element) {
	if (a->used == a->size) { // Checks if limit has been reached (used can go up to size)
		a->size *= 2; // Doubles size
		Contact* temp_array = realloc(a->array, a->size * sizeof(Contact)); // Reallocates space
	}

	if (temp_array == NULL) {
		printf("Memory Allocation Failed!");
		return;
	}
	else {
		a->array = temp_array;
	}

	a->array[a->used++]->firstName = 
}

void freeArray(Array* a) {
	free(a->array);
	a->array = NULL;
	a->used = a->size = 0;
}

void addContact() {
	printf("Enter a first name: ");
	printf("Enter a last name: ");
	printf("Enter a phone number: ");
}