#pragma once
#include "map.h"
#include "globals.h"
#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <math.h>
#include <string>

class Player
{

public:
  float pAng;
  float pX, pY, pdX, pdY, pAngDeg;
  float moveSpeed, rotSpeed;
  int ammo;
  int life;
  sf::RectangleShape playerSprite;

  Player(float pX, float pY) : pX(pX), pY(pY)
  {
    playerSprite.setSize(sf::Vector2f(MAP_SCALE / 2, MAP_SCALE / 2));
    playerSprite.setPosition((MAP_SCALE / 2 * MAP_X) / 2, (MAP_SCALE / 2 * MAP_Y) / 2);
    playerSprite.setOrigin(MAP_SCALE / 4, MAP_SCALE / 4);
    pdX = 0;
    pdY = 0;
    pAng = 0;
    pAngDeg = 0;
    moveSpeed = 0.09f;
    rotSpeed = 0.9f;
  }

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
	    (int)((pX + 0.1 * playerSprite.getLocalBounds().width/2) / MAP_SCALE)]){
	  pX += moveSpeed * pdX;
	}

	if (map.worldMap[map.mapX * (int)((pY) / MAP_SCALE) +
	    (int)((pX - 0.1 * playerSprite.getLocalBounds().width/2) / MAP_SCALE)]){
	  pX += moveSpeed * pdX;
	}

	if (map.worldMap[map.mapX * (int)((pY + 0.1 * playerSprite.getLocalBounds().height/2) / MAP_SCALE) +
	    (int)((pX) / MAP_SCALE)]){
	  pY += moveSpeed * pdY;
	}

	if (map.worldMap[map.mapX * (int)((pY - 0.1 * playerSprite.getLocalBounds().height/2) / MAP_SCALE) +
	    (int)((pX) / MAP_SCALE)]){
	  pY += moveSpeed * pdY;
	}
      }

      if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {

	pY += moveSpeed * pdY;
	pX += moveSpeed * pdX;

	if (map.worldMap[map.mapX * (int)((pY) / MAP_SCALE) +
	    (int)((pX + 0.1 * playerSprite.getLocalBounds().width/2) / MAP_SCALE)]){
	  pX -= moveSpeed * pdX;
	}

	if (map.worldMap[map.mapX * (int)((pY) / MAP_SCALE) +
	    (int)((pX - 0.1 * playerSprite.getLocalBounds().width/2) / MAP_SCALE)]){
	  pX -= moveSpeed * pdX;
	}

	if (map.worldMap[map.mapX * (int)((pY + 0.1 * playerSprite.getLocalBounds().height/2) / MAP_SCALE) +
	    (int)((pX) / MAP_SCALE)]){
	  pY -= moveSpeed * pdY;
	}

	if (map.worldMap[map.mapX * (int)((pY - 0.1 * playerSprite.getLocalBounds().height/2) / MAP_SCALE) +
	    (int)((pX) / MAP_SCALE)]){
	  pY -= moveSpeed * pdY;
	}
      }

      if (sf::Keyboard::isKeyPressed(sf::Keyboard::G)) {
      pX = 300.0f;
      pY = 300.0f;
      }
    }

  sf::RectangleShape getSprite() { return playerSprite; }

  void updatePlayer(float fps)
  {
    rotSpeed = 0.05f * FRAME_RATE / fps;
    moveSpeed = 1.f * FRAME_RATE / fps;
    pAngDeg = pAng * RADIAN;
    playerSprite.setRotation(pAngDeg);
    playerSprite.setPosition(pX / 2, pY / 2);
  }

  int checkExit(Map map)
  {
    int exit = 0;

    for (int i = -1; i < 2; i = i + 2)
      for (int j = -1; j < 2; j = j + 2)
      {
        if (map.worldMap[map.mapX * (int)(((pY) / MAP_SCALE) + 0.1 * i) + (int)(((pX / MAP_SCALE) + 0.1 * j))] == 7)
        {
          exit = 1;
        }
      }
    return exit;
  }
};
