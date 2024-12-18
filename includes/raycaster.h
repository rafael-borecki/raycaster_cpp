#pragma once
#include "map.h"
#include "player.h"
#include "globals.h"
#include <SFML/Graphics.hpp>
#include <math.h>


// struct para armazenar informacoes a respeito dos raios do algoritmo de raycast
typedef struct
{
	sf::Vector2f coordinates;
	int horv;
	int color;
	int index;
	float distance;
	float lineHeight;
} ray;

class Raycaster
{
public:
	void draw3D(sf::RenderWindow &window, std::vector<ray> rays);
	sf::RectangleShape renderStrip(ray nearest, float xPos, float yPos);
	std::vector<ray> renderLines(sf::RenderWindow &window, Player player, Map map);
	void drawLines(sf::RenderWindow &window, sf::Vector2f playerPos, std::vector<ray> rayPos, sf::Color color);
	ray scanHorizontal(sf::RenderWindow &window, Player player, Map map, float rayAng);
	ray scanVertical(sf::RenderWindow &window, Player player, Map map, float rayAng);
};
