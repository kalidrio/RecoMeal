User* parseDB();

User* mainMenu(User* user_list);

User* loginPage(User* user_list);

void signupPage(User* user_list);

void createAccount(char username[], char password[], User* user_list);

void saveAccountToDB(User account);