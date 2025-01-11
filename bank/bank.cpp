#include "bank.hpp"
#include <iostream>

#ifdef _WIN32
  #include <windows.h>
#else
  #include <unistd.h>
#endif

// Cross-platform sleep function with reduced sleep time
void sleepFor(int seconds) {
  const double adjustmentFactor = 0.1; // Adjust to make sleep time 50% shorter
  int adjustedMilliseconds = static_cast<int>(seconds * adjustmentFactor * 300);

  #ifdef _WIN32
    Sleep(adjustedMilliseconds);  // Windows Sleep uses milliseconds
  #else
    usleep(adjustedMilliseconds * 300);  // Unix-like usleep uses microseconds
  #endif
}


void showMenu() {
  std::cout << "Welcome to the ATM!" << std::endl;
  std::cout << "1. Check Balance" << std::endl;
  std::cout << "2. Deposit Money" << std::endl;
  std::cout << "3. Withdraw Money" << std::endl;
  std::cout << "4. Exit" << std::endl;
}


// Simplified loading function
void loading() {
  const int times_dot = 10;

  std::cout << "Processing";
  for (int i = 0; i < times_dot; i++) {
    std::cout << ".";
    sleepFor(1);  // Use cross-platform sleep
  }
  std::cout << std::endl;
}
void displayAll() {
  double balance = 0;
  int choice;
  double amount;

  bool continueLoop = true;

  while (continueLoop) {
    showMenu();
    std::cout << "Enter your choice: ";
    std::cin >> choice;

    switch (choice) {
      case 1:
        loading();
        std::cout << "Your current balance is: $" << balance << std::endl;
        break;
      case 2:
        std::cout << "Enter amount to deposit: $";
        std::cin >> amount;
        loading();
        balance += amount;
        std::cout << "Deposit successful. New balance: $" << balance << std::endl;
        break;
      case 3:
        std::cout << "Enter amount to withdraw: $";
        std::cin >> amount;
        loading();
        if (amount <= balance) {
          balance -= amount;
          std::cout << "Withdrawal successful. New balance: $" << balance << std::endl;
        } else {
          std::cout << "Insufficient funds!" << std::endl;
        }
        break;
      case 4:
        std::cout << "Thank you for using our ATM!" << std::endl;
        continueLoop = false;
        break;
      default:
        std::cout << "Invalid choice, try again." << std::endl;
        break;
    }
  }
}
