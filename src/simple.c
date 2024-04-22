#include <stdio.>
#include <string.h>
#include "simple.h"

void clear_buffer(void) { // to avoid infinite loops
	while ((getchar()) != '\n'); 
}

void read_data(FILE* from_meals, meal* catalogueArr, int* count) {

	char line[256];
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
	*count = i;
}

void inquire(void) {
	printf("\nPlease choose an option: \n");
	printf("\t1. Start program.\n");
	printf("\t2. See recent purchases. \n");
	printf("\t3. Record purchase.\n");
	printf("\t4. Exit\n");
	printf("\nOption: ");	
}

/*---------------------------------------------------------------
                        "Main" Function
---------------------------------------------------------------*/
int S_init(void) {
        
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
	
        int option = 0, error = 0, count = 0, trash;
        int* errPtr = &error;
        char trail; 

	// change size if necessary
	meal catalogueArr[15];

        read_data(from_meals, catalogueArr, &count);
        // read_data(from_history, history, &trash);

        while (option != 4) {
                if (!error) {
                        inquire();
                }
		int result = scanf("%d%c", &option, &trail);
		if (result == EOF) {
			printf("Ctrl-D.\nThank you for using RecoMeal! :D\n");
			return 1;
		}
                if (result != 2 || trail != '\n') {
                        printf("Error: Detected non-numeric input.\n");
			clear_buffer();
			printf("\nPlease choose a value within 1 to 4: ");
			*errPtr = 1;
			continue;
                }
                else {
                        printf("\n");
                        switch(option){
                                case 1:
					printf("Start Program\n");
                                        //suggest(catalogue, history, food_num, errPtr);
                                        break;
                                case 2:
					printf("See recent purchases\n");
                                        break;
                                case 3:
					printf("Record purchases\n");
					//record purchase;
                                        break;
                                case 4:
                                        printf("Program exited successfully.\n");
                                        break;
                                default:
                                        printf("Please choose a value within 1 to 4: ");
                                        break;
                        }
                }
        }
        fclose(from_meals);
	fclose(to_history);
        fclose(from_history);
        return 0;
}

/*---------------------------------------------------------------
                      "Case" Functions
---------------------------------------------------------------*/
void suggest(meal* catalogueArr, int count, int* errPtr) { //"CASE 1" 
	float budget;
	char trail;
	int result;

	while((result = scanf("%f%c", &budget, &trail)) != EOF) {
		
		printf("What is your budget for today's meal? PHP ");
		if (result != 2 || trail != '\n') {
			printf("Please enter your budget correctly.\n");
			clear_buffer();
			continue;
		}
		else {
			printf("With a budget of PHP %.2f, you can have the ff:\n", budget);
				
		}
	}

}

void print_recent(); //"CASE 2"

