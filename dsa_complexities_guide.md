# ⏱️ The Ultimate DSA Complexity Guide: Big-O, Theta & Omega

This guide provides a deep dive into the Time Complexities of every Data Structure and Algorithm in your syllabus. It specifically breaks down the **Best Case ($\Omega$ - Omega)**, **Average Case ($\Theta$ - Theta)**, and **Worst Case ($O$ - Big-O)**, along with the *exact reason why* they behave that way.

---

## 🧭 The Asymptotic Notations Explained
- **$\Omega$ (Omega) - Best Case:** The absolute luckiest scenario. The data is already perfectly arranged for the algorithm.
- **$\Theta$ (Theta) - Average Case:** The expected, realistic scenario for a random set of data.
- **$O$ (Big-O) - Worst Case:** The absolute unluckiest scenario. The algorithm has to do the maximum possible amount of work.

---

## 🔍 1. Searching Algorithms

| Algorithm | Best Case ($\Omega$) | Average Case ($\Theta$) | Worst Case ($O$) | Space Complexity |
| :--- | :--- | :--- | :--- | :--- |
| **Linear Search** | $\Omega(1)$ | $\Theta(N)$ | $O(N)$ | $O(1)$ |
| **Binary Search** | $\Omega(1)$ | $\Theta(\log N)$ | $O(\log N)$ | $O(1)$ iterative |

### The "Why":
- **Linear Search:** 
  - **Best Case:** The item you are looking for is the very first item in the array ($\Omega(1)$).
  - **Worst Case:** The item is at the very end of the array, or doesn't exist, forcing you to check every single item ($O(N)$).
- **Binary Search (Array MUST be sorted):** 
  - **Best Case:** The item happens to be the exact middle element on the very first cut ($\Omega(1)$).
  - **Worst Case:** You have to keep cutting the array in half until only 1 element remains ($O(\log N)$).

---

## 📊 2. Sorting Algorithms

| Algorithm | Best Case ($\Omega$) | Average Case ($\Theta$) | Worst Case ($O$) | Space Complexity |
| :--- | :--- | :--- | :--- | :--- |
| **Bubble Sort** | $\Omega(N)$ | $\Theta(N^2)$ | $O(N^2)$ | $O(1)$ |
| **Selection Sort**| $\Omega(N^2)$ | $\Theta(N^2)$ | $O(N^2)$ | $O(1)$ |
| **Insertion Sort**| $\Omega(N)$ | $\Theta(N^2)$ | $O(N^2)$ | $O(1)$ |
| **Merge Sort** | $\Omega(N \log N)$ | $\Theta(N \log N)$ | $O(N \log N)$ | $O(N)$ |
| **Quick Sort** | $\Omega(N \log N)$ | $\Theta(N \log N)$ | $O(N^2)$ | $O(\log N)$ |

### The "Why":
- **Bubble Sort:** 
  - **Best Case ($\Omega(N)$):** If you use an optimized bubble sort and the array is *already sorted*, it makes one pass, sees zero swaps were needed, and instantly stops.
- **Selection Sort:** 
  - **All Cases ($\Theta(N^2)$):** It is "dumb." Even if the array is already sorted, it still scans the entire remaining array every single time to find the absolute minimum. It never stops early.
- **Insertion Sort:**
  - **Best Case ($\Omega(N)$):** The array is already sorted. The inner shifting loop never triggers. It just walks through the array once.
- **Merge Sort:**
  - **All Cases ($\Theta(N \log N)$):** It blindly cuts the array in half all the way down to 1, and blindly merges them back. It doesn't care if the array is already sorted. It guarantees absolute consistency at the cost of $O(N)$ extra memory.
- **Quick Sort:**
  - **Best/Avg Case ($\Theta(N \log N)$):** The chosen pivot consistently cuts the array nicely into two relatively equal halves.
  - **Worst Case ($O(N^2)$):** The array is already sorted, and you stubbornly pick the last element as the pivot. Instead of cutting the array in half, it peels off exactly 1 element, degrading into a slow $N^2$ loop.

---

## 🧱 3. Core Data Structures (Arrays & Linked Lists)

### **Arrays (Dynamic/Static)**
| Operation | Best Case ($\Omega$) | Average Case ($\Theta$) | Worst Case ($O$) |
| :--- | :--- | :--- | :--- |
| **Access (Index)** | $\Omega(1)$ | $\Theta(1)$ | $O(1)$ |
| **Insert/Delete** | $\Omega(1)$ | $\Theta(N)$ | $O(N)$ |

