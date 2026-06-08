CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Iinclude
SRC = src/Playlist.cpp src/HistoryManager.cpp src/SongQueue.cpp src/SongLibrary.cpp src/UI.cpp src/main.cpp
OBJ = $(SRC:.cpp=.o)
TARGET = terminal_tunes

TEST_SRC = src/Playlist.cpp src/HistoryManager.cpp src/SongQueue.cpp src/SongLibrary.cpp src/test.cpp
TEST_OBJ = $(TEST_SRC:.cpp=.o)
TEST_TARGET = run_tests

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJ)

$(TEST_TARGET): $(TEST_OBJ)
	$(CXX) $(CXXFLAGS) -o $(TEST_TARGET) $(TEST_OBJ)

test: $(TEST_TARGET)
	./$(TEST_TARGET)

clean:
	rm -f src/*.o $(TARGET) $(TEST_TARGET)
