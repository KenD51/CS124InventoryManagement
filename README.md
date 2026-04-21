# CS124 Inventory Management 

# Inventory + Warehouse Optimization System

Project Overview

The Inventory + Warehouse Optimization System is a software application designed to manage products in a warehouse, track inventory levels, and improve the efficiency of item retrieval and restocking. 
The system simulates real warehouse operations by organizing item data, prioritizing tasks, and optimizing routes for workers or automated systems.

This project demonstrates how data structures and algorithms can be used to solve practical logistics and supply chain problems.

Real-World Use Cases

This type of system is useful in many real-world settings:

- e-commerce warehouses such as Amazon fulfillment centers
- grocery or retail backroom inventory systems
- manufacturing facilities that store parts and materials
- hospital supply storage and distribution
- shipping and logistics hubs
- 
Example scenarios

A warehouse employee needs to collect several items for an order. The system can determine the most efficient route through the warehouse.

A manager wants to know which items are low in stock and need to be reordered soon. The system can prioritize those products.

A business wants to reduce wasted movement and improve order fulfillment time. The system can use algorithms to optimize picking order.

Features

- add, remove, and update inventory items
- track item quantities and storage locations
- search for products by name, ID, or category
- alert when items fall below a minimum stock threshold
- generate restocking priority lists
- optimize item-picking order for customer orders
- simulate warehouse layout as a graph of locations
- display shortest path to collect multiple items
- support category-based or aisle-based organization
  
Data Structures Used

1. Hash map / unordered_map
Used for fast lookup of items by product ID or name.

Example:

- product ID → item record

- item name → location and quantity

2. Vector

Used to store lists of products, orders, or route sequences.

3. Priority queue

Used to prioritize restocking tasks or urgent orders.

Example:

- lowest stock items get highest priority

- urgent orders can be processed before standard ones

4. Graph

Used to model warehouse layout.

Example:

- nodes = shelves, aisles, or bins

- edges = walkable paths between locations

5. Set

Used to track visited locations or unique product categories.

Algorithms Used

Shortest path algorithm

Such as Dijkstra’s algorithm.

Used to find the fastest or shortest path through the warehouse to collect items.

Greedy algorithm

Used to determine a practical picking order or restocking sequence.

Sorting

Used to rank items by:

- quantity

- urgency

- popularity

- reorder priority

Search algorithms

Used to find matching products quickly by keyword or ID.

Why This Project Is Strong

This project is practical, easy to explain, and clearly tied to real industries. It also allows a team to divide work naturally:

- one person handles inventory management

- one person handles route optimization

- one person handles interface and reporting

It demonstrates both useful software design and core data structures and algorithms in a meaningful way.
