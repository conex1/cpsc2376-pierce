#include <iostream>
#include <fstream>
#include <iomanip>
#include <limits>  // Added for input validation

// Constants
const std::string BALANCE_FILE = "account_balance.txt";
const double INITIAL_BALANCE = 100.00;

// Function prototypes
double readBalanceFromFile();
void writeBalanceToFile(double balance);
void displayMenu();
void checkBalance(double balance);
double deposit(double balance);
double withdraw(double balance);

int main() {
    double balance;

    // Initialize balance from file or set to initial balance
    balance = readBalanceFromFile();
    if (balance < 0) {
        balance = INITIAL_BALANCE;
        writeBalanceToFile(balance);
    }

    std::cout << "Welcome to Your Bank Account!" << std::endl;
    if (balance == INITIAL_BALANCE) {
        std::cout << "Initializing account with $" << std::fixed << std::setprecision(2) << balance << "..." << std::endl;
    } else {
        std::cout << "Your current balance is: $" << std::fixed << std::setprecision(2) << balance << std::endl;
    }

    int choice;
    do {
        displayMenu();
        std::cout << "Enter your choice: ";
        
        // Input validation for menu choice
        while(!(std::cin >> choice)) {
            std::cout << "Invalid input! Please enter 1-4: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        switch (choice) {
            case 1:
                checkBalance(balance);
                break;
            case 2:
                balance = deposit(balance);
                writeBalanceToFile(balance);
                break;
            case 3:
                balance = withdraw(balance);
                writeBalanceToFile(balance);
                break;
            case 4:
                std::cout << "Exiting program. Goodbye!" << std::endl;
                break;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
        }
    } while (choice != 4);

    return 0;
}

// Read balance from file (unchanged)
double readBalanceFromFile() {
    std::ifstream file(BALANCE_FILE);
    if (!file) {
        return -1; // File does not exist
    }

    double balance;
    file >> balance;
    file.close();
    return balance;
}

// Write balance to file (unchanged)
void writeBalanceToFile(double balance) {
    std::ofstream file(BALANCE_FILE);
    if (!file) {
        std::cerr << "Error: Unable to write to file. Exiting program." << std::endl;
        exit(1);
    }

    file << std::fixed << std::setprecision(2) << balance;
    file.close();
}

// Display menu options (unchanged)
void displayMenu() {
    std::cout << "\nMenu:\n";
    std::cout << "1. Check Balance\n";
    std::cout << "2. Deposit Money\n";
    std::cout << "3. Withdraw Money\n";
    std::cout << "4. Exit\n";
}

// Check balance (unchanged)
void checkBalance(double balance) {
    std::cout << "Your current balance is: $" << std::fixed << std::setprecision(2) << balance << std::endl;
}

// Deposit money with validation
double deposit(double balance) {
    double amount;
    std::cout << "Enter deposit amount: ";
    
    // Input validation for deposit amount
    while(!(std::cin >> amount)) {
        std::cout << "Invalid input! Please enter a number: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    if (amount <= 0) {
        std::cout << "Error: Deposit amount must be positive." << std::endl;
    } else {
        balance += amount;
        std::cout << "Deposit successful. Your new balance is: $" << std::fixed << std::setprecision(2) << balance << std::endl;
    }

    return balance;
}

// Withdraw money with validation
double withdraw(double balance) {
    double amount;
    std::cout << "Enter withdrawal amount: ";
    
    // Input validation for withdrawal amount
    while(!(std::cin >> amount)) {
        std::cout << "Invalid input! Please enter a number: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    if (amount <= 0) {
        std::cout << "Error: Withdrawal amount must be positive." << std::endl;
    } else if (amount > balance) {
        std::cout << "Error: Insufficient funds. Your balance is: $" << std::fixed << std::setprecision(2) << balance << std::endl;
    } else {
        balance -= amount;
        std::cout << "Withdrawal successful. Your new balance is: $" << std::fixed << std::setprecision(2) << balance << std::endl;
    }

    return balance;
}