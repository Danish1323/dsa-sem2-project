# TerminalTunes: The Complete VIVA Deep-Dive Codebase Breakdown

This document provides an exhaustive, block-by-block, line-by-line explanation of the entire TerminalTunes codebase. It is designed to act as your ultimate cheat sheet for the VIVA. If the examiner asks you "Show me the exact line where memory is freed" or "Explain the time complexity of how you implemented the Stack", this file holds the answer in extreme detail.

---

## Table of Contents
1. [Core Data Structures & Architecture Rationale](#1-core-data-structures--architecture-rationale)
2. [Module 1: The Doubly Linked List (Playlist)](#2-module-1-the-doubly-linked-list-playlist)
3. [Module 2: The Custom Stack (HistoryManager)](#3-module-2-the-custom-stack-historymanager)
4. [Module 3: The Custom Queue (SongQueue)](#4-module-3-the-custom-queue-songqueue)
5. [Module 4: Algorithms (Searching & Shuffling)](#5-module-4-algorithms-searching--shuffling)
6. [Module 5: The Controller (main.cpp)](#6-module-5-the-controller-maincpp)
7. [VIVA Q&A: Defense Scenarios](#7-viva-qa-defense-scenarios)

---

## 1. Core Data Structures & Architecture Rationale

In this project, we deliberately avoided using standard C++ templates (like `std::list`, `std::stack`, or `std::queue`) for our core logic. The goal was to build the data structures from scratch using raw pointers and dynamic memory (`new` and `delete`). 

### Why a Doubly Linked List (DLL)?
A music player inherently requires three distinct actions: moving to the next song, returning to the previous song, and dynamically adding/removing songs without halting playback. 
- **Array/Vector**: An array stores elements contiguously in memory. If we want to insert a song into the middle of a playlist, the CPU must physically shift all subsequent elements forward, yielding an **O(n)** time complexity. Furthermore, arrays have fixed sizes, requiring expensive resizing (O(n) reallocation).
- **Singly Linked List (SLL)**: An SLL solves the insertion issue (achieving O(1) insertion) but lacks a `prev` pointer. It only points forward. Therefore, clicking "Previous Song" would require traversing the entire list from the head again to find the node just before the current one (O(n) time).
- **Doubly Linked List (DLL)**: A DLL assigns both a `next` and `prev` pointer to each node. This allows absolute **O(1)** time complexity for both "Next" and "Previous" actions. We can slide freely back and forth across the playlist.

### Why a Stack for History?
Listening history behaves exactly like a browser's "Back" button—it is a **Last-In-First-Out (LIFO)** data structure. The song you just finished playing is the very first one you see in your history. We implemented a custom Stack using a Singly Linked List (where pushing means inserting a new `head` node, achieving strict **O(1)** time complexity without risking array overflow or reallocation).

### Why a Queue for "Up Next"?
When a user queues songs, the first song they queued should play first. This is a **First-In-First-Out (FIFO)** structure. We built a custom Queue using a Singly Linked List equipped with both a `front` and `rear` pointer. Adding to the back (`rear->next = newNode`) and removing from the front (`front = front->next`) guarantees strict **O(1)** operations. Arrays used as queues suffer from index drifting and require circular logic; the Linked-List Queue completely circumvents this.

---

## 2. Module 1: The Doubly Linked List (Playlist)

The `Playlist` is the absolute heart of the project. It resides in `include/Song.h`, `include/Playlist.h`, and `src/Playlist.cpp`.

### 2.1 The Node Structure (`include/Song.h`)
```cpp
class Song {
public:
    std::string title;
    std::string artist;
    std::string album;
    int playCount;

    Song* prev; // Points to previous song
    Song* next; // Points to next song

    Song(std::string t, std::string a, std::string alb = "", int pc = 0)
        : title(t), artist(a), album(alb), playCount(pc), prev(nullptr), next(nullptr) {}
};
```
**Explanation:** 
Every element in a Linked List is called a "Node". Here, our node is `Song`. It holds the data payload (`title`, `artist`, `playCount`) and two raw pointers (`prev`, `next`). When a new `Song` is instantiated via the constructor, both pointers default to `nullptr`, meaning the node is disconnected from the list.

### 2.2 The Playlist Class Core (`src/Playlist.cpp`)
```cpp
Playlist::Playlist(std::string name)
    : name(name), head(nullptr), tail(nullptr), current(nullptr), songCount(0) {}
```
**Explanation:**
When we create a new Playlist, we establish our anchor pointers. 
- `head`: Points to the absolute first song.
- `tail`: Points to the absolute last song.
- `current`: Points to the song currently playing.
Initially, the list is empty, so all point to `nullptr`.

### 2.3 Insertion Logic: O(1) Time
```cpp
void Playlist::insertAtEnd(std::string title, std::string artist, std::string album) {
    Song* newSong = new Song(title, artist, album); // 1. Allocate memory dynamically
    if (!tail) { 
        // 2. If list is entirely empty, this song is the head, tail, and current.
        head = tail = current = newSong;
    } else {
        // 3. Normal DLL insertion logic
        tail->next = newSong; // Old tail points forward to new song
        newSong->prev = tail; // New song points backward to old tail
        tail = newSong;       // Update the master tail pointer to the new end
    }
    songCount++;
}
```
**Explanation:**
This block executes in perfect **O(1)** time because we maintain a `tail` pointer. We do not need to traverse the list to find the end. 

### 2.4 Navigation Logic: O(1) Time
```cpp
Song* Playlist::playNext() {
    if (current && current->next) { // Ensure there is actually a current song AND a next song
        current = current->next;    // O(1) pointer jump
        return playCurrent();       // Increments playCount
    }
    return nullptr; 
}
```
**Explanation:**
When the user types `next`, we literally just slide the `current` pointer forward by one link in the chain (`current = current->next`). This is why the Doubly Linked List is so powerful for this specific application.

### 2.5 Deletion Logic: O(1) Time (if pointer is known)
```cpp
bool Playlist::deleteCurrent() {
    if (!current) return false;

    Song* toDelete = current;

    // Fix the master head/tail pointers if we are deleting the ends
    if (current == head) head = head->next;
    if (current == tail) tail = tail->prev;

    // Stitch the list back together around the node we are deleting
    if (current->prev) current->prev->next = current->next;
    if (current->next) current->next->prev = current->prev;

    // Shift current to a safe adjacent node before nuking memory
    if (toDelete->next) current = toDelete->next;
    else if (toDelete->prev) current = toDelete->prev;
    else current = nullptr;

    delete toDelete; // FREE THE MEMORY to prevent a memory leak
    songCount--;
    return true;
}
```
**Explanation:**
When deleting a node in a DLL, we must connect the node *before* the target directly to the node *after* the target, completely bypassing the target node. `current->prev->next = current->next` tells the previous node to look past the current node. Finally, `delete toDelete;` frees the heap memory assigned via the `new` keyword.

---

## 3. Module 2: The Custom Stack (HistoryManager)

Found in `src/HistoryManager.cpp`. We built a Stack from scratch using a Singly Linked List.

### 3.1 Push Logic: O(1) Time
```cpp
void HistoryManager::push(std::string title, std::string artist) {
    HistoryNode* newNode = new HistoryNode(title, artist);
    newNode->next = topNode;
    topNode = newNode;
    size++;
}
```
**Explanation:**
To push a new song onto the stack (LIFO), we always insert at the "head" (which we call `topNode`). We create the new node, point its `next` to the old top, and then declare the new node as the new `topNode`. Because we don't have to shift elements (like in an array) or traverse to the end, it is **O(1)**.

### 3.2 Pop Logic: O(1) Time
```cpp
bool HistoryManager::pop(std::string& title, std::string& artist) {
    if (isEmpty()) return false;
    
    HistoryNode* toDelete = topNode;
    title = topNode->title;       // Extract data
    artist = topNode->artist;
    topNode = topNode->next;      // Shift top down
    
    delete toDelete;              // Free memory
    size--;
    return true;
}
```

---

## 4. Module 3: The Custom Queue (SongQueue)

Found in `src/SongQueue.cpp`. A Queue follows First-In-First-Out (FIFO). 

### 4.1 Enqueue (Adding to Queue): O(1) Time
```cpp
void SongQueue::enqueue(std::string title, std::string artist) {
    QueueNode* newNode = new QueueNode(title, artist);
    if (isEmpty()) {
        frontNode = rearNode = newNode;
    } else {
        rearNode->next = newNode;
        rearNode = newNode;
    }
    size++;
}
```
**Explanation:**
Because we maintain a specific pointer pointing to the very back of the list (`rearNode`), we can add songs to the end in constant time. 

### 4.2 Dequeue (Removing from Queue): O(1) Time
```cpp
bool SongQueue::dequeue(std::string& title, std::string& artist) {
    if (isEmpty()) return false;
    
    QueueNode* toDelete = frontNode;
    title = frontNode->title;
    artist = frontNode->artist;
    
    frontNode = frontNode->next;  // Advance the front pointer
    if (frontNode == nullptr) {
        rearNode = nullptr;       // Queue is completely empty now
    }
    
    delete toDelete;
    size--;
    return true;
}
```
**Explanation:**
We take from the `frontNode`. As soon as the queue becomes empty, we explicitly set `rearNode = nullptr` so we don't end up with a dangling pointer causing a segmentation fault.

---

## 5. Module 4: Algorithms (Searching & Shuffling)

### 5.1 Linear Search Algorithm: O(n) Time
```cpp
Song* Playlist::searchByTitle(const std::string& title) {
    Song* temp = head; // Start at the beginning
    std::string searchLower = toLower(title);
    
    while (temp) {     // Traverse until we hit nullptr (end of list)
        if (toLower(temp->title) == searchLower) {
            return temp; // Match found
        }
        temp = temp->next; // Move to next node
    }
    return nullptr; // Not found
}
```
**Explanation:**
Unlike arrays, Linked Lists do not have direct indexed access (e.g., `list[5]`). We cannot use Binary Search (which is O(log n)) because we can't instantly jump to the middle node. Therefore, we use **Linear Search**, starting at the `head` and looping `temp = temp->next` until we find the title. This takes **O(n)** time.

### 5.2 In-Place Fisher-Yates Shuffle Algorithm: O(n) Time, O(n) Space
```cpp
void Playlist::shuffle() {
    if (songCount <= 1) return;

    // 1. Copy pointers into a vector (O(n) time, O(n) space)
    std::vector<Song*> songs;
    Song* temp = head;
    while (temp) {
        songs.push_back(temp);
        temp = temp->next;
    }

    // 2. Fisher-Yates Shuffle (O(n) time)
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(songs.begin(), songs.end(), g);

    // 3. Rebuild the Doubly Linked List Pointers (O(n) time)
    head = songs[0];
    head->prev = nullptr;
    for (size_t i = 1; i < songs.size(); ++i) {
        songs[i-1]->next = songs[i];
        songs[i]->prev = songs[i-1];
    }
    tail = songs.back();
    tail->next = nullptr;
    
    current = head;
}
```
**Explanation:**
Shuffling a linked list by swapping nodes directly is incredibly inefficient and error-prone due to massive pointer rewiring. Instead, we extract just the *memory addresses* (pointers) of the nodes into a `std::vector`. We shuffle that array of pointers using the Fisher-Yates algorithm (`std::shuffle`). Once randomized, we loop through the vector and re-wire the `prev` and `next` pointers to match the new randomized order. This gives us O(n) performance, but costs O(n) auxiliary space to hold the vector array.

---

## 6. Module 5: The Controller (main.cpp)

The `main.cpp` file contains the **Read-Eval-Print Loop (REPL)** that drives the entire user experience.

### 6.1 The Event Loop
```cpp
while (true) {
    UI::clearScreen();
    UI::printDashboard(...); // Renders the UI
    
    std::string command = getInputLine("Enter Command > ");
    std::string cmdLower = toLower(command);
    
    // Command Router
    if (cmdLower == "play") { ... }
    else if (cmdLower == "next") { ... }
    else if (cmdLower == "exit") { ... break; }
}
```
**Explanation:**
The program constantly clears the screen, draws the dashboard showing the state of the data structures, asks the user for a string command, parses it, executes the command on the backend data structures, and then loops back to re-draw the updated screen.

### 6.2 Advanced Control Flow: The "Next" Command
```cpp
if (cmdLower == "next") {
    std::string qTitle, qArtist;
    
    // 1. Check if the Queue has a song first
    if (queue.dequeue(qTitle, qArtist)) {
        // If it does, find that song in the playlist and jump to it
        Song* found = activePlaylist->searchByTitle(qTitle);
        activePlaylist->setCurrent(found);
        history.push(found->title, found->artist);
    } else {
        // 2. Queue is empty, just move forward in the DLL
        Song* nextSong = activePlaylist->playNext();
        if (nextSong) {
            history.push(nextSong->title, nextSong->artist);
        }
    }
}
```
**Explanation:**
This perfectly mimics real-world apps like Spotify. When the user hits "Next", the program must check the Queue (FIFO) first. If a song is queued, it overrides the normal DLL flow. Only if the queue is empty does it call the standard O(1) `playNext()` pointer shift on the DLL. In both cases, the played song is Pushed onto the History Stack (LIFO).

---

## 7. VIVA Q&A: Defense Scenarios

**Q: Where exactly are you preventing memory leaks in your code?**
**A:** "In the destructors of my manager classes. For example, `Playlist::~Playlist()` calls a `clear()` function. Inside `clear()`, I run a `while(temp)` loop over the Doubly Linked List. Before I `delete temp;`, I temporarily save the pointer to `temp->next`, ensuring I don't lose the chain while freeing memory. The same is done for `HistoryManager::~HistoryManager()` and `SongQueue::~SongQueue()`."

**Q: Why not just use `std::list`? It is built into C++.**
**A:** "The objective of this DSA project is to demonstrate a fundamental understanding of underlying data structure mechanics. By building the Doubly Linked List from scratch, I proved my capability to manage raw heap memory (`new`/`delete`), manually manipulate bidirectional node pointers, and understand the deep-level O(1) constraints behind insertion and deletion algorithms."

**Q: Explain how the Developer Mode Visualizer works.**
**A:** "In `src/UI.cpp`, the `printDLLVisualizer` function receives a pointer to the `Playlist`. It starts at `Playlist->getHead()` and enters a `while(temp)` loop. As it traverses the Doubly Linked List, it prints `NULL <- ` at the start, prints the title of each node surrounded by arrows `<->`, and ends with `-> NULL`. It uses an `if (temp == current)` check to apply green ANSI coloring to the actively playing node."

**Q: What is the space complexity of this system?**
**A:** "The core space complexity is **O(n)**, where `n` is the total number of songs loaded into the system across the playlists. Each `Song` node consumes a fixed amount of memory (the strings and two pointers). The Stack and Queue consume **O(h)** and **O(q)** auxiliary space respectively. Since memory is dynamically allocated, the system only consumes exactly what it needs, avoiding the wasted pre-allocated padding that arrays suffer from."
