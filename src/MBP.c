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

food_item* file_reading(FILE *file) 
{
    food_item* temp = (food_item*)malloc(MAX * sizeof(food_item));
    int i = 0;
    while (fscanf(file, "%d %99s %f %f %f", &temp[i].id, temp[i].food_name, &temp[i].price, &temp[i].rating, &temp[i].sulit_value) == 5) {
        i++;
    }
    return temp;
}



void suggest_mode(FILE *fp, FILE *fp1){
	//fp1 is the last 10 transactions
	food_item data[MAX];
	//will just be using pointers and not using structures every time.
	food_item* history_ptr = file_reading(fp1);
	food_item* data_ptr = file_reading(fp);
	printf("These are your last 10 purchases: \n");
    
	for (int i = 0; i < 10; i++){
        printf("ID: %d  Food: %s  Rating: %f\n", history_ptr[i].id, history_ptr[i].food_name, history_ptr[i].rating);
    	}
   	
    while (1) {
        print_menu2();
        if (scanf("%d%c", &option, &extra) != 2 || extra != '\n') {
            printf("\nProgram exited with error code [01]:\n");
            printf("Input was not a single digit integer.\n");      
            return 1;
        } else {
            switch(option) {
                case 1:
                    printf("try");	//budget mode			
                    break;
                case 2:
                    printf("try again"); //rating mode
                    break;
                case 3:
                    printf("try until you succeed"); //sulit mode
                    break;
                case 4:
                    printf("Returning to Home...\n"); //exit
					free(history_ptr); //freeing the memory allocated by file_reading
                    return;
                default:
                    printf("Invalid option. Please choose again.\n");
            }
        }
    }
}
}

