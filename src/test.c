#include <stdio.h>
#include "structs.h"
#include "login.h"

int main() {
    User *user;

    user = parse_db();
    user = user->next;

    printf("%s\n", user->username);
    printf("%s", user->password);

    return 0;
}