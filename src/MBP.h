#define stdlen 50

typedef struct { 
	int ID;
	char main_course[stdlen];
	float Mprice;
	char side[stdlen];
	float Sprice;
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

void clear_buffer(void);
/**
 * @brief Repeatedly calls getchar() to read and discard characters in the input buffer
 * 	  until a '\n' is encountered, effectively clearing the input buffer.
 */

int S_init(User* user, User* head);
/**
 * @brief Initializes the RecoMeal program by reading data from files,
 *        printing recent purchase history, and suggesting meals based on history.
 *
 * This function initializes the RecoMeal program by opening and reading data
 * from the meals.txt and history.txt files. It then populates arrays of meal
 * and purchase structures accordingly. After printing the recent purchase history,
 * it suggests meals to the user based on their budget and past purchase history.
 * @return int Returns 0 on successful initialization, 1 otherwise.
 * @param account is used to access the username of the user to open his history file.
 * @param head is passed on to the function, this is the head pointer of the linked lists of accounts.
 */

void read_data(FILE* from_meals, meal* catalogueArr);
/**
 * @brief Reads meal data from a file into an array.
 *
 * This function reads meal data from the provided file pointer
 * and stores it in the array of meal structures.
 *
 * @param from_meals File pointer to the meals file.
 * @param catalogueArr Pointer to the array of meal structures.
 *
 * @note input file "meals.txt" has a fixed size of 15.
 * 	 size if therefore unneccessary.
 * @note count(included as Ptr) will be used by a later function.
 */

void read_history(FILE* from_history, purchase* historyArr);
/**
 * @brief Reads purchase history from a file into an array.
 *
 * This function reads purchase history data from the provided file pointer
 * and stores it in the array of purchase structures.
 *
 * @param from_history File pointer to the purchase history file.
 * @param historyArr Pointer to the array of purchase structures.
 */

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

void suggest(meal* catalogueArr, int count, FILE* to_history, User* user, User* head);	
/**
 * @brief Prompts the user for their budget and suggests meals accordingly.
 *
 * This function prompts the user to enter their budget for today's meal.
 * It then suggests meals based on the provided budget and past purchase history.
 *
 * @param catalogueArr Pointer to the array of meal structures representing available food items.
 * @param items Number of items in the catalogueArr array.
 * @param to_history File pointer to the purchase history file for recording new purchases.
 * @param user will be passed on other functions
 * @param head will be passed on other functions
 */

void budget_it(meal* catalogueArr, int items, float budget, FILE* to_history, User* user, User* head);
/**
 * @brief Filters and prints food items within the specified budget, sorted by sulitness.
 *
 * This function takes an array of meal structures, the number of items in the array,
 * and a budget as parameters. It filters the meal items based on the total price
 * within the specified budget, sorts them by sulitness in descending order, and prints
 * the filtered items in a table format.
 *
 * @param catalogueArr Pointer to the array of meal structures.
 * @param items Number of items in the catalogueArr array.
 * @param budget The budget for filtering food items.
 * @param to_history File pointer to the purchase history file.
 * @param account is passed on to the function, this is the structure of the current account.
 * @param head is passed on to the function, this is the head pointer of the linked lists of accounts.
 */

void inputMode(FILE* to_history);

/**
 * @brief Handles the input mode where the user can record a new purchase.
 *
 * This function allows the user to input details of a new purchase,
 * such as the name, price, and sulitness of the meal. It then records
 * the purchase in the purchase history file provided.
 *
 * @param to_history File pointer to the purchase history file for recording new purchases.
 */


void print_userMenu(void);

/**
*brief Handles the user account settings printing

**/

void userSettings(User* account, User* head);

/**
* @brief Handles the user account settings printing
* Takes a user input (1-3). This function executes 3 options based on the user input. 
* 1. Change user - opens the changeUser() function
* 2. Change password - opens the changePass() function
* 3. Delete account - executes the deleteAccount() and deleteAccountFromDB() functions.
* @param account is passed on to the function, this is the structure of the current account.
* @param head is passed on to the function, this is the head pointer of the linked lists of accounts.
**/



void delay(int seconds);
/**
* @brief delays the execution of the next lines.
* @param seconds the number of seconds you want to delay the program
**/


void delay_period(int seconds);
/**
* @brief delays the execution of a program for loading and prints "." to show loading.
* @param seconds the number of seconds you want to delay the program
**/