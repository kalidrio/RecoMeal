#include <stdio.h>
#include "structs.h"
#include "login.h"

int main () {
    User *user_list;
    User *user;

    user_list = parseDB();
    user_list = user_list->next;

    user = mainMenu(user_list);

    return 0;
}