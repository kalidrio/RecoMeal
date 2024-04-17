#include <stdio.h>
#include "structs.h"
#include "login.h"

int main() {
    User *user_list;
    User *curr_user;

    user_list = parseDB();
    curr_user = user_list->next; // skip head

    printf("%s\n", curr_user->username);
    printf("%s\n", curr_user->password);

    createAccount("JP", "1234", user_list);

    curr_user = curr_user->next; // next user

    printf("%s\n", curr_user->username);
    printf("%s\n", curr_user->password);

    curr_user = curr_user->next; // next user

    printf("%s\n", curr_user->username);
    printf("%s", curr_user->password);

    return 0;
}