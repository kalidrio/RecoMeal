typedef struct {
    int ID;
    char name[50];
    float price;
    float rating;
    float sulit_value;
} food_item;

// User defined functions
void read_data(FILE *from_catalogue, food_item* catalogue);
void print_Menu(void);
void peruse(FILE* from_catalogue, food_item* catalogue, int* errPtr);

// Initialization functions
int S_init(void);
