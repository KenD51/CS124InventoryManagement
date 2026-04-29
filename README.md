# CS124 Inventory Management 

# Inventory + Warehouse Optimization System
  Team members: Aaron, Kenshin, Darcie
  
Project Overview
The Inventory + Warehouse Optimization System is a software application designed to manage products in a warehouse, track inventory levels, and improve the efficiency of item retrieval and restocking. 
The system simulates real warehouse operations by organizing item data, prioritizing tasks, and optimizing routes for workers or automated systems.
This project demonstrates how data structures and algorithms can be used to solve practical logistics and supply chain problems.

# Features

- add, remove, and update inventory items
- track item quantities and storage locations
- search for products by name, ID, or category (Started)
- alert when items fall below a minimum stock threshold
- generate restocking priority lists
- optimize item-picking order for customer orders
- simulate warehouse layout as a graph of locations
- display shortest path to collect multiple items
- support category-based or aisle-based organization
  
# Data Structures Used

1. Hash map / unordered_map :Used for fast lookup of items by product ID or name.
2. Vector: Used to store lists of products, orders, or route sequences.
3. Priority queue: Used to prioritize restocking tasks or urgent orders.
4. Graph: Used to model warehouse layout.
5. Set: Used to track visited locations or unique product categories.

# MUST IMPLEMENT
- Sorting Algorithm to sort products and inventory (Started, Source, Merge)
- Ensure it is linear or binary (Started)
- Linked List - This is itemType, each product can be a linked list of all the attributes (Started, Source)
- Hash map (Done)
- Binary/search tree = hierarchy of items. Must implement BFS or DFS
- File reader for CSV (Started)

#Header Files we need
- Binary Search tree - BFS or DFS
- Sorting algorithm (Started)
- Linear Search
- Linked List/Node (Started)
- [OPTIONAL] Possibly graphs. Directional?

# Updates 4/28
- Added Merge Sorting Algorithm (WIP) (Header & Source included) (Darcie)
- Started Linked List (Header, some source) (Kenshin)
- Started on BST (Header, some source) (Kenshin)
- Starting implemenetation of RBT (Aaron)
- CSV Readers started (Aarom)

# Algorithms Used
- Shortest path algorithm: Dijkstra’s algorithm. Used to find the fastest or shortest path through the warehouse to collect items.
- Greedy algorithm: Used to determine a practical picking order or restocking sequence.
- Sorting: Used to rank items by: quantity, urgency, popularity, reorder priority
- Search algorithms: Used to find matching products quickly by keyword or ID.

# Division of Labor

 Darcie: Modular Testing + User Testing

 Aaron:  Modular Testing + User Testing

Kenshin: Modular Testing + User Testing


