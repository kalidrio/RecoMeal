#include<stdio.h>
#include<stdlib.h>

typedef struct {
        int ID;
        char name[50];
        float price;
        float rating;
        float sulit_value;
} food_item;

void read_data(FILE* from_catalogue, food_item* catalogue) {

	for (int i = 0; i < 13; i++) {
		if (fscanf(from_catalogue,
					"%d %s %f %f %f",
					&catalogue[i].ID,
					catalogue[i].name,
					&catalogue[i].price,
					&catalogue[i].rating,
					&catalogue[i].sulit_value) != 5) 
		{
			printf("Error reading data.\n");
			break;
		}
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

void peruse(FILE* from_catalogue, food_item* catalogue) { // file pointer and dynamic allocated array for catalogue

	for (int i = 0; i < 13; i++) {
	printf("\t%03d   %s\n", catalogue[i].ID, catalogue[i].name);
	}

	int option;
	while (1) {
		printf("\nInput ID# of Item for more details or 0 to exit: ");
		if (scanf("%d", &option) != 1 || (option > 13 || option < 0)) {
			printf("Please enter a valid number.\n");
			while (getchar() != '\n'); // clears input buffer
		} else if (option == 0) break;
			else { 
				printf("\n Dish Name: %s\n", catalogue[option-1].name);
				printf("     Price: Php %.2f\n", catalogue[option-1].price);
				printf("    Rating: %.2f/10\n", catalogue[option-1].rating);
				printf("Sulit-ness: %.2f\n", catalogue[option-1].sulit_value);
			}
	}
}

int S_init(void) {
        int option = 0;
        char extra;  // dummy var to catch trailing input

        FILE* from_catalogue = fopen("../DB/catalogue.txt", "r"); // catalogue.txt contains all information
								  // about food item
        if (!from_catalogue) {
                printf("Error opening catalogue.\n");
                return 1;
        }

        food_item* catalogue = malloc(sizeof(food_item) * 13); // catalogue begins with 13 items

        if (!catalogue) {
                printf("Memory allocation failed.\n");
                return 1;
        }

        for (int i = 0; i < 13; i++) { // read data into struct array via Sptr catalogue
		read_data(from_catalogue, catalogue);
	}

        while (option != 4) {

                print_Menu();

                // extra catches trailing non-numeric characters
                if (scanf("%d%c", &option, &extra) != 2 || extra != '\n')
                {
                        printf("\nProgram exited with error: Input was not a single digit integer.\n");
                        fclose(from_catalogue);
                        free(catalogue);
			catalogue == NULL;
                        return 1;
                }
                else {
			printf("\n");
                        switch(option){
                                case 1:
					peruse(from_catalogue, catalogue);
                                        break;
                                case 2:
                                        //display_mode(fp);
                                        break;
                                case 3:
                                        //input_mode(fp);
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
	catalogue = NULL;
}



























































