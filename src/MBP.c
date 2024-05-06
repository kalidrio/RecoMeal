#include <stdio.h>
#include <string.h>
#include "MBP.h"
#define buflen 256

int S_init(char* filename) {

    char line[buflen];
    int items = 0;
    int history_items = 0;
    int choice, result;
    char trail;

    char directory[100] = "../DB/";
    strcat(directory, filename);
    strcat(directory, "_history.txt");

    FILE* from_meals = fopen("../DB/meals.txt", "r");
    if (from_meals == NULL) {
        printf("Error opening input file.\n");
        return 1;
    }

    FILE* history = fopen(directory, "r+");
    if (history == NULL) {
        printf("Error opening history file.\n");
        fclose(from_meals);
        return 1;
    }

    printf("\n---------------WELCOME TO RECOMEAL------------------\n");
    printf("              Decide less, eat more                 \n");


    while (fgets(line, sizeof(line), from_meals) != NULL) {
        items++; // count # of items(based on \n chars) in meals.txt
    } rewind(from_meals); // return file ptr to the 
			  // start of file

    meal catalogueArr[items]; // create an array of structs		
    read_data(from_meals, catalogueArr); // read and store data to struct array

    while (fgets(line, sizeof(line), history) != NULL) {
        history_items++; // count # of items(based on \n chars) in history.txt
    } rewind(history); // Rewind file pointer to the beginning

    purchase historyArr[history_items];
    read_history(history, historyArr); 

    if (history_items <= 1) { // <= 1 accounts for cases where the file
			      // is mostly empty aside from a single \n char
	printf("\nNo recent purchases. Proceeding to load program...\n\n");
    } else {
    	print_purchase(historyArr, history_items);
    }
//dunno if u want to continue this kasi mababago flowchart
    printf("What would you like to do?(Ctrl-D to Exit)\n");
    printf("\t1. Suggest Mode\n\t2. User Settings\n\t3. Exit");
    while((result = scanf(" %d%c", &choice, &trail)) != EOF) {
        if (result != 2 || trail != '\n') {
            printf("\nPlease enter a valid option");
            clear_buffer();
            continue;
        }
        else {
            switch(choice) {
                case 1:
	                suggest(catalogueArr, items, history);
                    break;
                case 2:
                    print_userMenu();
                    //add create a function para dun sa settings dunno what tho
                    break;
                case 3:
	                printf("\n\nThank you for using RecoMeal!\n");
                    break;
                default: 
                    printf("\nPlease enter a valid number.");
                    clear_buffer();
                    continue;
            }
            break;
        }
    }


	printf("\n\nCtrl-D: End of program. Thank you for using RecoMeal!\n");
    fclose(from_meals);
    fclose(history);

    return 0;
}

void print_purchase(purchase* historyArr, int items) {
	printf("\n\nYou've recently bought the following:\n");
	printf("-----------------------------------------------\n");
	printf("|          MEAL         |  PRICE  | SULITNESS |\n");
	printf("|-----------------------|---------|-----------|\n");
	for (int i = 0; i < items; i++) {
		printf("|  %-20s |  %5.2f  |   %5.2f   |\n", 
				historyArr[i].name,
                historyArr[i].price,
				historyArr[i].sulitness);
	} 
	printf("-----------------------------------------------\n\n");

}


/**
 * @brief Reads purchase history from a file into an array.
 * 
 * This function reads purchase history data from the provided file pointer
 * and stores it in the array of purchase structures.
 * 
 * @param from_history File pointer to the purchase history file.
 * @param historyArr Pointer to the array of purchase structures.
 */
void read_history(FILE* from_history, purchase* historyArr) {
	char line[buflen];
	int i = 0;
	while (fgets(line, sizeof(line), from_history)) {
		sscanf(line, "%s %f %f",
					 historyArr[i].name,
                     &historyArr[i].price,
					 &historyArr[i].sulitness);
		i++;
	}
}




/**
 * @brief Reads meal data from a file into an array.
 * 
 * This function reads meal data from the provided file pointer
 * and stores it in the array of meal structures.
 * 
 * @param from_meals File pointer to the meals file.
 * @param catalogueArr Pointer to the array of meal structures.
 */
void read_data(FILE* from_meals, meal* catalogueArr) {
	char line[buflen];
	int i = 0;
	while (fgets(line, sizeof(line), from_meals)) {
		sscanf(line, "%d %49s %f %49s %f %49s %f %f %f",
							&catalogueArr[i].ID, 

							catalogueArr[i].main_course,
							&catalogueArr[i].Mprice,

							catalogueArr[i].side,
							&catalogueArr[i].Sprice,

							catalogueArr[i].beverage,
							&catalogueArr[i].Bprice,

							&catalogueArr[i].total_price,
							&catalogueArr[i].sulitness);
		i++;	
	}
}



/**
 * @brief Prompts the user for their budget and suggests meals accordingly.
 * 
 * This function prompts the user to enter their budget for today's meal.
 * It then suggests meals based on the provided budget and past purchase history.
 * 
 * @param catalogueArr Pointer to the array of meal structures representing available food items.
 * @param items Number of items in the catalogueArr array.
 * @param to_history File pointer to the purchase history file for recording new purchases.
 */
