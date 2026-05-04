#include "restockManager.h"

// --- RestockTask --- //
RestockTask::RestockTask(const std::string &id, const std::string &itemName, int quantityNeeded, int urgencyScore)
    : id(id), itemName(itemName), quantityNeeded(quantityNeeded), urgencyScore(urgencyScore) {}

//Getters and setters for the object.
const std::string &RestockTask::getId() const { return id; }
const std::string &RestockTask::getItemName() const { return itemName; }
int RestockTask::getQuantityNeeded() const { return quantityNeeded; }
int RestockTask::getUrgencyScore() const { return urgencyScore; }

// Operator overlord for comparing urgencies in the priority queue.
bool operator<(const RestockTask& a, const RestockTask& b) {
    return a.getUrgencyScore() < b.getUrgencyScore();
}
// --- Restock Task End --- //

// --- Constructors and Destructos --- //
RestockManager::RestockManager() {}
RestockManager::~RestockManager() {}
// --- Constructors and Destructors END --- //

// --- Restock Manager --- //
bool RestockManager::isEmpty() const {
  return restockQueue_.empty();  // Changed from 'restockQueue' to 'restockQueue_' to match member variable name, Idk why we are using this naming convention.
}

//Urgency is how many items are missing from the target quantity.
int RestockManager::calculateUrgency(const Item &item, int targetQuantity) const {
    return targetQuantity - item.getQuantity();  // Fixed from 'item.getQuantity' to 'item.getQuantity()' to call the method
}

//Restock Task will check if an item needs items, then it calculates the urgency and pushes a new object in the queue with urgency factored in.
void RestockManager::addRestockTask(const Item &item, int targetQuantity) {
    int needed = targetQuantity - item.getQuantity();
    if (needed > 0) {
        int score = calculateUrgency(item, targetQuantity);
        restockQueue_.push(RestockTask(item.getId(), item.getName(), needed, score));  // Changed from 'restockQueue' to 'restockQueue_'
    }
}

//We "process" an object in the queue by peeking at it, then we can pop it.
RestockTask RestockManager::popNextRestockTask() {
    RestockTask topTask = restockQueue_.top();  // Changed from 'restockQueue' to 'restockQueue_'
    restockQueue_.pop();
    return topTask;
}

RestockTask RestockManager::peekNextRestockTask() const{
    return restockQueue_.top();  // Changed from 'restockQueue' to 'restockQueue_'
}

//Traversal will return the current list as a vector.
std::vector<RestockTask> RestockManager::generatePriorityList() const {
    std::vector<RestockTask> list;
    std::priority_queue<RestockTask> temp = restockQueue_;  // Changed from 'std::priorityQueue' to 'std::priority_queue' and 'restockQueue' to 'restockQueue_'

    while(!temp.empty()){
        list.push_back(temp.top());
        temp.pop();
    }

    return list;
}

