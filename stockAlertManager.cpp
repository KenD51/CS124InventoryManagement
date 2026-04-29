#include "stockAlertManager.h"

// --- StockAlert Implementation ---

StockAlert::StockAlert(const std::string &id, const std::string &itemName, int currentQuantity, int threshold) 
    : id(id), itemName(itemName), currentQuantity(currentQuantity), threshold(threshold) {}

int StockAlert::getCurrentQuantity() const {
  return CurrentQuantity;
}

const std::string& StockAlert::getId() const {
  return id;
}

const std::string& StockAlert::getItemName() const {
  return itemName;
}

int StockAlert::getThreshold() const {
  return threshold;
}

// --- StockAlertManager Implementation ---
StockAlertManager::StockAlertManager() {}
StockAlertManager::~StockAlertManager() {}

void StockAlertManager::setMinimumThreshold(const std::string& id, int threshold) {
    thresholds[id] = thresholds;
}

int StockAlertManager::getThreshold(const std::string &id) const {
    if(thresholds.count(id))
    {
        return thresholds.at(id);
    }
}

std::vector<StockAlert> StockAlertManager::checkThresholds(const std::unordered_map<std::string, int>& currentInventory) const {
}


