#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <cstdio>

using namespace std;

class BankAccount {
private:
    int accountNumber;
    string name;
    double balance;

public:

    // Constructor
    BankAccount() {
        accountNumber = 0;
        name = "";
        balance = 0.0;
    }

    // Create a new account
    void createAccount() {
        cout << "\nEnter Account Number: ";
        cin >> accountNumber;
        cin.ignore();

        cout << "Enter Customer Name: ";
        getline(cin, name);

        cout << "Enter Initial Deposit: ";
        cin >> balance;

        if (balance < 0) {
            balance = 0;
            cout << "Invalid amount. Balance set to 0.\n";
        }
    }

    // Display account information
    void display() const {
        cout << "\n----------------------------------------\n";
        cout << "Account Number : " << accountNumber << endl;
        cout << "Customer Name  : " << name << endl;
        cout << "Balance        : Rs. " << fixed << setprecision(2)
             << balance << endl;
        cout << "----------------------------------------\n";
    }

    // Deposit money
    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            cout << "\nRs. " << amount << " deposited successfully.\n";
            cout << "New Balance: Rs. " << balance << endl;
        } else {
            cout << "\nInvalid deposit amount.\n";
        }
    }

    // Withdraw money
    bool withdraw(double amount) {
        if (amount <= 0) {
            cout << "\nInvalid withdrawal amount.\n";
            return false;
        }

        if (amount > balance) {
            cout << "\nInsufficient balance.\n";
            return false;
        }

        balance -= amount;

        cout << "\nRs. " << amount << " withdrawn successfully.\n";
        cout << "Remaining Balance: Rs. " << balance << endl;

        return true;
    }

    // Get account number
    int getAccountNumber() const {
        return accountNumber;
    }

    // Save account to file
    void saveToFile(ofstream &file) const {
        file << accountNumber << "|"
             << name << "|"
             << fixed << setprecision(2)
             << balance << endl;
    }

    // Load account from file
    bool loadFromLine(string line) {

        size_t pos;

        // Account number
        pos = line.find("|");

        if (pos == string::npos)
            return false;

        accountNumber = stoi(line.substr(0, pos));
        line.erase(0, pos + 1);

        // Name
        pos = line.find("|");

        if (pos == string::npos)
            return false;

        name = line.substr(0, pos);
        line.erase(0, pos + 1);

        // Balance
        balance = stod(line);

        return true;
    }
};


// Find account in file
bool findAccount(int accountNo, BankAccount &account) {

    ifstream file("bank_accounts.txt");

    if (!file) {
        return false;
    }

    string line;

    while (getline(file, line)) {

        if (account.loadFromLine(line)) {

            if (account.getAccountNumber() == accountNo) {
                file.close();
                return true;
            }
        }
    }

    file.close();
    return false;
}


// Create new account
void createNewAccount() {

    BankAccount account;

    account.createAccount();

    // Check whether account already exists
    BankAccount existing;

    if (findAccount(account.getAccountNumber(), existing)) {
        cout << "\nAccount number already exists!\n";
        return;
    }

    ofstream file("bank_accounts.txt", ios::app);

    if (!file) {
        cout << "\nError opening bank file!\n";
        return;
    }

    account.saveToFile(file);

    file.close();

    cout << "\nAccount created successfully!\n";
}


// Deposit money
void depositMoney() {

    int accountNo;
    double amount;

    cout << "\nEnter Account Number: ";
    cin >> accountNo;

    BankAccount account;

    if (!findAccount(accountNo, account)) {
        cout << "\nAccount not found!\n";
        return;
    }

    cout << "Enter Deposit Amount: Rs. ";
    cin >> amount;

    account.deposit(amount);

    // Update file
    ifstream file("bank_accounts.txt");
    ofstream temp("temp.txt");

    string line;

    while (getline(file, line)) {

        BankAccount tempAccount;

        if (tempAccount.loadFromLine(line)) {

            if (tempAccount.getAccountNumber() ==
                account.getAccountNumber()) {

                account.saveToFile(temp);
            }
            else {
                temp << line << endl;
            }
        }
    }

    file.close();
    temp.close();

    remove("bank_accounts.txt");
    rename("temp.txt", "bank_accounts.txt");
}


// Withdraw money
void withdrawMoney() {

    int accountNo;
    double amount;

    cout << "\nEnter Account Number: ";
    cin >> accountNo;

    BankAccount account;

    if (!findAccount(accountNo, account)) {
        cout << "\nAccount not found!\n";
        return;
    }

    cout << "Enter Withdrawal Amount: Rs. ";
    cin >> amount;

    if (!account.withdraw(amount)) {
        return;
    }

    // Update file
    ifstream file("bank_accounts.txt");
    ofstream temp("temp.txt");

    string line;

    while (getline(file, line)) {

        BankAccount tempAccount;

        if (tempAccount.loadFromLine(line)) {

            if (tempAccount.getAccountNumber() ==
                account.getAccountNumber()) {

                account.saveToFile(temp);
            }
            else {
                temp << line << endl;
            }
        }
    }

    file.close();
    temp.close();

    remove("bank_accounts.txt");
    rename("temp.txt", "bank_accounts.txt");
}


// Check balance
void checkBalance() {

    int accountNo;

    cout << "\nEnter Account Number: ";
    cin >> accountNo;

    BankAccount account;

    if (findAccount(accountNo, account)) {

        cout << "\n========== BALANCE DETAILS ==========\n";
        cout << "Account Number : "
             << account.getAccountNumber() << endl;

        account.display();

    }
    else {
        cout << "\nAccount not found!\n";
    }
}


// Display all accounts
void displayAllAccounts() {

    ifstream file("bank_accounts.txt");

    if (!file) {
        cout << "\nNo accounts found!\n";
        return;
    }

    string line;
    bool found = false;

    cout << "\n============================================\n";
    cout << "           ALL BANK ACCOUNTS\n";
    cout << "============================================\n";

    while (getline(file, line)) {

        BankAccount account;

        if (account.loadFromLine(line)) {

            account.display();
            found = true;
        }
    }

    if (!found) {
        cout << "No accounts found!\n";
    }

    file.close();
}


// Main function
int main() {

    int choice;

    do {

        cout << "\n\n============================================\n";
        cout << "          BANK MANAGEMENT SYSTEM\n";
        cout << "============================================\n";

        cout << "1. Create New Account\n";
        cout << "2. Deposit Money\n";
        cout << "3. Withdraw Money\n";
        cout << "4. Check Balance\n";
        cout << "5. Display All Accounts\n";
        cout << "6. Exit\n";

        cout << "============================================\n";

        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {

            case 1:
                createNewAccount();
                break;

            case 2:
                depositMoney();
                break;

            case 3:
                withdrawMoney();
                break;

            case 4:
                checkBalance();
                break;

            case 5:
                displayAllAccounts();
                break;

            case 6:
                cout << "\nThank you for using Bank Management System!\n";
                break;

            default:
                cout << "\nInvalid choice! Please try again.\n";
        }

    } while (choice != 6);

    return 0;
}
