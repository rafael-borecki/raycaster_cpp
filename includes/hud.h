#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include "map.h"
#include "raycaster.h"
#include "globals.h"
#include <iostream>

class HUD {

    // FPS do jogo
    sf::Text hudFps;    // texto do FPS
    float _fps;         // valor do FPS

    // Timer do tempo restante para termianr o nível atual do labirinto
    sf::Text hudTimer;  // texto do timer
    float _timer;       // valor do timer

    // Quantidade de níveis completados
    sf::Text hudLevels; // texto do level
    int _level;         // valor do level

    // Fonte do HUD
    sf::Font font;      

  public:

    // Método construtor do HUD
    HUD(std::string fontPath, int characterSize, sf::Color color);

    // Métodos de atualização do HUD
    void updateFps(sf::Clock &clock);
    void updateTimer(sf::Clock &clock);
    void updateLevel();
    void timerOfLevel();

    // Métodos de reset do HUD
    void resetTimer();
    void resetLevel();

    // Métodos de acesso HUD
    float getFps();
    float getTimer();
    int getLevel();
    
    // Setup da HUD para exposição na tela
    void hudDraw(sf::RenderWindow &window,  Map map,Raycaster raycast, std::vector<ray> rays, Player player);
};


