#include <stdio.h>
#include "structs.h"
#include "MBP.h"
#include "login.h"


int main() {
	User *user_list;
	User *user;

	user_list = parseDB();

	user=mainMenu(user_list);
	
    if (user == NULL) {
        return 0;
    }

	S_init(user, user_list);
	return 0;
}
