# AlgoBank: A Secure Banking System in C++

![Language](https://img.shields.io/badge/Language-C%2B%2B-blue.svg) ![Build](https://img.shields.io/badge/Build-Makefile-brightgreen.svg) ![Concepts](https://img.shields.io/badge/Concepts-OOP%20%7C%20DSA-orange.svg)

**AlgoBank is a command-line banking application meticulously engineered to demonstrate the practical application of core data structures and algorithms in a real-world context. Built entirely from scratch in C++, it simulates a secure, multi-user banking environment without relying on external frameworks or databases.**

This project was designed not just as a functional application, but as a technical showcase. It proves how fundamental computer science concepts like graphs, trees, and heaps can be leveraged to build intelligent, efficient, and secure software features, such as fraud detection and credit scoring.

---

## ✨ Core Features & DSA Implementation

This is the heart of the project. Each feature is powered by a specific data structure or algorithm, showcasing a deep understanding of applied computer science.

| Feature                      | Data Structure / Algorithm                                 | Technical Rationale & Implementation                                                                                                                              |
| ---------------------------- | ---------------------------------------------------------- | ----------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| **Account & User Management** | `unordered_map` (Hash Map)                            | Provides **O(1)** average time complexity for core account operations: creation, retrieval (login), and updates. The key is the integer `AccountId`.                  |
| **Transaction Ledger** | **Directed Weighted Graph** (Adjacency List)               | Models the flow of money perfectly. Users are nodes, and transactions are directed edges with the amount as the weight. This graph is the foundation for many other features. |
| **Fraud Detection** | **Depth First Search (DFS) Cycle Detection** on the graph  | After a transaction, a DFS is initiated from the sender to detect cycles (`A -> B -> C -> A`). Such cycles are a classic indicator of potential money laundering or complex scams. |
| **User Search & Autocomplete** | **Trie (Prefix Tree)** | Allows for highly efficient, prefix-based searching of user names. Provides autocomplete suggestions in **O(L)** time, where L is the length of the query.          |
| **Credit Rating System** | **`priority_queue` (Min-Heap)** | A custom credit score is calculated for each user. The Admin dashboard uses a Min-Heap to efficiently retrieve and display the users with the lowest credit scores in **O(k log n)** time. |
| **"Recent Payees" Cache** | **LRU (Least Recently Used) Cache** | Implemented with a `list` and `unordered_map`. This cache stores a user's most recent transaction partners, ensuring frequently accessed data is retrieved in **O(1)**. |
| **Connection Suggestions** | **Breadth-First Search (BFS)** | Suggests other "trusted" users by finding accounts within 2-3 hops in the transaction graph. BFS is ideal for finding the shortest path in terms of hops.        |
| **Community/Cluster Analysis** | **Disjoint Set Union (DSU) / Union-Find** | In the admin dashboard, this algorithm clusters users into "communities" of frequent transactors. It efficiently determines connected components within the transaction graph. |

---

## 🏗️ System Architecture

The system is designed with a strong emphasis on **Object-Oriented Principles** and **Separation of Concerns**.

-   **`BankSystem`**: The central orchestrator class. It acts as a facade, hiding the complexity of the subsystems from the `main` function. It owns all the core components.
-   **`Account`**: A simple data class (struct) representing a user's profile and balance.
-   **Component Classes**: Each major feature is encapsulated in its own class (`Graph`, `Trie`, `FraudDetector`, `CreditSystem`), making the system modular, testable, and easy to extend.
-   **`main.cpp`**: Serves only as the Command Line Interface (CLI) driver. It contains no core banking logic.

This clean, modular design is crucial for building scalable and maintainable software.

---

## 🛠️ Setup and Execution

Follow these steps to compile and run the project on your local machine.

### Prerequisites

You need a C++ compiler that supports the C++11 standard or newer.
-   **Windows**: [MinGW](https://www.mingw-w64.org/downloads/) (provides g++)
-   **macOS**: [Xcode Command Line Tools](https://developer.apple.com/xcode/resources/) (provides clang++)
-   **Linux**: `build-essential` package (provides g++)
    ```bash
    sudo apt-get update
    sudo apt-get install build-essential
    ```

### Compilation

There are two ways to compile the project. Using the `Makefile` is the recommended approach.

#### Method 1: Using the Makefile (Recommended)

This is the simplest method. Navigate to the project's root directory in your terminal and run:

```bash
make
```

This will automatically compile all source files and create an executable named `algobank`.

#### Method 2: Manual Compilation with g++

If you do not have `make` installed, you can compile all the source files manually with this single command:

```bash
g++ main.cpp BankSystem.cpp Graph.cpp FraudDetector.cpp Trie.cpp CreditSystem.cpp -o algobank -std=c++17
```
*(Note: Use `-std=c++11` if your compiler is older)*

### Running the Application

After compilation, an executable file will be created in your directory.
-   On **Linux or macOS**: `./algobank`
-   On **Windows**: `.\algobank.exe`

Execute the command in your terminal to start the AlgoBank system.

```bash
# On Windows
.\algobank.exe

# On Linux/macOS
./algobank
```
---

## 🚀 Usage Demonstration

Here is a sample walkthrough of the application:

**1. Create a new account:**
```
===================================
=== Welcome to AlgoBank System ===
===================================
1. Login
2. Create Account
3. Admin Dashboard
4. Exit
Enter your choice: 2

--- Create New Account ---
Enter your full name: John Doe
Create a PIN: 9876
Account created successfully for John Doe. Your Account ID is: 1006
```

**2. Log in with the new account:**
```
Enter your choice: 1

--- Login ---
Enter Account ID: 1006
Enter PIN: 9876
Login successful! Welcome, John Doe.
```

**3. Transfer money and see a fraud alert:**
(First, transfer $100 from John (1006) to Alice (1001). Then, from Alice back to John.)

```
--- Welcome John Doe (Account #1006) ---
Balance: $1000.00
...
Enter your choice: 1
Enter recipient Account ID: 1001
Enter amount: $100
Transfer successful.
```
*(Now log in as Alice and send money back to John to create a cycle)*

```
--- Welcome Alice (Account #1001) ---
Balance: $1100.00
...
Enter your choice: 1
Enter recipient Account ID: 1006
Enter amount: $50
Transfer successful.

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
!!! FRAUD ALERT: A potential cycle of transactions has been detected.
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
```

**4. Search for a user with the Trie:**
```
--- Welcome John Doe (Account #1006) ---
...
Enter your choice: 5
Enter name prefix to search: Dav
--- Search Results (Trie) ---
  - Name: David, Account ID: 1004
```
---

## 🔮 Future Enhancements

This project provides a solid foundation that can be extended in many ways:

-   **Persistence**: Integrate a lightweight database like SQLite to persist user and transaction data across sessions.
-   **REST API**: Build a C++ REST API (using a library like Crow or Pistache) on top of the core logic to allow web clients to interact with the system.
-   **Concurrency**: Implement a thread pool to handle multiple client requests or batch processing tasks simultaneously.
-   **GUI**: Develop a simple graphical user interface using a framework like Qt.
