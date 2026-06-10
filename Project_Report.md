# DSA-I Project Report

## 3.1 Cover Page
**University**: ITM Skills University  
**Project**: Case Study 173: Music Playlist Manager (Doubly Linked List)  
**Course**: Data Structures and Algorithms - I (Using C++)  
**Semester**: 2  

## 3.2 Student Details
**Name**: Danish Shaikh  
**Roll Number**: 150096725147  
**Course**: B.TECH COMPUTER SCIENCE AND ENGINEERING  
**Batch/Cohort**: 2025-29 / JEFF BEZOS  

## 3.3 Project Title
Case Study 173: Music Playlist Manager (Doubly Linked List)

## 3.4 Problem Statement
**Industry Context**: Music streaming applications allow users to create playlists, rearrange songs, and move between tracks efficiently.

**Workflow**: Songs are stored as nodes containing previous and next references. Users can move to the next song, return to previous songs, insert new tracks, or remove unwanted tracks. 

**Example Scenario**: A playlist contains Song A, Song B, and Song C. The user listens to Song B and decides to return to Song A using the previous pointer. The system provides smooth navigation, dynamic playlist management, enhanced user experience, and efficient music playback.

## 3.5 Objectives
Develop a flexible music playlist system that supports forward and backward navigation between songs. A Doubly Linked List allows navigation in both directions using next and previous pointers, making it ideal for playlist management.

## 3.6 Design/Architecture
**High-Level Architecture**:
`Music Library -> Playlist Manager -> Doubly Linked List -> Music Player Interface`

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
