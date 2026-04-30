
// -- Here We test all our stuff -- //
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


void displaySearchInventory(){
    std::cout << "=======================================\n";
    std::cout << "||         Inventory Search          ||\n";
    std::cout << "=======================================\n";

  //Here this is where we run our search programs
}

void displayRestockPriority(){
    std::cout << "=======================================\n";
    std::cout << "||          Restock Priority          ||\n";
    std::cout << "=======================================\n";

  //Here this is where we show our priority Queue.
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
