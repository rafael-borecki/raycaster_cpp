#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdio.h>
#include <vector>
#include "maze.h"
#include "globals.h"

class Map
{
public:
	int mapX = MAP_X;
	int mapY = MAP_Y;
	int mapS = MAP_SCALE;
	char worldMap[MAP_Y * MAP_X + 50];

	Map(int id);
	void drawMap(sf::RenderWindow &window);
	void drawRectangle(int i, int j, sf::RenderWindow &window, sf::Color color);
	void updateMap();
};
