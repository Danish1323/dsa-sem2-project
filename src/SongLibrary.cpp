#include "../include/SongLibrary.h"
#include <algorithm>

// Helper to convert string to lowercase
static std::string toLower(std::string s) {
    std::transform(s.begin(), s.end(), s.begin(), [](unsigned char c) {
        return std::tolower(c);
    });
    return s;
}

SongLibrary::SongLibrary() {
    loadDefaultSongs();
}

const std::vector<LibrarySong>& SongLibrary::getAllSongs() const {
    return songs;
}

std::vector<LibrarySong> SongLibrary::searchSongs(const std::string& query) const {
    if (query.empty()) {
        return songs;
    }
    
    std::string queryLower = toLower(query);
    std::vector<LibrarySong> results;
    
    for (const auto& song : songs) {
        if (toLower(song.title).find(queryLower) != std::string::npos ||
            toLower(song.artist).find(queryLower) != std::string::npos ||
            toLower(song.album).find(queryLower) != std::string::npos) {
            results.push_back(song);
        }
    }
    
    return results;
}

void SongLibrary::loadDefaultSongs() {
    songs = {
        // Rock / Classic Rock
        {"Numb", "Linkin Park", "Meteora"},
        {"In The End", "Linkin Park", "Hybrid Theory"},
        {"Faint", "Linkin Park", "Meteora"},
        {"Hotel California", "Eagles", "Hotel California"},
        {"Bohemian Rhapsody", "Queen", "A Night at the Opera"},
        {"Another One Bites the Dust", "Queen", "The Game"},
        {"Smells Like Teen Spirit", "Nirvana", "Nevermind"},
        {"Sweet Child O' Mine", "Guns N' Roses", "Appetite for Destruction"},
        
        // Pop Hits
        {"Blinding Lights", "The Weeknd", "After Hours"},
        {"Starboy", "The Weeknd", "Starboy"},
        {"Save Your Tears", "The Weeknd", "After Hours"},
        {"Shape of You", "Ed Sheeran", "Divide"},
        {"Perfect", "Ed Sheeran", "Divide"},
        {"Bad Habits", "Ed Sheeran", "Equals"},
        {"As It Was", "Harry Styles", "Harry's House"},
        {"Billie Jean", "Michael Jackson", "Thriller"},
        
        // Synthwave / Drive
        {"Nightcall", "Kavinsky", "Outrun"},
        {"Midnight City", "M83", "Hurry Up, We're Dreaming"},
        
        // Hip-hop
        {"Lose Yourself", "Eminem", "8 Mile"},
        {"Till I Collapse", "Eminem", "The Eminem Show"},
        
        // Modern Rock / Pop
        {"Believer", "Imagine Dragons", "Evolve"},
        {"Radioactive", "Imagine Dragons", "Night Visions"},
        {"Stay", "The Kid LAROI", "F*CK LOVE 3: Over You"},
        {"Take On Me", "a-ha", "Hunting High and Low"}
    };
}
