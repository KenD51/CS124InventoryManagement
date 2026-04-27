#ifndef RESTOCK_MANAGER_H
#define RESTOCK_MANAGER_H

#include "ItemTypes.h"
#include <vector>
#include <queue>
#include <string>

/**
 * @brief Represents a task for restocking an item. Each RestockTask includes the product ID,
 * item name, quantity needed to reach the target stock level, and an urgency score for prioritization.
 * The urgency score can be calculated based on factors
 * such as how far below the target stock level the current quantity is,
 * how critical the item is to operations, and how quickly it can be restocked.
 * 
 */
class RestockTask {
    private:
        std::string id;
        std::string itemName;
        int quantityNeeded;
        int urgencyScore; // Higher score indicates higher priority
    public:
        // Constructor to initialize all member variables of RestockTask.
        RestockTask(const std::string& id, const std::string& itemName, int quantityNeeded, int urgencyScore);
        // Getters for RestockTask member variables.
        const std::string& getId() const;
        const std::string& getItemName() const;
        int getQuantityNeeded() const;
        int getUrgencyScore() const;
};

/**
 * @class RestockManager
 * @brief Manages a priority queue to determine the optimal sequence for restocking items.
 */
class RestockManager {

private:
    // Priority queue to rank the restocking tasks by urgencyScore
    std::priority_queue<RestockTask> restockQueue_;
    
    /**
     * @brief Helper function to calculate an item's urgency score. the priority is how low the current stock is compared to the target quantiy.
     */
    int calculateUrgency(const Item& item, int targetQuantity) const;

public:
    // Constructor and Destructor
    RestockManager();
    ~RestockManager();

    /**
     * @brief Calculates urgency and adds an item to the restocking priority queue. 
     * This is pretty much just adding a task to the priorit queue, but we will use the helper above to calculate the urgency score. 
     * @param item The item that requires restocking.
     * @param targetQuantity The ideal stock level to reach.
     */
    void addRestockTask(const Item& item, int targetQuantity);

//Here we have the functions to manage the priority queue, pop, peek, traverse, and check if empty.

    /**
     * @brief Retrieves and removes the highest priority restock task from the queue. Tnis is for when we are ready to process the next restock task.
     * @return The most urgent RestockTask.
     */
    RestockTask popNextRestockTask();

    /**
     * @brief Peeks at the most urgent task without removing it. For checking what the next restock task is.
     * @return The most urgent RestockTask.
     */
    RestockTask peekNextRestockTask() const;

    /**
     * @brief Generates a sequential list of all pending restock tasks in order of priority. 
     * This is for when we want to see all the pending restock tasks in order of urgency.
     * @return A vector of tasks sorted from highest to lowest urgency.
     */
    std::vector<RestockTask> generatePriorityList() const;

    /**
     * @brief Checks if there are any pending restock tasks. Most likely just used to check if the priority queue is empty.
     * @return True if the priority queue is empty, false otherwise.
     */
    bool isEmpty() const;
};

#endif // RESTOCK_MANAGER_H