#include "../include/HistoryManager.h"

HistoryManager::HistoryManager() : topNode(nullptr), size(0) {}

HistoryManager::~HistoryManager() {
    clear();
}

void HistoryManager::push(std::string title, std::string artist) {
    HistoryNode* newNode = new HistoryNode(title, artist);
    newNode->next = topNode;
    topNode = newNode;
    size++;
}

bool HistoryManager::pop(std::string& title, std::string& artist) {
    if (isEmpty()) {
        return false;
    }
    HistoryNode* toDelete = topNode;
    title = topNode->title;
    artist = topNode->artist;
    topNode = topNode->next;
    delete toDelete;
    size--;
    return true;
}

bool HistoryManager::isEmpty() const {
    return topNode == nullptr;
}

int HistoryManager::getSize() const {
    return size;
}

void HistoryManager::clear() {
    HistoryNode* temp = topNode;
    while (temp) {
        HistoryNode* nextNode = temp->next;
        delete temp;
        temp = nextNode;
    }
    topNode = nullptr;
    size = 0;
}

std::vector<std::pair<std::string, std::string>> HistoryManager::getHistory() const {
    std::vector<std::pair<std::string, std::string>> historyList;
    HistoryNode* temp = topNode;
    while (temp) {
        historyList.push_back({temp->title, temp->artist});
        temp = temp->next;
    }
    return historyList;
}
