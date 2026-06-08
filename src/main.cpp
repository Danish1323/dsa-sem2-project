#include "Song.h"
#include "Playlist.h"
#include "HistoryManager.h"
#include "SongQueue.h"
#include "UI.h"
#include "SongLibrary.h"
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <algorithm>

// Safe input helper functions
std::string getInputLine(const std::string& prompt) {
    std::cout << prompt;
    std::string line;
    std::getline(std::cin, line);
    // Trim leading/trailing whitespace
    size_t start = line.find_first_not_of(" \t");
    size_t end = line.find_last_not_of(" \t");
    if (start == std::string::npos) return "";
    return line.substr(start, end - start + 1);
}

int getInputInt(const std::string& prompt) {
    while (true) {
        std::cout << prompt;
        std::string line;
        std::getline(std::cin, line);
        try {
            return std::stoi(line);
        } catch (...) {
            std::cout << Color::BOLD_RED << "  ✘ Invalid input. Please enter a valid number.\n" << Color::RESET;
        }
    }
}

// Case-insensitive comparison helper
bool equalsIgnoreCase(const std::string& a, const std::string& b) {
    if (a.length() != b.length()) return false;
    return std::equal(a.begin(), a.end(), b.begin(), [](char ac, char bc) {
        return std::tolower(ac) == std::tolower(bc);
    });
}

// Seed playlists with awesome starting data
void seedPlaylists(std::vector<Playlist*>& playlists) {
    Playlist* rock = new Playlist("Rock Legends");
    rock->insertAtEnd("Numb", "Linkin Park", "Meteora");
    rock->insertAtEnd("In The End", "Linkin Park", "Hybrid Theory");
    rock->insertAtEnd("Faint", "Linkin Park", "Meteora");
    rock->insertAtEnd("Hotel California", "Eagles", "Hotel California");
    rock->insertAtEnd("Bohemian Rhapsody", "Queen", "A Night at the Opera");
    playlists.push_back(rock);

    Playlist* pop = new Playlist("Pop Hits");
    pop->insertAtEnd("Blinding Lights", "The Weeknd", "After Hours");
    pop->insertAtEnd("Shape of You", "Ed Sheeran", "Divide");
    pop->insertAtEnd("As It Was", "Harry Styles", "Harry's House");
    playlists.push_back(pop);

    Playlist* drive = new Playlist("Midnight Drive");
    drive->insertAtEnd("Nightcall", "Kavinsky", "Outrun");
    drive->insertAtEnd("Starboy", "The Weeknd", "Starboy");
    drive->insertAtEnd("Midnight City", "M83", "Hurry Up, We're Dreaming");
    playlists.push_back(drive);

    Playlist* favs = new Playlist("Personal Favorites");
    playlists.push_back(favs);
}

