cmake_minimum_required(VERSION 3.5)
project(CS124InventoryManagement)

set(CMAKE_CXX_STANDARD 20)


add_executable(CS124InventoryManagement
        linkedList.h
        main.cpp
        itemType.h
        restockManager.h
        inventoryLinearSearch.h
        stockAlertManager.h
        main.cpp)
