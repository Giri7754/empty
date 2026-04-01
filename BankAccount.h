#pragma once
#include <iostream>
#include <string>
#include <iomanip>

class BankAccount {
protected:
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