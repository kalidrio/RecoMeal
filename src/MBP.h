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

int S_init(char* filename);
/**
 * @brief Initializes the RecoMeal program by reading data from files,
 *        printing recent purchase history, and suggesting meals based on history.
 *
 * This function initializes the RecoMeal program by opening and reading data
 * from the meals.txt and history.txt files. It then populates arrays of meal
 * and purchase structures accordingly. After printing the recent purchase history,
 * it suggests meals to the user based on their budget and past purchase history.
 * @param char filename is used here as a pointer to the name of user
 * @return int Returns 0 on successful initialization, 1 otherwise.
 */

void clear_buffer(void);

void read_data(FILE* from_meals, meal* catalogueArr);
/* inputfile has fixed size of 15, size is therefore unneccessary.
 * count is included as pointer to be used by a later function.
 */

void read_history(FILE* from_history, purchase* historyArr);

void print_purchase(purchase* historyArr, int items);
/**
 * @brief Prints the recent purchase history.
 *
 * This function takes an array of purchase structures representing recent purchases
 * and the number of items in the historyArr array. It prints the recent purchase
 * history in a formatted table.
 *
 * @param historyArr Pointer to the array of purchase structures.
 * @param items Number of items in the historyArr array.
 */

void suggest(meal* catalogueArr, int count, FILE* to_history);	
void budget_it(meal* catalogueArr, int items, float budget, FILE* to_history);
void inputMode(FILE* to_history);
void print_userMenu(void);
