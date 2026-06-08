#include "UI.h"
#include <iostream>
#include <iomanip>

namespace Color {
    const std::string RESET = "\033[0m";
    const std::string BOLD = "\033[1m";
    const std::string RED = "\033[31m";
    const std::string GREEN = "\033[32m";
    const std::string YELLOW = "\033[33m";
    const std::string BLUE = "\033[34m";
    const std::string MAGENTA = "\033[35m";
    const std::string CYAN = "\033[36m";
    const std::string BOLD_RED = "\033[1;31m";
    const std::string BOLD_GREEN = "\033[1;32m";
    const std::string BOLD_YELLOW = "\033[1;33m";
    const std::string BOLD_BLUE = "\033[1;34m";
    const std::string BOLD_MAGENTA = "\033[1;35m";
    const std::string BOLD_CYAN = "\033[1;36m";
    const std::string BOLD_WHITE = "\033[1;37m";
}

void UI::clearScreen() {
    std::cout << "\033[2J\033[1;1H";
}

void UI::drawLine(int width, std::string color) {
    std::cout << color;
    for (int i = 0; i < width; ++i) {
        std::cout << "─";
    }
    std::cout << Color::RESET << "\n";
}

std::string UI::getTruncatedString(const std::string& str, size_t maxLength) {
    if (str.length() > maxLength) {
        return str.substr(0, maxLength - 3) + "...";
    }
    return str;
}

void UI::printHeader() {
    std::cout << Color::BOLD_CYAN;
    std::cout << "╔══════════════════════════════════════════════════════════╗\n";
    std::cout << "║                     TERMINALTUNES                        ║\n";
    std::cout << "║          - Dynamic C++ DLL Music Simulator -             ║\n";
    std::cout << "╚══════════════════════════════════════════════════════════╝\n";
    std::cout << Color::RESET;
}

void UI::printDashboard(Playlist* activePlaylist, const HistoryManager& history, const SongQueue& queue, const std::vector<Playlist*>& playlists, bool developerMode, bool isPlaying) {
    printHeader();
    
    // Playlists status
    std::cout << Color::BOLD_WHITE << "  Playlists:  " << Color::RESET;
    if (playlists.empty()) {
        std::cout << Color::RED << "(None)" << Color::RESET;
    } else {
        for (size_t i = 0; i < playlists.size(); ++i) {
            if (activePlaylist && playlists[i]->getName() == activePlaylist->getName()) {
                std::cout << Color::BOLD_GREEN << "[" << playlists[i]->getName() << "] " << Color::RESET;
            } else {
                std::cout << Color::CYAN << playlists[i]->getName() << "  " << Color::RESET;
            }
        }
    }
    std::cout << "\n";
    
    drawLine(60, Color::CYAN);
    
    // Now playing card
    std::cout << Color::BOLD_YELLOW << "  NOW PLAYING  " << Color::RESET;
    if (activePlaylist && activePlaylist->getCurrent()) {
        if (isPlaying) {
            std::cout << Color::BOLD_GREEN << "▶ PLAYING" << Color::RESET << "\n";
        } else {
            std::cout << Color::BOLD_RED << "❚❚ PAUSED" << Color::RESET << "\n";
        }
        
        Song* cur = activePlaylist->getCurrent();
        std::cout << "  Title:  " << Color::BOLD_WHITE << cur->title << Color::RESET << "\n";
        std::cout << "  Artist: " << Color::CYAN << cur->artist << Color::RESET << "\n";
        if (!cur->album.empty()) {
            std::cout << "  Album:  " << Color::MAGENTA << cur->album << Color::RESET << "\n";
        }
        std::cout << "  Plays:  " << Color::YELLOW << cur->playCount << Color::RESET << "\n";
    } else {
        std::cout << Color::BOLD_RED << "❚❚ STOPPED" << Color::RESET << "\n";
        std::cout << Color::RED << "  No active song. Add or select a song in the current playlist.\n" << Color::RESET;
    }
    
    drawLine(60, Color::CYAN);
    
    // Quick statistics overview
    if (activePlaylist) {
        std::cout << "  Active Playlist: " << Color::BOLD_CYAN << activePlaylist->getName() << Color::RESET << "\n"
                  << "  Total Songs:     " << Color::BOLD_YELLOW << activePlaylist->getSongCount() << Color::RESET << "\n"
                  << "  Up Next Queue:   " << Color::BOLD_MAGENTA << queue.getSize() << " songs" << Color::RESET << "\n"
                  << "  History Stack:   " << Color::BOLD_BLUE << history.getSize() << " played" << Color::RESET << "\n";
    } else {
        std::cout << Color::YELLOW << "  No playlist selected. Use 'create' or 'switch' to start.\n" << Color::RESET;
    }
    
    if (developerMode) {
        drawLine(60, Color::MAGENTA);
        printDeveloperMode(activePlaylist);
    }
    
    drawLine(60, Color::CYAN);
}

