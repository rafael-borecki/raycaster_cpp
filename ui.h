#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "map.h"
#include "raycaster.h"
#include <iostream>

class UI {
  public:
    sf::Text uiFps;
    //sf::Text ammo;
    sf::Font font;

    UI() {
      font.loadFromFile("./assets/font.otf");
      uiFps.setFont(font);
      //ammo.setFont(font);
      uiFps.setCharacterSize(24);
      //ammo.setCharacterSize(24);
      uiFps.setFillColor(sf::Color::Green);
      //ammo.setFillColor(sf::Color::White);
      uiFps.setPosition(650,50);
      //ammo.setPosition(100,200);
    }
    
    void uiDraw(sf::RenderWindow &window, float fps, Map map,Raycaster raycast, std::vector<ray> rays, Player player/*, int p_ammo*/){
      uiFps.setString(std::to_string(fps));
      map.drawMap(window);
      window.draw(player.playerSprite);
      raycast.drawLines(window, sf::Vector2f(player.pX, player.pY), rays, sf::Color::Yellow);
      //ammo.setString(std::to_string(p_ammo));
      window.draw(uiFps);	
      //window.draw(ammo);
    }
};
