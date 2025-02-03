Persistent Bank Account
Objective:

Create a single-file C++ program (main.cpp) that simulates a bank account, where the balance is persistently stored in a file. The program should handle basic banking operations such as deposits, withdrawals, and balance checks. This program should be robust and update the file immediately after every transaction.



Instructions:



Program Features:

Store the balance in a file named account_balance.txt.
On program startup:
If account_balance.txt does not exist, create it and set the initial balance to $100.00.
If the file exists, read the current balance from the file.
Allow the user to perform the following actions:
Check the balance.
Deposit money (must be a positive amount).
Withdraw money (cannot exceed the current balance or be negative).
Update account_balance.txt immediately after every transaction.


Requirements:

Ensure file operations are handled securely and gracefully. For example:
If the file cannot be opened, display an appropriate error message and exit.
Validate all user inputs:
Deposits must be positive values.
Withdrawals must not exceed the current balance and must be positive values.
The program should be interactive, displaying a menu for the user to choose operations.


Expected Program Behavior:

Example Run 1: No Save File Exists
Welcome to Your Bank Account!
Initializing account with $100.00...
 
Menu:
1. Check Balance
2. Deposit Money
3. Withdraw Money
4. Exit
 
Enter your choice: 1
Your current balance is: $100.00
 
Example Run 2: Existing Save File
Welcome to Your Bank Account!
Your current balance is: $120.50
 
Menu:
1. Check Balance
2. Deposit Money
3. Withdraw Money
4. Exit
 
Enter your choice: 2
Enter deposit amount: 50
Deposit successful. Your new balance is: $170.50


Error Handling:

Attempting to withdraw more than available balance:
Enter withdrawal amount: 200
Error: Insufficient funds. Your balance is $170.50.
Attempting to deposit or withdraw invalid amounts:
Enter deposit amount: -10
Error: Deposit amount must be positive.
Deliverables:

Place the program in your Git repository under the practice/practice02 folder.
The file should be named main.cpp.
Ensure the program compiles and runs correctly.
Hints and Tips:

Use functions to organize your code (e.g., checkBalance, deposit, withdraw, readBalanceFromFile, writeBalanceToFile).
Pay attention to precision when handling money (use std::fixed and std::setprecision from <iomanip> to display balance with two decimal places).
Test your program thoroughly to ensure all edge cases are handled (e.g., invalid inputs, missing file, simultaneous read/write operations).
Submission:

Commit and push the main.cpp file to your repository under the specified folder. Ensure it is properly commented and formatted.