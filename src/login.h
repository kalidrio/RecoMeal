User* parseDB();

void mainMenu();

User* loginPage();

void signupPage();

void createAccount(char username[MAXLEN], char password[MAXLEN], User* user_list);

void saveAccountToDB(User account);