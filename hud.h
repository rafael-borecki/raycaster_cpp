#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "map.h"
#include "raycaster.h"
#include <iostream>

class HUD {

    // FPS do jogo
    sf::Text hudFps;

    // Timer do tempo restante para termianr o nível atual do labirinto
    sf::Text hudTimer;

    // Quantidade de níveis completados
    sf::Text hudLevels;

    //sf::Text ammo;
    sf::Font font;

  public:

    HUD(std::string fontPath, int characterSize, sf::Color color){ 
      
      // Setagem da fontes escolhida para o hud
      font.loadFromFile(fontPath);
      hudFps.setFont(font);
      hudTimer.setFont(font);
      hudLevels.setFont(font);

      // Setagem do tamanho dos caracteres
      hudFps.setCharacterSize(characterSize);
      hudTimer.setCharacterSize(characterSize);
      hudLevels.setCharacterSize(characterSize);

      // Setagem da cor dos caracteres
      hudFps.setFillColor(color);
      hudTimer.setFillColor(color);
      hudLevels.setFillColor(color);
      
      // Setagem das posições do FPS, timer e level
      hudFps.setPosition(FPS_HUDPOSITION);
      hudTimer.setPosition(TIMER_HUDPOSITION);
      hudLevels.setPosition(LEVEL_HUDPOSITION);
    }
    
    void hudDraw(sf::RenderWindow &window, float fps, Map map,Raycaster raycast, std::vector<ray> rays, Player player, int level, int time){
      
      // Set do FPS
      hudFps.setString("FPS: " + std::to_string(fps));
      hudTimer.setString("Time out: " + std::to_string(time));
      hudLevels.setString("Level: " + std::to_string(level));

      // Desenha o mapa
      map.drawMap(window);

      // Desenha o jogador
      window.draw(player.playerSprite);
      
      // Desenha as linhas do raycaster
      raycast.drawLines(window, sf::Vector2f(player.pX, player.pY), rays, sf::Color::Yellow);
      
      // Desenha o FPS
      window.draw(hudFps); window.draw(hudTimer); window.draw(hudLevels);

    }
};
