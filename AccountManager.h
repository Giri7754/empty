#pragma once
#include <unordered_map>
#include <memory>
#include <string>
#include "BankAccount.h"
/* ================= Singleton ================= */
class AccountManager {
    private:
    std::unordered_map<std::string, std::unique_ptr<BankAccount>> accounts;

    AccountManager() = default;

    public:
    AccountManager(const AccountManager&) = delete;
    AccountManager& operator=(const AccountManager&) = delete;

    static AccountManager& getInstance()
    {
        static AccountManager Manager;
        return Manager;
    }

    void addAccount(std::unique_ptr<BankAccount> account) {
        accounts[account->number()] = std::move(account);
    }

    BankAccount* find(const std::string& number){
        auto it = accounts.find(number);
        if (it !=accounts.end()) {
            return it->second.get();
        }
        return nullptr;
    }
    BankAccount* findMobile(const std::string& mobile){
        for (auto& it : accounts) {
            if (!it.second->mobile().compare(mobile)) {
                return it.second.get();
            }
        }
        return nullptr;
    }

    bool removeAccount(const std::string& number) {
        return accounts.erase(number) > 0;
    }
};