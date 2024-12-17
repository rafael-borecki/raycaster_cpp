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

    // Inteiro da posição da opção (1 e 0)
    int option = 0;

    // Timer do tempo restante para termianr o nível atual do labirinto
    sf::Text iLevelTimer;

    // Quantidade de níveis completados
    sf::Text iLevelLevels;

    // Fonte do texto
    sf::Font font;

    // Booleano para verificar continuidade do jogo
    bool continueGame;

  public:

    // Construtor da interface entre níveis
    InterLevel(std::string fontPath, int characterSize, sf::Color color);

    // Movimentação do cursor de opção
    void moveUp();
    void moveDown();

    // Navegação entre as opções
    void navegation();

    // Seleceção da opção
    bool select();

    // Verificação da continuidade do jogo
    bool continuation();

    // Retorna a fonte do texto
    sf::Font& getFont();

    // Desenha a interface entre níveis
    void iLevelDraw(sf::RenderWindow &window, int level, int time);
};

// Construtor e configuração (setup) da interface de interlevel
InterLevel::InterLevel(std::string fontPath, int characterSize, sf::Color color){
  
  // Inicialização da variável de continuidade do jogo
  continueGame = false;
  
  font.loadFromFile(fontPath);

  // Setagens opcões da interface 
  // Opção 1
  opt1Text.setString("Continuar jogando");                       // texto
  opt1Text.setPosition(500,300);                  // posição do texto na tela
  opt1Text.setFont(font);                         // fonte
  opt1Text.setCharacterSize(characterSize);       // tamanho do caractere
  opt1Text.setFillColor(sf::Color::White);        // cor do texto
  opt1Rect.setFillColor(sf::Color::Black);        // cor do retângulo de seleção
  opt1Rect.setSize(sf::Vector2f(20,50));          // tamanho do retângulo de seleção
  opt1Rect.setPosition(480,300);                  // posição do retângulo de seleção
  
  //Opção 2
  opt2Text.setString("Voltar ao menu principal");                       // texto
  opt2Text.setPosition(500,400);                  // posição na tela
  opt2Text.setFont(font);                         // fonte
  opt2Text.setCharacterSize(characterSize);       // tamanho do caractere
  opt2Text.setFillColor(sf::Color::White);        // cor do texto
  opt2Rect.setFillColor(sf::Color::Black);        // cor do retângulo de seleção
  opt2Rect.setSize(sf::Vector2f(20,50));          // tamanho do retângulo de seleção
  opt2Rect.setPosition(480,400);                  // posição do retângulo de seleção

  // Setagem da fontes escolhida para o iLevel
  iLevelTimer.setFont(font);
  iLevelLevels.setFont(font);

  // Setagem do tamanho dos caracteres
  iLevelTimer.setCharacterSize(characterSize);
  iLevelLevels.setCharacterSize(characterSize);

  // Setagem da cor dos caracteres
  iLevelTimer.setFillColor(color);
  iLevelLevels.setFillColor(color);
  
  // Setagem das posições do FPS, timer e level
  iLevelTimer.setPosition(TIMER_ILPOSITION);
  iLevelLevels.setPosition(LEVEL_ILPOSITION);
}

// Move cursor para opção 1
void InterLevel::moveUp(){
  option = 1;
}

// Move cursor para opção 2
void InterLevel::moveDown(){
  option = 2;
}

// Navegação entre as opções
void InterLevel::navegation(){
  
  // Verifica se a tecla de cima (opt 1) foi pressionada, se sim move para cima o cursor de opção
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
    opt1Rect.setFillColor(sf::Color::White);
    opt2Rect.setFillColor(sf::Color::Black);
    moveUp();
  }

  // Verifica se a tecla de baixo (opt 2) foi pressionada, se sim move para baixo o cursor de opção
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
    opt2Rect.setFillColor(sf::Color::White);
    opt1Rect.setFillColor(sf::Color::Black);
    moveDown();
  }

}

// Seleciona a opção e retorna true caso a tecla enter seja pressionada
bool InterLevel::select(){
  
  // Verifica se a tecla enter foi pressionada, uma opção foi selecionada e retorna true
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)){
    continueGame = (option == 1);
    return true;
  }
  
  // Caso contrário, retorna false
  return false;
}

// Retorna a continuidade do jogo
bool InterLevel::continuation(){
  return continueGame;
}

// Retorna a fonte do texto
sf::Font& InterLevel::getFont(){
  return font;
}

// Desenha a interface de interlevel
void InterLevel::iLevelDraw(sf::RenderWindow &window, int level, int time){
  
  // Setagem do timer e level
  iLevelTimer.setString("Time out: " + std::to_string(time));
  iLevelLevels.setString("Level: " + std::to_string(level));
  
  // Desenha o FPS, time out e level
  window.draw(iLevelTimer); window.draw(iLevelLevels);
  
  // Desenha as opções
  window.draw(opt1Text); window.draw(opt2Text);
  window.draw(opt1Rect); window.draw(opt2Rect);
}


class GameOver : public InterLevel
{
  // Texto de game over
  sf::Text gameOverText;

  public:

    // Construtor da interface de game over
    GameOver(std::string fontPath, int characterSize, sf::Color color);

    // Desenha a interface de game over
    void gameOverDraw(sf::RenderWindow &window,  int level, int time);
  
};

// Construtor da interface de game over e configuração da mensagem de game over
GameOver::GameOver(std::string fontPath, int characterSize, sf::Color color) : InterLevel(fontPath, characterSize, color){
  // Setagem do texto de game over
  gameOverText.setString("Game Over");
  gameOverText.setPosition(500, 200);
  gameOverText.setFont(getFont());
  gameOverText.setCharacterSize(48);
  gameOverText.setFillColor(color);
}

// Desenha a interface de game over (interface entre níveis + game over)
void GameOver::gameOverDraw(sf::RenderWindow &window,  int level, int time){
  // Desenha o texto de game over
  window.draw(gameOverText);

  // Desenha opções, timer e level
  iLevelDraw(window, level, time);
}