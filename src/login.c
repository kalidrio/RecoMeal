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

    fclose(ifp);

    // Set last user's next pointer to NULL
    if (tmp != NULL) {
        tmp->next = NULL;
    }
    else {
        head->next = NULL;
    }
    return head;
}

// Expected to return a user struct
// Returns NULL when input corresponds to exit program
User* mainMenu(User* user_list) {
    User* user = NULL;
    char trail;
    int choice; 
    int scanf_retvalue;

    while(1){
        printf("Welcome to RecoMeal!\n");
        printf("Ctrl+D anytime to exit.\n\n");
        printf("(1) Log In\n");
        printf("(2) Sign Up\n");
        printf("(3) Exit\n\n");

        printf("Please input the number of your choice: ");

        scanf_retvalue = scanf("%d%c", &choice, &trail);

        switch(scanf_retvalue) {
            case EOF:
                printf("\nEnd of file.\nThanks for using RecoMeal!");
                return NULL;
            case 2:
                if (trail != '\n') {
                    printf("\nInvalid input.\n\n");
                    while ((getchar()) != '\n'); // avoid inf loops
                    continue;
                }

                switch(choice) {
                    case 1:
                        user = loginPage(user_list);
                        if (user == NULL) {
                            continue;
                        }
                        return user;
                    case 2:
                        signupPage(user_list);
                        continue;
                    case 3:
                        printf("\nThanks for using RecoMeal!");
                        while ((getchar()) != '\n'); // avoid inf loops
                        return NULL;
                    default:
                        printf("\nInvalid choice. Please choose one of the options above.\n\n");
                        continue;
                }
                break;
            default:
                printf("\nExpected input is a single digit int.\n");
        }
    }
}

User* loginPage(User* user_list) {
    char username[MAXLEN];
    char password[MAXLEN];
    int scanf_retvalue;
    User* curr_user = user_list;

    printf("Username: ");
    scanf_retvalue = scanf("%s", username);

    if (scanf_retvalue == EOF) {
        printf("\nEnd of file.\nThanks for using RecoMeal!");
        exit(EXIT_SUCCESS);
    }

    printf("Password: ");
    scanf_retvalue = scanf("%s", password);

    if (scanf_retvalue == EOF) {
        printf("\nEnd of file.\nThanks for using RecoMeal!");
        exit(EXIT_SUCCESS);
    }

    while(1){
        if (curr_user == NULL){
            printf("\nAccount does not exist.\n\n");
            break;
        }

        if(strcmp(username, curr_user->username) == 0){
            if(strcmp(password, curr_user->password) == 0){
                return curr_user;
            }
            else{
                printf("\nWrong password.\n\n");
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
    int scanf_retvalue;
    User* curr_user = user_list;
    int flag = 1; // flag for creating account
    
    printf("\nEnter a username: ");
    scanf("%s", username);

    if (scanf_retvalue = EOF) {
        printf("\nEnd of file.\nThanks for using RecoMeal!");
        exit(EXIT_SUCCESS);
    }

    printf("Enter a password: ");
    scanf("%s", password);

    if (scanf_retvalue = EOF) {
        printf("\nEnd of file.\nThanks for using RecoMeal!");
        exit(EXIT_SUCCESS);
    }

    while (curr_user != NULL) {
        if (strcmp(curr_user->username, username) == 0) {
            flag = 0;
        }
        curr_user = curr_user->next;
    }
    
    if (flag == 1) {
        createAccount(username, password, user_list);
        printf("\n\n");
    }
    else {
        printf("\nUsername already exists.\n");
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
    strcpy(filename, "../DB/");
    strcat(filename, account->username);
    strcat(filename, "_history.txt");
    purchase_history = fopen(filename, "wt");
}

// Saves new user accounts to the DB
// DO NOT CALL THIS FUNCTION, call createAccount instead
void saveAccountToDB(User account) {
    FILE *accounts_file;

    accounts_file = fopen("../DB/accounts.txt", "at");
    fprintf(accounts_file, "\n%s", account.username);
    fprintf(accounts_file, "\n%s", account.password);

    fclose(accounts_file);
}