#include "../include/Song.h"
#include "../include/Playlist.h"
#include "../include/HistoryManager.h"
#include "../include/SongQueue.h"
#include "../include/SongLibrary.h"
#include <iostream>
#include <cassert>

void testPlaylistDLL() {
    std::cout << "Running Playlist DLL tests...\n";
    Playlist p("Test Playlist");
    assert(p.getSongCount() == 0);
    assert(p.getHead() == nullptr);
    assert(p.getTail() == nullptr);

    // Test insertAtEnd
    p.insertAtEnd("Song A", "Artist A", "Album A");
    assert(p.getSongCount() == 1);
    assert(p.getHead() != nullptr);
    assert(p.getHead() == p.getTail());
    assert(p.getHead() == p.getCurrent());
    assert(p.getHead()->title == "Song A");

    // Test insertAtBeginning
    p.insertAtBeginning("Song B", "Artist B", "Album B");
    assert(p.getSongCount() == 2);
    assert(p.getHead()->title == "Song B");
    assert(p.getTail()->title == "Song A");
    assert(p.getHead()->next == p.getTail());
    assert(p.getTail()->prev == p.getHead());

    // Test insertAfter
    bool res = p.insertAfter("Song B", "Song C", "Artist C", "Album C");
    assert(res == true);
    assert(p.getSongCount() == 3);
    assert(p.getHead()->next->title == "Song C");
    assert(p.getHead()->next->prev == p.getHead());
    assert(p.getHead()->next->next == p.getTail());
    assert(p.getTail()->prev->title == "Song C");

    // Test playNext & playPrevious
    p.setCurrent(p.getHead());
    assert(p.getCurrent()->title == "Song B");
    assert(p.playNext()->title == "Song C");
    assert(p.getCurrent()->title == "Song C");
    assert(p.playNext()->title == "Song A");
    assert(p.playNext() == nullptr); // End of list
    assert(p.playPrevious()->title == "Song C");
    assert(p.playPrevious()->title == "Song B");
    assert(p.playPrevious() == nullptr); // Start of list

    // Test deleteCurrent
    p.setCurrent(p.getHead()->next); // Song C
    assert(p.deleteCurrent() == true);
    assert(p.getSongCount() == 2);
    assert(p.getHead()->title == "Song B");
    assert(p.getTail()->title == "Song A");
    assert(p.getHead()->next == p.getTail());
    assert(p.getTail()->prev == p.getHead());
    assert(p.getCurrent()->title == "Song A"); // current moves to next after deletion

    // Test deleteByTitle
    assert(p.deleteByTitle("Song B") == true);
    assert(p.getSongCount() == 1);
    assert(p.getHead() == p.getTail());
    assert(p.getHead()->title == "Song A");

    // Clean up
    p.clear();
    assert(p.getSongCount() == 0);
    assert(p.getHead() == nullptr);
    assert(p.getTail() == nullptr);
    std::cout << "Playlist DLL tests passed!\n";
}

void testHistoryStack() {
    std::cout << "Running History Stack tests...\n";
    HistoryManager h;
    assert(h.isEmpty());
    assert(h.getSize() == 0);

    h.push("Song 1", "Artist 1");
    h.push("Song 2", "Artist 2");
    assert(h.getSize() == 2);
    assert(!h.isEmpty());

    auto list = h.getHistory();
    assert(list.size() == 2);
    assert(list[0].first == "Song 2"); // Most recent first
    assert(list[1].first == "Song 1");

    std::string t, a;
    assert(h.pop(t, a) == true);
    assert(t == "Song 2");
    assert(a == "Artist 2");
    assert(h.getSize() == 1);

    assert(h.pop(t, a) == true);
    assert(t == "Song 1");
    assert(h.isEmpty());
    std::cout << "History Stack tests passed!\n";
}

void testSongQueue() {
    std::cout << "Running Song Queue tests...\n";
    SongQueue q;
    assert(q.isEmpty());
    assert(q.getSize() == 0);

    q.enqueue("Song X", "Artist X");
    q.enqueue("Song Y", "Artist Y");
    assert(q.getSize() == 2);

    auto list = q.getQueue();
    assert(list.size() == 2);
    assert(list[0].first == "Song X"); // First-in, first-out
    assert(list[1].first == "Song Y");

    std::string t, a;
    assert(q.dequeue(t, a) == true);
    assert(t == "Song X");
    assert(q.getSize() == 1);

    assert(q.dequeue(t, a) == true);
    assert(t == "Song Y");
    assert(q.isEmpty());
    std::cout << "Song Queue tests passed!\n";
}

void testSongLibrary() {
    std::cout << "Running Song Library tests...\n";
    SongLibrary lib;
    
    // Check that we have the 24 preloaded songs
    const auto& all = lib.getAllSongs();
    assert(all.size() == 24);
    
    // Case-insensitive query matches
    auto weekndSongs = lib.searchSongs("Weeknd");
    assert(weekndSongs.size() == 3);
    assert(weekndSongs[0].artist == "The Weeknd");
    
    // Substring queries
    auto numbSearch = lib.searchSongs("num");
    assert(numbSearch.size() == 1);
    assert(numbSearch[0].title == "Numb");
    
    // Empty search query returns all
    auto allSearch = lib.searchSongs("");
    assert(allSearch.size() == 24);
    
    // No match query
    auto noMatch = lib.searchSongs("Nonexistent Query 123");
    assert(noMatch.empty());
    
    std::cout << "Song Library tests passed!\n";
}

int main() {
    std::cout << "=== RUNNING TERMINALTUNES UNIT TESTS ===\n";
    testPlaylistDLL();
    testHistoryStack();
    testSongQueue();
    testSongLibrary();
    std::cout << "=== ALL TESTS PASSED SUCCESSFULLY ===\n";
    return 0;
}
