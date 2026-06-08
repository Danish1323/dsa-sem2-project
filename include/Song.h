#ifndef SONG_H
#define SONG_H

#include <string>

class Song {
public:
    std::string title;
    std::string artist;
    std::string album;
    int playCount;

    Song* prev;
    Song* next;

    Song(std::string t, std::string a, std::string alb = "", int pc = 0)
        : title(t), artist(a), album(alb), playCount(pc), prev(nullptr), next(nullptr) {}
};

#endif // SONG_H
