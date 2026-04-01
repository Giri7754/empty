#include "AccountFactory.h"
#include "AccountManager.h"
#include "utilities.h"
#include <algorithm>


int main() {
    auto& manager = AccountManager::getInstance();
    int SBIcounter = 1, HDFCcounter = 1;
    bool running = true;
    while (running) {
        showMenu();
        int choice = 0;
        if (!readInt("Enter your choice (1 - 6): ", choice)) {
            std::cout << "Invalid choice.\n";
            continue;
        }
        switch (choice) {

        case 1: { // Create
            std::string name = readLine("Enter Name         : ");
            std::string type = readLine("Enter Account Type (saving/current) : ");
            std::transform(type.begin(), type.end(), type.begin(), ::tolower);

            double opening;
            if (!readDouble("Enter Opening Amount  : ", opening) || opening < 0.0) {
                std::cout << "Invalid amount\n";
                break;
            }

            std::string number = (type == "saving") 
            ? generateAccountNumber(type, SBIcounter) 
            : generateAccountNumber(type, HDFCcounter);
            
            auto acc = AccountFactory::createAccount(type, name, number, opening);

            if(!acc) {
                std::cout << "Invalid account type.\n";
                break;
            }

            manager.addAccount(std::move(acc));
            std::cout << "Account created successfully! Account Number: " << number << "\n";
            break;
        }

        case 2: { // Deposit
            std::string num = readLine("Enter Account Number: ");
            if(manager.find(num) == nullptr) {
                std::cout << "Account not found.\n";
                break;
            }
            double amt;
            if(!readDouble("Enter Amount: ", amt)) {
                std::cout << "Invalid deposit\n";
                break;
            }
            if(auto acc = manager.find(num)) {
                acc->deposit(amt);
                std::cout <<"Deposit Successful. New Balance: " << acc->balance() << "\n";
                break;
            }
        }

        case 3: { // Withdraw
            std::string num = readLine("Enter Account Number: ");
            auto acc = manager.find(num);
            if (acc == nullptr) {
                std::cout << "Account not found.\n";
                break;
            }   

            double amt;
            if (!readDouble("Enter Amount: ", amt) || !acc->withdraw(amt)) {
                std::cout << "Withdrawal failed (invalid amount or insufficient balance).\n";
                break;
            }
            std::cout << "Withdrawal successful. New balance: " << acc->balance() << "\n";
            break;
        }

        case 4: { // Display
            std::string num = readLine("Enter Account Number: ");
            auto acc = manager.find(num);
            if (acc != nullptr) {
                acc->print();
                break;
            }
            std::cout << "Account not found.\n";
            break;
        }

        case 5: { // Delete
            std::string num = readLine("Enter Account Number: ");
            auto acc = manager.find(num);
            if (acc == nullptr) {
                std::cout << "Account not found.\n";
                break;
            }

            acc->print();

            if (acc->balance() > 0.0) {
                std::cout << "Withdraw the balance before deleting the account.\n";
                std::string confirm = readLine("Withdraw balance? (y/n): ");
                std::transform(confirm.begin(), confirm.end(), confirm.begin(), ::tolower);
                if (!confirm.empty() && confirm[0] == 'y')
                 {
                    acc->withdraw(acc->balance());
                    std::cout << "Withdrawal successful.\n";
                }
            }

            std::string confirm = readLine("Delete account? (y/n): ");
            std::transform(confirm.begin(), confirm.end(), confirm.begin(), ::tolower);
            if (!confirm.empty() && (confirm[0]) == 'y') {
                manager.removeAccount(num);
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