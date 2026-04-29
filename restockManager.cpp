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
  return restockQueue.empty();
}

//Urgency is how many items are missing from the target quantity.
int RestockManager::calculateUrgency(const Item &item, int targetQuantity) const {
    return targetQuantity - item.getQuantity;
}

//Restock Task will check if an item needs items, then it calculates the urgency and pushes a new object in the queue with urgency factored in.
void RestockManager::addRestockTask(const Item &item, int targetQuantity) {
    int needed = targetQuantity - item.getQuantity();
    if (needed > 0) {
        int score = calculateUrgency(item, targetQuantity);
        restockQueue.push(RestockTask(item.getId(), item.getName(), needed, score));
    }
}

//We "process" an object in the queue by peeking at it, then we can pop it.
RestockTask RestockManager::popNextRestockTask() {
    RestockTask topTask = restockQueue.top();
    restockQueue.pop();
    return topTask;
}

RestockTask RestockManager::peekNextRestockTask() const{
    return restockQueue.top();
}

//Traversal will return the current list as a vector.
std::vector<RestockTask> RestockManager::generatePriorityList() const {
    std::vector<RestockTask> list;
    std::priorityQueue<RestockTask> temp = restockQueue;

    while(!temp.empty()){
        list.push_back(temp.top());
        temp.pop();
    }

    return list;
}

