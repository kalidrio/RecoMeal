#include <stdio.h>
#include <string.h>
#include "single.h"
#define buflen 256

int S_init(void) {

    char line[buflen];
    int items = 0;
    int history_items = 0;
    long size_toCheck = 0;

    FILE* from_meals = fopen("../DB/meals.txt", "r");
    if (from_meals == NULL) {
        printf("Error opening input file.\n");
        return 1;
    }

    FILE* history = fopen("../DB/history.txt", "r+");
    if (history == NULL) {
        printf("Error opening output file.\n");
        fclose(from_meals);
        return 1;
    }

    while (fgets(line, sizeof(line), from_meals) != NULL) {
        items++; // count # of items in meals.txt
    }
	rewind(from_meals);
    /*creates an array of structs*/
    meal catalogueArr[items]; 		
    /*reads the data from the file and puts them in the array.*/
    read_data(from_meals, catalogueArr);


    while (fgets(line, sizeof(line), history) != NULL) {
        history_items++; // count # of items in history.txt
    }
	rewind(history); // Rewind file pointer to the beginning


	if (history_items == 1) { 			// purchase history file is empty
		printf("No recent purchases. Proceeding to load program...\n\n");
	}	

    purchase historyArr[history_items];
    read_history(history, historyArr); 
	print_purchase(historyArr, history_items);	

	suggest(catalogueArr, items);


    fclose(from_meals);
    fclose(history);

    return 0;
}

void print_purchase(purchase* historyArr, int items) {
	printf("You've recently bought the following:\n");
	printf(" ID#	   MEAL	              SULITNESS\n");
	printf("----------------------------------------\n");
	for (int i = 0; i < items; i++) {
		printf(" %03d	  %-20s	%.2f\n", 
				historyArr[i].ID,
				historyArr[i].name,
				historyArr[i].sulitness);
	} 
}


void read_history(FILE* from_history, purchase* historyArr) {
	char line[buflen];
	int i = 0;
	while (fgets(line, sizeof(line), from_history)) {
		sscanf(line, "%d %s %f", &historyArr[i].ID, 
					 historyArr[i].name,
					 &historyArr[i].sulitness);
		i++;
	}
}








void read_data(FILE* from_meals, meal* catalogueArr) {
	char line[buflen];
	int i = 0;
	while (fgets(line, sizeof(line), from_meals)) {
		sscanf(line, "%d %49s %f %49s %f %49s %f %f %f",
							&catalogueArr[i].ID, 

							catalogueArr[i].main_course,
							&catalogueArr[i].Mprice,

							catalogueArr[i].dessert,
							&catalogueArr[i].Dprice,

							catalogueArr[i].beverage,
							&catalogueArr[i].Bprice,

							&catalogueArr[i].total_price,
							&catalogueArr[i].sulitness);
		i++;	
	}
}

void suggest(meal* catalogueArr, int items) {  
	float budget;
	char trail;
	int result;

	printf("Program running, press Ctrl-D to exit...\n\n");
	printf("\nWhat is your budget for today's meal? PHP ");
	while((result = scanf("%f%c", &budget, &trail)) != EOF) {
		if (result != 2 || trail != '\n') {
			printf("\nPlease enter your budget correctly. PHP ");
			clear_buffer();
			continue;
		}
		else {
			budget_it(catalogueArr, items, budget);
			printf("With a budget of PHP %.2f, you can have the ff:\n", budget);

				
		}
	}
	printf("\n\nCtrl-D: End of program. Thank you for using RecoMeal!\n");
}


/**
 * @brief Filters and prints food items within the specified budget, sorted by sulitness.
 * 
 * This function takes an array of meal structures, the number of items in the array,
 * and a budget as parameters. It filters the meal items based on the total price
 * within the specified budget, sorts them by sulitness in descending order, and prints
 * the filtered items in a table format.
 * 
 * @param catalogueArr Pointer to the array of meal structures.
 * @param items Number of items in the catalogueArr array.
 * @param budget The budget for filtering food items.
 */
void budget_it(meal* catalogueArr, int items, float budget) {
    int i;

    // Creating a new array of structures to copy the catalogue
    meal temp[items];
    
    // Copying the catalogue to the new array
    for (i = 0; i < items; i++) {
        temp[i] = catalogueArr[i];
    }
    
    // Bubble sort the array based on sulit_value in descending order
    for (i = 0; i < items - 1; i++) {
        for (int j = 0; j < items - i - 1; j++) {
            if (temp[j].sulitness < temp[j + 1].sulitness) {
                // Swap the items
                meal swap = temp[j];
                temp[j] = temp[j + 1];
                temp[j + 1] = swap;
            }
        }
    }

    // Printing food items within budget sorted by sulit value in a table
    printf("\nFood items within your budget sorted by sulit value:\n\n");
    printf("----------------------------------------------------------------------------------------------------------------------\n");
    printf("| ID | Main Course      | M. Price | Dessert       | D. Price | Beverage      | B. Price | Total Price | Sulitness |\n");
    printf("|----|------------------|----------|---------------|----------|---------------|----------|-------------|-----------|\n");

    for (i = 0; i < items; i++) {
        if (temp[i].total_price <= budget) {
            printf("| %-2d | %-15s | $%-7.2f | %-13s | $%-7.2f | %-13s | $%-7.2f | $%-10.2f | %-9.2f |\n",
                   temp[i].ID, temp[i].main_course, temp[i].Mprice,
                   temp[i].dessert, temp[i].Dprice,
                   temp[i].beverage, temp[i].Bprice,
                   temp[i].total_price, temp[i].sulitness);
        }
    }

    printf("----------------------------------------------------------------------------------------------------------------------\n");
}

