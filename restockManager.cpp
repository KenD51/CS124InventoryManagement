#include "restockManager.h"

RestockTask::RestockTask(const std::string &id, const std::string &itemName, int quantityNeeded, int urgencyScore) {

}
const std::string &RestockTask::getId() const {

}
const std::string &RestockTask::getItemName() const {

}
int RestockTask::getQuantityNeeded() const {

}
int RestockTask::getUrgencyScore() const {

}

RestockManager::RestockManager() {

}
RestockManager::~RestockManager() {

}
bool RestockManager::isEmpty() const {

}
int RestockManager::calculateUrgency(const Item &item, int targetQuantity) const {

}
void RestockManager::addRestockTask(const Item &item, int targetQuantity) {

}
RestockTask RestockManager::popNextRestockTask() {

}
RestockTask RestockManager::peekNextRestockTask() const{

}
std::vector<RestockTask> RestockManager::generatePriorityList() const {

}

