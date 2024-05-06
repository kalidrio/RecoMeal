#include <stdio.h>
#include "structs.h"
#include "login.h"
#include "account_management.h"

int main () {
    User *user_list;
    User *user;

    user_list = parseDB();

    user = mainMenu(user_list);

    return 0;
}