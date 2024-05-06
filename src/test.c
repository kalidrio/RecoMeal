#include <stdio.h>
#include "structs.h"
#include "login.h"
#include "account_management.h"

int main () {
    User *user_list;
    User *user;

    user_list = parseDB();

    user_list = user_list->next;

    changeUser(user_list);

    printf("%s", user_list->username);

    return 0;
}