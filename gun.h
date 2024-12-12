#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System/Time.hpp>
#include "player.h"

class Gun{
  public:
    sf::Sprite gunSprite;
    sf::Texture gunTexture;
    sf::Time lastShot;

    Gun(sf::RenderWindow &window) {
      setTexture();
      gunSprite.setOrigin(gunSprite.getLocalBounds().width/2, gunSprite.getLocalBounds().height/2);
      gunSprite.setPosition(window.getSize().x/2, window.getSize().y - gunSprite.getLocalBounds().height/2);
      lastShot = sf::seconds(0.0f);
    }

    void setTexture(){
      gunTexture.loadFromFile("pistol_shoot.png");
      gunSprite.setTexture(gunTexture);
      gunSprite.setScale(2.f,2.f);
      gunSprite.setTextureRect(sf::IntRect(0,0,64, 171));
    }
    
    void gunDraw(sf::RenderWindow &window, sf::Clock clock, Player *player) {
      
      window.draw(gunSprite);

      if(clock.getElapsedTime().asSeconds() - lastShot.asSeconds()  > 1.0f ){
	      if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
	        if(player->ammo){
	          player->dropAmmo();
	          lastShot = clock.getElapsedTime();
	          gunSprite.setTextureRect(sf::IntRect(96,0,64, 171));
	        }
	      }
      }

      else if (clock.getElapsedTime().asSeconds() - lastShot.asSeconds()  > 0.4f){
	      gunSprite.setTextureRect(sf::IntRect(0,0,64, 171));
      }

      if(sf::Keyboard::isKeyPressed(sf::Keyboard::R)){
	      lastShot = clock.getElapsedTime();
	      gunSprite.setTextureRect(sf::IntRect(0,0,0, 171));
	      player->ammo = 32;
      }

    }

};
