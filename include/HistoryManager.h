#ifndef HISTORY_MANAGER_H
#define HISTORY_MANAGER_H

#include <string>
#include <vector>

struct HistoryNode {
    std::string title;
    std::string artist;
    HistoryNode* next;

    HistoryNode(std::string t, std::string a) : title(t), artist(a), next(nullptr) {}
};

class HistoryManager {
private:
    HistoryNode* topNode;
    int size;

public:
    HistoryManager();
    ~HistoryManager();

    // Prevent copy constructor and assignment
    HistoryManager(const HistoryManager&) = delete;
    HistoryManager& operator=(const HistoryManager&) = delete;

    // Stack operations
    void push(std::string title, std::string artist);
    bool pop(std::string& title, std::string& artist);
    bool isEmpty() const;
    int getSize() const;
    void clear();

    // Return all items in the stack from top (most recent) to bottom
    std::vector<std::pair<std::string, std::string>> getHistory() const;
};

#endif // HISTORY_MANAGER_H
