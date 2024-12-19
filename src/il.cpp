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


/* Função para captura do nome do jogador
  Esta função abre uma interface com a única função de captura do nome do jogador
  -> Entrada: nenhuma
  -> Saída: nome do jogador
*/
std::string catchPlayerName(){

  // Variáveis para captura do nome do jogador
  std::string playerName;

  // Título de exibição da janela para usuário digitar o nome
  sf::Text title;
  title.setString("NOME DO Jogador");
  title.setFillColor(sf::Color::White);
  title.setCharacterSize(48);
  title.setPosition(500, 200);

  // Texto de exibição do nome do jogador até então digitado
  sf::Text textName;
  textName.setFillColor(sf::Color::White);
  textName.setCharacterSize(24);
  textName.setPosition(SCREEN_WIDTH / 2, 350); // posição do texto na tela

  // Retânqulo para exibição do nome do jogador
  sf::RectangleShape rect;
  rect.setFillColor(sf::Color::Black);
  rect.setOutlineColor(sf::Color::White);
  rect.setOutlineThickness(2);
  rect.setSize(sf::Vector2f(400, 50));
  rect.setPosition(450, 330);

  // Configuração da fonte do texto
  sf::Font font;
  font.loadFromFile("./assets/fonts/font.otf");
  textName.setFont(font);
  title.setFont(font);

  // Criação da janeal para captura do nome do jogador
  sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "LOGIN", sf::Style::Titlebar);
  window.setFramerateLimit(FRAME_RATE); 

  // Variável para verificação de eventos
  sf::Event event;

  // Enquanto a janela estiver aberta, digitamos captura-se o nome do jogador
  while(window.isOpen()){

    // Caso um evento seja detectado
    while(window.pollEvent(event)){

      // Caso o evento seja de fechamento da janela, fecha a janela
      if(event.type == sf::Event::Closed){
        window.close();
      }

      // Caso o evento seja de digitação de texto
      if(event.type == sf::Event::TextEntered){

        // Se o usuário apertar backspace e o nome não estiver vazio, apaga o último caractere
        if(event.text.unicode == '\b' && !playerName.empty())
          playerName.pop_back();
        
        // Se o caractere digitado for um caractere alfanumérico, adiciona ao nome
        else if(event.text.unicode < 128 && playerName.size() < 30)
          playerName += event.text.unicode;

      }

      // Caso o evento seja de apertar a tecla enter, fecha a janela
      if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter)
        window.close();

    }

    textName.setString(playerName); // Atualiza o texto com o nome digitado

    // Centralziação de texto na tela
    sf::FloatRect textNameRect = textName.getLocalBounds(); // armazenar as dimensões do texto
    textName.setOrigin(textNameRect.width/2, textNameRect.height/2); // seta origem no centro do texto


    window.clear();       // Limpa a tela para atualização do nome digitado
    window.draw(title);   // Desenha o título da janela
    window.draw(rect);    // Desenha o retângulo para exibição do nome
    window.draw(textName);// Desenha o nome digitado na tela
    window.display();     // Atualiza a tela

  }

  // Retorna o nome do jogador
  return playerName; 
}