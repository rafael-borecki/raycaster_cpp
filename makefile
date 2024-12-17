CXX = g++
CXXFLAGS = -lsfml-graphics -lsfml-window -lsfml-system

SRC = main.cpp menu.cpp file.cpp
HEADERS = raycaster.h globals.h map.h player.h hud.h maze.h il.h menu.h file.h
TARGET = game

all: clean $(TARGET)

$(TARGET): $(SRC) $(HEADERS)
	$(CXX) $(SRC) -o $(TARGET) $(CXXFLAGS)

clean:
	rm -f $(TARGET)

run: 
	./$(TARGET)
