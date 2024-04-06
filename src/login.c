#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"
#include "login.h"
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

// Creates User struct and links it to existing user list
void createAccount(char username[MAXLEN], char password[MAXLEN], User* user_list) {
    User* account;
    account = (User *) malloc(sizeof(User));

    strcpy(account->username, username);
    strcpy(account->password, password);

    saveAccountToDB(*account);

    user_list->next = account;
    account->next = NULL;
}

// Saves new user accounts to the DB
// DO NOT CALL THIS FUNCTION, call createAccount instead
void saveAccountToDB(User account) {
    FILE *count_file;
    FILE *new_user_file;
    int num_of_users;
    char filename[MAXLEN];

    count_file = fopen("DB/count.txt", "rt+"); // read and write mode
    new_user_file = fopen(filename, "wt");

    fscanf(count_file, "%d", num_of_users);
    fprintf(count_file, "%d", num_of_users++);

    sprintf(filename, "DB/%d.txt", num_of_users);

    fprintf(new_user_file, "%s\n%s", account.username, account.password);

    fclose(count_file);
    fclose(new_user_file);
}