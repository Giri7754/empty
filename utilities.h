#pragma once
#include <string>

std::string generateAccountNumber(const std::string& Type, int& counter);
void showMenu();
void clearInput();
std::string readLine(const std::string& prompt);
bool readDouble(const std::string& prompt, double& out);
bool readInt(const std::string& prompt, int& out);