int main() {
    std::vector<Playlist*> playlists;
    seedPlaylists(playlists);
    
    Playlist* activePlaylist = playlists[0];
    HistoryManager history;
    SongQueue queue;
    SongLibrary songLib;
    
    bool developerMode = true; // Default to true to show DLL visualizer
    bool isPlaying = false;
    std::string lastMessage = "Welcome to TerminalTunes! Type 'help' for commands.";
    std::string lastMessageType = "info";

    while (true) {
        UI::clearScreen();
        UI::printDashboard(activePlaylist, history, queue, playlists, developerMode, isPlaying);
        
        if (!lastMessage.empty()) {
            UI::printMessage(lastMessage, lastMessageType);
            lastMessage = "";
        }
        
        std::string command = getInputLine("Enter Command > ");
        
        // Command Router
        if (command.empty()) {
            continue;
        }
        
        // Transform command to lowercase for matching
        std::string cmdLower = command;
        std::transform(cmdLower.begin(), cmdLower.end(), cmdLower.begin(), [](unsigned char c) {
            return std::tolower(c);
        });

        if (cmdLower == "exit") {
            // Clean up dynamically allocated memory
            for (auto p : playlists) {
                delete p;
            }
            UI::clearScreen();
            std::cout << Color::BOLD_GREEN << "Thank you for using TerminalTunes! Goodbye!\n" << Color::RESET;
            break;
        }
        else if (cmdLower == "help") {
            UI::drawLine(60, Color::YELLOW);
            UI::printHelp();
            getInputLine("\nPress Enter to return to Dashboard...");
        }
        else if (cmdLower == "dev") {
            developerMode = !developerMode;
            lastMessage = "Developer Mode (DLL Visualizer) toggled " + std::string(developerMode ? "ON" : "OFF") + ".";
            lastMessageType = "info";
        }
        else if (cmdLower == "play") {
            if (activePlaylist && activePlaylist->getCurrent()) {
                activePlaylist->playCurrent();
                isPlaying = true;
                history.push(activePlaylist->getCurrent()->title, activePlaylist->getCurrent()->artist);
                lastMessage = "Now playing: " + activePlaylist->getCurrent()->title;
                lastMessageType = "success";
            } else {
                lastMessage = "No song available to play. Select or add a song first.";
                lastMessageType = "warning";
            }
        }
        else if (cmdLower == "pause") {
            if (isPlaying) {
                isPlaying = false;
                lastMessage = "Playback paused.";
                lastMessageType = "info";
            } else {
                lastMessage = "Already paused.";
                lastMessageType = "warning";
            }
        }
        else if (cmdLower == "next") {
            // First check queue
            std::string qTitle, qArtist;
            if (queue.dequeue(qTitle, qArtist)) {
                // Dequeued next song, look for it in the active playlist
                Song* found = activePlaylist->searchByTitle(qTitle);
                if (found) {
                    activePlaylist->setCurrent(found);
                    activePlaylist->playCurrent();
                    isPlaying = true;
                    history.push(found->title, found->artist);
                    lastMessage = "Playing queued song: " + found->title;
                    lastMessageType = "success";
                } else {
                    // Not in active playlist, let's look in all playlists
                    bool foundAnywhere = false;
                    for (auto p : playlists) {
                        Song* fs = p->searchByTitle(qTitle);
                        if (fs) {
                            activePlaylist = p;
                            activePlaylist->setCurrent(fs);
                            activePlaylist->playCurrent();
                            isPlaying = true;
                            history.push(fs->title, fs->artist);
                            lastMessage = "Switched to playlist [" + p->getName() + "] to play queued song: " + fs->title;
                            lastMessageType = "success";
                            foundAnywhere = true;
                            break;
                        }
                    }
                    if (!foundAnywhere) {
                        lastMessage = "Queued song '" + qTitle + "' not found in any playlist.";
                        lastMessageType = "error";
                    }
                }
            } else {
                // Standard playlist navigation
                if (activePlaylist) {
                    Song* nextSong = activePlaylist->playNext();
                    if (nextSong) {
                        isPlaying = true;
                        history.push(nextSong->title, nextSong->artist);
                        lastMessage = "Playing next song: " + nextSong->title;
                        lastMessageType = "success";
                    } else {
                        isPlaying = false;
                        lastMessage = "Reached the end of the playlist.";
                        lastMessageType = "warning";
                    }
                } else {
                    lastMessage = "No active playlist.";
                    lastMessageType = "error";
                }
            }
        }
        else if (cmdLower == "prev") {
            if (activePlaylist) {
                Song* prevSong = activePlaylist->playPrevious();
                if (prevSong) {
                    isPlaying = true;
                    history.push(prevSong->title, prevSong->artist);
                    lastMessage = "Playing previous song: " + prevSong->title;
                    lastMessageType = "success";
                } else {
                    lastMessage = "Reached the beginning of the playlist.";
                    lastMessageType = "warning";
                }
            } else {
                lastMessage = "No active playlist.";
                lastMessageType = "error";
            }
        }
        else if (cmdLower == "select") {
            if (!activePlaylist || activePlaylist->getSongCount() == 0) {
                lastMessage = "Active playlist is empty.";
                lastMessageType = "warning";
                continue;
            }
            std::string title = getInputLine("Enter song title to search > ");
            Song* found = activePlaylist->searchByTitle(title);
            if (found) {
                activePlaylist->setCurrent(found);
                activePlaylist->playCurrent();
                isPlaying = true;
                history.push(found->title, found->artist);
                lastMessage = "Selected and playing: " + found->title;
                lastMessageType = "success";
            } else {
                lastMessage = "Song '" + title + "' not found in this playlist.";
                lastMessageType = "error";
            }
        }
        else if (cmdLower == "add") {
            if (!activePlaylist) {
                lastMessage = "Create or switch to a playlist first.";
                lastMessageType = "warning";
                continue;
            }
            
            std::cout << "Add Options:\n";
            std::cout << "  1. Add from General Library catalog\n";
            std::cout << "  2. Enter custom song details manually\n";
            int addChoice = getInputInt("Enter choice (1-2) > ");
            
            std::string title, artist, album;
            bool songSelected = false;
            
            if (addChoice == 1) {
                std::string query = getInputLine("Enter catalog search query (or press Enter to view all) > ");
                auto results = songLib.searchSongs(query);
                UI::clearScreen();
                UI::printLibrarySongs(results, query.empty() ? "GENERAL SONG CATALOG" : "CATALOG SEARCH: '" + query + "'");
                
                if (results.empty()) {
                    getInputLine("\nPress Enter to return to Dashboard...");
                    continue;
                }
                
                int idx = getInputInt("\nEnter song index to add (1-" + std::to_string(results.size()) + ") > ");
                if (idx >= 1 && idx <= static_cast<int>(results.size())) {
                    LibrarySong selected = results[idx - 1];
                    title = selected.title;
                    artist = selected.artist;
                    album = selected.album;
                    songSelected = true;
                } else {
                    lastMessage = "Invalid index. Song not added.";
                    lastMessageType = "error";
                    continue;
                }
            } else if (addChoice == 2) {
                title = getInputLine("Enter song title > ");
                artist = getInputLine("Enter artist name > ");
                album = getInputLine("Enter album name (optional) > ");
                if (title.empty() || artist.empty()) {
                    lastMessage = "Title and Artist cannot be empty!";
                    lastMessageType = "error";
                    continue;
                }
                songSelected = true;
            } else {
                lastMessage = "Invalid choice. Song not added.";
                lastMessageType = "error";
                continue;
            }
            
            if (songSelected) {
                std::cout << "Where would you like to insert it?\n";
                std::cout << "  1. At the beginning\n";
                std::cout << "  2. At the end\n";
                std::cout << "  3. After a specific song\n";
                int choice = getInputInt("Enter choice (1-3) > ");
                
                if (choice == 1) {
                    activePlaylist->insertAtBeginning(title, artist, album);
                    lastMessage = "Inserted '" + title + "' at the beginning.";
                    lastMessageType = "success";
                } else if (choice == 2) {
                    activePlaylist->insertAtEnd(title, artist, album);
                    lastMessage = "Inserted '" + title + "' at the end.";
                    lastMessageType = "success";
                } else if (choice == 3) {
                    std::string afterTitle = getInputLine("Insert after which song title? > ");
                    if (activePlaylist->insertAfter(afterTitle, title, artist, album)) {
                        lastMessage = "Inserted '" + title + "' after '" + afterTitle + "'.";
                        lastMessageType = "success";
                    } else {
                        lastMessage = "Song '" + afterTitle + "' not found. Insertion failed.";
                        lastMessageType = "error";
                    }
                } else {
                    lastMessage = "Invalid insertion option. Song not added.";
                    lastMessageType = "error";
                }
            }
        }
        else if (cmdLower == "library") {
            UI::clearScreen();
            std::string query = getInputLine("Enter search query (or press Enter to view all) > ");
            auto results = songLib.searchSongs(query);
            UI::clearScreen();
            UI::printLibrarySongs(results, query.empty() ? "GENERAL SONG CATALOG" : "CATALOG SEARCH: '" + query + "'");
            
            if (results.empty()) {
                getInputLine("\nPress Enter to return to Dashboard...");
                continue;
            }
            
            std::string choice = getInputLine("\nWould you like to add a song from these results to the active playlist? (y/n) > ");
            if (choice == "y" || choice == "Y" || choice == "yes" || choice == "Yes") {
                int idx = getInputInt("Enter song index to add (1-" + std::to_string(results.size()) + ") > ");
                if (idx >= 1 && idx <= static_cast<int>(results.size())) {
                    LibrarySong selected = results[idx - 1];
                    std::cout << "Where would you like to insert it?\n";
                    std::cout << "  1. At the beginning\n";
                    std::cout << "  2. At the end\n";
                    std::cout << "  3. After a specific song\n";
                    int pos = getInputInt("Enter choice (1-3) > ");
                    
                    if (pos == 1) {
                        activePlaylist->insertAtBeginning(selected.title, selected.artist, selected.album);
                        lastMessage = "Added '" + selected.title + "' to the beginning.";
                        lastMessageType = "success";
                    } else if (pos == 2) {
                        activePlaylist->insertAtEnd(selected.title, selected.artist, selected.album);
                        lastMessage = "Added '" + selected.title + "' to the end.";
                        lastMessageType = "success";
                    } else if (pos == 3) {
                        std::string afterTitle = getInputLine("Insert after which song title? > ");
                        if (activePlaylist->insertAfter(afterTitle, selected.title, selected.artist, selected.album)) {
                            lastMessage = "Added '" + selected.title + "' after '" + afterTitle + "'.";
                            lastMessageType = "success";
                        } else {
                            lastMessage = "Song '" + afterTitle + "' not found. Insertion failed.";
                            lastMessageType = "error";
                        }
                    } else {
                        lastMessage = "Invalid insertion option. Song not added.";
                        lastMessageType = "error";
                    }
                } else {
                    lastMessage = "Invalid index.";
                    lastMessageType = "error";
                }
            }
        }

        else if (cmdLower == "delete") {
            if (!activePlaylist || activePlaylist->getSongCount() == 0) {
                lastMessage = "Active playlist is empty.";
                lastMessageType = "warning";
                continue;
            }
            
            std::cout << "Delete options:\n";
            std::cout << "  1. Delete currently playing song\n";
            std::cout << "  2. Delete a song by title\n";
            int choice = getInputInt("Enter choice (1-2) > ");
            
            if (choice == 1) {
                Song* curr = activePlaylist->getCurrent();
                std::string deletedTitle = curr ? curr->title : "";
                if (activePlaylist->deleteCurrent()) {
                    isPlaying = false;
                    lastMessage = "Deleted current song '" + deletedTitle + "'.";
                    lastMessageType = "success";
                } else {
                    lastMessage = "No current song selected to delete.";
                    lastMessageType = "error";
                }
            } else if (choice == 2) {
                std::string title = getInputLine("Enter song title to delete > ");
                Song* toDel = activePlaylist->searchByTitle(title);
                bool wasCurrent = (toDel && toDel == activePlaylist->getCurrent());
                if (activePlaylist->deleteByTitle(title)) {
                    if (wasCurrent) {
                        isPlaying = false;
                    }
                    lastMessage = "Deleted song '" + title + "'.";
                    lastMessageType = "success";
                } else {
                    lastMessage = "Song '" + title + "' not found.";
                    lastMessageType = "error";
                }
            } else {
                lastMessage = "Invalid deletion option.";
                lastMessageType = "error";
            }
        }
        else if (cmdLower == "create") {
            std::string name = getInputLine("Enter name for new playlist > ");
            if (name.empty()) {
                lastMessage = "Playlist name cannot be empty!";
                lastMessageType = "error";
                continue;
            }
            // Check if playlist name already exists
            bool exists = false;
            for (auto p : playlists) {
                if (equalsIgnoreCase(p->getName(), name)) {
                    exists = true;
                    break;
                }
            }
            if (exists) {
                lastMessage = "Playlist '" + name + "' already exists!";
                lastMessageType = "error";
            } else {
                Playlist* newPL = new Playlist(name);
                playlists.push_back(newPL);
                activePlaylist = newPL;
                isPlaying = false;
                lastMessage = "Playlist '" + name + "' created and selected.";
                lastMessageType = "success";
            }
        }
        else if (cmdLower == "switch") {
            if (playlists.empty()) {
                lastMessage = "No playlists available.";
                lastMessageType = "warning";
                continue;
            }
            std::cout << Color::BOLD_YELLOW << "  Select Playlist:\n" << Color::RESET;
            for (size_t i = 0; i < playlists.size(); ++i) {
                std::cout << "    " << (i + 1) << ". " << playlists[i]->getName() 
                          << " (" << playlists[i]->getSongCount() << " songs)\n";
            }
            int index = getInputInt("Enter playlist number > ");
            if (index >= 1 && index <= static_cast<int>(playlists.size())) {
                activePlaylist = playlists[index - 1];
                isPlaying = false;
                lastMessage = "Switched to playlist '" + activePlaylist->getName() + "'.";
                lastMessageType = "success";
            } else {
                lastMessage = "Invalid playlist number.";
                lastMessageType = "error";
            }
        }
        else if (cmdLower == "shuffle") {
            if (activePlaylist && activePlaylist->getSongCount() > 1) {
                activePlaylist->shuffle();
                isPlaying = false;
                lastMessage = "Shuffled playlist '" + activePlaylist->getName() + "' in-place.";
                lastMessageType = "success";
            } else {
                lastMessage = "Not enough songs to shuffle.";
                lastMessageType = "warning";
            }
        }
        else if (cmdLower == "display") {
            if (!activePlaylist || activePlaylist->getSongCount() == 0) {
                lastMessage = "Playlist is empty.";
                lastMessageType = "warning";
                continue;
            }
            UI::clearScreen();
            std::cout << Color::BOLD_YELLOW << "╔══════════════════════════════════════════════════════════╗\n";
            std::cout << "║                 PLAYLIST: " << std::left << std::setw(30) << activePlaylist->getName() << " ║\n";
            std::cout << "╚══════════════════════════════════════════════════════════╝\n" << Color::RESET;
            
            Song* temp = activePlaylist->getHead();
            int idx = 1;
            while (temp) {
                if (temp == activePlaylist->getCurrent()) {
                    std::cout << Color::BOLD_GREEN << " ➜  " << std::setw(2) << idx << ". " 
                              << std::left << std::setw(25) << UI::getTruncatedString(temp->title, 22) 
                              << " by " << std::left << std::setw(20) << UI::getTruncatedString(temp->artist, 18)
                              << " [Plays: " << temp->playCount << "]" << Color::RESET << "\n";
                } else {
                    std::cout << "    " << std::setw(2) << idx << ". " 
                              << std::left << std::setw(25) << UI::getTruncatedString(temp->title, 22) 
                              << " by " << std::left << std::setw(20) << UI::getTruncatedString(temp->artist, 18)
                              << " [Plays: " << temp->playCount << "]\n";
                }
                temp = temp->next;
                idx++;
            }
            getInputLine("\nPress Enter to return to Dashboard...");
        }
        else if (cmdLower == "queue") {
            std::cout << "Queue Options:\n";
            std::cout << "  1. View Queue\n";
            std::cout << "  2. Add Song to Queue (Play Next)\n";
            int choice = getInputInt("Enter choice (1-2) > ");
            
            if (choice == 1) {
                UI::clearScreen();
                UI::printQueue(queue);
                getInputLine("\nPress Enter to return to Dashboard...");
            } else if (choice == 2) {
                std::string title = getInputLine("Enter song title to queue > ");
                // Search if song exists in active playlist or another playlist to check artist
                std::string artist = "";
                Song* found = activePlaylist ? activePlaylist->searchByTitle(title) : nullptr;
                if (found) {
                    artist = found->artist;
                } else {
                    for (auto p : playlists) {
                        Song* fs = p->searchByTitle(title);
                        if (fs) {
                            artist = fs->artist;
                            break;
                        }
                    }
                }
                
                if (artist.empty()) {
                    artist = getInputLine("Artist not found. Enter artist name manually > ");
                }
                
                if (!title.empty() && !artist.empty()) {
                    queue.enqueue(title, artist);
                    lastMessage = "Queued '" + title + "' to play next.";
                    lastMessageType = "success";
                } else {
                    lastMessage = "Failed to queue song. Title and Artist are required.";
                    lastMessageType = "error";
                }
            } else {
                lastMessage = "Invalid queue option.";
                lastMessageType = "error";
            }
        }
        else if (cmdLower == "history") {
            UI::clearScreen();
            UI::printHistory(history);
            getInputLine("\nPress Enter to return to Dashboard...");
        }
        else if (cmdLower == "stats") {
            UI::clearScreen();
            UI::printStatistics(activePlaylist);
            getInputLine("\nPress Enter to return to Dashboard...");
        }
        else {
            lastMessage = "Unknown command. Type 'help' to see list of commands.";
            lastMessageType = "warning";
        }
    }
    
    return 0;
}
