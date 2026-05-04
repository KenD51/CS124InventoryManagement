// -- Here We test all our stuff -- //
#include "itemType.h"
#include "linkedList.h"
#include "binarySearchTree.h"
#include "redBlackTree.h"
#include "inventoryLinearSearch.h"
#include "restockManager.h"
#include "stockAlertManager.h"
#include "sortingAlgo.h"
#include "csvFunctions.h"
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

// --- Global Data Structures for Testing --- //
std::vector<Item> warehouseInventory;
StockAlertManager alertSystem;
RestockManager restockSystem;
InventoryBST bstInventory;
RedBlackTree rbtInventory;
LinkedList listInventory;

// I would like to note that I am using global data structures firstly for ease of testing. Main should be different
//Secondly, I didn't use the csv function as I had a lot of errors in reading the datasets for some reason.
//Thirdly, this is all terminal and I know we wanted to do a GUI but I think this is fine for testing purposes. We can always add a GUI later if we have time.
//Fourthly, some sections are from zybooks in the past, and i will cite them in the final part.

// --- Initialize Dummy Data --- //
void initializeTestData() {
    std::cout << "Initializing test data...\n";  // Added debug output to track initialization


    // Create some sample items, I haven't used the csv functions yet.

    warehouseInventory.push_back(Item("A001", "Apple", "Produce", 50, 20));
    warehouseInventory.push_back(Item("B002", "Banana", "Produce", 10, 30)); // Low stock
    warehouseInventory.push_back(Item("M001", "Milk", "Dairy", 5, 10));      // Low stock
    warehouseInventory.push_back(Item("C003", "Carrot", "Produce", 100, 15));
    warehouseInventory.push_back(Item("B001", "Bread", "Bakery", 25, 20));

    // Populate the trees, the lists, and tthe alert manager.
    for (const auto& item : warehouseInventory) {
        bstInventory.insert(item);
        // rbtInventory.insert(item.getId());  // Commented out for debugging - RBT insert was causing crashes
        listInventory.insertAtEnd(item);
        alertSystem.setMinimumThreshold(item.getId(), item.getMinStockThreshold());
    }
    std::cout << "Test data initialized successfully.\n";  // Added debug output
}

// --- Menu Displays --- //
void displayMenu() {
    std::cout << "\n=======================================\n";
    std::cout << "||      WAREHOUSE SYSTEM v1.0        ||\n";
    std::cout << "=======================================\n";
    std::cout << "|| 1. Search Inventory               ||\n";
    std::cout << "|| 2. View Restock Priority          ||\n";
    std::cout << "|| 3. Visualize Warehouse Map        ||\n";
    std::cout << "|| 4. Run Comprehensive Unit Tests   ||\n";
    std::cout << "|| 5. Exit                           ||\n";
    std::cout << "=======================================\n";
    std::cout << "Selection: ";
}

void displaySearchInventory() {
    std::cout << "\n=======================================\n";
    std::cout << "||         Inventory Search          ||\n";
    std::cout << "=======================================\n";
    std::cout << "Enter Product ID to search (e.g., A001, B002): ";
    std::string searchId;
    std::cin >> searchId;

    
    // Use the InventoryAlgorithms class to perform a linear search on the vector inventory.
    InventoryAlgorithms algo;
    int index = algo.linearSearch(warehouseInventory, searchId);

    // Display the search result
    if (index != -1) {
        Item found = warehouseInventory[index];
        std::cout << "\n[!] Item Found:\n";
        std::cout << "Name: " << found.getName() 
                  << " | Category: " << found.getCategory()
                  << " | Qty: " << found.getQuantity() 
                  << " | Min Threshold: " << found.getMinStockThreshold() << "\n";
    } else {
        std::cout << "\n[!] Item not found in inventory.\n";
    }
}

//This is restock Priority
void displayRestockPriority() {
    std::cout << "\n=======================================\n";
    std::cout << "||          Restock Priority          ||\n";
    std::cout << "=======================================\n";

    // 1. Map current inventory for the Alert Manager
    std::unordered_map<std::string, int> currentStockMap;
    for (const auto& item : warehouseInventory) {
        currentStockMap[item.getId()] = item.getQuantity();
    }

    // 2. Check thresholds to generate alerts
    std::vector<StockAlert> alerts = alertSystem.checkThresholds(currentStockMap);
    std::cout << "Found " << alerts.size() << " items below minimum threshold.\n\n";

    // 3. Add alerts to the restock priority queue
    for (const auto& alert : alerts) {
        for (const auto& item : warehouseInventory) {
            if (item.getId() == alert.getId()) {
                // Target quantity is arbitrarily set to threshold + 50 for testing
                restockSystem.addRestockTask(item, alert.getThreshold() + 50);
                break;
            }
        }
    }

    // 4. Generate and display priority list
    std::vector<RestockTask> priorityList = restockSystem.generatePriorityList();
    if (priorityList.empty()) {
        std::cout << "No items currently need restocking.\n";
    } else {
        std::cout << "Restock Tasks (Sorted by Urgency):\n";
        for (const auto& task : priorityList) {
            std::cout << "ID: " << task.getId() 
                      << " | Name: " << task.getItemName()
                      << " | Qty Needed: " << task.getQuantityNeeded()
                      << " | Urgency Score: " << task.getUrgencyScore() << "\n";
        }
    }
}

