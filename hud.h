#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "map.h"
#include "raycaster.h"
#include "globals.h"
#include <iostream>

class HUD {

    // FPS do jogo
    sf::Text hudFps;
    float _fps;

    // Timer do tempo restante para termianr o nível atual do labirinto
    sf::Text hudTimer;
    float _timer;

    // Quantidade de níveis completados
    sf::Text hudLevels;
    int _level;

    //sf::Text ammo;
    sf::Font font;

  public:

    HUD(std::string fontPath, int characterSize, sf::Color color){

      // Inicialização do FPS, timer e level
      _fps = 0.f;
      _timer = MAXTIMEOUT;
      _level = 1; 
      
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

    // Atualiza o FPS do jogo
    void updateFps(sf::Clock &clock){
      _fps = 1.0f/clock.restart().asSeconds();
    }

    // Atualiza o timer do jogo a cada segundo
    void updateTimer(sf::Clock &clock){

      // Atualiza o timer de acordo com a passagem do tempo de jogo em determiando level
      _timer -= clock.getElapsedTime().asSeconds();

      // Se houver menos que 120 segundos pra terminar, muda a cor do timer
      if( _timer <= 120)
        hudTimer.setFillColor(sf::Color::Yellow);

      if( _timer <= 90)
        hudTimer.setFillColor(sf::Color(255, 165, 0)); // Laranja

      if( _timer <= 30)
        hudTimer.setFillColor(sf::Color::Red);
    }

    // Atualiza o level do jogo
    void updateLevel(){
      _level++;
    }

    // Seta o time Out para p level atual de jogo
    void timerOfLevel(){
      _timer = MAXTIMEOUT/_level + MINTIMEOUT;
    }

    // Reset do timer
    void resetTimer(){
      _timer = MAXTIMEOUT;
    }

    // Reset do level
    void resetLevel(){
      _level = 1;
    }

    // Retorna fps do jogo
    float getFps(){
      return _fps;
    }

    // Retorna o tempo restante para terminar o nível
    float getTimer(){
      return _timer;
    }

    // Retorna o level atual do jogo
    int getLevel(){
      return _level;
    }
    
    void hudDraw(sf::RenderWindow &window,  Map map,Raycaster raycast, std::vector<ray> rays, Player player){
      
      // Set do FPS
      hudFps.setString("FPS: " + std::to_string(_fps));
      hudTimer.setString("Time out: " + std::to_string((int)_timer));
      hudLevels.setString("Level: " + std::to_string(_level));

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
