#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include "globals.h"


class InterLevel {

    // Vetores de opções do menu e posições das opções
    sf::Text opt1Text, opt2Text;
    sf::Vector2f opt1Position, opt2Position;
    sf::RectangleShape opt1Rect, opt2Rect; 

    // Timer do tempo restante para termianr o nível atual do labirinto
    sf::Text iLevelTimer;

    // Quantidade de níveis completados
    sf::Text iLevelLevels;

    // Fonte do texto
    sf::Font font;

    // Inteiro da posição da opção (1 e 2)
    int option = 0;

    // Booleano para verificar continuidade do jogo
    bool continueGame;

    // cursor na opção 1 
    void moveUp(){option = 1;}

    // cursor na opção 2
    void moveDown(){option = 2;}

  public:

    // Construtor da interface entre níveis
    InterLevel(std::string fontPath, int characterSize, sf::Color color);

    // Navegação entre as opções
    void navegation();

    // Seleceção da opção
    bool select();

    // Verificação da continuidade do jogo
    bool continuation();

    // Retorna a fonte do texto
    sf::Font& getFont(){return font;}

    // Desenha a interface entre níveis
    void iLevelDraw(sf::RenderWindow &window, int level, int time);
};

class GameOver : public InterLevel{
  // Texto de game over
  sf::Text gameOverText;

public:

  // Construtor da interface de game over
  GameOver(std::string fontPath, int characterSize, sf::Color color);

  // Desenha a interface de game over
  void gameOverDraw(sf::RenderWindow &window,  int level, int time);
  
};

