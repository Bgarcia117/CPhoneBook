#define _CRT_SECURE_NO_WARNINGS // Allows for scanf() to be used in Visual Studio


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_CAPACITY 5
#define MAX_LENGTH 20


typedef struct {
	char firstName[MAX_LENGTH];
	char lastName[MAX_LENGTH];
	char phoneNum[MAX_LENGTH];
} Contact;

typedef struct {
	Contact* array; // Creates pointers to a number of Contact structures
	int used;
	int size;
} Array;

void initArray(Array*, int);
void checkArrayCapacity(Array*, int);
void freeArray(Array*);
void addContact(Array*);
int getContactIndex(Array*);
void displayContactInfo(const Array*, int);
void deleteAllContacts(Array*);


int main() {

	Array friends; // Instantiation of "dynamic" array structure
	initArray(&friends, INITIAL_CAPACITY); // Initializes members of the structures

	int selection = 0;

	while (selection != 6) {
		printf("Please choose from the following options: \n");
		printf("1) Add a contact\n");
		printf("2) Delete a contact\n");
		printf("3) Find a contact\n");
		printf("4) Display contacts\n");
		printf("5) Delete all contact\n");
		printf("6) Close program\n");
		printf("Please make a selection(1-6): \n");
		scanf("%d", &selection);
		getchar();

		switch (selection) {
			case 1: // Adds a contact
				addContact(&friends);
				if (friends.used > 0) {
					for (int i = 0; i < friends.used; i++) {
						displayContactInfo(&friends, i);
					}
				}

				break;
			case 2:
				if (friends.used == 0) {
					printf("There are no contacts saved.");
					break;
				}
				else {
					deleteAllContacts(&friends);
				}

				break;
			case 3:
				break;
			case 4:
				break;
			case 5:
				if (friends.used == 0) {
					printf("There are no contacts saved.");
					break;
				}
				else {
					deleteAllContacts(&friends);
				}
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
	a->array = malloc(initialSize * sizeof(Contact));
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
	printf("-----------------------------------------------\n");
	// Arrow to access members of the Array struct since a pointer is being used
	// Dot operator for access to members of the current Contact Struct
	printf("Enter a first name: ");
	fgets(a->array[a->used].firstName, MAX_LENGTH, stdin); 
	// Removes trailing \n
	a->array[a->used].firstName[strcspn(a->array[a->used].firstName, "\n")] = 0;

	printf("Enter a last name: ");
	fgets(a->array[a->used].lastName, MAX_LENGTH, stdin);
	a->array[a->used].lastName[strcspn(a->array[a->used].lastName, "\n")] = 0;

	printf("Enter a phone number: ");
	fgets(a->array[a->used].phoneNum, MAX_LENGTH, stdin);
	a->array[a->used].phoneNum[strcspn(a->array[a->used].phoneNum, "\n")] = 0;

	a->used++;
}

int getContactIndex(Array* a) {
	char _firstName[MAX_LENGTH];
	char _lastName[MAX_LENGTH];

	printf("Enter a first name: ");
	fgets(_firstName, MAX_LENGTH, stdin); // Needs error handling for \n 
	_firstName[strcspn(_firstName, "\n")] = 0;

	printf("Enter a last name: ");
	fgets(_lastName, MAX_LENGTH, stdin);
	_firstName[strcspn(_firstName, "\n")] = 0;
	
	for (int i = 0; i <= a->used; i++) {
		// Compares temp variable with names in the contact structures
		if (strcmp(_firstName, a->array[i].firstName) == 0 && strcmp(_lastName, a->array[i].lastName) == 0) {
			return i; // Returns index
		}
	}
    
	printf("%s %s not found. Please try again.", _firstName, _lastName);
	return -1;
}

void displayContactInfo(const Array* a, int index) {
	if (index < 0) {
		return;
	}

	printf("First Name: %s\n", a->array[index].firstName);
	printf("Last Name: %s\n", a->array[index].lastName);
	printf("Phone Number: %s\n", a->array[index].phoneNum);
	printf("-----------------------------------------------\n");
}

void deleteContact(Array* a) {
	char userChoice[5];

	printf("Are you sure you want to delete all contacts?\n");
	printf("Type Yes or No: \n");
	fgets(userChoice, 5, stdin);
	userChoice[strcspn(userChoice, "\n")] = 0;

	if (strcmp(userChoice, "No") == 0 || strcmp(userChoice, "no") == 0) {
		return;
	}
	else {
		free(a->array); // Frees memory of the dynamically allocated memory
		a->array = NULL; // Elminates dangling pointer
		a->used = 0;
	}
}