void UI::printDeveloperMode(Playlist* activePlaylist) {
    std::cout << Color::BOLD_MAGENTA << "  [DEVELOPER MODE: Doubly Linked List Visualizer]" << Color::RESET << "\n  ";
    if (!activePlaylist || !activePlaylist->getHead()) {
        std::cout << Color::BOLD_WHITE << "NULL" << Color::RESET << "\n";
        return;
    }
    
    std::cout << Color::BOLD_WHITE << "NULL" << Color::RESET;
    
    Song* temp = activePlaylist->getHead();
    while (temp) {
        std::cout << Color::YELLOW << " ◀──▶ " << Color::RESET;
        std::string label = getTruncatedString(temp->title, 12);
        if (temp == activePlaylist->getCurrent()) {
            std::cout << Color::BOLD_GREEN << "⟦ " << label << " (plays: " << temp->playCount << ") ⟧" << Color::RESET;
        } else {
            std::cout << Color::CYAN << "[" << label << "]" << Color::RESET;
        }
        temp = temp->next;
    }
    std::cout << Color::YELLOW << " ──▶ " << Color::BOLD_WHITE << "NULL" << Color::RESET << "\n";
}

void UI::printStatistics(Playlist* activePlaylist) {
    if (!activePlaylist) {
        std::cout << Color::RED << "  No active playlist to view statistics.\n" << Color::RESET;
        return;
    }
    
    std::cout << Color::BOLD_YELLOW << "╔══════════════════════════════════════════════════════════╗\n";
    std::cout << "║                   PLAYLIST STATISTICS                    ║\n";
    std::cout << "╚══════════════════════════════════════════════════════════╝\n" << Color::RESET;
    std::cout << "  Playlist Name:       " << Color::BOLD_CYAN << activePlaylist->getName() << Color::RESET << "\n";
    std::cout << "  Total Songs:         " << Color::BOLD_WHITE << activePlaylist->getSongCount() << Color::RESET << "\n";
    std::cout << "  Total Plays:         " << Color::BOLD_GREEN << activePlaylist->getTotalPlays() << Color::RESET << "\n";
    std::cout << "  Unique Artists:      " << Color::BOLD_BLUE << activePlaylist->getUniqueArtistsCount() << Color::RESET << "\n";
    
    Song* mostPlayed = activePlaylist->getMostPlayedSong();
    if (mostPlayed && mostPlayed->playCount > 0) {
        std::cout << "  Most Played Song:    " << Color::BOLD_MAGENTA << mostPlayed->title 
                  << Color::RESET << " by " << Color::CYAN << mostPlayed->artist 
                  << Color::RESET << " (" << Color::YELLOW << mostPlayed->playCount << " plays)" << Color::RESET << "\n";
    } else {
        std::cout << "  Most Played Song:    " << Color::RED << "N/A (No songs have play counts yet)\n" << Color::RESET;
    }
}

void UI::printHistory(const HistoryManager& history) {
    std::cout << Color::BOLD_YELLOW << "╔══════════════════════════════════════════════════════════╗\n";
    std::cout << "║                    LISTENING HISTORY                     ║\n";
    std::cout << "║                  (Stack: Most Recent First)              ║\n";
    std::cout << "╚══════════════════════════════════════════════════════════╝\n" << Color::RESET;
    
    auto items = history.getHistory();
    if (items.empty()) {
        std::cout << Color::RED << "  History is empty. Play some songs to populate!\n" << Color::RESET;
        return;
    }
    
    for (size_t i = 0; i < items.size(); ++i) {
        std::cout << "  " << std::setw(2) << (i + 1) << ". " 
                  << Color::BOLD_WHITE << items[i].first << Color::RESET 
                  << " by " << Color::CYAN << items[i].second << Color::RESET << "\n";
    }
}

