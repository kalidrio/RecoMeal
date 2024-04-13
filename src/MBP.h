typedef struct {
        int ID;
        char name[50];
        float price;
        float rating;
        float sulit_value;
} food_item;

void read_data(FILE *from_catalogue, food_item* catalogue);	

void print_Menu(void);

void peruse_mode(FILE* from_catalogue, food_item* catalogue);

int S_init(void);

