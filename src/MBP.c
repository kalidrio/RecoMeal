#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "MBP.h"

void read_data(FILE* from_catalogue, food_item* catalogue) {
	int i = 0;
	int result;
	while ((result = fscanf(from_catalogue, "%d %s %f %f %f",
				      &catalogue[i].ID,
				      catalogue[i].name,
				      &catalogue[i].price,
				      &catalogue[i].rating,
				      &catalogue[i].sulit_value)) == 5) {
        	i++;
	}
	if (result != EOF && result != 5) { // error handling
		fprintf(stderr, "Error reading data.\n");
	}

	if (ferror(from_catalogue)) { // more detailed error msg
		perror("Error: \n");
	}
}

void print_Menu(void) {
	printf("\nWhat would you like to do? [ENTER THE NUMBER]\n");
	printf("\t1. Peruse Mode\n");
	printf("\t2. Suggest Mode\n");
	printf("\t3. Input Mode\n");
	printf("\t4. Exit\n");
	printf("\nChoice: ");
}

void peruse(FILE* from_catalogue, food_item* catalogue, int* errPtr) {
	for (int i = 0; i < 13; i++) {
		printf("\t%03d   %s\n", catalogue[i].ID, catalogue[i].name);
	}

	int option;
	char trail; // dummy var to catch trailing characters
	int result;

	printf("\nEnter ID# for more info or 0 to exit: ");
	while ((result = scanf("%d%c", &option, &trail)) != EOF) {
		if (result != 2 || trail != '\n') {
			printf("\nProgram exited with error: ");
			printf("\n\tInput was not solely an integer\n");
			*errPtr = 1;
			return;
		}

		if (option < 0 || option > 13) { 
			printf("\nPlease enter an ID#(1 - 13): ");
			continue;

		} else 	if (option == 0) return;

		printf("\n Dish Name: %s\n", catalogue[option-1].name);
		printf("     Price: Php %.2f\n", catalogue[option-1].price);
		printf("    Rating: %.2f/10\n", catalogue[option-1].rating);
		printf("Sulit-ness: %.2f\n", catalogue[option-1].sulit_value);

		printf("\nEnter ID# for more info or 0 to exit: ");
	}

	printf("Ctrl-D(Program end).\n");
	*errPtr = 1;
	return;

}

int S_init(void) {
	int option = 0;
	char trail; // dummy var to catch trailing characters
	int error = 0;
	int* errPtr = &error;

	FILE* from_catalogue = fopen("../DB/catalogue.txt", "r");
	if (!from_catalogue) {
		printf("Error opening catalogue.\n");
		return 1;
	}

	food_item* catalogue = malloc(sizeof(food_item) * 13);
	if (!catalogue) {
		printf("Memory allocation failed.\n");
		return 1;
	}

	read_data(from_catalogue, catalogue);

	while (option != 4 && !error) {
		if (!error) {
			print_Menu();
		}
		if (scanf("%d%c", &option, &trail) != 2 || trail != '\n') {
			printf("\nProgram exited with error: ");
			printf("\n\tInput was not solely an integer.\n");
			fclose(from_catalogue);
			free(catalogue);
			return 1;
		}
		else {
			printf("\n");
			switch(option){
				case 1:
					peruse(from_catalogue, catalogue, errPtr);
					break;
				case 2:
					// Implement Suggest Mode
					break;
				case 3:
					// Implement Input Mode
					break;
				case 4:
					printf("Program exited successfully.\n");
					break;
				default:
					printf("Please choose a value within 1 to 4\n");
					break;
			}
		}
	}

	fclose(from_catalogue);
	free(catalogue);
	return 0;
}
