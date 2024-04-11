#include<stdio.h>

void print_Menu(void) {
	printf("\nWhat would you like to do? [ENTER THE NUMBER]\n");
	printf("\t1. Peruse Mode\n");	
	printf("\t2. Suggest Mode\n");
	printf("\t3. Input Mode\n");
	printf("\t4. Exit\n");
	return;
}

void peruse_mode(void) {
	printf("peruse\n");
	return;
}

int S_init(void) {
	int option = 0;
	char extra;  // dummy var to catch trailing input
	while (option != 4) {

		print_Menu();

		// extra catches trailing non-numeric characters
		if (scanf("%d%c", &option, &extra) != 2 || extra != '\n')
	       	{
			printf("\nProgram exited with error code [01]:\n");
			printf("Input was not a single digit integer.\n");      
			return 1;
		}
		else {
			switch(option){
				case 1:
					peruse_mode();
					break;
				case 2:
					//display_mode(fp);
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





