#define MAXLEN 1000

typedef struct usr_node {
    char username[MAXLEN];
    char password[MAXLEN];
    struct usr_node *next;
} User;