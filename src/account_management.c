#include <string.h>
#include "account_management.h"
#include "structs.h"

void changeUser(User* account) {
    char new_username[MAXLEN];

    printf("Input new username: ");
    scanf("%s", new_username);

    strcpy(account->username, new_username);
    printf("Username changed successfully");
}

void changePass(User* account) {
    char new_password[MAXLEN];

    printf("Input new password: ");
    scanf("%s", new_password);

    strcpy(account->username, new_password);
    printf("Password changed successfully");
}

// No need to pass *head, as head will never be deleted
void deleteAccount(User* account, User* head) {
    User* prev_node;

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
}