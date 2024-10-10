#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

class Account {
private:
    int accountNumber;
    string accountHolderName;
    float balance;
    vector<string> transactionHistory;

public:
    void createAccount();
    void displayAccount();
    void depositMoney(float amount);
    void withdrawMoney(float amount);
    float getBalance();
    int getAccountNumber();
    string getAccountHolderName();
    void recordTransaction(string transaction);
    void displayTransactions();
    void setAccount(int accNo, string name, float bal);
    vector<string> getTransactionHistory();
};

void Account::createAccount() {
    cout << "Enter Account Number: ";
    cin >> accountNumber;
    cout << "Enter Account Holder Name: ";
    cin.ignore();
    getline(cin, accountHolderName);
    balance = 0;
    transactionHistory.clear();
    cout << "Account created successfully!\n";
}

void Account::displayAccount() {
    cout << "Account Number: " << accountNumber << endl;
    cout << "Account Holder Name: " << accountHolderName << endl;
    cout << "Balance: " << balance << endl;
}

void Account::depositMoney(float amount) {
    balance += amount;
    string transaction = "Deposited: " + to_string(amount);
    recordTransaction(transaction);
    cout << "Deposited " << amount << " successfully!\n";
}

void Account::withdrawMoney(float amount) {
    if (amount <= balance) {
        balance -= amount;
        string transaction = "Withdrew: " + to_string(amount);
        recordTransaction(transaction);
        cout << "Withdrew " << amount << " successfully!\n";
    } else {
        cout << "Insufficient balance!\n";
    }
}

float Account::getBalance() {
    return balance;
}

int Account::getAccountNumber() {
    return accountNumber;
}

string Account::getAccountHolderName() {
    return accountHolderName;
}

void Account::recordTransaction(string transaction) {
    transactionHistory.push_back(transaction);
}

void Account::displayTransactions() {
    cout << "Transaction History for Account " << accountNumber << ":\n";
    for (string transaction : transactionHistory) {
        cout << transaction << endl;
    }
}

void Account::setAccount(int accNo, string name, float bal) {
    accountNumber = accNo;
    accountHolderName = name;
    balance = bal;
}

vector<string> Account::getTransactionHistory() {
    return transactionHistory;
}

void saveAccount(Account &account) {
    ofstream file("accounts.txt", ios::app);
    if (file.is_open()) {
        file << account.getAccountNumber() << endl;
        file << account.getAccountHolderName() << endl;
        file << account.getBalance() << endl;
        file << "Transactions:\n";
        for (string transaction : account.getTransactionHistory()) {
            file << transaction << endl;
        }
        file << "END\n";
        file.close();
    }
}

void loadAccounts(vector<Account> &accounts) {
    ifstream file("accounts.txt");
    if (file.is_open()) {
        while (!file.eof()) {
            Account account;
            int accNo;
            string name;
            float bal;
            file >> accNo;
            file.ignore();
            getline(file, name);
            file >> bal;
            account.setAccount(accNo, name, bal);
            accounts.push_back(account);
            string line;
            getline(file, line);
            while (getline(file, line) && line != "END") {
                account.recordTransaction(line);
            }
        }
        file.close();
    }
}

Account* searchAccount(vector<Account> &accounts, int accNo) {
    for (Account &acc : accounts) {
        if (acc.getAccountNumber() == accNo) {
            return &acc;
        }
    }
    return nullptr;
}

int main() {
    vector<Account> accounts;
    loadAccounts(accounts);

    int choice;
    do {
        cout << "\n\n\t\tBANKING SYSTEM";
        cout << "\n\n\t1. CREATE ACCOUNT";
        cout << "\n\t2. DEPOSIT MONEY";
        cout << "\n\t3. WITHDRAW MONEY";
        cout << "\n\t4. CHECK BALANCE";
        cout << "\n\t5. VIEW TRANSACTIONS";
        cout << "\n\t6. EXIT";
        cout << "\n\n\tSelect Your Option (1-6): ";
        cin >> choice;

        switch (choice) {
            case 1: {
                Account newAccount;
                newAccount.createAccount();
                accounts.push_back(newAccount);
                saveAccount(newAccount);
                break;
            }
            case 2: {
                int accNo;
                cout << "Enter Account Number: ";
                cin >> accNo;
                Account* account = searchAccount(accounts, accNo);
                if (account != nullptr) {
                    float amount;
                    cout << "Enter amount to deposit: ";
                    cin >> amount;
                    account->depositMoney(amount);
                    saveAccount(*account);
                } else {
                    cout << "Account not found!\n";
                }
                break;
            }
            case 3: {
                int accNo;
                cout << "Enter Account Number: ";
                cin >> accNo;
                Account* account = searchAccount(accounts, accNo);
                if (account != nullptr) {
                    float amount;
                    cout << "Enter amount to withdraw: ";
                    cin >> amount;
                    account->withdrawMoney(amount);
                    saveAccount(*account);
                } else {
                    cout << "Account not found!\n";
                }
                break;
            }
            case 4: {
                int accNo;
                cout << "Enter Account Number: ";
                cin >> accNo;
                Account* account = searchAccount(accounts, accNo);
                if (account != nullptr) {
                    cout << "Balance: " << account->getBalance() << endl;
                } else {
                    cout << "Account not found!\n";
                }
                break;
            }
            case 5: {
                int accNo;
                cout << "Enter Account Number: ";
                cin >> accNo;
                Account* account = searchAccount(accounts, accNo);
                if (account != nullptr) {
                    account->displayTransactions();
                } else {
                    cout << "Account not found!\n";
                }
                break;
            }
            case 6:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid option!\n";
        }
    } while (choice != 6);

    return 0;
}
