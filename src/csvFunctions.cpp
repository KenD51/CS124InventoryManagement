#include "csvFunctions.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <unordered_map>

//Renamed to loadInventoryFromCSV as I want the name to be more intuitive.
void loadInventoryFromCSV(const std::string& filename, std::vector<Item>& inventory, StockAlertManager& alertManager) {
    std::ifstream file(filename);

    // Check if the file was opened successfully
    if (!file.is_open()) {
        std::cerr << "Error: Could not open dataset at " << filename << std::endl;
        return;
    }

    std::string line;
    // Skip the first row since it contains the column headers and fluff
    std::getline(file, line);

    // Keep track of products we have already added to avoid redundant entries. The dataset actually contained items that were already added and i create a map 
    // to ensure we only add each unique product once to our inventory and alert manager.
    std::unordered_map<std::string, bool> processedItems;

    //Read each line of the dataset.
    while (std::getline(file, line)) {
        // Use stringstream to parse the CSV line
        std::stringstream ss(line);

        //We took the most bare bones parts of the dataset that all the datasets have in common, because other datasets have extra parameters and i chose to ignore them
        std::string date, storeId, productId, category, region, invLevelStr;

        // Parse up to the 6th column (Inventory Level) which acts as our current stock quantit. Pull characters unti comma.
        std::getline(ss, date, ',');
        std::getline(ss, storeId, ',');
        std::getline(ss, productId, ',');
        std::getline(ss, category, ',');
        std::getline(ss, region, ',');
        std::getline(ss, invLevelStr, ',');

        // Ignore malformed lines
        if (productId.empty() || invLevelStr.empty()) {
            continue;
        }

        // Add the product if it hasn't been instantiated in our inventory yet, using the productid as identifier and comapre with contents in map
        //WE only add new products.
        if (processedItems.find(productId) == processedItems.end()) {
            int quantity = 0;
            try {
                quantity = std::stoi(invLevelStr);
            } catch (...) {
                continue; // Skip lines where the inventory level can't be parsed
            }

            //This is personal fluff, but because we have category, and product id, I combined them toghether to make it more user friendly
            std::string name = category + " Model " + productId.substr(1); 
            int defaultThreshold = 20; // Set a default threshold for all products. Will work on this tomorrow.
            // Create the item and add it to the inventory and alert manager
            inventory.push_back(Item(productId, name, category, quantity, defaultThreshold));
            alertManager.setMinimumThreshold(productId, defaultThreshold);

            // Mark this product as established
            processedItems[productId] = true;
        }
    }

    file.close();
    std::cout << "Successfully loaded " << inventory.size() << " unique products from CSV." << std::endl;
}