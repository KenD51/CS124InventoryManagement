#include "inventoryLinearSearch.h"

InventoryAlgorithms::InventoryAlgorithms() {
  
}

InventoryAlgorithms::~InventoryAlgorithms() {

}

int InventoryAlgorithms::linearSearch(const std::vector<Item>& inventory, const std::string& targetId) {
  for (int i = 0; i < inventory.size(); i++) {
    if (inventory[i] == targetId) {
      return i; // return index if found
    }
    return -1; // return -1 if not found
}

void InventoryAlgorithms::sortInventoryByID(std::vector<Item>& inventory) {
  mergeSort(inventory); // Still figuring out how to isolate ID
}

void InventoryAlgorithms::sortInventoryByQuantity(std::vector<Item>& inventory) {
  mergeSort(inventory); // Still figuring out how to isolate by quantity
}
