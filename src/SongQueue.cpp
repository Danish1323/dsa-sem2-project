#include "SongQueue.h"

SongQueue::SongQueue() : frontNode(nullptr), rearNode(nullptr), size(0) {}

SongQueue::~SongQueue() {
    clear();
}

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

bool SongQueue::dequeue(std::string& title, std::string& artist) {
    if (isEmpty()) {
        return false;
    }
    QueueNode* toDelete = frontNode;
    title = frontNode->title;
    artist = frontNode->artist;
    
    frontNode = frontNode->next;
    if (!frontNode) {
        rearNode = nullptr;
    }
    
    delete toDelete;
    size--;
    return true;
}

bool SongQueue::isEmpty() const {
    return frontNode == nullptr;
}

int SongQueue::getSize() const {
    return size;
}

void SongQueue::clear() {
    QueueNode* temp = frontNode;
    while (temp) {
        QueueNode* nextNode = temp->next;
        delete temp;
        temp = nextNode;
    }
    frontNode = rearNode = nullptr;
    size = 0;
}

std::vector<std::pair<std::string, std::string>> SongQueue::getQueue() const {
    std::vector<std::pair<std::string, std::string>> queueList;
    QueueNode* temp = frontNode;
    while (temp) {
        queueList.push_back({temp->title, temp->artist});
        temp = temp->next;
    }
    return queueList;
}
