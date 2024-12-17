#include <SFML/Graphics.hpp>
#include "maze.h"
#include "map.h"
#include "player.h"
#include "raycaster.h"
#include "globals.h"
#include "hud.h"
#include "il.h"
#include "menu.h"

int main() {
  // Criação do menu
  MenuWindow *menu = createMenu();
  menu->runWindow();

  // Criação da janela do jogo
  sf::RenderWindow gameWindow(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Poo proj", sf::Style::Titlebar);
  gameWindow.setFramerateLimit(FRAME_RATE); 
  
  // Variáveis de tempo de jogo
  float timeOut = MAXTIMEOUT;
  sf::Clock clock;
  sf::Time elapsed;
  float fps = 0;

  // Variável de nível do jogo
  int level = 1;
  
  // Criação do mapa
  int mapId = 3;
  Map map(mapId);

  // Criação do jogador
  Player player(300.f, 300.f);
  Raycaster raycast;

  // Criação da interface do jogo
  HUD hud("./assets/font.otf", 24, sf::Color::Green);

  // Criação da interface de interlevel
  InterLevel iLevel("./assets/font.otf", 24, sf::Color::Green);
  GameOver gameOver("./assets/font.otf", 24, sf::Color::Green);

  // Setagem do céu do mapa
  sf::RectangleShape skybox;
  skybox.setSize(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT/2));
  skybox.setOrigin(sf::Vector2f(0,0));
  skybox.setFillColor(sf::Color{137,180,210});
  
  while (gameWindow.isOpen()) {
    
    // Atualiza o tempo restante para jogador completar o nível
    elapsed = clock.getElapsedTime();
    timeOut -= elapsed.asSeconds();

    // Caso o tempo tenha acabado (GAME OVER)
    if(timeOut <= 0){

      // Limpeza da tela para abertura da interface de Game Over
      gameWindow.clear({0,0,0});
      
      // Enquanto não selecionar sair do jogo ou continuar, exibe a interface de Game Over
      while(!gameOver.select()){

        // Atualiza a interface de Game Over
        gameOver.navegation();
        gameOver.select();

        // Exibição da interface de Game Over
        gameOver.gameOverDraw(gameWindow, level, timeOut);

        // Atualiza a tela de Game Over
        gameWindow.display();
      }

      // Caso o jogador deseje sair do jogo (voltar ao menu)
      if(!gameOver.continuation()){
        
        // Abertura do menu
        delete menu;
        menu = createMenu();
        menu->runWindow();
        
      }

      // Time out reset
      timeOut = MAXTIMEOUT;

      // Level reset
      level = 1;

      // Atualiza o mapa
      map.updateMap();

      //reseta posição do jogador para o meio do mapa
      player.pX = 300.f;
      player.pY = 300.f;
    }

    // Atualiza o FPS
    fps = 1.0f/clock.restart().asSeconds();

    // Verificação de necessidade de fechar o jogo
    sf::Event event;
    while (gameWindow.pollEvent(event)) {
      
      if (event.type == sf::Event::Closed)
        gameWindow.close();
      
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        gameWindow.close();
    }


    gameWindow.clear(sf::Color{27,115,0});
    gameWindow.draw(skybox);
    std::vector<ray> render =  raycast.renderLines(gameWindow, player, map);
    raycast.draw3D(gameWindow, render);
    player.rotatePlayer(map);
    player.updatePlayer(fps);
    
    // Verifica se jogador chegou na saída do mapa
    if(player.checkExit(map)){ // Caso sim:

      // Incrementa o nível do jogo
      level++;

      // Diminui o tempo restante para o jogador completar o nível
      timeOut = MAXTIMEOUT/level + MINTIMEOUT;    

      // Limpeza da tela para abertura da interface entre níveis
      gameWindow.clear({0,0,0});
      
      // Enquanto não selecionar sair do jogo ou continuar, exibe a interface de interlevel
      while(!iLevel.select()){

        // Atualiza a interface de interlevel
        iLevel.navegation();
        iLevel.select();

        // Exibição da interface de interlevel
        iLevel.iLevelDraw(gameWindow, level, timeOut);

        // Atualiza a tela de interlevel
        gameWindow.display();
      }

      // Caso o jogador deseje sair do jogo (voltar ao menu)
      if(!iLevel.continuation()){
        
        // Level e Time out reset
        timeOut = MAXTIMEOUT;
        level = 1;
        
        // Abertura do menu
        delete menu;
        menu = createMenu();
        menu->runWindow();
        
      }
      
      // Atualiza o mapa
      map.updateMap();

      //reseta posição do jogador para o meio do mapa
      player.pX = 300.f;
      player.pY = 300.f;

    }

    // Desenho e exibição da interface do jogo
    hud.hudDraw(gameWindow,fps, map, raycast, render, player, level, timeOut);
    gameWindow.display();
  }
}

