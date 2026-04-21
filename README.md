# CS124PocketLawyer
An Ohlone CS124 Project focused on informing a user about law enforcement and government  agencies.

Current ideas  here:
1) (Darcie) Decision tree for Q&A in emergency situations.
   - Fast and simple, gives quick resources for those in need.
   - Must give a disclaimer that this is a tool to be used and not something to be used in court.
  
     
2) (Darcie) Adding historical, anonymized data of reported activity counts by county || Official statistic or reports of recent ICE harassment or of crimes.
   - Most of this info would be crowdfunded so it is unverified and time-sesitive.
   - The most we can do is report official statistics or reports and having a sorting algorithms we can view the most recent official sighting as well as what county and city they have frequent reports in.
  

3) (Kenshin) Legal Document Parsing Engine
   - Objective:
        To assist users in parsing through the specific language of citations or government notices, translating dense legal jargon into plain English, or going to relevant articles quickly.
   - Technical Implementation:
        String Matching Algorithms: Application of algorithms (Gemini recommends Boyer-Moore or Knuth-Morris-Pratt) to scan uploaded text or manual input for specific legal clauses or mandatory disclosure requirements.
   - Hash Table Mapping: Used to map identified "red flags" or mandatory phrases directly to their plain-English explanations and corresponding legal rights.
   For example, we can have a GUI app that can help somebody quite quickly.
     1. Let's say a person uses Darcie’s "Emergency Q&A" and presses the button or says yes to terminal for: "Is a police officer asking to see your ID?"
     2. The User taps or inputs "Yes."
     3. The Parser logic instantly pulls the specific "Leaf Node" from the Penal Code Tree related to "Failure to Identify."
     4. The UI displays a simple "TL;DR" summary: "In California, you generally do not have to show ID unless you are being detained or are driving."
     5. Below that summary, there is a button: "Read the Full Law." Because of the tree, that button takes them exactly to Section 148, not just the top of the page.- 
- Possible tree structure:
   - The Root (Level 0): The entire Code (e.g., "California Penal Code").
   - The Branches (Level 1 & 2): These nodes are the containers. A node that contains links to sub-topics like "Search and Seizure" or "Right to Counsel" instead of the full law.
   - The Leaves (Level 3+): These are the leaf nodes. They contain the actual string data (the text of the law) and the metadata (the law number, the date it was passed).
- The bottom line idea is that we try to create a search engine that parses the entire code and lets you go to the specific chapter or give a tldr very quickly.

A single node can have the name of the node like "Article 4: something", a type such as the hierachy level "Article" or "Chapter", the children are more specific nodes like "Section: 2102" or "Section: 2104" and the LEAF NODES will have the actual text like "In California, you generally do not have to show ID unless you are being detained or are driving".

//
//
//
//
README 1: Contact Management System

Project Overview

The Contact Management System is a program designed to store, organize, and retrieve user contact information efficiently. It allows users to add, update, delete, and search for contacts based on different attributes such as name, phone number, or email.

This project demonstrates how data structures can be used to manage and search structured data in a practical, real-world application.

Real-World Use Cases

This type of system is useful in many everyday applications:

- personal contact lists (phone or email directories)
- business contact management systems
- customer relationship management (CRM) tools
- school or organization directories
- Example scenarios:

A user wants to quickly find a phone number by typing part of a name.

A business needs to store and manage hundreds of client contacts.

A student wants to organize classmates’ contact information and search by name or category.

Features

- add new contacts (name, phone number, email, etc.)
- edit existing contact information
- delete contacts
- search contacts by:
- name
- phone number
- email
- display all stored contacts
- optional: sort contacts alphabetically
- optional: group contacts by category (friends, work, school)

Data Structures Used

1. Hash map / unordered_map
Used for fast lookup of contacts.

Example:

- name → contact information
- Provides average constant-time access for searching and updating.
  
2. Vector

Used to store and display lists of contacts.

3. Struct / class

Used to represent a contact with multiple fields such as:

- name
- phone number
- email
  
Algorithms Used

Linear search

Used for partial matches (e.g., searching by part of a name).

Sorting

Used to display contacts in alphabetical order.

String comparison

Used for matching search queries with stored contact information.

Why This Project Is Strong

This project is simple, practical, and easy to demonstrate. It clearly shows how data structures like hash maps improve performance compared to basic list searching.

It is also highly extensible, allowing additional features such as:

- file saving/loading
- contact grouping
- search optimization
//

//

//

//

README 2: Inventory + Warehouse Optimization System

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

//

//

//

//

README 3: File Directory System / Search Engine

Project Overview

The File Directory System / Search Engine is a program that organizes files and allows users to search through them efficiently. It simulates the way operating systems and search engines manage file structures, keywords, and user queries.

This project focuses on efficient storage, retrieval, and ranking of file results using data structures and search algorithms.

Real-World Use Cases

This kind of system is useful in many real-world applications:

- desktop file management tools
- cloud storage platforms like Google Drive or Dropbox
- enterprise document search systems
- legal or medical record retrieval systems
- search bars in operating systems or websites
- 
Example scenarios

A user needs to find all files containing the word "budget" across many folders. The system returns matching files quickly.

A company stores thousands of documents and wants employees to locate relevant files by keyword. The system provides a searchable index.

A student wants a tool that organizes project folders and supports fast lookup by file type, folder path, or file content.

Features

- create and manage a hierarchical file directory structure
- add, rename, move, and delete files or folders
- search files by name
- search files by extension or type
- search by content keywords
- support recursive folder traversal
- display full file paths for matching results
- rank search results by relevance
- allow prefix-based autocomplete for filenames
- optionally track recently accessed files

Data Structures Used

1. Tree
Used to model the directory hierarchy.

Example:

- root directory
- subfolders as children
- files stored within folder nodes

2. Hash map / unordered_map

Used for quick file lookups and indexing.

Example:

- keyword → list of files containing that keyword
- filename → file metadata
1. Trie

Used for autocomplete or prefix-based filename search.

Example:

type "rep" and get "report.docx", "research.pdf", etc.
2. Vector / list

Used to store search results or file collections.

3. Set

Used to avoid duplicate file results during keyword searches.

Algorithms Used

Tree traversal

Such as DFS or BFS.

Used to:

- explore folder structures
- list files recursively
- search through directories
- Inverted index construction
- Used to map words to the files containing them.

This is the same general concept used by search engines.

String matching

Used for:

- file name queries
- keyword searches
- extension filtering
- Sorting / ranking

Used to sort results by:

- match count
- recency
- alphabetical order
- path depth

Why This Project Is Strong

This project has very clear DS&A relevance and mimics systems people use every day. It is practical, scalable, and easy to demo.


one person builds the file tree structure
one person builds the keyword search/indexing system
one person handles user interaction and result ranking
It is a strong project because it connects trees, hashing, tries, and searching into one realistic application.
