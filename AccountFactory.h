#pragma once
#include <memory>
#include <string>
#include "BankAccount.h"
#include "SavingAccount.h"
#include "CurrentAccount.h"
/* ================= Factory ================= */
class AccountFactory {
    public:
    static std::unique_ptr<BankAccount> createAccount(const std::string& type, const std::string& name, const std::string& number, double opening) {
        if (type == "saving") {
            return std::make_unique<SavingAccount>(name, number, opening);
        }
        else if (type == "current") {
            return std::make_unique<CurrentAccount>(name, number, opening);
        }
        return nullptr;
    }
};