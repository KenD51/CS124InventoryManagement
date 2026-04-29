#ifndef STOCK_ALERT_MANAGER_H
#define STOCK_ALERT_MANAGER_H

#include "itemType.h" //This is the base header for the ProductID type and other item-related definitions
#include <vector>
#include <string>
#include <unordered_map>

//IDE has created much of the comments here for the header, and is subject to change.

/**
 * @brief Represents an alert for an item that has fallen below its threshold. StockAlert constructor
 * contains the product ID, item name, current quantity, and the threshold that was breached.
 */
class StockAlert {
    private:
        std::string id; // Unique identifier for the product
        std::string itemName;
        int currentQuantity;   // Current quantity of the item in stock
        int threshold;  // Minimum acceptable quantity before an alert is triggered
    public:
        // Constructor, initializes all member vatiables to create the Stockalert class.
        StockAlert(const std::string& id, const std::string& itemName, int currentQuantity, int threshold);
        // Getters
        const std::string& getId() const;
        const std::string& getItemName() const;
        int getCurrentQuantity() const;
        int getThreshold() const;
};

/**
 * @class stockAlertManager
 * @brief Monitors inventory levels and generates alerts for low stock.
 */
class StockAlertManager {

private:
    // Map of ProductIDs to their respective minimum stock thresholds. Simply put, we 
    // can use this map to create a "database" and check if a product(key) is below its threshold by comparing it to the current inventory.
    std::unordered_map<std::string, int> thresholds_;
public:
    // Constructor and Destructor
    StockAlertManager();
    ~StockAlertManager();

    /**
     * @brief Updates or sets the minimum stock threshold for a specific product. Self explanatoy.
     * @param id The unique identifier of the product. This is usually a string!
     * @param threshold The minimum acceptable quantity before an alert is triggered.
     */
    void setMinimumThreshold(const std::string& id, int threshold);

    /**
     * @brief Scans the current inventory map and returns a list of ALL items below their threshold. We will most likely traverse 
     * // the current inventory in the map and compare each product's quantity to its corresponding threshold in the thresholds_ map. 
     * @param currentInventory A map of ProductIDs to their current quantities.
     * @return A vector of StockAlert objects detailing the low stock items.
     */

    std::vector<StockAlert> checkThresholds(const std::unordered_map<std::string, int>& currentInventory) const;

    /**
     * @brief Retrieves the current threshold for a specific product.
     * @param id The unique identifier of the product.
     * @return The minimum stock threshold, or 0 if not set.
     */
    int getThreshold(const std::string& id) const;


};

#endif // STOCK_ALERT_MANAGER_H