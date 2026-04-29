#include "csvFunctions.h"
#include "linkedList.h"
#include "itemType.h"
#include "redBlackTree.h"
#include <iostream>
#include <fstream>
#include <ostream>
#include <sstream>
#include <string>

bool loadFromFile(const std::string& filename, LinkedList& inventoryList, RedBlackTree& inventoryTree) {
    std::ifstream inFile(filename);
    std::string line;

    if (!inFile.is_open()) {
        std::cout << "Error opening file!" << std::endl;
        return false;
    }

    std::getline(inFile, line); // skip header

    while (std::getline(inFile, line)) {
        if (line.empty()) {
            continue;
        }
        std::stringstream ss(line);

        std::string id;
        std::string name;
        std::string category;
        std::string quantityString;
        std::string minStockThresholdString;

        std::getline(ss, id, ',');
        std::getline(ss, name, ',');
        std::getline(ss, category, ',');
        std::getline(ss, quantityString, ',');
        std::getline(ss, minStockThresholdString, ',');

        if (!minStockThresholdString.empty() && minStockThresholdString.back() == '\r') {
            minStockThresholdString.pop_back();
        }
        if (!name.empty() && name.front() == ' ') {
            name.erase(0, name.find_first_not_of(' '));
        }
        if (!category.empty() && category.front() == ' ') {
            category.erase(0, category.find_first_not_of(' '));
        }
        if (!quantityString.empty() && quantityString.front() == ' ') {
            quantityString.erase(0, quantityString.find_first_not_of(' '));
        }
        if (!minStockThresholdString.empty() && minStockThresholdString.front() == ' ') {
            minStockThresholdString.erase(0, minStockThresholdString.find_first_not_of(' '));
        }
        if (id.empty()|| name.empty() || category.empty() || quantityString.empty()|| minStockThresholdString.empty()) {
            continue;
        }
        int quantity = std::stoi(quantityString);
        int minStockThreshold = std::stoi(minStockThresholdString);

        Item item(id, name, category, quantity, minStockThreshold);
        inventoryList.insertAtEnd(item);
        inventoryTree.insert(id);

    }

    inFile.close();
    return true;
}


std::string getFilename() {
    std::string filename;
    std::cout << "Please enter the name of the file you'd like to load: ";
    std::cin >> filename;
    return filename;
}