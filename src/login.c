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

        // Link to head if first user
        if (i == 1) {
            head->next = (User *) malloc(sizeof(User));
            tmp = head->next;
        }
        // Link to last user if not
        else {
            tmp->next = (User *) malloc(sizeof(User));
            tmp = tmp->next;
        }

        // Create User struct for current user
        fscanf(ifp, "%s", tmp->username);
        fscanf(ifp, "%s", tmp->password);
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
    FILE *count_file;
    FILE *new_user_file;
    int num_of_users;
    char filename[MAXLEN];

    count_file = fopen("DB/count.txt", "rt");
    fscanf(count_file, "%d", &num_of_users);
    fclose(count_file);

    count_file = fopen("DB/count.txt", "wt");
    fprintf(count_file, "%d", num_of_users + 1);

    sprintf(filename, "DB/%d.txt", num_of_users + 1);
    
    new_user_file = fopen(filename, "wt");

    fprintf(new_user_file, "%s\n%s", account.username, account.password);

    fclose(count_file);
    fclose(new_user_file);
}