void suggest(meal* catalogueArr, int items, FILE* to_history) {  
	float budget;
	char trail;
	int result; 

	printf("\nProgram running, press Ctrl-D to exit...\n\n");
	printf("\nWhat is your budget for today's meal? PHP ");
	while((result = scanf("%f%c", &budget, &trail)) != EOF) {
		if (result != 2 || trail != '\n') {
			printf("\nPlease enter your budget correctly. PHP ");
			clear_buffer();
			continue;
		}
		else {
			printf("With a budget of PHP %.2f, you can have the ff:\n", budget);
			budget_it(catalogueArr, items, budget, to_history);
            break;          
		}
	}
	printf("\n\nCtrl-D: End of program. Thank you for using RecoMeal!\n");
}


/**
 * @brief Clears the input buffer to avoid infinite loops.
 * 
 * This function clears the input buffer by consuming all characters
 * from the standard input stream until encountering a newline character.
 */
void clear_buffer(void) { 				// to avoid infinite loops
	while ((getchar()) != '\n'); 
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
 * @param to_history File pointer to the purchase history file.
 */
void budget_it(meal* catalogueArr, int items, float budget, FILE* to_history) {
    int i;
    int result;
    char trail, choice;

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
    printf("--------------------------------------------------------------------------------------------------------------------------------\n");
    printf("|  ID  |          Main Course       | M. Price | Side Dish     | S. Price | Beverage      | B. Price | Total Price | Sulitness |\n");
    printf("|------|----------------------------|----------|---------------|----------|---------------|----------|-------------|-----------|\n");

    for (i = 0; i < items; i++) {
        if (temp[i].total_price <= budget) {
            printf("| %03d  | %-25s  | ₱%-7.2f | %-13s | ₱%-7.2f | %-13s | $%-7.2f | $%-10.2f | %-9.2f |\n",
                   temp[i].ID, temp[i].main_course, temp[i].Mprice,
                   temp[i].side, temp[i].Sprice,
                   temp[i].beverage, temp[i].Bprice,
                   temp[i].total_price, temp[i].sulitness);
        }
    }

    printf("--------------------------------------------------------------------------------------------------------------------------------\n");


    printf("Would you like to record a purchase? Y/N.\n");


    while((result = scanf(" %c%c", &choice, &trail)) != EOF) {
        if (result != 2 || trail != '\n') {
            printf("\nPlease enter Y or N.");
            clear_buffer();
            continue;
        }
        else {
            switch(choice) {
                case 'y':
                case 'Y':
                    inputMode(to_history);
                    break;
                case 'n':
                case 'N':
                    break;
                default: 
                    printf("\nPlease enter Y or N.");
                    clear_buffer();
                    continue;
            }
            break;
        }
    }
}

/**
 * @brief Handles the input mode where the user can record a new purchase.
 * 
 * This function allows the user to input details of a new purchase,
 * such as the name, price, and sulitness of the meal. It then records
 * the purchase in the purchase history file provided.
 * 
 * @param to_history File pointer to the purchase history file for recording new purchases.
 */
void inputMode(FILE* to_history) {
    rewind(to_history); //places the pointer at the start;
    int items = 0; // Initialize items to 0
    int result;
    char line[buflen], trail;
    while (fgets(line, sizeof(line), to_history) != NULL) {
        items++; // count # of items and places the pointer at the end of the file
    }

    // Increase size by 1 for the new purchase
    purchase currHistory[items + 1];

    // Read history into currHistory array
    rewind(to_history);
    read_history(to_history, currHistory);

    // Move existing purchases back by one position
    for (int i = items; i > 0; i--) {
        currHistory[i] = currHistory[i - 1];
    }

    purchase temp;

    printf("Please enter the name of the Meal: ");
    while((result = scanf(" %s%c", temp.name, &trail)) != EOF) {
        if (result != 2 || trail != '\n') {
            printf("\nPlease enter again.");
            clear_buffer();
            continue;
        }
        else{
            break;
        }
    }
    printf("\n");


    printf("Please enter the Price of the Meal: ");
    while ((result = scanf("%f%c", &temp.price, &trail)) != EOF) {
        if (result != 2 || trail != '\n') {
            printf("\nPlease enter again.");
            clear_buffer();
            continue;
        } else {
            break;
        }
    }
    printf("\n");

    printf("Please enter the Sulitness of the Meal (1-10): ");
    while ((result = scanf("%f%c", &temp.sulitness, &trail)) != EOF) {
        if (result != 2 || trail != '\n') {
            printf("\nPlease enter again. ");
            clear_buffer();
            continue;
        } else {
            break;
        }
    }
    printf("\n");


    rewind(to_history);
    currHistory[0] = temp;
    for(int i=0; i<(items+1); i++ ){
        fprintf(to_history, "%s %f %f\n", currHistory[i].name, currHistory[i].price, currHistory[i].sulitness);
    }

}
/*user settings*/
void print_userMenu(void){
    printf("What would you like to do?\n");
    printf("\t1. Change User\n\t2.Change Password\n\t3. Delete Account\n");
}
