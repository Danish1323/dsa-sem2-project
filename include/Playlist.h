#ifndef PLAYLIST_H
#define PLAYLIST_H

#include "Song.h"
#include <string>
#include <vector>

class Playlist {
private:
    std::string name;
    Song* head;
    Song* tail;
    Song* current;
    int songCount;

public:
    Playlist(std::string name);
    ~Playlist();

    // Prevent copy construction and assignment to protect pointers
    Playlist(const Playlist&) = delete;
    Playlist& operator=(const Playlist&) = delete;

    std::string getName() const;
    Song* getHead() const;
    Song* getTail() const;
    Song* getCurrent() const;
    int getSongCount() const;

    void setCurrent(Song* song);

    // Song navigation (Complexity: O(1))
    Song* playNext();
    Song* playPrevious();
    Song* playCurrent(); // Plays the current song (increments playCount)

    // Song Insertion (Complexity: O(1) where node reference is known, O(1) for beg/end)
    void insertAtBeginning(std::string title, std::string artist, std::string album = "");
    void insertAtEnd(std::string title, std::string artist, std::string album = "");
    bool insertAfter(const std::string& afterTitle, std::string title, std::string artist, std::string album = "");

    // Song Deletion (Complexity: O(1) if node is known/current, O(n) if searching by title)
    bool deleteCurrent();
    bool deleteByTitle(const std::string& title);

    // Search (Complexity: O(n))
    Song* searchByTitle(const std::string& title);

    // Shuffle (Complexity: O(n))
    void shuffle();

    // Statistics Helpers
    int getTotalPlays() const;
    Song* getMostPlayedSong() const;
    int getUniqueArtistsCount() const;
    
    // Clear list
    void clear();
};

#endif // PLAYLIST_H
