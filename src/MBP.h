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
	char name[stdlen];
	float price;
	float sulitness;
} purchase;


int S_init(void);

void clear_buffer(char* filename);

void read_data(FILE* from_meals, meal* catalogueArr);
/* inputfile has fixed size of 15, size is therefore unneccessary.
 * count is included as pointer to be used by a later function.
 */

void read_history(FILE* from_history, purchase* historyArr);

void print_purchase(purchase* historyArr, int items);

void suggest(meal* catalogueArr, int count, FILE* to_history);	
void budget_it(meal* catalogueArr, int items, float budget, FILE* to_history);
void inputMode(FILE* to_history);
