#include "itemType.h"
#include "restockManager.h"
#include "stockAlertManager.h"
#include <iostream>
#include <string>

// --- Possible GUI Here -- //
void displayMenu() {
    std::cout << "=======================================\n";
    std::cout << "||      WAREHOUSE SYSTEM v1.0        ||\n";
    std::cout << "=======================================\n";
    std::cout << "|| 1. Search Inventory               ||\n";
    std::cout << "|| 2. View Restock Priority          ||\n";
    std::cout << "|| 3. Visualize Warehouse Map        ||\n";
    std::cout << "|| 4. Exit                           ||\n";
    std::cout << "=======================================\n";
    std::cout << "Selection: ";
}

//Very basic main
int main() {
    int choice;
    while (true) {
        displayMenu();
        std::cin >> choice;
        if (choice == 4) break;
    }
    return 0;
}
