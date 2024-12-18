#include "il.h"

// Construtor e configuração (setup) da interface de interlevel
InterLevel::InterLevel(std::string fontPath, int characterSize, sf::Color color){
  
  // Inicialização da variável de continuidade do jogo
  _continueGame = false;
  
  _font.loadFromFile(fontPath);

  // Setagens opcões da interface 
  // Opção 1
  _opt1Text.setString("Continuar jogando");         // texto
  _opt1Text.setPosition(OPT1_TEXT_POSITION);        // posição do texto na tela
  _opt1Text.setFont(_font);                         // fonte
  _opt1Text.setCharacterSize(characterSize);        // tamanho do caractere
  _opt1Text.setFillColor(sf::Color::White);         // cor do texto
  _opt1Rect.setFillColor(sf::Color::Black);         // cor do retângulo de seleção
  _opt1Rect.setSize(sf::Vector2f(OPT1_RECT_SIZE));  // tamanho do retângulo de seleção
  _opt1Rect.setPosition(OPT1_RECT_POSITION);        // posição do retângulo de seleção
  
  //Opção 2
  _opt2Text.setString("Voltar ao menu principal");  // texto
  _opt2Text.setPosition(OPT2_TEXT_POSITION);        // posição na tela
  _opt2Text.setFont(_font);                         // fonte
  _opt2Text.setCharacterSize(characterSize);        // tamanho do caractere
  _opt2Text.setFillColor(sf::Color::White);         // cor do texto
  _opt2Rect.setFillColor(sf::Color::Black);         // cor do retângulo de seleção
  _opt2Rect.setSize(sf::Vector2f(OPT2_RECT_SIZE));  // tamanho do retângulo de seleção
  _opt2Rect.setPosition(OPT2_RECT_POSITION);        // posição do retângulo de seleção

  // Setagem da fontes escolhida para o iLevel
  _iLevelTimer.setFont(_font);
  _iLevelLevels.setFont(_font);

  // Setagem do tamanho dos caracteres
  _iLevelTimer.setCharacterSize(characterSize);
  _iLevelLevels.setCharacterSize(characterSize);

  // Setagem da cor dos caracteres
  _iLevelTimer.setFillColor(color);
  _iLevelLevels.setFillColor(color);
  
  // Setagem das posições do FPS, timer e level
  _iLevelTimer.setPosition(TIMER_ILPOSITION);
  _iLevelLevels.setPosition(LEVEL_ILPOSITION);
}

// Navegação entre as opções
void InterLevel::navegation(){
  // Verifica se a tecla de cima (opt 1) foi pressionada, se sim move para cima o cursor de opção
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) ||  sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
    _opt1Rect.setFillColor(sf::Color::White);
    _opt2Rect.setFillColor(sf::Color::Black);
    moveUp();
  }
  // Verifica se a tecla de baixo (opt 2) foi pressionada, se sim move para baixo o cursor de opção
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) ||  sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
    _opt2Rect.setFillColor(sf::Color::White);
    _opt1Rect.setFillColor(sf::Color::Black);
    moveDown();
  }

}

// Seleciona a opção e retorna true caso a tecla enter seja pressionada
bool InterLevel::select(){
  
  // Verifica se a tecla enter foi pressionada, uma opção foi selecionada e retorna true
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)){
    _continueGame = (_option == 1);
    return true;
  }
  
  // Caso contrário, retorna false
  return false;
}

// Retorna a continuidade do jogo
bool InterLevel::continuation(){
  return _continueGame;
}

// Desenha a interface de interlevel
void InterLevel::iLevelDraw(sf::RenderWindow &window, int level, int time){
  
  // Setagem do timer e level
  _iLevelTimer.setString("Time out: " + std::to_string(time));
  _iLevelLevels.setString("Level: " + std::to_string(level));
  
  // Desenha o FPS, time out e level
  window.draw(_iLevelTimer); window.draw(_iLevelLevels);
  
  // Desenha as opções
  window.draw(_opt1Text); window.draw(_opt2Text);
  window.draw(_opt1Rect); window.draw(_opt2Rect);
}

// Construtor da interface de game over e configuração da mensagem de game over
GameOver::GameOver(std::string fontPath, int characterSize, sf::Color color) : InterLevel(fontPath, characterSize, color){
  // Setagem do texto de game over
  _gameOverText.setString("Game Over");
  _gameOverText.setPosition(500, 200);
  _gameOverText.setFont(getFont());
  _gameOverText.setCharacterSize(48);
  _gameOverText.setFillColor(color);
}

// Desenha a interface de game over (interface entre níveis + game over)
void GameOver::gameOverDraw(sf::RenderWindow &window,  int level, int time){
  // Desenha o texto de game over
  window.draw(_gameOverText);

  // Desenha opções, timer e level
  iLevelDraw(window, level, time);
}
