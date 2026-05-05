cmake_minimum_required(VERSION 3.5)
project(CS124InventoryManagement)

set(CMAKE_CXX_STANDARD 20)

include_directories(include)

# We use src files so we need to adjust the pathing, that was causing the shenanigans
add_executable(CS124InventoryManagement
        src/main.cpp
        src/linkedList.cpp
        src/binarySearchTree.cpp
        src/inventoryLinearSearch.cpp
        src/redBlackTree.cpp
        src/restockManager.cpp
        src/sortingAlgo.cpp
        src/stockAlertManager.cpp
        src/csvFunctions.cpp
        src/itemType.cpp
)
