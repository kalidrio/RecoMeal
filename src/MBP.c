
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "MBP.h"
  
  
void print_menu(void);
void print_menu2(void);
void print_menu3(void);

//void peruse_mode(FILE *fp);


//suggest mode
void suggest_mode(food_item *catalogue, food_item *history, int food_num);
void budget_mode(food_item *fp, int food_num, float budgets);
void rating_mode(food_item *fp, int food_num, float rating);
void sulit_value_mode(food_item *fp, int food_num, float sulit_value);
void sorting_algo_price(food_item *items, int num_items);
void sorting_algo_rating(food_item *items, int num_items);
void sorting_algo_sulit(food_item *items, int num_items);

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

void print_Menu(void) {
	printf("\nWhat would you like to do? [ENTER THE NUMBER]\n");
	printf("\t1. Peruse Mode\n");
	printf("\t2. Suggest Mode\n");
	printf("\t3. Input Mode\n");
	printf("\t4. Exit\n");
	printf("\nChoice: ");
}

void peruse(food_item* catalogue, int* errPtr) {
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
			printf("\n\tDetected non-numeric input.\n");
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
	int food_num, trash;
	int* errPtr = &error;

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
	read_data(from_catalogue, catalogue, &food_num);
	read_data(from_history, history, &trash);
	
	while (option != 4 && !error) {
		if (!error) {
			print_Menu();
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
					suggest_mode(catalogue, history, food_num);
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



void suggest_mode(food_item *catalogue, food_item *history, int food_num){
	char extra;
	float budgets, rating, sulit_value;
	char trail; // dummy var to catch trailing characters
	int result;

	printf("\n-----------SUGGEST MODE----------- %d\n", food_num);
	printf("\nThese are your last 10 purchases: \n");

	for (int i = 0; i < 10; i++){
        printf("ID: %03d  Food: %-20s  Rating: %.2f\n", history[i].ID, history[i].name, history[i].rating);
	}
   	


	printf("\nWhat is your budget for todays meal? [ex. 50.00]");
	while ((result = scanf("%f%c", &budgets, &trail)) != EOF) {
		if (result != 2 || trail != '\n') {
			printf("\nPlease enter your budget correctly");
			continue;
		}
		else{
		budget_mode(catalogue, food_num, budgets);	//budget mode			
		printf("Based on")
        }
    }
}



// Budget mode function
void budget_mode(food_item *item_food, int food_num, float budgets) {
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
    printf("Food items within your budget sorted by sulit value:\n");
    printf("===========================================\n\n");
    for (i = food_num - 1; i >= 0; i--) {
        if (sorted_catalogue[i].price <= budgets) {
            printf("ID: %03d  Food: %-20s  Price: %.2f  Rating: %.2f  Sulit Value: %.2f\n",
                   sorted_catalogue[i].ID, sorted_catalogue[i].name,
                   sorted_catalogue[i].price, sorted_catalogue[i].rating, sorted_catalogue[i].sulit_value);
        }
    }
    
    // Free dynamically allocated memory
    free(sorted_catalogue);
}






void print_menu(void) {
	printf("\nWhat would you like to do? [ENTER THE NUMBER]\n");
	printf("\t1. Peruse Mode\n");	
	printf("\t2. Suggest Mode\n");
	printf("\t3. Input Mode\n");
	printf("\t4. Exit\n");
	return;
}
void print_menu2(void) {
	printf("\nFilter the food items based on: [ENTER THE NUMBER]\n");
	printf("\t1. Budget\n");	
	printf("\t2. Ratings\n");
	printf("\t3. Sulit Value\n");
	printf("\t4. Return to Home.\n");
	return;
}

void print_menu3(void) {
	printf("\nWhat would you like to enter?\n");
	printf("\t1. Existing food item.\n");	
	printf("\t2. New food item\n");
	printf("\t3. Return to Home\n");
	return;
}









