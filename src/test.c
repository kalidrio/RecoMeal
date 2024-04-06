#include <stdio.h>
#include "structs.h"
#include "login.h"

int main() {
    User *user_list;
    User *curr_user;

    user_list = parse_db();
    curr_user = user_list->next; // skip head

    printf("%s\n", curr_user->username);
    printf("%s", curr_user->password);

    createAccount("Jelyn", "1234", user_list);

    return 0;
}