#include <iostream>
#include <vector>
#include <string>
#include <iomanip>


#include "itemType.h"              
#include "sortingAlgo.h"           
#include "stockAlertManager.h"     
#include "restockManager.h"        
#include "inventoryLinearSearch.h" 

// Color Codes for professional terminal output. I define the colors here by their ANSI 
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define CYAN    "\033[36m"

// UI Helper Functions to clear the screen to make it look more professional.
void clearScreen() {
#ifdef _WIN32 // Windows
    system("cls");  // Clear the console on Windows
#else
    system("clear");    // Clear the console on Unix/Linux/Mac
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

//Wait for user input to return to the main menu after the operation.
void wait() {
    std::cout << "\n" << CYAN << "Press Enter to return to main menu..." << RESET;
    std::cin.ignore(100, '\n');
    std::cin.get();
}

// Hardcoded Data Initialization
void initializeInventory(std::vector<Item>& inventory, StockAlertManager& alertManager) {
    // Creating a diverse dataset for testing all algorithms
    // Arguments: ID, Name, Category, Quantity, MinStockThreshold
    inventory.push_back(Item("101", "Laptop Pro", "Electronics", 5, 10)); // Low stock
    inventory.push_back(Item("102", "Office Chair", "Furniture", 25, 5));
    inventory.push_back(Item("103", "Mechanical Keyboard", "Electronics", 12, 15)); // Low stock
    inventory.push_back(Item("104", "Desk Lamp", "Furniture", 40, 10));
    inventory.push_back(Item("105", "4K Monitor", "Electronics", 8, 5));
    
    // Set thresholds in alert manager
    for (const auto& item : inventory) {
        alertManager.setMinimumThreshold(item.getId(), item.getMinStockThreshold());
    }
}

int main() {

    // Main inventory vector and manager instances
    std::vector<Item> inventory;
    StockAlertManager alertManager;
    RestockManager restockManager;
    InventoryAlgorithms searchAlgo;
    
    //Initialize inventory, but this is hardcoded for testing purposes.
    initializeInventory(inventory, alertManager);

    // Main loop for the dashboard interface
    bool running = true;
    while (running) {
        clearScreen(); //We clean terminal 
        displayLogo(); 

        std::cout << YELLOW << "[ MAIN DASHBOARD ]" << RESET << std::endl;
        std::cout << "1. View Full Inventory Report" << std::endl;
        std::cout << "2. Search for Product" << std::endl;
        std::cout << "3. Run Stock Alert Audit" << std::endl;
        std::cout << "4. Sort by Quantity" << std::endl;
        std::cout << "5. Generate Restocking List" << std::endl;
        std::cout << "6. Exit System" << std::endl;
        std::cout << "\nSelect an operation: ";

        //Input validation for what the user selects in the menu and ignore invalid input.
        int choice;
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(100, '\n'); // Clear the error state and ignore invalid input
            std::cout << RED << "Invalid input. Please enter a number corresponding to the menu" << RESET << std::endl;
            continue;
        }

        //Zybooks code from like old stuff from my previous classes.
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
                
                // Display each item in the inventory
                for (const auto& item : inventory) {
                    std::cout << std::left << std::setw(10) << item.getId()
                              << std::setw(25) << item.getName()
                              << std::setw(15) << item.getCategory()
                              << std::setw(10) << item.getQuantity()
                              << std::setw(10) << item.getMinStockThreshold() << std::endl;
                }
                wait(); // Wait for user input before returning to menu
                break; // We break after each case to return to the main menu after the operation is complete.
            }
            case 2: { // Linear Search
                std::string target;
                std::cout << "\nEnter exact Product ID to locate: ";
                std::cin.ignore();
                std::getline(std::cin, target);
                
                // Perform linear search using the InventoryAlgorithms class, display the contents if gound.
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
                
                // Create a map of inventory for the alert manager
                std::unordered_map<std::string, int> currentInventory;
                for (const auto& item : inventory) {
                    currentInventory[item.getId()] = item.getQuantity();
                }
                
                // Check thresholds, which will return a vector of items below min stocks.
                std::vector<StockAlert> alerts = alertManager.checkThresholds(currentInventory);
                
                // Display results in a table format. If there are no alerts, display a message indicating all items are above threshold.
                if (alerts.empty()) {
                    std::cout << GREEN << "All items are above minimum threshold levels." << RESET << std::endl;
                } else {
                    std::cout << RED << "Low stock items detected:\n" << RESET << std::endl;
                    std::cout << std::left << std::setw(10) << "ID" 
                              << std::setw(25) << "Product Name" 
                              << std::setw(15) << "Current Qty" 
                              << std::setw(10) << "Threshold" << std::endl;
                    std::cout << std::string(70, '-') << std::endl;
                    
                    // Display each alert in the vector
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
                
                // Generate restock tasks for items below target quantity
                int targetQuantity = 20; // Target stock level
                for (const auto& item : inventory) {
                    restockManager.addRestockTask(item, targetQuantity);
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
            case 6: { //Literal meme button make sure to delete this before committing, heheheha
                std::cout << "::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n"
                          << "::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n"
                          << "::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n"
                          << "::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n"
                          << "::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n"
                          << ":::::::::::::::::::::::::::::::::::::::-=*%@@@@%%%%%%###***=::::::::::::::::::::::::::::::::::::::::\n"
                          << "::::::::::::::::::::::::::::::::::-#@@@@@@@@@@@@@@@@@@@@@@@@@@@%=::::::::::::::::::::::::::::::::::\n"
                          << ":::::::::::::::::::::::::::::::+@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@%=:::::::::::::::::::::::::::::::\n"
                          << "::::::::::::::::::::::::::::=%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*:::::::::::::::::::::::::::::\n"
                          << "::::::::::::::::::::::::::+@@@@@@@@@@@@@@@@%##********###%@@@@@@@@@@@@@=:::::::::::::::::::::::::::\n"
                          << "::::::::::::::::::::::::#@@@@@@@@@@@@@%**++++++++++++++++++++*%@@@@@@@@@+::::::::::::::::::::::::::\n"
                          << "::::::::::::::::::::::#@@@@@@@@@@@%*++++++++++++++++++++++++++++*@@@@@@@@+:::::::::::::::::::::::::\n"
                          << "::::::::::::::::::::+@@@@@@@@@@#++++++++++++++++++++++++++++++++++*@@@@@@@=::::::::::::::::::::::::\n"
                          << ":::::::::::::::::::%@@@@@@@@@%*++++++++++++++++++++++++++++++++++++*%@@@@@@-:::::::::::::::::::::::\n"
                          << "::::::::::::::::::@@@@@@@@@%*+++++++++++++++++++++++++++++++++++++++*@@@@@@%:::::::::::::::::::::::\n"
                          << ":::::::::::::::::#@@@@@@@@@@@@@@@@@@@@@@@@@%%#**+++++++++++++++++++++#@@@@@@#::::::::::::::::::::::\n"
                          << "::::::::::::::::-@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@%*++++++++++++++++*%@@@@@@=:::::::::::::::::::::\n"
                          << ":::::::::::::::+@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@%*+++++++++++++*#@@@@@@%:::::::::::::::::::::\n"
                          << ":::::::::::::#@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@#+++++++++++++#%@@@@@@-::::::::::::::::::::\n"
                          << ":::::::::::+@@@@@@@@@@*=----:::::::::---------*%%@@@@@@@@%++++++++++++*#@@@@@@*::::::::::::::::::::\n"
                          << "::::::::::%@@@@@@@%=--:.....        ..:---------*###@@@@@@%*++++++++++*#%@@@@@@::::::::::::::::::::\n"
                          << ":::::::::%@@@@@@#--:........        ...:---------####@@@@@@%++++++++++*##@@@@@@-:::::::::::::::::::\n"
                          << "::::::::#@@@@@@---:..    . ..... .. ...----------#####@@@@@@#+++++++++*##@@@@@@+:::::::::::::::::::\n"
                          << ":::::::+@@@@@#-----...............:::-----------=#####@@@@@@#++++++++++##%@@@@@%++==-:::::::::::::\n"
                          << ":::::::%@@@@@:----------------------------------######@@@@@@#++++++++++###@@@@@@@@@@@@@@@%*=::::::\n"
                          << "::::::-@@@@@%=--------------------------------=#######@@@@@@#++++++++++*##%@@@@@@@@@@@@@@@@@@#::::\n"
                          << "::::::+@@@@@%##=----------------------------=#########@@@@@@#++++++++++*##%@@@@@@@@@@@@@@@@@@@%:::\n"
                          << "::::::=@@@@@@###########***+++====-===+**############%@@@@@@*++++++++++*##%@@@@@%+*****#@@@@@@@+:::\n"
                          << ":::::::@@@@@@@######################################@@@@@@@#+++++++++++*##%@@@@@@++++++++#@@@@@%:::\n"
                          << ":::::::*@@@@@@@%###################################@@@@@@@%++++++++++++###%@@@@@@+++++++++@@@@@@+::\n"
                          << "::::::::%@@@@@@@@%###############################%@@@@@@@%+++++++++++++###%@@@@@@*++++++++%@@@@@#::\n"
                          << ":::::::::%@@@@@@@@@@@%#########################@@@@@@@@@#+++++++++++++*###%@@@@@@*****++++*@@@@@@::\n"
                          << "::::::::::*@@@@@@@@@@@@@@@@%###############%@@@@@@@@@@@*++++++++++++++*###%@@@@@@%########*@@@@@@-:\n"
                          << ":::::::::::+@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*++++++++++++++++####%@@@@@@%#########@@@@@@=:\n"
                          << ":::::::::::*@@@@@@%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@#*+++++++++++++++++++#####@@@@@@%#########@@@@@@*:\n"
                          << ":::::::::::*@@@@@@*+++*#%@@@@@@@@@@@@@@@@@@%#*+++++++++++++++++++++++*#####@@@@@@@#########%@@@@@%:\n"
                          << ":::::::::::#@@@@@@+++++++++++********++++++++++++++++++++++++++++++++######@@@@@@@#########%@@@@@@:\n"
                          << ":::::::::::#@@@@@%++++++++++++++++++++++++++++++++++++++++++++++++++*######@@@@@@@#########%@@@@@@-:\n"
                          << ":::::::::::#@@@@@#++++++++++++++++++++++++++++++++++++++++++++++++++*######@@@@@@@#########%@@@@@@-:\n"
                          << ":::::::::::#@@@@@%+++++++++++++++++++++++++++++++++++++++++++++++++*#######@@@@@@@##########@@@@@@=:\n"
                          << ":::::::::::#@@@@@#*++++++++++++++++++++++++++++++++++++++++++++++++########@@@@@@@##########@@@@@@=:\n"
                          << ":::::::::::%@@@@@#*+++++++++++++++++++++++++++++++++++++++++++++++*########@@@@@@@##########@@@@@@+:\n"
                          << ":::::::::::%@@@@@##*++++++++++++++++++++++++++++++++++++++++++++++#########@@@@@@%##########@@@@@@*:\n"
                          << ":::::::::::%@@@@@##*+++++++++++++++++++++++++++++++++++++++++++++*#########@@@@@@%##########@@@@@@*:\n"
                          << ":::::::::::%@@@@@###*+++++++++++++++++++++++++++++++++++++++++++*##########@@@@@@%##########@@@@@@#:\n"
                          << ":::::::::::#@@@@@####++++++++++++++++++++++++++++++++++++++++++*###########@@@@@@%##########@@@@@@#:\n"
                          << ":::::::::::#@@@@@#####*+++++++++++++++++++++++++++++++++++++++*############@@@@@@%##########@@@@@@#:\n"
                          << ":::::::::::*@@@@@######*+++++++++++++++++++++++++++++++++++++*############%@@@@@@%##########@@@@@@+:\n"
                          << ":::::::::::+@@@@@%#######+++++++++++++++++++++++++++++++++++##############%@@@@@@##########%@@@@@@=:\n"
                          << ":::::::::::=@@@@@@#########*++++++++++++++++++++++++++++**################%@@@@@@##########%@@@@@@-:\n"
                          << ":::::::::::-@@@@@@##############****++++++++********######################%@@@@@@##########%@@@@@%::\n"
                          << "::::::::::::%@@@@@%#######################################################%@@@@@@##########@@@@@@=::\n"
                          << "::::::::::::#@@@@@@#######################################################%@@@@@@##########@@@@@%:::\n"
                          << "::::::::::::=@@@@@@#######################################################%@@@@@@#########@@@@@@+:::\n"
                          << ":::::::::::::@@@@@@%######################################################%@@@@@@#######%@@@@@@#::::\n" << std::endl;
                wait(); 
                running = false;
                break;
            }
            case 7: { // Exit
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