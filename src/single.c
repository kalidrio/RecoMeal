#include <stdio.h>
#include <string.h>
#include "single.h"
#define buflen 256

/*---------------------------------------------------------------
                        Insert Documentation here 
---------------------------------------------------------------*/
int S_init(void) {
        int option = 0, count = 0, trash;
	long size_toCheck;
        char trail; 

	FILE* from_meals = fopen("../DB/meals.txt", "r");
        if (!from_meals) {
                printf("Error opening input file.\n");
                return 1;
        }

	FILE* to_history = fopen("../DB/purchase_history.txt", "w");
        FILE* from_history = fopen("../DB/purchase_history.txt", "r");
        if (!from_history) {
                printf("Error opening purchase history.\n");
		return 1;
        }
	
	meal catalogueArr[15]; 				// catalogue is fixed at 15 items.
        read_data(from_meals, catalogueArr, &count);
	
	fseek(from_history, 0, SEEK_END);		// move fp to EOF
	size_toCheck = ftell(from_history);		// get current position of fp

	if (size_toCheck == 0) { 			// purchase history file is empty
		printf("No recent purchases. Proceeding to load program...\n\n");
	}	
	
	else {
		char line[buflen];
		int items = 0;
		while (fgets(line, sizeof(line), from_history) != NULL) 
			items++; 			// count # of recent purchases
		
		if (items == 0) {
			printf("emptyfile\n");
			return 1;
		}

		purchase historyArr[items];
		
		read_history(from_history, historyArr, items); 

		print_purchase(historyArr, items);	
	}

	suggest(catalogueArr, count);

        fclose(from_meals);
	fclose(to_history);
        fclose(from_history);
        return 0;
}

void clear_buffer(void) { 				// to avoid infinite loops
	while ((getchar()) != '\n'); 
}

void read_data(FILE* from_meals, meal* catalogueArr) {
	char line[buflen];
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
	}
}

void read_history(FILE* from_history, purchase* historyArr) {
	char line[buflen];
	while (fgets(line, sizeof(line), from_history)) {
		sscanf(line, "%d %s %f", &historyArr[i].ID, 
					 historyArr[i].name,
					 &historyArr[i].sulitness);
	}
}

void print_purchase(purchase* historyArr, int items) {
	printf("You've recently bought the following:\n");
	printf("\tID#	MEAL	SULITNESS\n");
	printf("\t\n--------------------------\n");
	for (int i = 0; i < items; i++) {
		printf("\t%d	%49s	%.2f\n", 
				historyArr[i].ID,
				historyArr[i].name,
				historyArr[i].sulitness);
	} 
}

void suggest(meal* catalogueArr, int count) {  
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
			printf("With a budget of PHP %.2f, you can have the ff:\n", budget);
				
		}
	}
	printf("\n\nCtrl-D: End of program. Thank you for using RecoMeal!\n");
}