void UI::printQueue(const SongQueue& queue) {
    std::cout << Color::BOLD_YELLOW << "╔══════════════════════════════════════════════════════════╗\n";
    std::cout << "║                       SONG QUEUE                         ║\n";
    std::cout << "║                  (Queue: First In First Out)             ║\n";
    std::cout << "╚══════════════════════════════════════════════════════════╝\n" << Color::RESET;
    
    auto items = queue.getQueue();
    if (items.empty()) {
        std::cout << Color::RED << "  Queue is empty. Type 'queue' to add songs next-up!\n" << Color::RESET;
        return;
    }
    
    for (size_t i = 0; i < items.size(); ++i) {
        std::cout << "  " << std::setw(2) << (i + 1) << ". " 
                  << Color::BOLD_WHITE << items[i].first << Color::RESET 
                  << " by " << Color::CYAN << items[i].second << Color::RESET << "\n";
    }
}

void UI::printMessage(const std::string& msg, std::string type) {
    if (type == "success") {
        std::cout << Color::BOLD_GREEN << "  ✔ " << msg << Color::RESET << "\n";
    } else if (type == "error") {
        std::cout << Color::BOLD_RED << "  ✘ " << msg << Color::RESET << "\n";
    } else if (type == "warning") {
        std::cout << Color::BOLD_YELLOW << "  ⚠ " << msg << Color::RESET << "\n";
    } else {
        std::cout << Color::BOLD_BLUE << "  ℹ " << msg << Color::RESET << "\n";
    }
}

void UI::printLibrarySongs(const std::vector<LibrarySong>& songs, const std::string& title) {
    std::cout << Color::BOLD_YELLOW << "╔══════════════════════════════════════════════════════════╗\n";
    // Using string subtraction to center it roughly
    std::string cleanTitle = title;
    if (cleanTitle.length() > 50) cleanTitle = cleanTitle.substr(0, 47) + "...";
    std::cout << "║ " << std::left << std::setw(56) << cleanTitle << "║\n";
    std::cout << "╚══════════════════════════════════════════════════════════╝\n" << Color::RESET;
    
    if (songs.empty()) {
        std::cout << Color::RED << "  No songs found in the library catalog.\n" << Color::RESET;
        return;
    }
    
    std::cout << "  " << Color::BOLD_WHITE 
              << std::left << std::setw(6) << "Index" 
              << std::left << std::setw(25) << "Song Title" 
              << std::left << std::setw(20) << "Artist" 
              << "Album" << Color::RESET << "\n";
    drawLine(60, Color::CYAN);
    
    for (size_t i = 0; i < songs.size(); ++i) {
        std::cout << "  " << std::left << std::setw(6) << (i + 1)
                  << std::left << std::setw(25) << getTruncatedString(songs[i].title, 22)
                  << std::left << std::setw(20) << getTruncatedString(songs[i].artist, 18)
                  << getTruncatedString(songs[i].album, 18) << "\n";
    }
}

void UI::printHelp() {
    std::cout << Color::BOLD_YELLOW << "  AVAILABLE COMMANDS:\n" << Color::RESET;
    std::cout << Color::CYAN << "  [Navigation]\n" << Color::RESET;
    std::cout << "    next         - Play next song in playlist\n";
    std::cout << "    prev         - Play previous song in playlist\n";
    std::cout << "    play         - Play/resume current song\n";
    std::cout << "    pause        - Pause playback\n";
    std::cout << "    select       - Search and jump to a specific song\n";
    
    std::cout << Color::CYAN << "  [Playlist Management]\n" << Color::RESET;
    std::cout << "    add          - Add a new song to active playlist\n";
    std::cout << "    delete       - Delete a song from active playlist\n";
    std::cout << "    create       - Create a new empty playlist\n";
    std::cout << "    switch       - Switch to another playlist\n";
    std::cout << "    shuffle      - Shuffle active playlist in-place\n";
    std::cout << "    display      - List all songs in active playlist\n";
    
    std::cout << Color::CYAN << "  [Song Library Catalog]\n" << Color::RESET;
    std::cout << "    library      - Search & browse general song catalog\n";
    
    std::cout << Color::CYAN << "  [Queue & History]\n" << Color::RESET;
    std::cout << "    queue        - Add a song to play next, or view queue\n";
    std::cout << "    history      - View recently played songs stack\n";
    
    std::cout << Color::CYAN << "  [Stats & Developer]\n" << Color::RESET;
    std::cout << "    stats        - Show active playlist statistics dashboard\n";
    std::cout << "    dev          - Toggle Developer Mode (DLL Visualizer)\n";
    
    std::cout << Color::CYAN << "  [General]\n" << Color::RESET;
    std::cout << "    help         - Display this command list\n";
    std::cout << "    exit         - Quit TerminalTunes\n";
}

