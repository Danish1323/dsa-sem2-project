#ifndef SONG_LIBRARY_H
#define SONG_LIBRARY_H

#include <string>
#include <vector>

struct LibrarySong {
    std::string title;
    std::string artist;
    std::string album;
};

class SongLibrary {
private:
    std::vector<LibrarySong> songs;

public:
    SongLibrary();
    
    // Returns all songs in the library
    const std::vector<LibrarySong>& getAllSongs() const;
    
    // Searches songs by title, artist, or album (case-insensitive)
    std::vector<LibrarySong> searchSongs(const std::string& query) const;
    
private:
    void loadDefaultSongs();
};

#endif // SONG_LIBRARY_H
