#include "stockAlertManager.h"

StockAlert::StockAlert(const std::string &id, const std::string &itemName, int currentQuantity, int threshold) {

}

int StockAlert::getCurrentQuantity() const {

}

const std::string& StockAlert::getId() const {

}

const std::string& StockAlert::getItemName() const {

}

int StockAlert::getThreshold() const {

}

StockAlertManager::StockAlertManager() {

}

StockAlertManager::~StockAlertManager() {

}
std::vector<StockAlert> StockAlertManager::checkThresholds(const std::unordered_map<std::string, int>& currentInventory) const {

}

void StockAlertManager::setMinimumThreshold(const std::string& id, int threshold) {

}

int StockAlertManager::getThreshold(const std::string &id) const {

}
