#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

#include "itemType.h"              
#include "sortingAlgo.h"           
#include "stockAlertManager.h"     
#include "restockManager.h"        
#include "inventoryLinearSearch.h" 
#include "csvFunctions.h"          // Added CSV handling header
#include "redBlackTree.h"
#include "linkedList.h"
#include "heapSort.h"
#include <unordered_map> 

// Color Codes for professional terminal output
#define RESET   "\033[0m" 
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define CYAN    "\033[36m"

// UI Helper Functions
void clearScreen() {
#ifdef _WIN32 
    system("cls");  
#else
    system("clear");    
#endif 
}

void displayLogo() {
    std::cout << CYAN << R"(
======================================================================
  ___ _  _ _   _ ___ _  _ _____ ___  ______   __
 |_ _| \| | | | | __| \| |_   _/ _ \| _ \ \ / /
  | || .` | \_/ | _|| .` | | || (_) |   /\ V / 
 |___|_|\_|\___/|___|_|\_| |_| \___/|_|_\ |_|  

                  B Y   A D K  (Aaron, Darcie, Kenshin)
======================================================================
    )" << RESET << std::endl;
}

void wait() {
    std::cout << "\n" << CYAN << "Press Enter to return to main menu..." << RESET;
    std::cin.ignore(100, '\n');
    std::cin.get(); 
}

