
Bank Account System – ATM Simulation
•	Project Description
This is a C++ program that simulates a basic ATM system. It allows a user to manage multiple bank accounts (Savings and Checking) with support for deposits, withdrawals, transaction history, and balance tracking. The program uses object-oriented programming principles such as inheritance, polymorphism, and abstract classes. Each account stores its transaction history dynamically, and the bank stores accounts in a resizable array of pointers.
*Features
✔ Create a Savings or Checking account
✔ Deposit money into an account
✔ Withdraw money from an account
✔ View full transaction history for any account
✔ Dynamically calculates account balance using pointer arithmetic
✔ Remove accounts
✔ List all account balances
✔ Menu-driven interface using cin and cout
•	Technologies Used
•	C++ Programming Language
•	Dev-C++ or any IDE using a standard GCC compiler
•	Standard C++ libraries (iostream, cstring, iomanip, limits) *File Structure
my project folder should contain the following files:
•	Testing the System
I can test different scenarios such as:
•	Depositing into multiple accounts.
•	Trying to withdraw more than allowed (especially for savings).
•	Opening and removing accounts.
•	Viewing histories and balances.
•	Future Improvements (Optional Ideas)
•	Add login authentication (PINs for each account).
•	Save and load account data from files.
•	Apply interest to savings accounts monthly.
•	Add account holder names and details.
•	GUI version using frameworks like Qt or Windows Forms • Abstract Class: Account with pure virtual functions Inheritance: SavingsAccount and CheckingAccount derive from Account •Polymorphism: Method dispatching based on account type • Dynamic Arrays: For storing accounts and transaction history • Pointer Arithmetic: To calculate balances from transaction arrays



