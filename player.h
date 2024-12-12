#pragma once
#include "map.h"
#include "globals.h"
#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <math.h>
#include <string>

class Player {
  
  public:
    
    float pAng;
    float pX, pY, pdX, pdY, pAngDeg;
    float moveSpeed, rotSpeed;
    int ammo;
    int life;
    sf::RectangleShape playerSprite;

    Player(float pX, float pY): pX(pX), pY(pY) {
      playerSprite.setSize(sf::Vector2f(MAP_SCALE/2,MAP_SCALE/2));
      playerSprite.setPosition((MAP_SCALE/2 * MAP_X)/2, (MAP_SCALE/2 * MAP_Y)/2);
      playerSprite.setOrigin(MAP_SCALE/4, MAP_SCALE/4);
      pdX = 0;
      pdY = 0;
      pAng = 0;
      pAngDeg = 0;
      moveSpeed = 0.09f;
      rotSpeed  = 0.9f;
      ammo = 32;
      life = 100;
    }

    //void setTexture(std::string texturePath) {
      //playerTexture.loadFromFile(texturePath);
      //playerSprite.setTexture(playerTexture);
    //}

    //sf::Sprite getSprite() { return playerSprite; }
    sf::RectangleShape getSprite() { return playerSprite; }

    void rotatePlayer(Map map) {
      
      if (pAng > 6.29) {
	      pAng = 0.01f;
      }

      if (pAng < 0) {
	      pAng = 2 * PI - 0.001f;
      }

      if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
	      pAng += rotSpeed;
	      pdX = cos(pAng);
	      pdY = sin(pAng);
      }

      if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
	      pAng -= rotSpeed;
	      pdX = cos(pAng);
	      pdY = sin(pAng);
      }

      if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
	      
        pX -= moveSpeed * pdX;
	      pY -= moveSpeed * pdY;
	      
        if (map.worldMap[map.mapX * (int)((pY) / MAP_SCALE) +
	          (int)((pX + playerSprite.getLocalBounds().width/2) / MAP_SCALE)]){
	        pX += moveSpeed * pdX;
	      }

	      if (map.worldMap[map.mapX * (int)((pY) / MAP_SCALE) +
	          (int)((pX - playerSprite.getLocalBounds().width/2) / MAP_SCALE)]){
	        pX += moveSpeed * pdX;
	      }

	      if (map.worldMap[map.mapX * (int)((pY + playerSprite.getLocalBounds().height/2) / MAP_SCALE) +
	          (int)((pX) / MAP_SCALE)]){
	        pY += moveSpeed * pdY;
	      }

	      if (map.worldMap[map.mapX * (int)((pY - playerSprite.getLocalBounds().height/2) / MAP_SCALE) +
	          (int)((pX) / MAP_SCALE)]){
	        pY += moveSpeed * pdY;
	      }
      }

      if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
	      
        pY += moveSpeed * pdY;
	      pX += moveSpeed * pdX;

	      if (map.worldMap[map.mapX * (int)((pY) / MAP_SCALE) +
	          (int)((pX + playerSprite.getLocalBounds().width/2) / MAP_SCALE)]){
	        pX -= moveSpeed * pdX;
	      }

	      if (map.worldMap[map.mapX * (int)((pY) / MAP_SCALE) +
	          (int)((pX - playerSprite.getLocalBounds().width/2) / MAP_SCALE)]){
	        pX -= moveSpeed * pdX;
	      }

	      if (map.worldMap[map.mapX * (int)((pY + playerSprite.getLocalBounds().height/2) / MAP_SCALE) +
	          (int)((pX) / MAP_SCALE)]){
	        pY -= moveSpeed * pdY;
	      }

	      if (map.worldMap[map.mapX * (int)((pY - playerSprite.getLocalBounds().height/2) / MAP_SCALE) +
	          (int)((pX) / MAP_SCALE)]){
	        pY -= moveSpeed * pdY;
	      }
      }

      if (sf::Keyboard::isKeyPressed(sf::Keyboard::G)) {
	      pX = 300.f;
	      pY = 300.f;
      }
      
    }

    void updatePlayer(float fps) {
      rotSpeed = 0.05f * FRAME_RATE/fps;
      moveSpeed = 2.f * FRAME_RATE/fps;
      pAngDeg = pAng * RADIAN;
      playerSprite.setRotation(pAngDeg);
      playerSprite.setPosition(pX/2, pY/2);
    }

    void dropAmmo() {
      ammo = ammo - 1;
    }

    int getAmmo() {
      return ammo;
    }
    int getLife() {
      return life;
    }
};

