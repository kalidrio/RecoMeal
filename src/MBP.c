#include <stdio.h>
#include <string.h>
#include "structs.h"
#include "MBP.h"
#include "account_management.h"
#include "login.h"


#define buflen 256

void clear_buffer(void) { // to avoid infinite loops
	while ((getchar()) != '\n'); 
}

int S_init(User* user, User* head) {

    char line[buflen];
    int items = 0;
    int history_items = 0;  
    int choice, result;
    char trail;

    char directory[100] = "../DB/";
    strcat(directory, user->username);
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
    read_data(from_meals, catalogueArr); // 1. read and store data to struct array

    while (fgets(line, sizeof(line), history) != NULL) {
        history_items++; // count # of items(based on \n chars) in history.txt
    } rewind(history); // Rewind file pointer to the beginning

    purchase historyArr[history_items];
    read_history(history, historyArr); // 2. read and store to history structArr 

    if (history_items <= 1) { // <= 1 accounts for cases where the file
			      // is mostly empty aside from a single \n char
	printf("\nNo recent purchases. Proceeding to load program...\n\n");
    } else {
    	print_purchase(historyArr, history_items); // 3. Self-explanatory
    }
    suggest(catalogueArr, items, history, user, head);


    fclose(from_meals);
    fclose(history);
    return 0;
}

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

void suggest(meal* catalogueArr, int items, FILE* to_history, User* user, User* head) {  
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
			budget_it(catalogueArr, items, budget, to_history, user, head);
            break;          
		}
	}
	printf("\n\nCtrl-D: End of program. Thank you for using RecoMeal!\n");
}

void budget_it(meal* catalogueArr, int items, float budget, FILE* to_history, User* user, User* head) {
    int i;
    int choice, result;
    char trail;

    meal temp[items]; // temp struct Arr for copying the catalogue
    
    for (i = 0; i < items; i++) { // copy operation
        temp[i] = catalogueArr[i];
    }
    
    for (i = 0; i < items - 1; i++) { // Bubble sort based on sulitness, descending order
        for (int j = 0; j < items - i - 1; j++) {
            if (temp[j].sulitness < temp[j + 1].sulitness) {
                // Swap the items
                meal swap = temp[j];
                temp[j] = temp[j + 1];
                temp[j + 1] = swap;
            }
        }
    }

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


    printf("\n\t1. Record a purchase.\n");
    printf("\t2. Update User Settings.\n");
    printf("\t3. End Program.\n");


    while((result = scanf(" %d%c", &choice, &trail)) != EOF) {
        if (result != 2 || trail != '\n') {
            printf("\nPlease enter a valid number");
            clear_buffer();
            continue;
        }
        else {
            switch(choice) {
                case 1:
                    inputMode(to_history);
                    break;
                case 2:
                    print_userMenu();
                    userSettings(user, head);
                    break;
                case 3:
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
    printf("What would you like to do? (Ctrl-D to Exit)\n");
    printf("\t1. Change User\n\t2. Change Password\n\t3. Delete Account\n");
}


void userSettings(User* account, User* head){
    int result, choice;
    char trail;

    while((result = scanf(" %d%c", &choice, &trail)) != EOF) {
        if (result != 2 || trail != '\n') {
            printf("\nPlease enter a valid option");
            clear_buffer();
            continue;
        }
        else {
            switch(choice) {
                case 1:
                    changeUser(account);
                    break;
                case 2:
                    changePass(account);
                    break;
                case 3:
                    deleteAccount(account, head);
		    deleteAccountFromDB(account, head);
                    break;
                default:
                    printf("\nPlease enter a valid number.");
                    clear_buffer();
                    continue;
            }
            break;
        }
    }
}


/*-------------------------------------------------------------------------------------------------------------------------------*/
/*--------------------------------------------------------END OF PROGRAM---------------------------------------------------------*/
/*-------------------------------------------------------------------------------------------------------------------------------*/
