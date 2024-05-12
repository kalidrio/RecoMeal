User Manual:

Getting Started

  Github repo: https://github.com/kalidrio/RecoMeal 
  Open a terminal and navigate to the src directory.
  To build the program, please use: 
**"gcc -o recomeal main.c login.c MBP.c account_management.c"**
  Type “./recomeal” in the terminal to call the program, no additional arguments are needed.
  The program may terminate anytime by pressing Ctrl-D/Ctrl-Z(EOF)

Multi-user Support(MUS)

1. Upon opening the program, users are greeted with a main menu prompting them to either sign in, log in, or exit. New users should start by creating an account. 
    a. Sign In: new users are prompted to choose a username and enter a password. 
        Usernames are case sensitive.
        In the occurrence that a user chooses an existing username, an error message will appear. 
    b. Log In: existing users are prompted to enter their username and password. 
        Appropriate error messages will be displayed in the occurrence of an error such as a wrong password or a nonexistent username. 
    c. Exit: this closes the program. 

Once the user has successfully created an account, the program will now execute the Meal Budget Portion(MBP) feature of the program.


Meal Budget Portion(MBP)

1. The MBP feature begins with checking a user’s purchase history. If it exists, the program prints out the user’s recent purchases before
   continuing; if not, the program prints “No recent purchases…” to the screen and continues.

2. The program promptly asks the user to input their budget(in pesos). There are three possible scenarios:
      a. Invalid: Non-numeric input causes the program to display an error message, clear the buffer, and ask for input again.
      b. EOF: Ctrl-D/Ctrl-Z causes the program to promptly end and display an exit message associated with termination by EOF.
      c. Valid: Only numeric input allows the program to proceed to the next step as normal.

3. The program then prints all meals that are within the budget specified by the user, ranked by “sulitness”.

4. The program then displays a submenu for further options.
    a. Record a recent purchase: the program asks for the following data:
        i.  Dish name
       ii.  Dish price
      iii.  Sulitness
   The data is stored in a history file associated with the user’s account.

    b. Update User info: this opens up another submenu with the following options:
        i.  Change username
       ii.  Change password
      iii.  Delete Account

    c. Exit: this closes the program.
   
The program ends and displays the exit message associated with a successful run.





