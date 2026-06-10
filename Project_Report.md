# DSA-I Project Report: TerminalTunes

## 3.1 Cover Page
**Project**: TerminalTunes  
**Course**: Data Structures and Algorithms - I (Using C++)  
**Semester**: 2  

## 3.2 Student Details
**Name**: Danish Shaikh  
**Role**: Sole Developer  

## 3.3 Project Title
TerminalTunes - Dynamic C++ DLL Music Simulator

## 3.4 Problem Statement
In modern software, managing sequences of media requires efficient navigation, queueing, and historical tracking. The problem is to develop a robust, terminal-based music playlist management system simulating operations like moving forward/backward through tracks, shuffling, tracking listening history, and managing an upcoming song queue. This must be built entirely from scratch using fundamental Data Structures without relying on pre-built STL containers (like `std::list`, `std::stack`, or `std::queue`) to demonstrate profound understanding of memory management and algorithmic efficiency.

## 3.5 Objectives
1. To apply theoretical DSA concepts to a real-world application (music player).
2. To implement custom core structures: a Doubly Linked List (Playlist), a Singly Linked List Stack (History), and a Singly Linked List Queue (Upcoming).
3. To achieve O(1) time complexity for core navigation and insertion operations.
4. To strictly manage dynamic memory with pointers.

## 3.6 Design/Architecture
The system uses Object-Oriented Principles in C++17. 
- **Playlist Manager**: Manages Doubly Linked List nodes (`Song`).
- **History Manager**: A Stack built via a Singly Linked List (`HistoryNode`).
- **Song Queue**: A Queue built via a Singly Linked List (`QueueNode`).
- **Terminal UI**: Handles I/O, ANSI coloring, and visualizes the linked list dynamically.

## 3.7 Algorithm Description
- **Insertion/Deletion**: Standard DLL pointer updates (`prev->next = next`, etc.) executed in O(1) time.
- **Search**: Linear traversal of the DLL (`current = current->next`) until a match is found.
- **Shuffle**: Extracts pointers into a temporary array, applies the Fisher-Yates shuffle algorithm, and then reconstructs the DLL `prev`/`next` links in randomized order.

## 3.8 Complexity Analysis
| Operation | Data Structure | Time Complexity | Space Complexity |
|---|---|:---:|:---:|
| Play Next/Prev Song | Doubly Linked List | **O(1)** | **O(1)** |
| Insert at Beginning/End | Doubly Linked List | **O(1)** | **O(1)** |
| Search Song by Title | Doubly Linked List | **O(n)** | **O(1)** |
| Shuffle Playlist | Vector + DLL Rebuild | **O(n)** | **O(n)** |
| Push to / Pop from History| Custom Stack (SLL) | **O(1)** | **O(1)** |
| Enqueue / Dequeue Song | Custom Queue (SLL) | **O(1)** | **O(1)** |

## 3.9 Screenshots of Execution
*(Please insert images from the `screenshots/` directory here before exporting to PDF)*
- Dashboard.png
- Stats.png
- Library.png

## 3.10 Results and Findings
The custom Doubly Linked List successfully achieved true O(1) time complexity for track navigation, yielding instantaneous UI feedback. Writing custom structures instead of using dynamic arrays avoided costly memory reallocation. The combination of a DLL, Stack, and Queue perfectly mirrored the architecture of commercial applications like Spotify, proving the real-world value of fundamental DSA concepts.

## 3.11 Conclusion
TerminalTunes successfully meets all objectives by delivering a fully functional, memory-safe playlist simulator. By strictly using C++ and custom-built data structures, the project is a comprehensive demonstration of memory management, pointer manipulation, and Object-Oriented design.

## 3.12 GitHub Repository Link
https://github.com/Danish1323/dsa-sem2-project
