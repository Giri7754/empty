#include <iostream>
#include <string>
#include <unordered_map>
#include <limits>
#include <algorithm>
#include <iomanip>
#include <sstream>
#include <memory>

/* ==============Account Number Generator============== */
std::string generateAccountNumber(const std::string& Type, int& counter){
    std::stringstream ss;
    if(Type == "saving"){
        ss << "SBI" << std::setw(7) << std::setfill('0') << counter++;
    } else {
        ss << "HDFC" << std::setw(7) << std::setfill('0') << counter++;
    }
    return ss.str();
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
/* ================= Factory ================= */

/* ================= BankAccount Class ================= */
class BankAccount {
private:
    std::string name_;
    std::string number_;
    double balance_{0.0};

public:
    BankAccount(std::string name, std::string number, double opening)
        : name_(std::move(name)), number_(std::move(number)), balance_(opening) {}

    virtual ~BankAccount() = default;

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

    virtual std::string accountType() const = 0;

    void print() const {
        std::cout << "----------------------------\n";
        std::cout << "Account Holder : " << name_ << "\n";
        std::cout << "Account Number : " << number_ << "\n";
        std::cout << "Account Type   : " << accountType() << "\n";
        std::cout << "Balance        : " << std::fixed << std::setprecision(2) << balance_ << "\n";
        std::cout << "----------------------------\n";
    }
};

/* ================= Derived Classes ================= */
class SavingAccount : public BankAccount {
public:
    SavingAccount(std::string name, std::string number, double opening)
        : BankAccount(std::move(name), std::move(number), opening) {}

    std::string accountType() const override {
        return "Savings";
    }
};

class CurrentAccount : public BankAccount {
public:
    CurrentAccount(std::string name, std::string number, double opening)
        : BankAccount(std::move(name), std::move(number), opening) {}

    std::string accountType() const override {
        return "Current";
    }
};

/* ================= Menu ================= */
void showMenu() {
    std::cout << "\n============ Bank Management System ============\n";
    std::cout << "1. Create Account\n";
    std::cout << "2. Deposit Money\n";
    std::cout << "3. Withdraw Money\n";
    std::cout << "4. Display Account Details\n";
    std::cout << "5. Delete Account\n";
    std::cout << "6. Exit\n";
    std::cout << "===============================================\n";
}

/* ================= Main ================= */
int main() {
    std::unordered_map<std::string, std::unique_ptr<BankAccount>> accounts;
    int SBIcounter = 1;
    int HDFCcounter = 1;

    bool running = true;
    while (running) {
        showMenu();
        int choice = 0;
        if (!readInt("Enter your choice (1–6): ", choice)) {
            std::cout << "Invalid choice.\n";
            continue;
        }
        switch (choice) {

        case 1: { // Create
            std::string name = readLine("Enter Name         : ");
            std::string type = readLine("Enter Account Type : ");
            std::transform(type.begin(), type.end(), type.begin(), ::tolower);

            double opening;
            if (!readDouble("Enter Opening Amount  : ", opening) || opening < 0.0) {
                std::cout << "Invalid amount\n";
                break;
            }

            std::string number;
            if (type == "saving") {
                number = generateAccountNumber(type, SBIcounter);
                accounts[number] = std::make_unique<SavingAccount>(name, number, opening);
            }
            else if (type == "current") {
                number = generateAccountNumber(type, HDFCcounter);
                accounts[number] = std::make_unique<CurrentAccount>(name, number, opening);
            }
            else {
                std::cout << "Invalid account type\n";
                break;
            }

            std::cout << "Account created successfully.\n";
            std::cout << "Your Account Number is : " << number << "\n";
            break;
        }

        case 2: { // Deposit
            std::string num = readLine("Enter Account Number: ");
            auto it = accounts.find(num);
            if (it == accounts.end()) {
                std::cout << "Account not found.\n";
                break;
            }   

            double amt;
            if (!readDouble("Enter Amount: ", amt) || !it->second->deposit(amt)) {
                std::cout << "Invalid deposit\n";
                break;
            }
            std::cout << "New Balance: " << it->second->balance() << "\n";
            break;
        }

        case 3: { // Withdraw
            std::string num = readLine("Enter Account Number: ");
            auto it = accounts.find(num);
            if (it == accounts.end()) {
                std::cout << "Account not found.\n";
                break;
            }   

            double amt;
            if (!readDouble("Enter Amount: ", amt) || !it->second->withdraw(amt)) {
                std::cout << "Withdrawal failed (invalid amount or insufficient balance).\n";
                break;
            }
            std::cout << "Withdrawal successful. New balance: " << it->second->balance() << "\n";
            break;
        }

        case 4: { // Display
            std::string num = readLine("Enter Account Number: ");
            auto it = accounts.find(num);
            if (it != accounts.end()) {
                it->second->print();
                break;
            }
            std::cout << "Account not found.\n";
            break;
        }

        case 5: { // Delete
            std::string num = readLine("Enter Account Number: ");
            auto it = accounts.find(num);
            if (it == accounts.end()) {
                std::cout << "Account not found.\n";
                break;
            }

            it->second->print();

            if (it->second->balance() > 0.0) {
                std::cout << "Withdraw the balance before deleting the account.\n";
                std::string confirm = readLine("Withdraw balance? (y/n): ");
                std::transform(confirm.begin(), confirm.end(), confirm.begin(), ::tolower);
                if (!confirm.empty() && confirm[0] == 'y')
                 {
                    it->second->withdraw(it->second->balance());
                    std::cout << "Withdrawal successful.\n";
                }
            }

            std::string confirm = readLine("Delete account? (y/n): ");
            std::transform(confirm.begin(), confirm.end(), confirm.begin(), ::tolower);
            if (!confirm.empty() && (confirm[0]) == 'y') {
                accounts.erase(it);
                std::cout << "Account deleted.\n";
                break;
            }
            else{      
                std::cout << "Account deletion cancelled.\n";
                break;
            }
            
        }

        case 6: // Exit case
            running = false;
            std::cout << "Thank you for using our banking system!\n";
            break;
        }
    }
    return 0;
}