//Adjusted main to parse all three datasets.
int main() {

    std::vector<Item> inventory;
    StockAlertManager alertManager;
    RestockManager restockManager;
    InventoryAlgorithms searchAlgo;
    RedBlackTree inventoryTree; //Fix: Mismatch named.
    LinkedList inventoryList;
    
    // --- NEW: Dataset Selection Menu ---
    clearScreen(); 
    displayLogo(); 
    
    std::cout << YELLOW << "[ SYSTEM INITIALIZATION ]" << RESET << std::endl;
    std::cout << "Select the inventory dataset to load:" << std::endl;
    std::cout << "1. Retail Store Inventory" << std::endl;
    std::cout << "2. Grocery Inventory and Sales Dataset" << std::endl;
    std::cout << "3. Sales Data" << std::endl;
    std::cout << "\nEnter choice (1-3): ";

    //I used if and else if for choosing which dataset to load. Note that hardcoding is gone.
    int datasetChoice;
    std::string targetCSV = "assets/retail_store_inventory.csv"; // Default fallback
    
    if (std::cin >> datasetChoice) {
        if (datasetChoice == 2) {
            targetCSV = "assets/Grocery_Inventory_and_Sales_Dataset.csv";
        } else if (datasetChoice == 3) {
            targetCSV = "assets/sales_data.csv";
        }
    } else {
        // Clear invalid input
        std::cin.clear();
        std::cin.ignore(100, '\n');
    }

    // --- Load Inventory from Selected CSV ---
    std::cout << "\nLoading inventory database from " << targetCSV << "..." << std::endl;
    loadInventoryFromCSV(targetCSV, inventory, alertManager);
    wait();
    // -----------------------------------

    // Main loop for the dashboard interface
    bool running = true;
    while (running) {
        clearScreen(); 
        displayLogo(); 

        std::cout << YELLOW << "[ MAIN DASHBOARD ]" << RESET << std::endl;
        std::cout << "1. View Full Inventory Report" << std::endl;
        std::cout << "2. Search for Product" << std::endl;
        std::cout << "3. Run Stock Alert Audit" << std::endl;
        std::cout << "4. Sort by Quantity" << std::endl;
        std::cout << "5. Generate Restocking List" << std::endl;
        std::cout << "6. Insert Product into Inventory Tree" << std::endl;
        std::cout << "7. Search Product in Inventory Tree" << std::endl;
        std::cout << "8. Delete Product from Inventory" << std::endl;
        std::cout << "9. Print Inventory in-order (ID based)" << std::endl;
        std::cout << "10. Sort by Name (Heap Sort)" << std::endl; // <--- NEW
        std::cout << "11. Exit System" << std::endl;
        std::cout << "\nSelect an operation: ";

        int choice;
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(100, '\n'); 
            std::cout << RED << "Invalid input. Please enter a number corresponding to the menu" << RESET << std::endl;
            continue;
        }

        switch (choice) {
            case 1: { // Display Table
                clearScreen();
                std::cout << YELLOW << "--- WAREHOUSE INVENTORY REPORT ---" << RESET << "\n\n";
                std::cout << std::left << std::setw(10) << "ID" 
                          << std::setw(25) << "Product Name" 
                          << std::setw(15) << "Category" 
                          << std::setw(10) << "Stock" 
                          << std::setw(10) << "Threshold" << std::endl;
                std::cout << std::string(70, '-') << std::endl;
                
                for (const auto& item : inventory) {
                    std::cout << std::left << std::setw(10) << item.getId()
                              << std::setw(25) << item.getName()
                              << std::setw(15) << item.getCategory()
                              << std::setw(10) << item.getQuantity()
                              << std::setw(10) << item.getMinStockThreshold() << std::endl;
                }
                wait(); 
                break; 
            }
            case 2: { // Linear Search
                std::string target;
                std::cout << "\nEnter exact Product ID to locate: ";
                std::cin.ignore();
                std::getline(std::cin, target);
                
                int index = searchAlgo.linearSearch(inventory, target);
                if (index != -1) {
                    std::cout << GREEN << "\nItem Found!" << RESET << std::endl;
                    std::cout << std::left << std::setw(10) << "ID" 
                              << std::setw(25) << "Product Name" 
                              << std::setw(15) << "Category" 
                              << std::setw(10) << "Stock" 
                              << std::setw(10) << "Threshold" << std::endl;
                    std::cout << std::string(70, '-') << std::endl;
                    const auto& item = inventory[index];
                    std::cout << std::left << std::setw(10) << item.getId()
                              << std::setw(25) << item.getName()
                              << std::setw(15) << item.getCategory()
                              << std::setw(10) << item.getQuantity()
                              << std::setw(10) << item.getMinStockThreshold() << std::endl;
                } else {
                    std::cout << RED << "\nItem not found in current inventory." << RESET << std::endl;
                }
                wait();
                break;
            }
            case 3: { // Stock Alerts
                clearScreen();
                std::cout << YELLOW << "--- CRITICAL STOCK ALERTS ---" << RESET << std::endl;
                
                std::unordered_map<std::string, int> currentInventory;
                std::unordered_map<std::string, std::string> itemNames;
                for (const auto& item : inventory) {
                    currentInventory[item.getId()] = item.getQuantity();
                    itemNames[item.getId()] = item.getName();
                }
                
                std::vector<StockAlert> alerts = alertManager.checkThresholds(currentInventory, itemNames);
                
                if (alerts.empty()) {
                    std::cout << GREEN << "All items are above minimum threshold levels." << RESET << std::endl;
                } else {
                    std::cout << RED << "Low stock items detected:\n" << RESET << std::endl;
                    std::cout << std::left << std::setw(10) << "ID" 
                              << std::setw(25) << "Product Name" 
                              << std::setw(15) << "Current Qty" 
                              << std::setw(10) << "Threshold" << std::endl;
                    std::cout << std::string(70, '-') << std::endl;
                    
                    for (const auto& alert : alerts) {
                        std::cout << std::left << std::setw(10) << alert.getId()
                                  << std::setw(25) << alert.getItemName()
                                  << std::setw(15) << alert.getCurrentQuantity()
                                  << std::setw(10) << alert.getThreshold() << std::endl;
                    }
                }
                wait();
                break;
            }
            case 4: { // Sort by Quantity
                clearScreen();
                std::cout << "\nSorting inventory by quantity for logistics optimization..." << std::endl;
                searchAlgo.sortInventoryByQuantity(inventory);
                std::cout << GREEN << "Sort Complete. View 'Full Inventory Report' to see results." << RESET << std::endl;
                wait();
                break;
            }
            case 5: { // Restocking
                clearScreen();
                std::cout << YELLOW << "--- GENERATING RESTOCKING PRIORITY ---" << RESET << std::endl;
    
                for (const auto& item : inventory) {
                     //Fixing it so that target should be relative to the item's own threshold, like 50.
                    int dynamicTarget = item.getMinStockThreshold() + 50; 
                    restockManager.addRestockTask(item, dynamicTarget);
    }
                if (restockManager.isEmpty()) {
                    std::cout << GREEN << "No restocking needed. All items are at or above target levels." << RESET << std::endl;
                } else {
                    auto restockList = restockManager.generatePriorityList();
                    std::cout << "\nRestocking Priority (Highest to Lowest):\n" << std::endl;
                    std::cout << std::left << std::setw(10) << "ID" 
                              << std::setw(25) << "Product Name" 
                              << std::setw(15) << "Qty Needed" 
                              << std::setw(10) << "Urgency" << std::endl;
                    std::cout << std::string(70, '-') << std::endl;
                    
                    for (const auto& task : restockList) {
                        std::cout << std::left << std::setw(10) << task.getId()
                                  << std::setw(25) << task.getItemName()
                                  << std::setw(15) << task.getQuantityNeeded()
                                  << std::setw(10) << task.getUrgencyScore() << std::endl;
                    }
                }
                wait();
                break;
            }
            case 6: { // Insert
                clearScreen();
                std::cout << YELLOW << "--- INSERT PRODUCT INTO INVENTORY ---" << RESET << std::endl;

                std::string id;
                std::string name;
                std::string category;
                int quantity;
                int minStockThreshold;

                std::cout << "Enter Product ID: ";
                std::cin.ignore();
                std::getline(std::cin, id);
                std::cout << "Enter Product Name: ";
                std::getline(std::cin, name);
                std::cout << "Enter Category: ";
                std::getline(std::cin, category);
                std::cout << "Enter Quantity: ";
                std::cin >> quantity;
                std::cout << "Enter Threshold: ";
                std::cin >> minStockThreshold;

                //Fix for menu.
                std::cin.ignore(100, '\n');

                Item newItem(id, name, category, quantity, minStockThreshold);

                inventoryTree.insert(newItem);
                inventoryList.insertAtEnd(newItem);
                inventory.push_back(newItem);

                alertManager.setMinimumThreshold(id, minStockThreshold);

                std::cout << GREEN << "Item Inserted." << RESET << std::endl;
                wait();
                break;
            }
            case 7: { // Search
                clearScreen();
                std::cout << YELLOW << "--- SEARCH FOR PRODUCT IN INVENTORY ---" << RESET << std::endl;

                std::string targetId;
                std::cout << "Enter Product ID to search: ";
                std::cin.ignore(); // FIX: Added missing ignore to prevent skipping!
                std::getline(std::cin, targetId);

                Item* foundItem = inventoryTree.search(targetId);

                if (foundItem != nullptr) {
                    std::cout << GREEN << "Item Found." << RESET << std::endl;
                    std::cout << foundItem->getId() << std::endl;
                }
                else {
                    std::cout << RED << "Item not found." << RESET << std::endl;
                }
                wait();
                break;
            }
            case 8: { // Delete
                clearScreen();
                std::cout << YELLOW << "--- DELETE PRODUCT FROM INVENTORY ---" << RESET << std::endl;

                std::string targetId;
                std::cout << "Enter Product ID to delete: ";
                std::cin.ignore(); // FIX: Added missing ignore to prevent skipping!
                std::getline(std::cin, targetId);

                if (inventoryTree.count(targetId) == 0){
                    std::cout << RED << "Item not found." << RESET << std::endl;
                }
                else {
                    inventoryTree.erase(targetId);
                    inventoryList.remove(targetId);
                    alertManager.removeThreshold(targetId);
                    for (auto it = inventory.begin(); it != inventory.end(); it++) {
                        if (it->getId() == targetId) {
                            inventory.erase(it);
                            break;
                        }
                    }
                    std::cout << GREEN << "Item Deleted." << RESET << std::endl;
                }
                wait();
                break;
            }
            case 9: { // Print In-Order
                clearScreen();
                std::cout << YELLOW << "--- PRINT INVENTORY IN-ORDER BY ID---" << RESET << std::endl;

                inventoryTree.print();

                wait();
                break;
            }
            case 10: { // NEW: Heap Sort by Name
                clearScreen();
                std::cout << "\nSorting inventory alphabetically by product name using Heap Sort..." << std::endl;
                
                heapSortByName(inventory); // Call your new function!
                
                std::cout << GREEN << "Sort Complete. View 'Full Inventory Report' (Option 1) to see results." << RESET << std::endl;
                wait();
                break;
            }
            case 11: { // MOVED: Exit
                std::cout << "Exiting ADK Warehouse Optimizer. Security log closed." << std::endl;
                running = false;
                break;
            }
            default:
                std::cout << RED << "Invalid selection." << RESET << std::endl;
                wait();
                break;
        }
    }

    return 0;
}