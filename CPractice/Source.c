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

// Function prototypes
void initArray(Array*, int);
void checkArrayCapacity(Array*, int);
void freeArray(Array*);
void addContact(Array*);
int getContactIndex(Array*);
void displayContactInfo(const Array*, int);
void deleteAllContacts(Array*);
void deleteOneContact(Array*, int);
void alphabetizeByFirstName(Array*);
void alphabetizeByLastName(Array*);

int main() {

	Array friends; // Instantiation of "dynamic" array structure
	initArray(&friends, INITIAL_CAPACITY); // Initializes members of the structures

	int selection = 0;
	char userChoice[5];

	while (selection != 7) {
		printf("-----------------------------------------------\n");
		printf("Please choose from the following options: \n");
		printf("1) Add A Contact\n");
		printf("2) Delete A Contact\n");
		printf("3) Find A Contact\n");
		printf("4) Display All Contacts\n");
		printf("5) Delete All Contact\n");
		printf("6) Alphabetize Contacts\n");
		printf("7) Close Program\n");
		printf("Please make a selection(1-6): \n");
		scanf("%d", &selection);
		getchar();

		switch (selection) {
			case 1: // Adds a contact
				addContact(&friends);
				break;
			case 2: // Deletes a single contact
				if (friends.used == 0) {
					printf("There are no contacts saved.\n");
					break;
				}
				else {
					printf("-----------------------------------------------\n");
					printf("To delete a contact:\n");
					deleteOneContact(&friends, getContactIndex(&friends));
				}

				break;

			case 3: // Find a single contact
				if (friends.used == 0) {
					printf("There are no contacts saved to display.\n");
					break;
				}
				else {
					displayContactInfo(&friends, getContactIndex(&friends));
				}

				break;

			case 4: // Displays all contacts
				if (friends.used == 0) {
					printf("There are no contacts saved to display.\n");
					break;
				}
				else {
					printf("Contacts: \n");
					for (int i = 0; i < friends.used; i++) {
						displayContactInfo(&friends, i);
					}
				}
				break;

			case 5: // Delete all contacts
				if (friends.used == 0) {
					printf("There are no contacts saved.\n");
					break;
				}

				printf("Are you sure you want to delete all contacts?\n");
				printf("Type Yes or No: \n");

				fgets(userChoice, 5, stdin);
				userChoice[strcspn(userChoice, "\n")] = 0;

				if (strcmp(userChoice, "No") == 0 || strcmp(userChoice, "no") == 0) {
					return;
				}
				else {
					deleteAllContacts(&friends); // Frees memory reserved for Contact struct pointers in Array struct
					initArray(&friends, INITIAL_CAPACITY); // Re-initalizes pointers to Contact structs
				}
				break;

			case 6: // Alphabetize contacts by first name
				if (friends.used == 0) {
					printf("There are no contacts saved to display.\n");
					break;
				} 
				else if (friends.used == 1) {
					break;
				}
				
				int sortSelection;
				printf("-----------------------------------------------\n");
				printf("Sort contacts by: \n");
				printf("1) First Name\n");
				printf("2) Last Name\n");
				printf("Make a selection (1-2)\n");
				scanf("%d", &sortSelection);
				getchar();

				if (sortSelection == 1) {
					alphabetizeByFirstName(&friends);
				}
				else if (sortSelection == 2) {
					alphabetizeByLastName(&friends);
				}
				else {
					printf("Please make a valid selection.\n");
				}
				break;

			case 7:
				break;

			default:
				printf("Please make a valid selection.\n");
				scanf("%d", &selection);
				getchar();
		}
	}

}

void initArray(Array* a, int initialSize) {
	Contact* temp_array = malloc(initialSize * sizeof(Contact)); // Attemps to allocate space for Contact pointers

	if (!temp_array) {
		printf("Memory allocation failed! Please try again.\n");
		return;
	}

	a->array = temp_array; // Sets the array to the allocated space from the temp variable
	a->used = 0;
	a->size = initialSize;
}

void checkArrayCapacity(Array* a, int element) { // Make sure to use this
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
	a->array[a->used].firstName[strcspn(a->array[a->used].firstName, "\n")] = '\0';

	printf("Enter a last name: ");
	fgets(a->array[a->used].lastName, MAX_LENGTH, stdin);
	a->array[a->used].lastName[strcspn(a->array[a->used].lastName, "\n")] = '\0';

	printf("Enter a phone number: ");
	fgets(a->array[a->used].phoneNum, MAX_LENGTH, stdin);
	a->array[a->used].phoneNum[strcspn(a->array[a->used].phoneNum, "\n")] = '\0';

	a->used++;
}

int getContactIndex(Array* a) {
	char _firstName[MAX_LENGTH];
	char _lastName[MAX_LENGTH];

	printf("Enter a first name: ");
	fgets(_firstName, MAX_LENGTH, stdin);
	_firstName[strcspn(_firstName, "\n")] = '\0';

	printf("Enter a last name: ");
	fgets(_lastName, MAX_LENGTH, stdin);
	_lastName[strcspn(_lastName, "\n")] = '\0';
	
	for (int i = 0; i < a->used; i++) {
		// Compares temp variable with names in the contact structures
		if (strcmp(_firstName, a->array[i].firstName) == 0 && strcmp(_lastName, a->array[i].lastName) == 0) {
			return i; // Returns index
		}
	}
    
	printf("%s %s was not found. Please try again.\n", _firstName, _lastName);
	return -1;
}

void displayContactInfo(const Array* a, int index) {
	if (index < 0) {
		return;
	}

	printf("-----------------------------------------------\n");
	printf("First Name: %s\n", a->array[index].firstName);
	printf("Last Name: %s\n", a->array[index].lastName);
	printf("Phone Number: %s\n", a->array[index].phoneNum);
}

// Function frees dynamically allocated memory
void deleteAllContacts(Array* a) {
	free(a->array); // Frees memory of the dynamically allocated memory
	a->array = NULL; // Elminates dangling pointer
	a->used = 0;
}

void deleteOneContact(Array* a, int index) {
	if (index == -1) {
		printf("Contact could not be found. Please try again.\n");
	} else if (index == a->used - 1) { // Checks if the struct is at the last pointer
		a->used--;
		return;
	}

	for (index; index < a->used-1; index++) {
		a->array[index] = a->array[index + 1]; // Shifts elements to overwrite element being removed
	}
	a->used--;
}

void alphabetizeByFirstName(Array* a) {
	int swaps;
	do {
		swaps = 0; // Tracks if a swap is made
		for (int i = 0; i < a->used - 1; i++) {
			if (strcmp(a->array[i].firstName, a->array[i + 1].firstName) > 0) {
				Contact temp = a->array[i];
				a->array[i] = a->array[i + 1];
				a->array[i + 1] = temp;
				swaps = 1; // Marks if a swap is made
			}
		}
	} while (swaps); // Continues if a swap is made
}

void alphabetizeByLastName(Array* a) { // Note: C does not support function overloading
	int swaps;
	do {
		swaps = 0; // Tracks if a swap is made
		for (int i = 0; i < a->used - 1; i++) {
			if (strcmp(a->array[i].lastName, a->array[i + 1].lastName) > 0) {
				Contact temp = a->array[i];
				a->array[i] = a->array[i + 1];
				a->array[i + 1] = temp;
				swaps = 1; // Marks if a swap is made
			}
		}
	} while (swaps);
}
