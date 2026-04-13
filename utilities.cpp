#include "utilities.h"
#include <iostream>
#include <string>
#include <limits>
#include <iomanip>
#include <sstream>
#include <algorithm>

/* ==============Account Number Generator============== */
std::string generateAccountNumber(const std::string& Type, int& counter){
    std::stringstream ss;
    if(Type[0] == 's'){
        ss << "SBI" << std::setw(7) << std::setfill('0') << counter++;
    } else if(Type[0] == 'c') {
        ss << "HDFC" << std::setw(7) << std::setfill('0') << counter++;
    }
    return ss.str();
}

/* ==============Utility Functions============== */

// To Clear the input if the user enters invalid input
void clearInput() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

// To read a line of input from the user
std::string readLine(const std::string& prompt) {
    std::cout << prompt;
    std::string s;
    std::getline(std::cin, s);
    return s;
}

// To read a double value from the user with error handling
bool readDouble(const std::string& prompt, double& out) {
    std::cout << prompt;
    if (!(std::cin >> out)) {
        clearInput();
        return false;
    }
    clearInput();
    return true;
}

// To read an integer value from the user with error handling
bool readInt(const std::string& prompt, int& out) {
    std::cout << prompt;
    if (!(std::cin >> out)) {
        clearInput();
        return false;
    }
    clearInput();
    return true;
}

// To check a Mobile Number is valid or not

bool isValidMobileNumber(const std::string& mobile){
    if(mobile.length() == 10 && std::all_of(mobile.begin(), mobile.end(), ::isdigit)) {
        return true;
    }
    else{
        std::cout << "You have entered an invalid mobile number." <<std::endl;
        isValidMobileNumber(readLine("Enter Mobile Number: "));

    }
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
