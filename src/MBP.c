
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "MBP.h"
  
  
void print_menu(void);
void print_menu2(void);
void print_menu3(void);

//void peruse_mode(FILE *fp);


//suggest mode
void suggest_mode(food_item *data_ptr, food_item *history_ptr, int food_num);
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

  
  

void read_data(FILE* from_catalogue, food_item* catalogue, int food_num) {
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
	int error = 0, food_num;
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
	read_data(from_catalogue, catalogue, food_num);
	read_data(from_history, history, food_num);
	
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
	return 0;
}


void sorting_algo_price(food_item *tb_sorted, int num_items) 
{
    int i, j;
    food_item temp;

    for (i = 0; i < num_items - 1; i++) {
        for (j = 0; j < num_items - i - 1; j++) {
            // Compare prices and swap if needed
            if (tb_sorted[j].price > tb_sorted[j + 1].price) {
                temp = tb_sorted[j];
                tb_sorted[j] = tb_sorted[j + 1];
                tb_sorted[j + 1] = temp;
            }
        }
    }
}




void suggest_mode(food_item *data_ptr, food_item *history_ptr, int food_num){
	int option = 0;
	char extra;
	float budgets, rating, sulit_value;
	printf("\n-----------SUGGEST MODE-----------\n");


	printf("These are your last 10 purchases: \n");

	for (int i = 0; i < 10; i++){
        printf("ID: %d  Food: %s  Rating: %f\n", history_ptr[i].ID, history_ptr[i].food_name, history_ptr[i].rating);
    	}
   	
    while (1) {
		option = 0; 
        print_menu2();
        if (scanf("%d%c", &option, &extra) != 2 || extra != '\n' || option < 1 || option > 4) {
            printf("\nError: Input was not a single digit integer. Please try again.\n");
            // Clear the input buffer
            while ((getchar()) != '\n');
            continue; // Continue to the next iteration of the loop
        }
		else {
            switch(option) {
                case 1:
					printf("What is your budget for the meal?: \n");
					scanf("%f", &budgets);
                    budget_mode(data_ptr, food_num, budgets);	//budget mode			
                    break;
                case 2:
					printf("Find foods based on rating (ENTER RATING 1.0 -10.0): \n");
					scanf("%f", &rating);
                    rating_mode(data_ptr, food_num, rating); //rating mode
                    break;
                case 3:
					printf("Find foods based on rating (ENTER RATING 1.0-5.0): \n");
					scanf("%f", &rating);
                    sulit_value_mode(data_ptr, food_num, sulit_value); //sulit mode
                    break;
                case 4:
                    printf("\nReturning to Home...\n"); //exit
					free(history_ptr); //freeing the memory allocated by file_reading
                    free(data_ptr);
					return;
                default:
                    printf("Invalid option. Please choose again.\n");
            }
        }
    }
}


void budget_mode(food_item *item_food, int food_num, float budgets){
	
	printf("Food items within your budget\n");
	printf("===========================================\n\n");
	
	//will make a sorting algorithm
	sorting_algo_price(item_food, food_num);
	//printing food within budget
    for (int i = 0; i < food_num; i++) {
        if (item_food[i].price <= budgets) {
            printf("%05d  %s\nPHP %.2f\n", item_food[i].ID, item_food[i].food_name, item_food[i].price);
        }
    }
	printf("Returning....\n");
	return;
}


void rating_mode(food_item *item_food, int food_num, float rating){	
	if (rating<10.0) {
		printf("Foods available from rating %f to %f\n", rating-0.5, rating+0.5);
	}
	else{
		printf("Foods available from rating %f to %f\n", rating-0.5, rating);

	}
		printf("===========================================\n\n");	
		//will make a sorting algorithm
		sorting_algo_rating(item_food, food_num);
		//printing food within -0.5 and +0.5 rating
		for (int i = 0; i < food_num; i++) {
			if (item_food[i].rating >= (rating-0.5) && item_food[i].rating <= (rating+0.5)) {
				printf("%05d  %s\nRating: %.2f\n", item_food[i].ID, item_food[i].food_name, item_food[i].rating);
			}
		}
		printf("Returning....\n");
		return;		
}

void sulit_value_mode(food_item *item_food, int food_num, float sulit_value){
	printf("Food items that has a sulit value of %f and above\n", sulit_value);
	printf("===========================================\n\n");
	
	//will make a sorting algorithm
	sorting_algo_sulit(item_food, food_num);
	//printing food within budget
    for (int i = 0; i < food_num; i++) {
        if (item_food[i].sulit_value >= sulit_value) {
            printf("%05d %s\nSulit value: %.2f\n", item_food[i].ID, item_food[i].food_name, item_food[i].sulit_value);
        }
    }
	printf("Returning....\n");
	return;
}



/*
void input_mode(food_item *, FILE *fp1){
	int option = 0;
	food_item* history_ptr = file_reading(fp1, &trash);
	food_item* data_ptr = file_reading(fp, &food_num);
}

*/
    while (1) {
        print_menu3();
        if (scanf("%d%c", &option, &extra) != 2 || extra != '\n') {
            printf("\nError: Input was not a single digit integer. Please try again.\n");
            // Clear the input buffer
            while ((getchar()) != '\n');
            continue; // Continue to the next iteration of the loop
        }
		else {
            switch(option) {
                case 1:
                    //existing(data_ptr, history_ptr);	//existing food item		
                    break;
                case 2:
                    //new_item(data_ptr, history_ptr); //rating mode
                    break;
                case 3:
					printf("\nReturning to Home...\n"); //exit
					free(history_ptr); //freeing the memory allocated by file_reading
                    free(data_ptr);
					return;
                    break;
                default:
                    printf("Invalid option. Please choose again.\n");
            }
        }
    }
}
	

/*void existing(food_item *add, food_item *add_history){
return;
}




void new_item(food_item *add, food_item *add_history){

		}
	}
*/


void sorting_algo_rating(food_item *tb_sorted, int num_items) 
{
    int i, j;
    food_item temp;

    for (i = 0; i < num_items - 1; i++) {
        for (j = 0; j < num_items - i - 1; j++) {
            // Compare ratings and swap if needed
            if (tb_sorted[j].rating > tb_sorted[j + 1].rating) {
                temp = tb_sorted[j];
                tb_sorted[j] = tb_sorted[j + 1];
                tb_sorted[j + 1] = temp;
            }
        }
    }
}

void sorting_algo_sulit(food_item *tb_sorted, int num_items) 
{
    int i, j;
    food_item temp;

    for (i = 0; i < num_items - 1; i++) {
        for (j = 0; j < num_items - i - 1; j++) {
            // Compare sulit value and swap if needed
            if (tb_sorted[j].sulit_value > tb_sorted[j + 1].sulit_value) {
                temp = tb_sorted[j];
                tb_sorted[j] = tb_sorted[j + 1];
                tb_sorted[j + 1] = temp;
            }
        }
    }
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









