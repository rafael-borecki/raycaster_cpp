#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include "globals.h"


class INTERLEVEL {

    // FPS do jogo
    sf::Text ilevelFps;

    // Timer do tempo restante para termianr o nível atual do labirinto
    sf::Text ilevelTimer;

    // Quantidade de níveis completados
    sf::Text ilevelLevels;

    //sf::Text ammo;
    sf::Font font;

  public:

    INTERLEVEL(std::string fontPath, int characterSize, sf::Color color){ 
      
      // Setagem da fontes escolhida para o ilevel
      font.loadFromFile(fontPath);
      ilevelFps.setFont(font);
      ilevelTimer.setFont(font);
      ilevelLevels.setFont(font);

      // Setagem do tamanho dos caracteres
      ilevelFps.setCharacterSize(characterSize);
      ilevelTimer.setCharacterSize(characterSize);
      ilevelLevels.setCharacterSize(characterSize);

      // Setagem da cor dos caracteres
      ilevelFps.setFillColor(color);
      ilevelTimer.setFillColor(color);
      ilevelLevels.setFillColor(color);
      
      // Setagem das posições do FPS, timer e level
      ilevelFps.setPosition(FPS_ILPOSITION);
      ilevelTimer.setPosition(TIMER_ILPOSITION);
      ilevelLevels.setPosition(LEVEL_ILPOSITION);
    
    void ilevelDraw(sf::RenderWindow &window, float fps, int level, int time){
      
      // Set do FPS
      ilevelTimer.setString("Time out: " + std::to_string(time));
      ilevelLevels.setString("Level: " + std::to_string(level));

      
      // Desenha o FPS
      window.draw(ilevelFps); window.draw(ilevelTimer); window.draw(ilevelLevels);

    }
};