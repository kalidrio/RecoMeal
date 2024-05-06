#include <stdio.h>
#include "MBP.h"
#include "structs.h"
#include "login.h"


int main() {
	User *user_list;
	User *user;

	user_list = parseDB();

	user=mainMenu(user_list);
	
	S_init(user->username);
	return 0;
}
