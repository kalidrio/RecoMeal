#define stdlen 50

typedef struct { 
	int ID;
	char main_course[stdlen];
	float Mprice;
	char dessert[stdlen];
	float Dprice;
	char beverage[stdlen];
	float Bprice;
	float total_price;
	float sulitness;
} meal; 

typedef struct {
	int ID;
	char name[stdlen];
	float sulitness;
} purchase;


int S_init(void);

void clear_buffer(void);

void read_data(FILE* from_meals, meal* catalogueArr, int* count);
/* inputfile has fixed size of 15, size is therefore unneccessary.
 * count is included as pointer to be used by a later function.
 */

void read_history(FILE* from_history, purchase* historyArr, int items);

void print_purchase(purchase* historyArr, int items);

void suggest(meal* catalogueArr, int count);	

