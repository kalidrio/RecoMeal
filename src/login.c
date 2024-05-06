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

    ifp = fopen("DB/accounts.txt", "rt");

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

void mainMenu() {
    int choice; 

    while(1){
        printf("(1) Log In\n");
        printf("(2) Sign Up\n");
        printf("(3) Exit\n\n");

        printf("Choice: ");

        scanf("%d", &choice);

        switch(choice){
            case 1:
                loginPage();
                continue;
            case 2:
                signupPage();
                continue;
            case 3:
                return;
            default:
                printf("\nInvalid choice. Please choose one of the options above.");
                continue;
        }
    }
}

User* loginPage() {
    char username[MAXLEN];
    char password[MAXLEN];

    printf("Username: ");
    scanf("%s", username);
    printf("Password: ");
    scanf("%s", password);

}

void signupPage() {
    char username[MAXLEN];
    char password[MAXLEN];

    printf("Username: ");
    scanf("%s", username);
    printf("Password: ");
    scanf("%s", password);
}

// Creates User struct and links it to existing user list
void createAccount(char username[], char password[], User* user_list) {
    User *account;
    account = (User *) malloc(sizeof(User));

    strcpy(account->username, username);
    strcpy(account->password, password);
    account->next = NULL;

    saveAccountToDB(*account);

    while (user_list->next != NULL) {
        user_list = user_list->next;
    }

    user_list->next = account;
}

// Saves new user accounts to the DB
// DO NOT CALL THIS FUNCTION, call createAccount instead
void saveAccountToDB(User account) {
    FILE *accounts_file;

    accounts_file = fopen("DB/accounts.txt", "at");
    fprintf(accounts_file, "%s\n", account.username);
    fprintf(accounts_file, "%s\n", account.password);

    fclose(accounts_file);
}