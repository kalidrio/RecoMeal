#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"
#include "login.h"

// Parses /DB and creates a linked list of User structs
// NOTE: The head of the struct does not represent a user and should be skipped when looping through the list
User* parseDB() {
    User *head;
    // head does not represent a user. in the case where the system starts with 0 users,
    // this function will still return a user pointer, so that users created later can still be attached to it.

    User *tmp;
    FILE *ifp;
    char username[MAXLEN];
    char password[MAXLEN];
    int counter = 1;

    ifp = fopen("../DB/accounts.txt", "rt");

    head = (User *) malloc(sizeof(User));

    while (1) {
        // Get username and password
        if (fscanf(ifp, "%s", username) != EOF) {
            fscanf(ifp, "%s", password);
        }
        else {
            break; // Exit on EOF
        }

        // Link to head if first user
        if (counter == 1) {
            head->next = (User *) malloc(sizeof(User));
            tmp = head->next;
        }
        // Link to last user if not
        else {
            tmp->next = (User *) malloc(sizeof(User));
            tmp = tmp->next;
        }

        // Create User struct for current user
        strcpy(tmp->username, username);
        strcpy(tmp->password, password);

        counter++;
    }

    // Set last user's next pointer to NULL
    tmp->next = NULL;
    return head;
}

User* mainMenu(User* user_list) {
    User* user = NULL;
    int choice; 

    while(1){
        printf("(1) Log In\n");
        printf("(2) Sign Up\n");
        printf("(3) Exit\n\n");

        printf("Please input the number of your choice: ");

        scanf("%d", &choice);

        switch(choice){
            case 1:
                while (user == NULL) {
                    user = loginPage(user_list);
                }
                return user;
            case 2:
                signupPage(user_list);
                continue;
            case 3:
                return NULL;
            default:
                printf("\nInvalid choice. Please choose one of the options above\n\n.");
                continue;
        }
    }
}

User* loginPage(User* user_list) {
    char username[MAXLEN];
    char password[MAXLEN];
    User* curr_user = user_list;

    printf("Username: ");
    scanf("%s", username);
    printf("\nPassword: ");
    scanf("%s", password);

    while(1){
        if (curr_user == NULL){
            printf("\nAccount does not exist\n\n.");
            break;
        }

        if(strcmp(username, curr_user->username) == 0){
            if(strcmp(password, curr_user->password) == 0){
                return curr_user;
            }
            else{
                printf("\nWrong password\n\n.");
                break;
            }
        }
        curr_user = curr_user->next;
    }

    return NULL;
}

void signupPage(User* user_list) {
    char username[MAXLEN];
    char password[MAXLEN];

    while (1) {
        printf("Enter a username: ");
        scanf("%s", username);
        printf("\nEnter a password: ");
        scanf("%s", password);

        while (user_list->next != NULL && user_list->username != username) {
            user_list = user_list->next;
        }
        
        if (user_list->next != NULL) {
            createAccount(username, password, user_list);
            printf("\n\n");
            break;
        }
        else {
            printf("\n\nUsername already exists.");
        }
    }
}

// Creates User struct and links it to existing user list
// Also creates a text file for storing purchase history in the format of (username)_history.txt
void createAccount(char username[], char password[], User* user_list) {
    User *account;
    char filename[MAXLEN];
    FILE *purchase_history;
    account = (User *) malloc(sizeof(User));

    // Create account
    strcpy(account->username, username);
    strcpy(account->password, password);
    account->next = NULL;

    saveAccountToDB(*account);

    while (user_list->next != NULL) {
        user_list = user_list->next;
    }

    user_list->next = account;

    // Create txt file
    strcpy(filename, account->username);
    strcat(filename, "_history.txt");
    purchase_history = fopen(filename, "wt");
}

// Saves new user accounts to the DB
// DO NOT CALL THIS FUNCTION, call createAccount instead
void saveAccountToDB(User account) {
    FILE *accounts_file;

    accounts_file = fopen("../DB/accounts.txt", "at");
    fprintf(accounts_file, "%s\n", account.username);
    fprintf(accounts_file, "%s\n", account.password);

    fclose(accounts_file);
}