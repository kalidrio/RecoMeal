#include <stdio.h>
#include <stdlib.h>
#include "MBP.h"

void read_data(FILE* from_catalogue, food_item* catalogue) {
	int i = 0;
	while (fscanf(from_catalogue, "%d %s %f %f %f",
				      &catalogue[i].ID,
				      catalogue[i].name,
				      &catalogue[i].price,
				      &catalogue[i].rating,
				      &catalogue[i].sulit_value) == 5) {
        	i++;
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

void peruse(FILE* from_catalogue, food_item* catalogue) {
	for (int i = 0; i < 13; i++) {
		printf("\t%03d   %s\n", catalogue[i].ID, catalogue[i].name);
	}

	int option;
	while (1) {
		printf("\nInput ID# of Item for more details or 0 to exit: ");
		if (scanf("%d", &option) != 1 || (option > 13 || option < 0) || option == 0) {
		printf("Please enter a valid number.\n");
		break;
	}
	else {
		printf("\n Dish Name: %s\n", catalogue[option-1].name);
		printf("     Price: Php %.2f\n", catalogue[option-1].price);
		printf("    Rating: %.2f/10\n", catalogue[option-1].rating);
		printf("Sulit-ness: %.2f\n", catalogue[option-1].sulit_value);
		}
	}
}

int S_init(void) {
	int option = 0;

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

	while (option != 4) {
		print_Menu();
		if (scanf("%d", &option) != 1) {
			printf("\nProgram exited with error: Input was not a single digit integer.\n");
			fclose(from_catalogue);
			free(catalogue);
			return 1;
		}
		else {
			printf("\n");
			switch(option){
				case 1:
					peruse(from_catalogue, catalogue);
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
