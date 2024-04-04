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
    float ratio;
}food_item;


int main (){
    int i, option=0;
    FILE *ifp, *ofp;

	while (1) {
		printf("What would you like to do? (ENTER THE NUMBER)\n");
		printf("1. Peruse Mode\n2. Display Mode\n3. Input Mode\n4. Exit\n");
		scanf("%d", &option);
		switch(option){
			case 1: peruse_mode();
				continue;
			case 2: display_mode();
				continue;
			case 3: input_mode();
				continue;
			case 4: printf("program end\n");
					exit();
					return 0;
			default: printf("Please choose a valid option\n");
				continue;

	} 
	

	}
	



	return 0;
	//hiiiiiiiiiii
    
}


// hi mark
//hello JP

//test pulling
//hello
