#include <iostream>
#include <string>
#include <unordered_map>
#include <limits>
#include <algorithm>
#include <iomanip>
#include <sstream>

/* ==============Account Number Generator============== */
std::string generateAccountNumber(const std::string&Type){
    std::stringstream ss;
    
}
/* ==============Utility Functions============== */

void clearInput() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

std::string readLine(const std::string& prompt) {
    std::cout << prompt;
    std::string s;
    std::getline(std::cin, s);
    if (!s.empty() && s.back() == '\r') s.pop_back();
    return s;
}

bool readDouble(const std::string& prompt, double& out) {
    std::cout << prompt;
    if (!(std::cin >> out)) {
        clearInput();
        return false;
    }
    clearInput();
    return true;
}

bool readInt(const std::string& prompt, int& out) {
    std::cout << prompt;
    if (!(std::cin >> out)) {
        clearInput();
        return false;
    }
    clearInput();
    return true;
}

/* ================= BankAccount Class ================= */

class BankAccount {
private:
    std::string name_;
    std::string number_;
    double balance_{0.0};

public:
    BankAccount(std::string name, std::string number, double opening)
        : name_(name),
          number_(number),
          balance_(opening) {}

    const std::string& name() const {
        return name_;
    }

    const std::string& number() const {
        return number_;
    }

    double balance() const {
        return balance_;
    }

    bool deposit(double amount) {
        if (amount < 0.0)
            return false;
        balance_ += amount;
        return true;
    }

    bool withdraw(double amount) {
        if (amount < 0.0 || amount > balance_)
            return false;
        balance_ -= amount;
        return true;
    }
    virtual ~BankAccount();
    virtual std::string accountType() const = 0;

    void print() const {
        std::cout << "----------------------------\n";
        std::cout << "Account Holder : " << name_ << "\n";
        std::cout << "Account Number : " << number_ << "\n";
        std::cout << "Account Type   : " << accountType(); // Assuming all accounts are savings for simplicity
        std::cout << "Balance        : " << balance_ << "\n";
        std::cout << "----------------------------\n";
    }
};

/* Derived class for Savings Account */
class SavingAccount : public BankAccount {
public:
    SavingAccount(std::strng name, std::string number, double opening)
        : BankAccount(name, number, opening) {}

        
        std::string accountType() const override {
            std::string confirm = readline("We're having Saving Account only in SBI.Do You want to proceed? (y/n): ");
            transform(confirm.begin(), confirm.end(), confirm.begin(), ::tolower);
            if (!confirm.empty() && confirm[0] == 'y') {
                
                return "Savings";
            }
            return "Thank you for let us know. Please choose another account type.";
        }
};

/*Derived class for Current Account */
class CurrentAccount : public: BankAccount {
    public:
    CurrentAccount (std::string name, std::string number, double opening)
        : BankAccount(name, number, opening) {}
        
        std::string accountType() const override{
            std::string confirm = readline("We're having Current Account only in HDFC.Do You want to proceed? (y/n): ");
            transform(confirm.begin(), confirm.end(), confirm.begin(), ::tolower);
            if (!confirm.empty() && confirm[0] == 'y') {
                
                return "Current";
            }
            return "Thank you for let us know. Please choose another account type.";
        }   
};

/* ================= Menu ================= */

void showMenu() {
    std::cout << "\n================= Bank Management System =================\n";
    std::cout << "1. Create Account\n";
    std::cout << "2. Deposit Money\n";
    std::cout << "3. Withdraw Money\n";
    std::cout << "4. Display Account Details\n";
    std::cout << "5. Delete an Existing Account\n";
    std::cout << "6. Exit\n";
    std::cout << "==========================================================\n";
}

/* ================= Main ================= */

int main() {
    std::unordered_map<std::string, BankAccount*> accounts;
    bool running = true;

    while (running) {
        showMenu();
        int choice = 0;

        if (!readInt("Enter your choice (1-6): ", choice)) {
            std::cout << "Invalid choice.\n";
            continue;
        }

        switch (choice) {

            case 1: { // Create
                std::string name = readLine("Enter Name           : ");
                std::string Type = readLine("Enter Account Type   : ");
                transform(Type.begin(), Type.end(), Type.begin(), ::tolower);
                if(Type == "savings" || Type == "saving"){
                    SavingAccount* acc = new account(name, generateAccountNumber(Type), 0.0);
                    accounts.emplace(acc->number(), acc);


                }
                if (number.empty()) {
                    std::cout << "Account number cannot be empty.\n";
                    break;
                }
                if (accounts.count(number)) {
                    std::cout << "Account already exists.\n";
                    break;
                }

                double opening = 0.0;
                if (!readDouble("Enter Opening Amount : ", opening) || opening < 0.0) {
                    std::cout << "Invalid opening amount.\n";
                    break;
                }

                accounts.emplace(number, BankAccount{name, number, opening});
                std::cout << "Account created successfully.\n";
                break;
            }

            case 2: { // Deposit
                std::string number = readLine("Enter Account Number : ");
                auto it = accounts.find(number);

                if (it == accounts.end()) {
                    std::cout << "Account not found.\n";
                    break;
                }

                double amt;
                if (!readDouble("Enter Deposit Amount : ", amt) || !it->second.deposit(amt)) {
                    std::cout << "Invalid deposit amount.\n";
                    break;
                }

                std::cout << "Deposit successful. New balance: "
                          << it->second.balance() << "\n";
                break;
            }

            case 3: { // Withdraw
                std::string number = readLine("Enter Account Number    : ");
                auto it = accounts.find(number);

                if (it == accounts.end()) {
                    std::cout << "Account not found.\n";
                    break;
                }

                double amt;
                if (!readDouble("Enter Withdrawal Amount : ", amt)
                    || !it->second.withdraw(amt)) {
                    std::cout << "Withdrawal failed (invalid or insufficient balance).\n";
                    break;
                }

                std::cout << "Withdrawal successful. New balance: "
                          << it->second.balance() << "\n";
                break;
            }

            case 4: { // Display
                std::string number = readLine("Enter Account Number : ");
                auto it = accounts.find(number);

                if (it == accounts.end()) {
                    std::cout << "Account not found.\n";
                    break;
                }

                it->second.print();
                break;
            }

            case 5: { // Delete
                std::string number = readLine("Enter Account Number to delete : ");
                auto it = accounts.find(number);

                if (it == accounts.end()) {
                    std::cout << "Account not found.\n";
                    break;
                }

                it->second.print();

                if (it->second.balance() > 0.0) {
                    std::cout << "Withdraw balance before deleting account.\n";
                    break;
                }

                std::string confirm = readLine("Delete this account? (y/n): ");
                std::transform(confirm.begin(), confirm.end(), confirm.begin(), ::tolower);

                if (!confirm.empty() && confirm[0] == 'y') {
                    accounts.erase(it);
                    std::cout << "Account deleted successfully.\n";
                } else {
                    std::cout << "Deletion cancelled.\n";
                }
                break;
            }

            case 6:
                std::cout << "Thank you for using the Bank Management System.\n";
                running = false;
                break;

            default:
                std::cout << "Please enter a valid choice.\n";
        }
    }

    return 0;
}