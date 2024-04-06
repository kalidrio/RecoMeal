#include <stdio.h>
#include <stdlib.h>
#include "structs.h"
#define MAXLEN 1000

// Parses /DB and creates a linked list of User structs
// NOTE: The head of the struct does not represent a user and should be skipped when looping through the list
User* parseDB() {
    User *head;
    // head does not represent a user. in the case where the system starts with 0 users,
    // this function will still return a user pointer, so that users created later can still be attached to it.

    User *tmp;
    FILE *ifp;
    char curr_filename[MAXLEN];
    int num_of_users;

    ifp = fopen("DB/count.txt", "rt");
    fscanf(ifp, "%d", &num_of_users);
    fclose(ifp);

    head = (User *) malloc(sizeof(User));

    for (int i = 1; i <= num_of_users; i++) {
        sprintf(curr_filename, "DB/%d.txt", i);
        ifp = fopen(curr_filename, "rt");

        // Create User struct for current user
        tmp = (User *) malloc(sizeof(User));
        fscanf(ifp, "%s", tmp->username);
        fscanf(ifp, "%s", tmp->password);

        // Link to head if first user
        if (i == 1) {
            head->next = tmp;
        }

        // Allocate memory for next user and set tmp to next user
        tmp->next = (User *) malloc(sizeof(User));
        tmp = tmp->next;
    }

    // Set last user's next pointer to NULL
    tmp->next = NULL;
    return head;
}

void mainMenu() {

}

User* loginPage() {

}

void signupPage() {

}

void createAccount(User* user_list) {

}

void saveAccountToDB(User account) {
    
}