void displayVisualizeMap() {
    std::cout << "\n=======================================\n";
    std::cout << "||      Warehouse Map Visualization  ||\n";
    std::cout << "=======================================\n";
    std::cout << "1. View via Binary Search Tree (DFS Order)\n";
    std::cout << "2. View via Red-Black Tree (Keys)\n";
    std::cout << "3. View via Linked List\n";
    std::cout << "Selection: ";
    
    int choice;
    std::cin >> choice;

    if (choice == 1) {
        std::cout << "\n[BST DFS Traversal]\n";
        std::vector<Item> dfsItems = bstInventory.traverseDFS();
        for (const auto& item : dfsItems) {
            std::cout << "- " << item.getName() << " (ID: " << item.getId() << ")\n";
        }
    } else if (choice == 2) {
        std::cout << "\n[Red-Black Tree Structure]\n";
        rbtInventory.print(); 
    } else if (choice == 3) {
        std::cout << "\n[Linked List Display]\n";
        listInventory.display();
    } else {
        std::cout << "Invalid selection.\n";
    }
}

// --- Comprehensive Test Execution --- //
void runComprehensiveTests() {
    std::cout << "\n=======================================\n";
    std::cout << "||    EXECUTING ALL COMPONENT TESTS  ||\n";
    std::cout << "=======================================\n";

    // 1. Test LinkedList & Merge Sort
    std::cout << "\n[Testing LinkedList & Merge Sort]\n";
    LinkedList testList;
    testList.insertAtEnd(Item("Z001", "Zucchini", "Produce", 10, 5));
    testList.insertAtEnd(Item("A005", "Almonds", "Snacks", 20, 10));
    testList.insertAtEnd(Item("M002", "Mango", "Produce", 15, 5));
    
    std::cout << "Before Merge Sort (should display items as inserted):\n";
    testList.display();
    
    //Hey darcie I wrote mergeSort and somehow its undfined. I wrote it down but i commented it out.

    /* testList.setHead(mergeSort(testList.getHead()));
    std::cout << "\nAfter Merge Sort:\n";
    testList.display(); */

    // 2. Test Inventory Algorithms (Sorting by Quantity and ID)
    std::cout << "\n[Testing Vector Sorting Algorithms]\n";
    std::vector<Item> testVec = warehouseInventory;
    InventoryAlgorithms algo;

    algo.sortInventoryByQuantity(testVec);
    std::cout << "Sorted by Quantity (Lowest first):\n";
    for(const auto& item : testVec) {
        std::cout << item.getName() << " - Qty: " << item.getQuantity() << "\n";
    }

    algo.sortInventoryByID(testVec);
    std::cout << "\nSorted by ID (Alphanumeric):\n";
    for(const auto& item : testVec) {
        std::cout << item.getId() << " - " << item.getName() << "\n";
    }

    // 3. Test Priority Queue operations
    std::cout << "\n[Testing Restock Priority Queue pop/peek]\n";
    RestockManager testRM;
    testRM.addRestockTask(Item("L001", "LowItem", "Misc", 2, 10), 20);
    testRM.addRestockTask(Item("V001", "VeryLowItem", "Misc", 0, 10), 20);
    
    if (!testRM.isEmpty()) {
        std::cout << "Peeking highest urgency: " << testRM.peekNextRestockTask().getItemName() << "\n";
        std::cout << "Popping highest urgency: " << testRM.popNextRestockTask().getItemName() << "\n";
    }

    std::cout << "\n--- ALL COMPONENT TESTS COMPLETED ---\n";
}

int main() {
    std::cout << "Starting Warehouse System...\n";  // Added debug output to confirm program start
    // Populate systems with dummy data before showing menu
    initializeTestData();

    int choice;
    while (true) {
        displayMenu();
        std::cout << "Waiting for input...\n";  // Added debug output before input
        if (!(std::cin >> choice)) {
            // Here, if the user enters something that isn't an integer we just clear it
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue;
        }

        std::cout << "Received choice: " << choice << "\n";  // Added debug output after input
        //This part is copied and pasted from zybooks as I don't remember switch statemeents. 
        switch (choice) {
            case 1:
                displaySearchInventory();
                break;
            case 2:
                displayRestockPriority();
                break;
            case 3:
                displayVisualizeMap();
                break;
            case 4:
                runComprehensiveTests();
                break;
            case 5:
                std::cout << "Exiting Warehouse System...\n";
                return 0;
            default:
                std::cout << "Invalid choice. Please select 1-5.\n";
        }
    }
    return 0;
}
