#pragma once
#include <memory>
#include <string>
#include "BankAccount.h"
#include "SavingAccount.h"
#include "CurrentAccount.h"
/* ================= Factory ================= */
class AccountFactory {
    public:
    static std::unique_ptr<BankAccount> createAccount(const std::string& type, const std::string& name, const std::string& number, double opening, const std::string& mobile) {
        if (type[0] == 's') {
            return std::make_unique<SavingAccount>(name, number, opening, mobile);
        }
        else if (type[0] == 'c') {
            return std::make_unique<CurrentAccount>(name, number, opening, mobile);
        }
        return nullptr;
    }
};