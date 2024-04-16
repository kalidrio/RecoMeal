#include<stdio.h>
#include<stdlib.h>
#define MAX 10000

typedef struct 
{
    int id;
    char food_name[100];
    float price;
    float rating;
    float sulit_value;
}food_item;


void print_menu(void);
void print_menu2(void);
//void peruse_mode(FILE *fp);
void suggest_mode(FILE *fp, FILE *fp1);
//void input_mode(FILE *fp);
void budget_mode(food_item *fp, int food_num, float budgets);
void rating_mode(food_item *fp, int food_num, float rating);
void sulit_value_mode(food_item *fp, int food_num, float sulit_value);
void sorting_algo_price(food_item *items, int num_items);
void sorting_algo_rating(food_item *items, int num_items);
void sorting_algo_sulit(food_item *items, int num_items);


int S_init(void) {
	int option = 0;
	char extra;  // dummy var to catch trailing input
	FILE *fp;
	FILE *fp1;


	fp = fopen("../DB/food_items.txt", "r+");  //opens the file for reading and writing
	fp1 = fopen("../DB/purchase_history.txt", "r+");
	
	while (option != 4) {
		print_menu();
		// extra catches trailing non-numeric characters
		if (scanf("%d%c", &option, &extra) != 2 && extra != '\n')
	       	{
			printf("\nProgram exited with error code [01]:\n");
			printf("Input was not a single digit integer.\n");      
			return 1;
		}
		else {
			switch(option){
				case 1:
					//peruse_mode(fp);
					break;
				case 2:
					suggest_mode(fp, fp1);
					break;
				case 3:
					//input_mode(fp);
					break;
				case 4:
					printf("\nProgram exited successfully.\n");
					return 0;
				default:
					printf("\nPlease choose a value within 1 to 4\n");
					break;
			}
		} 
	}	
}


//functions to read food_items
food_item* file_reading(FILE *file, int *food_num) 
{
    food_item* temp = (food_item*)malloc(MAX * sizeof(food_item));
    int i = 0;
    while (fscanf(file, "%d %99s %f %f %f", &temp[i].id, temp[i].food_name, &temp[i].price, &temp[i].rating, &temp[i].sulit_value) == 5) {
        i++;
    }
	*food_num = i-1;
    return temp;
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



void suggest_mode(FILE *fp, FILE *fp1){
	int option = 0;
	char extra;
	float budgets, rating, sulit_value;
	int food_num, trash;

	//fp1 is the last 10 transactions
	food_item data[MAX];
	//will just be using pointers and not using structures every time.
	food_item* history_ptr = file_reading(fp1, &trash);
	food_item* data_ptr = file_reading(fp, &food_num);
	printf("\n-----------SUGGEST MODE-----------\n");


	printf("These are your last 10 purchases: \n");

	for (int i = 0; i < 10; i++){
        printf("ID: %d  Food: %s  Rating: %f\n", history_ptr[i].id, history_ptr[i].food_name, history_ptr[i].rating);
    	}
   	
    while (1) {
		option = 0; 
        print_menu2();
        if (scanf("%d%c", &option, &extra) != 2 || extra != '\n') {
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
            printf("%05d  %s\nPHP %.2f\n", item_food[i].id, item_food[i].food_name, item_food[i].price);
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
				printf("%05d  %s\nRating: %.2f\n", item_food[i].id, item_food[i].food_name, item_food[i].rating);
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
            printf("%05d %s\nSulit value: %.2f\n", item_food[i].id, item_food[i].food_name, item_food[i].sulit_value);
        }
    }
	printf("Returning....\n");
	return;
}

