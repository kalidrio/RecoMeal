//headers
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 10000


typedef struct 
{
    int id;
    char food_name[100];
    float price;
    float rating;
    float sulit_value;
}food_item;


void peruse_mode(FILE *fp);
void display_mode(FILE *fp);
void input_mode(FILE *fp);
void exit_program(FILE *fp);
float sulit_calculation(float price, float rating, float sulit_value);

int main (){
    int i, option=0;
    FILE *fp;
	
	fp = fopen("Food_Items.txt",  "r+");


	while (1) {
		printf("What would you like to do? (ENTER THE NUMBER)\n");
		printf("1. Peruse Mode\n2. Display Mode\n3. Input Mode\n4. Exit\n");
		scanf("%d", &option);
		switch(option){
			case 1: peruse_mode(fp);
				continue;
			case 2: display_mode(fp);
				continue;
			case 3: input_mode(fp);
				continue;
			case 4: printf("program end\n");
					exit_program(fp);
					return 0;
			default: printf("Please choose a valid option\n");
				continue;
	} 
	}
	
	return 0;
	//hiiiiiiiiiii
    
}

void peruse_mode (FILE *fp){
	printf("Peruse Mode: \n");
	printf("Here is the List of all the Food Items Available: \n");


}


void display_mode (FILE *fp){
	printf("Display Mode: \n");
	printf("Here are the top most rated food items: \n");
	//create a program that sorts all the foods by ranking. then print the top 5 or 10 food items.


}
void input_mode (FILE *fp){
	printf("Input Mode: \n");
	printf("Please type all the details: \n");

}


void exit_program (FILE *fp){
	//programs to do before closing the program such as updating the rankings.

}

float sulit_calculation(float price, float rating, float sulit_value){
	float sulit_ba = (price*0.4)+(rating*0.4)+(sulit_value*0.2); 
	return sulit_ba;
}


// hi mark
//hello JP

//test pulling
//hello
