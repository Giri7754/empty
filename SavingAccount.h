#pragma once
#include "BankAccount.h"

/* ================= Saving Account Derived Class  ================= */
class SavingAccount : public BankAccount {
public:
    SavingAccount(std::string name, std::string number, double opening, std::string mobile)
        : BankAccount(std::move(name), std::move(number), opening, std::move(mobile)) {}

    std::string accountType() const override {
        return "Savings";
    }
};