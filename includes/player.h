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
    //pAng: Angulacao do jogador em graus e radianos respectivamente
    float pAng, pAngDeg;
    //pX, pY: Coordenadas do jogador no plano 2D
    float pX, pY, pdX, pdY;
    //Variaveis que armazenam modulo da velocidade de translado e rotacao
    float moveSpeed, rotSpeed;
    //Variavel para armezanar o formato do jogador - apenas no minimapa 2D
    sf::RectangleShape playerSprite;

    Player(float pX, float pY);

    //Metodo de movimentacao principal
    void rotatePlayer(Map map);
    void resetPosition();
    sf::RectangleShape getSprite() { return playerSprite; }
    void updatePlayer(float fps);
    int checkExit(Map map);
};
