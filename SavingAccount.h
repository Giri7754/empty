#pragma once
#include "BankAccount.h"

/* ================= Saving Account Derived Class  ================= */
class SavingAccount : public BankAccount {
public:
    SavingAccount(std::string name, std::string number, double opening)
        : BankAccount(std::move(name), std::move(number), opening) {}

    std::string accountType() const override {
        return "Savings";
    }
};