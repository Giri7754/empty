## Bank Management System


This project Bank Management System implemented using Object‑Oriented Programming  and modern C++ 11 features.  
It supports creating bank accounts, depositing and withdrawing money, displaying account details, and deleting accounts.

The application is designed using **Singleton** and **Factory Method** design patterns to ensure clean architecture.

---

## Concepts and design Patterns Used

- Object‑Oriented Programming (OOP)
- Singleton Design Pattern
- Factory Method Design Pattern
- Smart Pointers (std::unique_ptr)
- STL Containers (std::unordered_map)

---

## Utility Function

---GenerateAccountNumber---

**Concepts Used:**
- String formatting
- Pass‑by‑reference
- Encapsulation

**Description:**
Generates a unique account number based on the account type using a counter to ensure uniqueness.

---

### `readLine`
**Concepts Used:**
- Input handling
- Encapsulation

**Description:**
Reads full‑line string input safely from the user.

---

### `readInt and readDouble`
**Concepts Used:**
- Input validation
- Error handling
- Pass‑by‑reference

**Description:**
Safely reads numeric input and prevents invalid data entry.

---

## Menu Handling

### `showMenu`
**Concepts Used:**
- Separation of concerns

**Description:**
Displays the banking system menu independently of business logic.

---

## Core Classes

### `BankAccount` (Abstract Base Class)
**Concepts Used:**
- Abstraction
- Encapsulation
- Runtime Polymorphism
- Virtual functions
- Virtual destructor

**Description:**
Represents a generic bank account and defines common attributes and operations such as deposit, withdrawal, and display.  
Declares a pure virtual function to enforce derived‑class implementation.

### `SavingAccount and CurrentAccount`

**Concepts Used:**
- Inheritance
- Polymorphism

**Description:**
Derived classes representing specific account types.  
They override virtual functions from BankAccount to provide account‑specific behavior.

## `FactoryMethod`

**Concepts Used:**
- Factory Method Pattern
- Decoupling

**Description:**
Handles the creation of different account objects based on user input.  
This removes object‑creation responsibility from main.

---

## `Singleton`

**Concepts Used:**
- Singleton pattern
- STL containers
- Smart pointers

**Description:**
Manages all bank accounts using a single shared instance.  
Ensures that only one account registry exists throughout program execution, preventing inconsistent data and duplicate records.

---
