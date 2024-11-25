CXX = g++
CXXFLAGS = -lsfml-graphics -lsfml-window -lsfml-system

SRC = main.cpp
HEADERS = raycaster.h globals.h map.h player.h ui.h
TARGET = game

all: $(TARGET)

$(TARGET): $(SRC) $(HEADERS)
	$(CXX) $(SRC) -o $(TARGET) $(CXXFLAGS)

clean:
	rm -f $(TARGET)

