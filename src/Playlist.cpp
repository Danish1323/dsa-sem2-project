#include "../include/Playlist.h"
#include <algorithm>
#include <random>
#include <set>
#include <iostream>

// Helper function for case-insensitive string comparison
static std::string toLower(std::string s) {
    std::transform(s.begin(), s.end(), s.begin(), [](unsigned char c) {
        return std::tolower(c);
    });
    return s;
}

Playlist::Playlist(std::string name)
    : name(name), head(nullptr), tail(nullptr), current(nullptr), songCount(0) {}

Playlist::~Playlist() {
    clear();
}

std::string Playlist::getName() const {
    return name;
}

Song* Playlist::getHead() const {
    return head;
}

Song* Playlist::getTail() const {
    return tail;
}

Song* Playlist::getCurrent() const {
    return current;
}

int Playlist::getSongCount() const {
    return songCount;
}

void Playlist::setCurrent(Song* song) {
    current = song;
}

Song* Playlist::playNext() {
    if (current && current->next) {
        current = current->next;
        return playCurrent();
    }
    return nullptr; // No next song
}

Song* Playlist::playPrevious() {
    if (current && current->prev) {
        current = current->prev;
        return playCurrent();
    }
    return nullptr; // No previous song
}

Song* Playlist::playCurrent() {
    if (current) {
        current->playCount++;
        return current;
    }
    return nullptr;
}

void Playlist::insertAtBeginning(std::string title, std::string artist, std::string album) {
    Song* newSong = new Song(title, artist, album);
    if (!head) {
        head = tail = current = newSong;
    } else {
        newSong->next = head;
        head->prev = newSong;
        head = newSong;
    }
    songCount++;
}

void Playlist::insertAtEnd(std::string title, std::string artist, std::string album) {
    Song* newSong = new Song(title, artist, album);
    if (!tail) {
        head = tail = current = newSong;
    } else {
        tail->next = newSong;
        newSong->prev = tail;
        tail = newSong;
    }
    songCount++;
}

bool Playlist::insertAfter(const std::string& afterTitle, std::string title, std::string artist, std::string album) {
    Song* afterSong = searchByTitle(afterTitle);
    if (!afterSong) {
        return false;
    }

    Song* newSong = new Song(title, artist, album);
    newSong->next = afterSong->next;
    newSong->prev = afterSong;

    if (afterSong->next) {
        afterSong->next->prev = newSong;
    } else {
        tail = newSong; // If afterSong was the tail, newSong is now the tail
    }
    afterSong->next = newSong;
    songCount++;
    return true;
}

bool Playlist::deleteCurrent() {
    if (!current) {
        return false;
    }

    Song* toDelete = current;

    if (current == head) {
        head = head->next;
    }
    if (current == tail) {
        tail = tail->prev;
    }

    if (current->prev) {
        current->prev->next = current->next;
    }
    if (current->next) {
        current->next->prev = current->prev;
    }

    // Set new current
    if (toDelete->next) {
        current = toDelete->next;
    } else if (toDelete->prev) {
        current = toDelete->prev;
    } else {
        current = nullptr;
    }

    delete toDelete;
    songCount--;
    return true;
}

bool Playlist::deleteByTitle(const std::string& title) {
    Song* toDelete = searchByTitle(title);
    if (!toDelete) {
        return false;
    }

    if (toDelete == current) {
        return deleteCurrent();
    }

    if (toDelete == head) {
        head = head->next;
    }
    if (toDelete == tail) {
        tail = tail->prev;
    }

    if (toDelete->prev) {
        toDelete->prev->next = toDelete->next;
    }
    if (toDelete->next) {
        toDelete->next->prev = toDelete->prev;
    }

    delete toDelete;
    songCount--;
    return true;
}

Song* Playlist::searchByTitle(const std::string& title) {
    Song* temp = head;
    std::string searchLower = toLower(title);
    while (temp) {
        if (toLower(temp->title) == searchLower) {
            return temp;
        }
        temp = temp->next;
    }
    return nullptr;
}

void Playlist::shuffle() {
    if (songCount <= 1) {
        return; // Nothing to shuffle
    }

    // Copy node pointers to a vector
    std::vector<Song*> songs;
    Song* temp = head;
    while (temp) {
        songs.push_back(temp);
        temp = temp->next;
    }

    // Shuffle the vector using random_device and mt19937
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(songs.begin(), songs.end(), g);

    // Rebuild the Doubly Linked List pointers
    head = songs[0];
    head->prev = nullptr;
    for (size_t i = 1; i < songs.size(); ++i) {
        songs[i-1]->next = songs[i];
        songs[i]->prev = songs[i-1];
    }
    tail = songs.back();
    tail->next = nullptr;

    // Reset current to the new head
    current = head;
}

int Playlist::getTotalPlays() const {
    int total = 0;
    Song* temp = head;
    while (temp) {
        total += temp->playCount;
        temp = temp->next;
    }
    return total;
}

Song* Playlist::getMostPlayedSong() const {
    if (!head) return nullptr;
    
    Song* mostPlayed = head;
    Song* temp = head->next;
    while (temp) {
        if (temp->playCount > mostPlayed->playCount) {
            mostPlayed = temp;
        }
        temp = temp->next;
    }
    return mostPlayed;
}

int Playlist::getUniqueArtistsCount() const {
    std::set<std::string> artists;
    Song* temp = head;
    while (temp) {
        artists.insert(temp->artist);
        temp = temp->next;
    }
    return artists.size();
}

void Playlist::clear() {
    Song* temp = head;
    while (temp) {
        Song* nextSong = temp->next;
        delete temp;
        temp = nextSong;
    }
    head = tail = current = nullptr;
    songCount = 0;
}
