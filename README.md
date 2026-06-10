# 2.1 Project Title: TerminalTunes

> A colorful terminal-based music playlist management system built in **C++17**, designed to demonstrate Data Structures and Algorithms concepts through an engaging, real-world simulation.

---

## 2.2 Problem Statement

In modern software, managing sequences of media (like a playlist of songs) requires efficient navigation, queueing, and historical tracking. The problem is to develop a robust, terminal-based music playlist management system that simulates real-world operations such as moving forward and backward through tracks, shuffling, tracking listening history, and managing an upcoming song queue. This system must be built entirely from scratch using fundamental Data Structures and Algorithms (without relying on pre-built, high-level STL containers like `std::list`, `std::stack`, or `std::queue`) to demonstrate a profound understanding of memory management and algorithmic efficiency.

---

## 2.3 Objectives

1. **Practical Application of DSA**: To apply theoretical Data Structures and Algorithms concepts to a recognizable, real-world application (a music player).
2. **Custom Data Structures**: To implement a custom Doubly Linked List (for the playlist), a custom Stack using a Singly Linked List (for listening history), and a custom Queue using a Singly Linked List (for the upcoming song queue).
3. **Algorithmic Efficiency**: To ensure core operations like navigation (next/previous) and insertion occur in **O(1)** time complexity.
4. **Memory Management**: To strictly manage dynamic memory using C++ pointers, ensuring no memory leaks occur during node creation and deletion.
5. **Interactive UI**: To build an engaging, colorful terminal interface that provides live visualizations of the underlying data structures.

---

## 2.4 System Overview / Architecture

TerminalTunes is structured using Object-Oriented Principles in C++17. The system is divided into modular components:

```
TerminalTunes
│
├── Playlist Manager
│     ├── Playlist (Doubly Linked List)
│     ├── Song Nodes (DLL Nodes)
│     └── Navigation Engine (next/prev in O(1))
│
├── Song Library (Preloaded Catalog + Vector Search)
│
├── History Manager (Custom Stack — Singly Linked List)
│
├── Song Queue (Custom Queue — Singly Linked List)
│
├── Statistics Engine
│
├── Shuffle Manager (Vector + Fisher-Yates + DLL Rebuild)
│
└── Terminal UI (ANSI Colors + Box Drawing)
```

---

## 2.5 Data Structures and Algorithms Used

### Data Structures
1. **Doubly Linked List**: Used as the core `Playlist`. Allows **O(1)** bidirectional traversal (`next`/`prev`) and efficient node manipulation.
2. **Custom Stack (Singly Linked List)**: Used for the `HistoryManager` to track recently played songs in a Last-In-First-Out (LIFO) order.
3. **Custom Queue (Singly Linked List)**: Used for the `SongQueue` to manage the "Up Next" songs in a First-In-First-Out (FIFO) order.
4. **Array / Vector**: Used for the `SongLibrary` catalog and temporarily during the playlist shuffling process.

### Algorithms
1. **Fisher-Yates Shuffle**: Used to randomize the playlist in **O(n)** time.
2. **Linear Search**: Used to find specific songs by title in the Doubly Linked List in **O(n)** time.

---

## 2.6 Implementation Approach

The project was developed strictly using **C++17** with a focus on Object-Oriented Programming (OOP).
1. **Node Design**: `Song`, `HistoryNode`, and `QueueNode` structs/classes were designed with raw pointers (`next`, `prev`).
2. **Manager Classes**: `Playlist`, `HistoryManager`, and `SongQueue` were created to encapsulate the pointer manipulation logic, ensuring operations like `insert`, `delete`, `push`, and `enqueue` were self-contained.
3. **Memory Management**: Destructors (`~Playlist()`, etc.) were carefully implemented to traverse the linked lists and `delete` dynamically allocated memory to prevent leaks.
4. **Integration**: The `main.cpp` file acts as the controller, taking user input via a REPL (Read-Eval-Print Loop) and routing commands to the appropriate data structure managers while updating the UI.

---

## 2.7 Time and Space Complexity Analysis

| Operation | Data Structure | Time Complexity | Space Complexity |
|---|---|:---:|:---:|
| Play Next/Prev Song | Doubly Linked List | **O(1)** | **O(1)** |
| Insert at Beginning/End | Doubly Linked List | **O(1)** | **O(1)** |
| Delete Current Node | Doubly Linked List | **O(1)** | **O(1)** |
| Search Song by Title | Doubly Linked List | **O(n)** | **O(1)** |
| Display All Songs | Doubly Linked List | **O(n)** | **O(1)** |
| Shuffle Playlist | Vector + DLL Rebuild | **O(n)** | **O(n)** |
| Push to / Pop from History | Custom Stack (SLL) | **O(1)** | **O(1)** |
| Enqueue / Dequeue Song | Custom Queue (SLL) | **O(1)** | **O(1)** |

---

## 2.8 Execution Steps

### Prerequisites
- **g++** compiler with C++17 support
- macOS or Linux terminal

### Build and Run
```bash
# 1. Compile the project using the provided Makefile
make

# 2. Run the application
./terminal_tunes

# 3. (Optional) Run the automated unit test suite
make test

# 4. Clean compiled objects
make clean
```

---

## 2.9 Sample Inputs and Outputs

Sample input and output files are provided in the `/sample_io/` directory of the repository.

**Sample User Flow (`sample_io/sample_input.txt`):**
```
play
next
select
Hotel California
stats
history
dev
exit
```

The system responds interactively to these commands, displaying colored UI updates, advancing the Doubly Linked List pointer, pushing to the History Stack, and rendering the Developer Mode visualization. See `sample_io/sample_output.txt` for the raw text output.

---

## 2.10 Screenshots

### Main Dashboard with DLL Visualizer
![Dashboard](screenshots/dashboard.png)

### Help Menu — All Available Commands
![Help Menu](screenshots/help_menu.png)

### General Song Library Catalog
![Song Library](screenshots/song_library.png)

### Playlist Statistics Dashboard
![Statistics](screenshots/stats_dashboard.png)

### Unit Tests — All Passing
![Unit Tests](screenshots/unit_tests.png)

---

## 2.11 Results and Observations

1. **Performance**: The custom Doubly Linked List successfully achieved true O(1) time complexity for track navigation, resulting in instantaneous feedback within the terminal UI.
2. **Memory Efficiency**: By writing custom linked lists instead of using dynamic arrays (`std::vector`) for the active playlist, we avoided costly array resizing operations in memory. 
3. **Data Structure Synergy**: The combination of a DLL (for sequential navigation), a Stack (for historical backtracking), and a Queue (for future planning) perfectly mirrored the architecture of commercial music applications like Spotify or Apple Music, proving the direct real-world applicability of fundamental DSA concepts.
4. **Robustness**: The automated unit tests (`make test`) verified that pointer manipulation held up under edge cases (e.g., deleting the head node, navigating an empty list, popping an empty stack).

---

## 2.12 Conclusion

The TerminalTunes project successfully meets all objectives by delivering a fully functional, memory-safe, terminal-based music playlist simulator. By strictly using C++ and custom-built data structures (Doubly Linked Lists, Stacks, Queues), the project serves as a comprehensive demonstration of memory management, pointer manipulation, algorithmic efficiency, and Object-Oriented design. It proves that complex application features can be elegantly constructed from foundational computer science principles.
