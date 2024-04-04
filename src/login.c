#include <stdio.h>
#define MAXLEN 1000

typedef struct usr_node {
    char username[MAXLEN];
    char password[MAXLEN];
} User;

// Parses /DB and creates a linked list of User structs
User* parse_db() {
    User *tmp;
    FILE *ifp;
    int num_of_users;

    ifp = fopen("count.txt", "rt");
    fscanf(ifp, "%d", &num_of_users);
    fclose(ifp);

    for (int i = 1; i <= num_of_users; i++) {
        ifp = fopen(("%d.txt", i), "rt");

        tmp = (User *) malloc(sizeof(User));
        fscanf(ifp, "%s", tmp->username);
        fscanf(ifp, "%s", tmp->password);
    }

    return;
}