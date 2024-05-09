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

int count(char line, FILE* file) {
	int units = 0;
	while(fgets(line, sizeof(line), file) != NULL) {
		units++ // count # of items(based on \n chars)
	}
	rewind(file); // return file ptr to file start
	return units;
}

void print_other_options(void){
	printf("\nWould you like to perform another action?\n");
	printf("\n\t(1) Record a purchase\n");
	printf("\t(2) Update Account info\n");
	printf("\t(3) Exit\n");
	printf("\nChoice: ");
}

void print_userMenu(void){
	printf("What would you like to do? (Ctrl-D to Exit)\n");
	printf("\t(1) Change Username\n\t(2) Change Password\n\t(3) Delete Account\n");
}

int MBP_main(User* user, User* head) {

	char line[buflen];
	int items = 0, history_items = 0;
	int choice, result;
	float budget;
	char trail;
	char directory[100] = "../DB/";
while (1) {
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

	items = count(line, from_meals);
	meal catalogueArr[items]; // items now defined, static size array possible
	read_data(from_meals, catalogueArr); 

	history_items = count(line, from_history);
	purchase historyArr[history_items];

	if (history_items <= 1) { // accounts for cases where file is mostly empty except for one \n char
		printf("\nNo recent purchases. Loading program...\n\n");	
	} else {
		print_purchase(historyArry, history_items);
	}

	printf("\nProgram running, press Ctrl-D to exit:...\n\n");
	printf("What is your budget for today's meal? PHP ");
	
	result = scanf("%f%c", &budget, &trail);
	switch(result) {
		case EOF:
			printf("End of file.\nThank you for using RecoMeal!\n");
			return 1;
		
		case 2:
			if (trail == '\n') {
				printf("With a budget of PHP %.2f, you can have the ff:\n", budget);
				suggest(catalogueArr, items, budget, to_history, user, head);
				break;
			} else {
				printf("Invalid input.\n");
				clear_buffer();
				continue;
			}
			break;

		default:
			printf("Expected input is a float.\n");
			clear_buffer();
			continue;
	}
	print_other_options();
	result = scanf("%d%c", &choice, &trail);
       	switch(result) {
		case EOF:
			printf("End of file.\nThank you for using RecoMeal!\n");
			return 1;

		case 2:
			if (trail == '\n') {
				switch(choice) {
					case 1:
						inputMode(to_history);
						break;
					case 2:
						print_userMenu();
						result = scanf("%d%c", &choice, &trail);
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
								printf("\nPlease enter a valid number.\n");
								clear_buffer();
								continue;
						}
						break;
					case 3:
						return 0;
					default:
						printf("\nPlease enter a choice from 1 to 3: ");
						clear_buffer();
						continue;
				}
			} else {
				printf("Invalid input.\n");
				clear_buffer();
				continue;
			}
			break;

		default:
			printf("Please enter choice correctly.");
			clear_buffer();
			continue;
	}	
}
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
		sscanf(line, "%s %f %f", historyArr[i].name,
					&historyArr[i].price,
					&historyArr[i].sulitness);
		i++;
	}
}

void print_purchase(purchase* historyArr, int items) {
        printf("\n\nYou've recently bought the following:\n");
        printf("------------------------------------------------\n");
        printf("|          MEAL         |   PRICE  | SULITNESS |\n");
        printf("|-----------------------|----------|-----------|\n");
        for (int i = 0; i < items; i++) {
                printf("|  %-20s |  %6.2f  |   %5.2f   |\n",
                                historyArr[i].name,
                                historyArr[i].price,
                                historyArr[i].sulitness);
        }
        printf("------------------------------------------------\n\n");
}

void suggest(meal* catalogueArr, int items, float budget, FILE* to_history, User* user, User* head) {
	meal temp[items]; // structArr for copying the catalogue

	for(i = 0; i < items; i++) { // copy operation
		temp[i] = catalogueArr[i];
	}

	for(i = 0; i < items - 1; i++) { // Bubble sort based on sulitness, descending order
		for(int j = 0; j < items - i - 1; j++) {
			if(temp[j].sulitness < temp[j+1].sulitness) {
				meal swap = temp[j];
				temp[j] = temp[j+ 1];
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
            		printf("| %03d  | %-25s  | ₱%-7.2f | %-13s | ₱%-7.2f | %-13s | ₱%-7.2f | ₱%-10.2f | %-9.2f |\n",
                   		temp[i].ID, temp[i].main_course, temp[i].Mprice,
                   		temp[i].side, temp[i].Sprice,
                   		temp[i].beverage, temp[i].Bprice,
                   		temp[i].total_price, temp[i].sulitness);
        	}
	}

	printf("--------------------------------------------------------------------------------------------------------------------------------\n");
}

void inputMode(FILE* to_history) {
	int result, items = 0;
	char trail, line[buflen];
	
	rewind(to_history);
	items = count(line, to_history);

	purchase currHistory[items + 1]; // size + 1 to accomodate new purchase
	
	rewind(to_history);
	read_history(to_history, currHistory);

	for(int i = items; i > 0; i--) { // shift items by one place
		currHistory[i] = currHistory[i - 1];
	}

	purchase temp;
	printf("\nMeal name: "); 
	while((result = scanf("%s%c", temp.name, &trail)) != EOF) {
		if(result != 2 || trail != '\n') {
			printf("\nPlease enter again.\n");
			clear_buffer();
			continue;
		} else break;
	}	
	printf("\nMeal price: ");
	while((result = scanf("%f%c", &temp.price, &trail)) != EOF) {
		if(result != 2 || trail != '\n') {
			printf("\nPlease enter again.\n");
			clear_buffer();
			continue;
		} else break;
	}
	printf("\nMeal rating (1 - 10): ");
	while((result = scanf("%f%c", &temp.sulitness, &trail)) != EOF) {
		if (result != 2; || trail != '\n') {
			printf("\nPlease enter again.");
			clear_buffer();
			continue;
		} else break;
	}

	rewind(to_history);
	currHistory[0] = temp;
	for(int i = 0; i < (items + 1); i++) {
		fprinf(to_history, "%s %f %f\n", currHistory[i].name,
						 currHistory[i].price,
						 currHistory[i].sulitness);
	}
}
/*-------------------------------------------------------------------------------------------------------------------------------*/
/*--------------------------------------------------------END OF PROGRAM---------------------------------------------------------*/
/*-------------------------------------------------------------------------------------------------------------------------------*/
