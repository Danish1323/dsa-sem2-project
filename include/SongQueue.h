#ifndef SONG_QUEUE_H
#define SONG_QUEUE_H

#include <string>
#include <vector>

struct QueueNode {
    std::string title;
    std::string artist;
    QueueNode* next;

    QueueNode(std::string t, std::string a) : title(t), artist(a), next(nullptr) {}
};

class SongQueue {
private:
    QueueNode* frontNode;
    QueueNode* rearNode;
    int size;

public:
    SongQueue();
    ~SongQueue();

    // Prevent copy constructor and assignment
    SongQueue(const SongQueue&) = delete;
    SongQueue& operator=(const SongQueue&) = delete;

    // Queue operations (Complexity: O(1))
    void enqueue(std::string title, std::string artist);
    bool dequeue(std::string& title, std::string& artist);
    bool isEmpty() const;
    int getSize() const;
    void clear();

    std::vector<std::pair<std::string, std::string>> getQueue() const;
};

#endif // SONG_QUEUE_H
