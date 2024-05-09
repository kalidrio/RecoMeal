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

int S_init(User* user, User* head) {

	char line[buflen];
	int items = 0, history_items = 0;
	int choice, result;
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
				suggest(catalogueArr, items, history, user, head);
				break;
			} else {
				printf("Invalid input.\n");
				clear_buffer();
				break; // (continue)
			}
			break;

		default:
			printf("Expected input is a float.\n");
			clear_buffer();
			break; // (continue)
	}
}
	return 0;
}
