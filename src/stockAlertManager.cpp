#include "stockAlertManager.h"

// --- StockAlert Implementation ---
StockAlert::StockAlert(const std::string &id, const std::string &itemName, int currentQuantity, int threshold) 
    : id(id), itemName(itemName), currentQuantity(currentQuantity), threshold(threshold) {}

int StockAlert::getCurrentQuantity() const { return currentQuantity; } // Spelling error here.
const std::string& StockAlert::getId() const { return id; }
const std::string& StockAlert::getItemName() const { return itemName; }
int StockAlert::getThreshold() const { return threshold; }

// --- StockAlertManager Implementation ---
StockAlertManager::StockAlertManager() {}
StockAlertManager::~StockAlertManager() {}

void StockAlertManager::setMinimumThreshold(const std::string& id, int threshold) {
    minimumThresholds[id] = threshold; 
}

int StockAlertManager::getThreshold(const std::string &id) const {
    if(minimumThresholds.count(id)) {
        return minimumThresholds.at(id);
    }
    return 0; // Fix: I added return 0 to have a default return value if there is no id.
}

void StockAlertManager::removeThreshold(const std::string& productId) {
    minimumThresholds.erase(productId);
}

// Pushing checkThresholds logic
std::vector<StockAlert> StockAlertManager::checkThresholds(const std::unordered_map<std::string, int>& currentInventory, const std::unordered_map<std::string, std::string>& itemNames) const {
    std::vector<StockAlert> alerts;
    
    // Traverse the current inventory map with two quantities, the id of the product and the currently 
    for (const auto& pair : currentInventory) {
        std::string currentId = pair.first;
        int currentQty = pair.second;

        //Get threstholds to find the minimum
        int minThreshold = getThreshold(currentId);
        
        // If a threshold exists and the current stock has fallen below it
        if (minThreshold > 0 && currentQty < minThreshold) {
            // Get the item name from the itemNames map
            std::string name;
            if (itemNames.count(currentId)) {
                name = itemNames.at(currentId);
            } else {
                name = "Unknown";
            }
            alerts.push_back(StockAlert(currentId, name, currentQty, minThreshold));
        }
    }
    return alerts;
}

