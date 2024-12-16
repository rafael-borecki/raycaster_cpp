#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "map.h"
#include "raycaster.h"
#include <iostream>

class UI {

    // FPS do jogo
    sf::Text uiFps;

    // Timer do tempo restante para termianr o nível atual do labirinto
    sf::Text uiTimer;

    // Quantidade de níveis completados
    sf::Text uiLevels;

    //sf::Text ammo;
    sf::Font font;

  public:

    UI(){ 
      
      // Setagem da fontes escolhida para o UI
      font.loadFromFile("./assets/font.otf");
      uiFps.setFont(font);
      uiTimer.setFont(font);
      uiLevels.setFont(font);

      // Setagem do tamanho dos caracteres
      uiFps.setCharacterSize(24);
      uiTimer.setCharacterSize(24);
      uiLevels.setCharacterSize(24);

      // Setagem da cor dos caracteres
      uiFps.setFillColor(sf::Color::Green);
      uiTimer.setFillColor(sf::Color::Green);
      uiLevels.setFillColor(sf::Color::Green);
      
      // Setagem das posições do FPS, timer e level
      uiFps.setPosition(350,50);
      uiTimer.setPosition(750, 50);
      uiLevels.setPosition(1150, 50);
    }
    
    void uiDraw(sf::RenderWindow &window, float fps, Map map,Raycaster raycast, std::vector<ray> rays, Player player, int level, int time){
      
      // Set do FPS
      uiFps.setString("FPS: " + std::to_string(fps));
      uiTimer.setString("Time out: " + std::to_string(time));
      uiLevels.setString("Level: " + std::to_string(level));

      // Desenha o mapa
      map.drawMap(window);

      // Desenha o jogador
      window.draw(player.playerSprite);
      
      // Desenha as linhas do raycaster
      raycast.drawLines(window, sf::Vector2f(player.pX, player.pY), rays, sf::Color::Yellow);
      
      // Desenha o FPS
      window.draw(uiFps); window.draw(uiTimer); window.draw(uiLevels);

    }
};
