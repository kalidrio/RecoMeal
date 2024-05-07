#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"
#include "account_management.h"


void changeUser(User* account) {
    char new_username[MAXLEN];
    char buffer[MAXLEN];
    char old_filename[MAXLEN] = "../DB/";
    char new_filename[MAXLEN] = "../DB/";
    int fscanf_retvalue;
    FILE *accounts_file;
    FILE *new_file;

    printf("Input new username: ");
    scanf("%s", new_username);

    // Rename history.txt file
    strcat(old_filename, account->username);
    strcat(old_filename, "_history.txt");
    strcat(new_filename, new_username);
    strcat(new_filename, "_history.txt");

    rename(old_filename, new_filename);

    accounts_file = fopen("../DB/accounts.txt", "rt");
    new_file = fopen("../DB/new_accounts.txt", "wt");

    while (1) {
        fscanf_retvalue = fscanf(accounts_file, "%s", buffer);

        // Write new username on past username match
        if (strcmp(buffer, account->username) == 0) {
            fprintf(new_file, "%s\n", new_username);
            continue;
        }
        if (fscanf_retvalue == EOF) {
            break;
        }

        fprintf(new_file, "%s\n", buffer);
    }

    strcpy(account->username, new_username);

    fclose(accounts_file);
    fclose(new_file);

    remove("../DB/accounts.txt");
    rename("../DB/new_accounts.txt", "../DB/accounts.txt");

    printf("Username changed successfully");
}

void changePass(User* account) {
    char new_password[MAXLEN];
    char buffer[MAXLEN];
    int fscanf_retvalue;
    FILE *accounts_file;
    FILE *new_file;

    printf("Input new password: ");
    scanf("%s", new_password);

    strcpy(account->password, new_password);

    accounts_file = fopen("../DB/accounts.txt", "rt");
    new_file = fopen("../DB/new_accounts.txt", "wt");

    while (1) {
        fscanf_retvalue = fscanf(accounts_file, "%s", buffer);

        // Write new password on username match
        if (strcmp(buffer, account->username) == 0) {
            fprintf(new_file, "%s\n", buffer);
            fscanf(accounts_file, "%s", buffer);
            fprintf(new_file, "%s\n", new_password);
            continue;
        }
        if (fscanf_retvalue == EOF) {
            break;
        }

        fprintf(new_file, "%s\n", buffer);
    }

    fclose(accounts_file);
    fclose(new_file);

    remove("../DB/accounts.txt");
    rename("../DB/new_accounts.txt", "../DB/accounts.txt");

    printf("Password changed successfully");
}

// No need to pass **head, as head will never be deleted
void deleteAccount(User* account, User* head) {
    User* prev_node = head;

    // Find node previous to account node
    while (1) {
        if (prev_node->next != account){
            prev_node = prev_node->next;
            continue;
        }
        break;
    }

    prev_node->next = account->next;
    free(account);

    deleteAccountFromDB(account, head);
}

void deleteAccountFromDB(User* account, User* head) {
    char buffer[MAXLEN];
    int fscanf_retvalue;
    FILE *accounts_file;
    FILE *new_file;

    accounts_file = fopen("../DB/accounts.txt", "rt");
    new_file = fopen("../DB/new_accounts.txt", "wt");

    while (1) {
        fscanf_retvalue = fscanf(accounts_file, "%s", buffer);

        // Skip writing username and password on username match
        if (strcmp(buffer, account->username) == 0) {
            fscanf(accounts_file, "%s", buffer);
            continue;
        }
        if (fscanf_retvalue == EOF) {
            break;
        }

        fprintf(new_file, "%s\n", buffer);
    }

    fclose(accounts_file);
    fclose(new_file);

    remove("../DB/accounts.txt");
    rename("../DB/new_accounts.txt", "../DB/accounts.txt");
}