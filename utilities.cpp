#include "utilities.h"
#include <iostream>
#include <string>
#include <limits>
#include <iomanip>
#include <sstream>


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
