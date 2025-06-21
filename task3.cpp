#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
using namespace std;

class Transaction {
public:
    string type;
    float amount;

    Transaction(string t, float a) : type(t), amount(a) {}
};

class Account {
private:
    string accountNumber;
    float balance;
    vector<Transaction> history;

public:
    Account(string accNo) : accountNumber(accNo), balance(0.0f) {}

    string getAccountNumber() { return accountNumber; }

    float getBalance() { return balance; }

    void deposit(float amount) {
        balance += amount;
        history.push_back(Transaction("Deposit", amount));
        cout << "✅ Deposited: " << amount << endl;
    }

    bool withdraw(float amount) {
        if (amount > balance) {
            cout << "❌ Insufficient balance!" << endl;
            return false;
        }
        balance -= amount;
        history.push_back(Transaction("Withdraw", amount));
        cout << "✅ Withdrawn: " << amount << endl;
        return true;
    }

    bool transfer(Account &receiver, float amount) {
        if (withdraw(amount)) {
            receiver.deposit(amount);
            history.push_back(Transaction("Transferred to " + receiver.getAccountNumber(), amount));
            return true;
        }
        return false;
    }

    void showTransactions() {
        cout << "📜 Transaction History for " << accountNumber << ":\n";
        for (auto &t : history) {
            cout << "- " << t.type << ": " << t.amount << endl;
        }
    }

    void showAccountDetails() {
        cout << "📄 Account: " << accountNumber << ", Balance: " << fixed << setprecision(2) << balance << endl;
    }
};

class Customer {
private:
    string name;
    string id;
    Account account;

public:
    Customer(string n, string i) : name(n), id(i), account(i) {}

    string getID() { return id; }

    Account& getAccount() { return account; }

    void showDetails() {
        cout << "\n👤 Customer: " << name << ", ID: " << id << endl;
        account.showAccountDetails();
    }
};

// Helper function to find customer by ID
Customer* findCustomer(vector<Customer> &customers, const string &id) {
    for (auto &cust : customers) {
        if (cust.getID() == id) return &cust;
    }
    return nullptr;
}

int main() {
    vector<Customer> customers;
    int choice;

    while (true) {
        cout << "\n====== Banking System Menu ======\n";
        cout << "1. Create Customer\n2. Deposit\n3. Withdraw\n4. Transfer\n5. Show Transactions\n6. Show Account Details\n0. Exit\nChoose: ";
        cin >> choice;

        if (choice == 0) break;

        string id, id2;
        float amount;

        switch (choice) {
            case 1:
                {
                    string name, id;
                    cout << "Enter customer name: ";
                    cin >> name;
                    cout << "Enter customer ID: ";
                    cin >> id;
                    if (findCustomer(customers, id)) {
                        cout << "❌ Customer already exists.\n";
                        break;
                    }
                    customers.push_back(Customer(name, id));
                    cout << "✅ Customer created.\n";
                }
                break;

            case 2:
                cout << "Enter customer ID: ";
                cin >> id;
                if (Customer* cust = findCustomer(customers, id)) {
                    cout << "Enter deposit amount: ";
                    cin >> amount;
                    cust->getAccount().deposit(amount);
                } else {
                    cout << "❌ Customer not found.\n";
                }
                break;

            case 3:
                cout << "Enter customer ID: ";
                cin >> id;
                if (Customer* cust = findCustomer(customers, id)) {
                    cout << "Enter withdrawal amount: ";
                    cin >> amount;
                    cust->getAccount().withdraw(amount);
                } else {
                    cout << "❌ Customer not found.\n";
                }
                break;

            case 4:
                cout << "Enter sender ID: ";
                cin >> id;
                cout << "Enter receiver ID: ";
                cin >> id2;
                cout << "Enter amount: ";
                cin >> amount;

                {
                    Customer* sender = findCustomer(customers, id);
                    Customer* receiver = findCustomer(customers, id2);
                    if (sender && receiver) {
                        sender->getAccount().transfer(receiver->getAccount(), amount);
                    } else {
                        cout << "❌ One or both customers not found.\n";
                    }
                }
                break;

            case 5:
                cout << "Enter customer ID: ";
                cin >> id;
                if (Customer* cust = findCustomer(customers, id)) {
                    cust->getAccount().showTransactions();
                } else {
                    cout << "❌ Customer not found.\n";
                }
                break;

            case 6:
                cout << "Enter customer ID: ";
                cin >> id;
                if (Customer* cust = findCustomer(customers, id)) {
                    cust->showDetails();
                } else {
                    cout << "❌ Customer not found.\n";
                }
                break;

            default:
                cout << "❌ Invalid choice.\n";
        }
    }

    cout << "👋 Exiting Banking System. Goodbye!\n";
    return 0;
}
