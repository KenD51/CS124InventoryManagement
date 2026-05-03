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
    // Fix: Apparently we are using 'thresholds_' instead of threshold. Alright...
    thresholds_[id] = threshold; 
}

int StockAlertManager::getThreshold(const std::string &id) const {
    if(thresholds_.count(id)) {
        return thresholds_.at(id);
    }
    return 0; // Fix: I added return 0 to have a default return value if there is no id.
}

// Pushing checkThresholds logic
std::vector<StockAlert> StockAlertManager::checkThresholds(const std::unordered_map<std::string, int>& currentInventory) const {
    std::vector<StockAlert> alerts;
    
    // Traverse the current inventory map with two quantities, the id of the product and the currently 
    for (const auto& pair : currentInventory) {
        std::string currentId = pair.first;
        int currentQty = pair.second;

        //Get threstholds to find the minimum
        int minThreshold = getThreshold(currentId);
        
        // If a threshold exists and the current stock has fallen below it
        if (minThreshold > 0 && currentQty < minThreshold) {
            // Hey I think the map implementation needs tweaking as I don't have a name in the map. I used pending name as a placeholder.....
            alerts.push_back(StockAlert(currentId, "Pending_Name", currentQty, minThreshold));
        }
    }
    return alerts;
}

