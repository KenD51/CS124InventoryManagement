#ifndef CSV_FUNCTIONS_H
#define CSV_FUNCTIONS_H

#include <vector>
#include <string>
#include "itemType.h"
#include "stockAlertManager.h"

// Parses the provided CSV and populates the inventory vector and alert manager
void loadInventoryFromCSV(const std::string& filename, std::vector<Item>& inventory, StockAlertManager& alertManager);

#endif