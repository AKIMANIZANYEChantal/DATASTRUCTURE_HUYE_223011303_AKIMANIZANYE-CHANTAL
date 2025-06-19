#include <iostream>
#include <iomanip>
#include <cstring>
#include <limits>

using namespace std;

struct Transaction {
    char date[11];
    float amount;
};

class Account {
protected:
    int id;
    Transaction* history;
    int count;
    int capacity;

    void resizeHistory(int newCap) {
        Transaction* temp = new Transaction[newCap];
        for (int i = 0; i < count; i++) {
            temp[i] = history[i];
        }
        delete[] history;
        history = temp;
        capacity = newCap;
    }

    void addTransaction(float amt) {
        if (count == capacity) {
            resizeHistory(capacity * 2);
        }

        char d[11];
        cout << "Enter date (YYYY-MM-DD): ";
        cin >> setw(11) >> d;
        strncpy(history[count].date, d, 10);
        history[count].date[10] = '\0';
        history[count].amount = amt;
        count++;
    }

public:
    Account(int acc_id) {
        id = acc_id;
        count = 0;
        capacity = 4;
        history = new Transaction[capacity];
    }

    virtual ~Account() {
        delete[] history;
    }

    int getId() const {
        return id;
    }

    float getBalance() const {
        float total = 0;
        Transaction* p = history;
        for (int i = 0; i < count; i++) {
            total += (p + i)->amount;
        }
        return total;
    }

    virtual void deposit(float amt) = 0;
    virtual void withdraw(float amt) = 0;

    void printHistory() const {
        cout << "\nTransaction history for account #" << id << ":\n";
        for (int i = 0; i < count; i++) {
            cout << left << setw(12) << history[i].date
                 << right << setw(10) << history[i].amount << endl;
        }
        cout << "Current Balance: " << getBalance() << "\n";
    }
};

class SavingsAccount : public Account {
public:
    SavingsAccount(int acc_id) : Account(acc_id) {}

    void deposit(float amt) {
        addTransaction(amt);
    }

    void withdraw(float amt) {
        if (getBalance() - amt < 0) {
            cout << "Insufficient funds in savings account.\n";
        } else {
            addTransaction(-amt);
        }
    }
};

class CheckingAccount : public Account {
public:
    CheckingAccount(int acc_id) : Account(acc_id) {}

    void deposit(float amt) {
        addTransaction(amt);
    }

    void withdraw(float amt) {
        if (getBalance() - amt < -500) {
            cout << "Overdraft limit exceeded (-500).\n";
        } else {
            addTransaction(-amt);
        }
    }
};

class Bank {
    Account** accounts;
    int count;
    int capacity;

    void resizeAccounts(int newCap) {
        Account** temp = new Account*[newCap];
        for (int i = 0; i < count; i++) {
            temp[i] = accounts[i];
        }
        delete[] accounts;
        accounts = temp;
        capacity = newCap;
    }

public:
    Bank() {
        count = 0;
        capacity = 4;
        accounts = new Account*[capacity];
    }

    ~Bank() {
        for (int i = 0; i < count; i++) {
            delete accounts[i];
        }
        delete[] accounts;
    }

    void addAccount(Account* acc) {
        if (count == capacity) {
            resizeAccounts(capacity * 2);
        }
        accounts[count++] = acc;
        cout << "Account #" << acc->getId() << " added.\n";
    }

    void removeAccount(int id) {
        for (int i = 0; i < count; i++) {
            if (accounts[i]->getId() == id) {
                delete accounts[i];
                for (int j = i; j < count - 1; j++) {
                    accounts[j] = accounts[j + 1];
                }
                count--;
                if (count < capacity / 4 && capacity > 4) {
                    resizeAccounts(capacity / 2);
                }
                cout << "Account #" << id << " removed.\n";
                return;
            }
        }
        cout << "Account not found.\n";
    }

    Account* find(int id) {
        for (int i = 0; i < count; i++) {
            if (accounts[i]->getId() == id) {
                return accounts[i];
            }
        }
        return NULL;
    }

    void listBalances() {
        cout << "\nAll account balances:\n";
        for (int i = 0; i < count; i++) {
            cout << "Account #" << accounts[i]->getId()
                 << " Balance: " << accounts[i]->getBalance() << endl;
        }
    }
};

void clearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int main() {
    Bank bank;
    int nextId = 1;

    while (true) {
        cout << "\n--- ATM MENU ---\n";
        cout << "1. Open Savings Account\n";
        cout << "2. Open Checking Account\n";
        cout << "3. Deposit\n";
        cout << "4. Withdraw\n";
        cout << "5. View Transaction History\n";
        cout << "6. Remove Account\n";
        cout << "7. List All Balances\n";
        cout << "0. Exit\n";
        cout << "Choose an option: ";

        int choice;
        if (!(cin >> choice)) {
            clearInput();
            continue;
        }

        int id;
        float amount;
        Account* acc = NULL;

        switch (choice) {
            case 1:
                bank.addAccount(new SavingsAccount(nextId++));
                break;
            case 2:
                bank.addAccount(new CheckingAccount(nextId++));
                break;
            case 3:
                cout << "Enter account ID: ";
                cin >> id;
                cout << "Enter amount to deposit: ";
                cin >> amount;
                acc = bank.find(id);
                if (acc != NULL) acc->deposit(amount);
                else cout << "Account not found.\n";
                break;
            case 4:
                cout << "Enter account ID: ";
                cin >> id;
                cout << "Enter amount to withdraw: ";
                cin >> amount;
                acc = bank.find(id);
                if (acc != NULL) acc->withdraw(amount);
                else cout << "Account not found.\n";
                break;
            case 5:
                cout << "Enter account ID: ";
                cin >> id;
                acc = bank.find(id);
                if (acc != NULL) acc->printHistory();
                else cout << "Account not found.\n";
                break;
            case 6:
                cout << "Enter account ID to remove: ";
                cin >> id;
                bank.removeAccount(id);
                break;
            case 7:
                bank.listBalances();
                break;
            case 0:
                cout << "Exiting program.\n";
                return 0;
            default:
                cout << "Invalid option.\n";
                break;
        }
    }
}

