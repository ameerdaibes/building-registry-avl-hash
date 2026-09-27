# Building Registry AVL & Hash Manager

A C-based building information management system that uses an **AVL tree** for balanced record storage and an **open-addressing hash table** for efficient lookup and data management.

## Features

- Load building records from a file
- Store and organize records using an AVL tree
- Insert new building records
- Search for buildings by name
- Update existing building information
- Delete building records
- List buildings in alphabetical order
- Filter buildings by number of apartments
- Display buildings with unpaid fees
- Save AVL tree data to a file
- Build a hash table from stored records
- Insert and delete hash table entries
- Search records and report collision counts
- Display hash table size and load factor
- Save updated hash table data back to file

## Data Structures & Concepts

- AVL Trees
- Self-Balancing Binary Search Trees
- Hash Tables
- Open Addressing
- Hash Functions
- Collision Handling
- File I/O
- Searching and Updating Records

## Technologies

- C
- Standard C Libraries
- File-based storage

## Record Structure

Each building record contains information such as:

- Building name
- Building number
- Address
- Number of apartments
- Establishment year
- Fee payment status

## How It Works

The program first loads building information into an AVL tree, allowing records to remain balanced and searchable.

The data can then be saved and used to construct a hash table, where building names are used as keys for faster direct lookup.

## What I Learned

This project strengthened my understanding of balanced trees, hashing, collision handling, structured data storage, and comparing different approaches for organizing and retrieving records efficiently.

## Author

Ameer Daibes  
Computer Engineering Student — Birzeit University

[LinkedIn](https://www.linkedin.com/in/ameer-daibes-1510aa207)
