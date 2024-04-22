typedef struct { 
	int ID;
	char main_course[50];
	float Mprice;
	char dessert[50];
	float Dprice;
	char beverage[50];
	float Bprice;
	float total_price;
	float sulitness;
} meal; 

void read_data(FILE* from_meals, meal* catalogueArr, int* count);
void clear_buffer(void);
void inquire(void);

int S_init(void);

void suggest(meal* catalogueArr, int count, int* errPtr);	//case 1

void print_recent;						//case 2

void record; 							//case 3

