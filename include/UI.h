#ifndef UI_H
#define UI_H

#include "Playlist.h"
#include "HistoryManager.h"
#include "SongQueue.h"
#include "SongLibrary.h"
#include <string>
#include <vector>

namespace Color {
    extern const std::string RESET;
    extern const std::string BOLD;
    extern const std::string RED;
    extern const std::string GREEN;
    extern const std::string YELLOW;
    extern const std::string BLUE;
    extern const std::string MAGENTA;
    extern const std::string CYAN;
    extern const std::string BOLD_RED;
    extern const std::string BOLD_GREEN;
    extern const std::string BOLD_YELLOW;
    extern const std::string BOLD_BLUE;
    extern const std::string BOLD_MAGENTA;
    extern const std::string BOLD_CYAN;
    extern const std::string BOLD_WHITE;
}

class UI {
public:
    static void clearScreen();
    static void drawLine(int width, std::string color = Color::RESET);
    static void printHeader();
    static void printDashboard(Playlist* activePlaylist, const HistoryManager& history, const SongQueue& queue, const std::vector<Playlist*>& playlists, bool developerMode, bool isPlaying);
    static void printDeveloperMode(Playlist* activePlaylist);
    static void printStatistics(Playlist* activePlaylist);
    static void printHistory(const HistoryManager& history);
    static void printQueue(const SongQueue& queue);
    static void printLibrarySongs(const std::vector<LibrarySong>& songs, const std::string& title = "GENERAL SONG LIBRARY");
    static void printMessage(const std::string& msg, std::string type = "info");
    static void printHelp();
    static std::string getTruncatedString(const std::string& str, size_t maxLength);
};

#endif // UI_H
