# AGENTS.md

# TerminalTunes

A terminal-based music playlist management system built in C++ using Data Structures and Algorithms concepts, primarily a Doubly Linked List.

---

## Project Vision

TerminalTunes is a colorful terminal music player that simulates real-world playlist management.

The project focuses on demonstrating Data Structures and Algorithms concepts while providing an engaging user experience through a modern terminal interface.

The application allows users to:

- Navigate songs forward and backward
- Create and manage multiple playlists
- Search songs
- Shuffle playlists
- Track listening history
- View playlist statistics
- Visualize the underlying data structure

---

# Technology Stack

Language:

- C++17

Environment:

- Terminal / Console Application

Primary Data Structure:

- Doubly Linked List

Additional Data Structures:

- Stack (Recently Played Songs)
- Vector (Shuffle Support)
- Queue (Optional Song Queue Feature)

---

# Core Architecture

```text
TerminalTunes
│
├── Playlist Manager
│     ├── Playlist
│     ├── Song Nodes
│     └── Navigation Engine
│
├── Search System
│
├── History Manager
│
├── Statistics Engine
│
├── Shuffle Manager
│
└── Terminal UI
```

---

# Data Structures

## Song Node

Each song must be stored as a node in a Doubly Linked List.

Attributes:

- Song Title
- Artist Name
- Album Name (Optional)
- Play Count
- Previous Pointer
- Next Pointer

Example:

```cpp
class Song {
public:
    string title;
    string artist;
    int playCount;

    Song* prev;
    Song* next;
};
```

---

## Playlist

A playlist manages a collection of songs using a Doubly Linked List.

Required pointers:

```cpp
Song* head;
Song* tail;
Song* current;
```

Responsibilities:

- Insert Song
- Delete Song
- Play Next
- Play Previous
- Search Song
- Display Playlist

---

# Required Features

## 1. Multiple Playlists

Examples:

- Rock Legends
- Pop Hits
- Midnight Drive
- Personal Favorites

Each playlist should maintain its own Doubly Linked List.

---

## 2. Song Navigation

Users should be able to:

- Play current song
- Move to next song
- Move to previous song

Target Complexity:

O(1)

---

## 3. Song Insertion

Allow:

- Insert at beginning
- Insert at end
- Insert after specific song

Target Complexity:

O(1) where applicable

---

## 4. Song Deletion

Allow removal of:

- Current song
- Song by title

Target Complexity:

O(1) if node reference is known

---

## 5. Search Feature

Search songs by title.

Implementation:

Linear Traversal

Complexity:

O(n)

---

## 6. Shuffle Mode

Implementation Idea:

- Copy node pointers into vector
- Randomize order
- Navigate randomized list

Complexity:

O(n)

---

## 7. Listening History

Implementation:

Stack

Features:

- Store previously played songs
- Display recent listening history

---

## 8. Statistics Dashboard

Display:

- Total Songs
- Total Artists
- Current Song
- Most Played Song
- Total Plays

---

## 9. Developer Mode

Purpose:

Visualize the internal Doubly Linked List.

Example:

```text
NULL <- Numb <-> In The End <-> Faint -> NULL
```

This feature exists primarily for DSA demonstration during viva.

---

# User Interface Guidelines

TerminalTunes should not feel like a basic menu-driven assignment.

Goals:

- Colorful interface
- Clear navigation
- Box-drawing characters
- Consistent layout
- User-friendly commands

Example Style:

```text
╔══════════════════════════════════════╗
║          TERMINALTUNES              ║
╚══════════════════════════════════════╝
```

Use colors for:

- Current Song
- Success Messages
- Errors
- Menus
- Statistics

---

# Coding Standards

## General Rules

- Use meaningful variable names
- Avoid global variables where possible
- Follow Object-Oriented Design
- Comment non-trivial logic
- Keep functions focused on one responsibility

---

## Naming Conventions

Classes:

```cpp
Playlist
Song
HistoryManager
```

Methods:

```cpp
playNext()
playPrevious()
insertSong()
deleteSong()
```

Variables:

```cpp
currentSong
playlistName
songCount
```

---

# Expected Complexity Analysis

| Operation         | Complexity |
| ----------------- | ---------- |
| Next Song         | O(1)       |
| Previous Song     | O(1)       |
| Insert End        | O(1)       |
| Delete Known Node | O(1)       |
| Search Song       | O(n)       |
| Display Playlist  | O(n)       |

---

# Repository Structure

```text
TerminalTunes/

├── src/
│   ├── Song.cpp
│   ├── Playlist.cpp
│   ├── HistoryManager.cpp
│   ├── UI.cpp
│   └── main.cpp
│
├── include/
│   ├── Song.h
│   ├── Playlist.h
│   ├── HistoryManager.h
│   └── UI.h
│
├── screenshots/
│
├── sample_io/
│
├── docs/
│
├── README.md
│
└── AGENTS.md
```

---

# Project Goal

TerminalTunes should demonstrate strong understanding of:

- Doubly Linked Lists
- Memory Management
- Pointer Manipulation
- Time Complexity Analysis
- Object-Oriented Programming
- Real-World DSA Applications

The project should remain educational, technically correct, and visually engaging while maintaining a clear focus on Data Structures and Algorithms.
