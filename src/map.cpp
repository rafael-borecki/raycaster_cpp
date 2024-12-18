#include "map.h"

Map::Map(int id) {

    if (id == 1)
    {
        char tempMap[] = {
            1, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 1,
            1, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 1,
            1, 0, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
            1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
            1, 0, 0, 0, 0, 0, 2, 2, 0, 2, 2, 0, 0, 0, 0, 3, 0, 3, 0, 3, 0, 0, 0, 1,
            1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
            1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 3, 0, 0, 0, 3, 0, 0, 0, 1,
            1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
            1, 0, 0, 0, 0, 0, 2, 5, 0, 2, 2, 1, 0, 0, 0, 3, 0, 3, 0, 3, 0, 0, 0, 1,
            1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
            1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
            1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
            1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
            1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
            1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
            1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
            1, 0, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
            1, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
            1, 0, 0, 4, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 4, 0, 5, 0, 3, 0, 1,
            1, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
            1, 0, 0, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 2, 0, 4, 0, 5, 0, 3, 0, 1,
            1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
            1, 0, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
            1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
        std::copy(std::begin(tempMap), std::end(tempMap), worldMap);
    }

    else if (id == 2)
    {
        // Labirinto vazio
        Maze maze(mapX, mapY);

        // Gera mapa do labirinto
        char *tempMap = maze.getMazeMap();

        // Copia mapa gerado para o mapa do mundo
        std::copy(tempMap, tempMap + MAP_X * MAP_Y, worldMap);
    }

    else if (id == 3)
    {
        // Labirinto aleatório
        Maze maze(mapX, mapY);
        maze.toRandomMaze();

        // Gera mapa do labirinto
        char *tempMap = maze.getMazeMap();

        // Copia mapa gerado para o mapa do mundo
        std::copy(tempMap, tempMap + MAP_X * MAP_Y, worldMap);
    }
}

void Map::drawMap(sf::RenderWindow &window) {
    for (int x = 0; x < mapX; x++)
    {
        for (int y = 0; y < mapY; y++)
        {
            if (worldMap[y * mapX + x] == 5)
            {
                drawRectangle(x, y, window, sf::Color{255, 0, 255});
            }
            if (worldMap[y * mapX + x] == 4)
            {
                drawRectangle(x, y, window, sf::Color{255, 255, 0});
            }
            if (worldMap[y * mapX + x] == 3)
            {
                drawRectangle(x, y, window, sf::Color{0, 0, 255});
            }
            if (worldMap[y * mapX + x] == 1) // parede
            {
                drawRectangle(x, y, window, sf::Color{76, 20, 0});
            }
            if (worldMap[y * mapX + x] == 0) // caminho
            {
                drawRectangle(x, y, window, sf::Color{180, 180, 180});
            }
            if (worldMap[y * mapX + x] == 7) // saída
            {
                drawRectangle(x, y, window, sf::Color{180, 180, 180});
            }
        }
    }
}

void Map::drawRectangle(int i, int j, sf::RenderWindow &window, sf::Color color) {
    sf::RectangleShape rect;
    rect.setFillColor(color);
    rect.setSize(sf::Vector2f(MAP_SCALE / 2, MAP_SCALE / 2));
    rect.setPosition(static_cast<float>(i * MAP_SCALE / 2), static_cast<float>(j * MAP_SCALE / 2));
    window.draw(rect);
}

void Map::updateMap() {
    // Labirinto aleatório
    Maze maze(mapX, mapY);
    maze.toRandomMaze();

    // Gera mapa do labirinto
    char *tempMap = maze.getMazeMap();

    // Copia mapa gerado para o mapa do mundo
    std::copy(tempMap, tempMap + MAP_X * MAP_Y, worldMap);
}
