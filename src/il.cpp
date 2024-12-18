#include "il.h"

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