- **Why Access is $O(1)$:** Memory is contiguous. The computer uses a math formula (`Base_Address + Index * Size`) to instantly jump to the physical memory location without searching.
- **Why Insert is $O(N)$:** If you insert at the very beginning (Worst Case), every single other element must physically shift one space to the right to make room. (Inserting at the very end is Best Case $O(1)$).

### **Singly & Doubly Linked Lists**
| Operation | Best Case ($\Omega$) | Average Case ($\Theta$) | Worst Case ($O$) |
| :--- | :--- | :--- | :--- |
| **Access (Search)**| $\Omega(1)$ | $\Theta(N)$ | $O(N)$ |
| **Insert/Delete** | $\Omega(1)$ | $\Theta(1)$ | $O(1)$ |

- **Why Access is $O(N)$:** Nodes are scattered randomly in memory. There is no index. You MUST start at the `head` and traverse node-by-node.
- **Why Insert is $O(1)$:** If you already have a pointer to the location, inserting simply requires re-routing 2 pointer links. No elements are ever shifted.

---

## 🥞 4. Stacks & Queues

| Operation | Best Case ($\Omega$) | Average Case ($\Theta$) | Worst Case ($O$) |
| :--- | :--- | :--- | :--- |
| **Push/Enqueue** | $\Omega(1)$ | $\Theta(1)$ | $O(1)$ |
| **Pop/Dequeue** | $\Omega(1)$ | $\Theta(1)$ | $O(1)$ |

### The "Why":
- **Stacks (LIFO):** You only ever interact with the `top`. You never search or shift the bottom. Therefore, it is strictly $O(1)$.
- **Queues (FIFO):** You only add to the `rear` and remove from the `front`. Because you explicitly maintain pointers to both ends, it is strictly $O(1)$.

---

## 🌳 5. Trees

### **Binary Search Tree (BST)**
| Operation | Best Case ($\Omega$) | Average Case ($\Theta$) | Worst Case ($O$) |
| :--- | :--- | :--- | :--- |
| **Search/Insert** | $\Omega(1)$ | $\Theta(\log N)$ | $O(N)$ |

- **Average Case ($\Theta(\log N)$):** The tree is somewhat bushy. Every time you go left or right, you eliminate half the remaining nodes, identical to Binary Search logic.
- **Worst Case ($O(N)$):** The data was inserted in sorted order (1, 2, 3, 4). The tree formed a single right-leaning straight line (a "Skewed Tree"). It loses all its "half-cutting" power and becomes a slow Linked List.

### **AVL Trees & B-Trees (Self-Balancing)**
| Operation | Best Case ($\Omega$) | Average Case ($\Theta$) | Worst Case ($O$) |
| :--- | :--- | :--- | :--- |
| **Search/Insert** | $\Omega(1)$ | $\Theta(\log N)$ | $O(\log N)$ |

- **Why Worst Case is protected at $O(\log N)$:** AVL trees mathematically calculate a Balance Factor. If the tree starts becoming a straight line (skewed), it executes a physical Rotation to perfectly re-balance itself. It literally forbids the $O(N)$ worst-case from ever existing.

---

## 🕸️ 6. Graphs & Graph Algorithms

### **Traversal: Breadth-First (BFS) & Depth-First (DFS)**
- **Time Complexity:** $O(V + E)$ where $V$ is Vertices (nodes) and $E$ is Edges (lines).
- **The "Why":** To fully explore a graph, you must visit every single city ($V$) and travel down every single highway ($E$) exactly once.

### **Dijkstra's Shortest Path Algorithm**
- **Time Complexity:** $O((V + E) \log V)$ (when using a Min-Heap/Priority Queue).
- **The "Why":** You explore every edge ($E$), and every time you find a shorter route, you update the Min-Heap. Updating a Min-Heap takes $\log V$ time.

### **Prim's Algorithm (Minimum Spanning Tree)**
- **Time Complexity:** $O((V + E) \log V)$
- **The "Why":** Very similar to Dijkstra. It aggressively chooses the cheapest connecting edge using a Min-Heap ($\log V$).

---

## 🗄️ 7. Hashing (Direct Access)

| Operation | Best Case ($\Omega$) | Average Case ($\Theta$) | Worst Case ($O$) |
| :--- | :--- | :--- | :--- |
| **Search/Insert** | $\Omega(1)$ | $\Theta(1)$ | $O(N)$ |

### The "Why":
- **Best/Avg Case ($\Theta(1)$):** You pass a key through a math function (Hash Function). It instantly calculates the exact memory index to place the data. Lightning fast.
- **Worst Case ($O(N)$):** **A Collision.** If the hash function accidentally calculates the exact same index for 50 different items, they all get stuffed into a single Linked List at that slot. You must now traverse that slow Linked List to find your item.
