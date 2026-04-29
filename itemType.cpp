#include "itemType.h"

Item::Item(std::string newId, std::string newName, std::string newDescription, int newQuantity, int newMinStockThreshold) {
    id = newId;
    name = newName;
    description = newDescription;
    quantity = newQuantity;
    minStockThreshold = newMinStockThreshold;
}
