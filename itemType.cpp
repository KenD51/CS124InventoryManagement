#include "itemType.h"

Item::Item(std::string newId, std::string newName, std::string newCategory, int newQuantity, int newMinStockThreshold) {
    id = newId;
    name = newName;
    category = newCategory;
    quantity = newQuantity;
    minStockThreshold = newMinStockThreshold;
}

Item::Item() {
    id = " ";
    name = " ";
    category = " ";
    quantity = 0;
    minStockThreshold = 0;
}

std::string Item::getCategory() const {
    return category;
}

std::string Item::getId() const {
    return id;
}

std::string Item::getName() const {
    return name;
}

int Item::getQuantity() const {
    return quantity;
}

int Item::getMinStockThreshold() const {
    return minStockThreshold;
}
