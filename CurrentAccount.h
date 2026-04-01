#pragma once
#include "BankAccount.h"

/* ================= Current Account Derived Class  ================= */

class CurrentAccount : public BankAccount {
public:
    CurrentAccount(std::string name, std::string number, double opening)
        : BankAccount(std::move(name), std::move(number), opening) {}

    std::string accountType() const override {
        return "Current";
    }
};