#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "MBP.h"
  
//void peruse_mode(FILE *fp);


//suggest mode
void suggest(food_item *catalogue, food_item *history, int food_num, int* errPtr);
void budget_it(food_item *fp, int food_num, float budget);
/*
//input mode
void input_mode(FILE *fp, FILE *fp1);
void existing(food_item *add, food_item *add_history);
void new_item(food_item *add, food_item *add_history);
*/  

void read_data(FILE* from_catalogue, food_item* catalogue, int *food_num) {
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
	*food_num = i;
	if (result != EOF && result != 5) { // error handling
		fprintf(stderr, "Error reading data.\n");
	}

	if (ferror(from_catalogue)) { // more detailed error msg
		perror("Error: \n");
	}

}

void clear_buffer(void) {
	while ((getchar()) != '\n'); // to clear buffer
}

void print_modes(void) {
	printf("\nWhat would you like to do? [ENTER THE NUMBER]\n");
	printf("\t1. Peruse Mode\n");
	printf("\t2. Suggest Mode\n");
	printf("\t3. Input Mode\n");
	printf("\t4. Exit\n");
	printf("\nChoice: ");
}

/*---------------------------------------------------------------
			"Case Functions" 
---------------------------------------------------------------*/

void peruse(food_item* catalogue, int* errPtr) {  // "PERUSE" //
	int ID, result;
	char trail; // dummy var to catch trailing characters

	for (int i = 0; i < 13; i++) 
		printf("\t%03d   %s\n", catalogue[i].ID, catalogue[i].name);
	
	printf("\nEnter ID# for more info or 0 to exit: ");
	while ((result = scanf("%d%c", &ID, &trail)) != EOF) {
		if (result != 2 || trail != '\n') {
			printf("\nPlease enter a valid ID# (Press 0 to exit): ");
			clear_buffer();
			continue;
		}

		if (ID < 0 || ID > 13) {
			printf("\nPlease enter an ID# from 1 to 13: ");
			continue;
		} else if (ID == 0) return;

		printf("\n Dish Name: %s\n", catalogue[ID-1].name);
		printf("     Price: Php %.2f\n", catalogue[ID-1].price);
		printf("    Rating: %.2f/10\n", catalogue[ID-1].rating);
		printf("Sulit-ness: %.2f\n", catalogue[ID-1].sulit_value);
		
		printf("\nEnter ID# for more info or 0 to exit: ");
	}
	printf("Ctrl-D(Program end).\n");
	printf("Thank you for using Recomeal! :D\n\n");
	*errPtr = 1;
	return;
}

void suggest(food_item *catalogue, food_item *history, int food_num, int* errPtr){ // "SUGGEST"
	float budget;
	char trail; // dummy var to catch trailing characters
	int result;

	printf("Most recent purchases:\n\n");
	printf("--------------------------------------------\n");
        printf(" ID\t Food\t\t\t   Rating\n");
	printf("--------------------------------------------\n");

	for (int i = 0; i < 10; i++)
		printf(" %03d\t %-25s  %.2f🌟\n", history[i].ID, history[i].name, history[i].rating);
		printf("\nWhat is your budget for today's meal? Php ");
		while ((result = scanf("%f%c", &budget, &trail)) != EOF) { 
			if (result != 2 || trail != '\n') {
				printf("\nPlease enter your budget correctly.");
				clear_buffer(); // to avoid infinite loop
				continue;
			}
			else{
				budget_it(catalogue, food_num, budget);//budget mode			
				printf("\nBased on your budget, I highly recommend this.\n");
				printf("Enjoy your meal!\n");
				*errPtr = 1;
				return;
        		}
    		}
	printf("Ctrl-D(Program end).\n");
	printf("Thank you for using Recomeal! :D\n\n");
	*errPtr = 1;
	return;
}



// Budget mode function
void budget_it(food_item *item_food, int food_num, float budgets) {
    int i, j;
    
    // Creating a new array of structures to copy the catalogue
    food_item *sorted_catalogue = malloc(food_num * sizeof(food_item));
    if (sorted_catalogue == NULL) {
        printf("Memory allocation failed\n");
        return;
    }
    
    // Copying the catalogue to the new array
    for (i = 0; i < food_num; i++) {
        sorted_catalogue[i] = item_food[i];
        // Calculate sulit value (assuming it's price / rating for simplicity)
        sorted_catalogue[i].sulit_value = sorted_catalogue[i].price / sorted_catalogue[i].rating;
    }
    
    // Bubble sort the array based on sulit_value
    for (i = 0; i < food_num - 1; i++) {
        for (j = 0; j < food_num - i - 1; j++) {
            if (sorted_catalogue[j].sulit_value > sorted_catalogue[j + 1].sulit_value) {
                // Swap the items
                food_item temp = sorted_catalogue[j];
                sorted_catalogue[j] = sorted_catalogue[j + 1];
                sorted_catalogue[j + 1] = temp;
            }
        }
    }
    
    // Printing food items within budget from highest to lowest sulit value
    printf("\nFood items within your budget sorted by sulit value:\n\n");
	printf("-----------------------------------------------------------\n");
	printf(" ID\tFood\t\t\tPrice\t\tSulit-ness\n");
	printf("-----------------------------------------------------------\n");

    for (i = food_num - 1; i >= 0; i--) {
        if (sorted_catalogue[i].price <= budgets) {
            printf(" %03d  \t%-20s\tPhp %.2f\t  %.2f 😋\n",
                   sorted_catalogue[i].ID, sorted_catalogue[i].name,
                   sorted_catalogue[i].price, sorted_catalogue[i].sulit_value);
        }
    }
    
    // Free dynamically allocated memory
    free(sorted_catalogue);
}

/*---------------------------------------------------------------
			"Main Function" 
---------------------------------------------------------------*/
int S_init(void) {
	// var declarations
	int option = 0;
	char trail; // dummy var to catch trailing characters
	int error = 0;
	int food_num, trash;
	int* errPtr = &error;

	// file ptr & dynamic mem allocation
	FILE* from_catalogue = fopen("../DB/catalogue.txt", "r");
	if (!from_catalogue) {
		printf("Error opening catalogue.\n");
		return 1;
	}
	
	FILE* from_history = fopen("../DB/purchase_history.txt", "r");
	if (!from_catalogue) {
		printf("Error opening catalogue.\n");
		return 1;
	}


	food_item* catalogue = malloc(sizeof(food_item) * 13);
	if (!catalogue) {
		printf("Memory allocation failed.\n");
		return 1;
	}
	
	food_item* history = malloc(sizeof(food_item) * 13);
	if (!catalogue) {
		printf("Memory allocation failed.\n");
		return 1;
	}
	
	// File reading
	read_data(from_catalogue, catalogue, &food_num);
	read_data(from_history, history, &trash);
	
	while (option != 4 && !error) {
		if (!error) {
			print_modes();
		}
		if (scanf("%d%c", &option, &trail) != 2 || trail != '\n') {
			printf("\nProgram exited with error: ");
			printf("\n\tDetected non-numeric input.\n");
			fclose(from_catalogue);
			free(catalogue);
			return 1;
		}
		else {
			printf("\n");
			switch(option){
				case 1:
					peruse(catalogue, errPtr);
					break;
				case 2:
					suggest(catalogue, history, food_num, errPtr);
					break;
				case 3:
					//input_mode(catalogue, history, food_num);
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
	fclose(from_history);
	free(history);
	return 0;
}
