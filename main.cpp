#include <SFML/Graphics.hpp>
#include "globals.h"            // Arquivo de cabeçalho das variáveis globais
#include "map.h"                // Arquivo de cabeçalho do mapa     
#include "maze.h"               // Arquivo de cabeçalho do labirinto
#include "player.h"             // Arquivo de cabeçalho do jogador
#include "raycaster.h"          // Arquivo de cabeçalho do raycaster
#include "menu.h"               // Arquivo de cabeçalho do menu
#include "hud.h"                // Arquivo de cabeçalho da interface do HUD          
#include "il.h"                 // Arquivo de cabeçalho da interface de interLevel
#include "file.h"

int main() {
  // Definição do objeto para controle do arquivo de record
  PlayerInfo player_infos;
  PlayerInfo record_infos;
  RecordFile recordFile("records.txt");

  // Nome do jogador
  player_infos.setName("Player1");
  
  // Criação do menu
  Window *menu = createMenu();
  menu->runWindow();

  // Criação da janela do jogo
  sf::RenderWindow gameWindow(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "RAYCASTER", sf::Style::Titlebar);
  gameWindow.setFramerateLimit(FRAME_RATE); 
  
  // Clock do jogo -> permite trabalhar com fps e o time out
  sf::Clock clock;
  
  // Criação do mapa de jogo
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
    hud.updateTimer(clock);

    // Caso o tempo tenha acabado (GAME OVER)
    if(hud.getTimer() <= 0){

      // Limpeza da tela para abertura da interface de Game Over
      gameWindow.clear({0,0,0});
      
      // Enquanto não selecionar sair do jogo ou continuar, exibe a interface de Game Over
      while(!gameOver.select()){

        // Atualiza a interface de Game Over
        gameOver.navegation();  // verifica e trata a navegação na tela
        gameOver.select();      // verifica e trata se o jogador selecionou alguma opção

        // Exibição da interface de Game Over
        gameOver.gameOverDraw(gameWindow, hud.getLevel(), hud.getTimer());

        // Atualiza a tela de Game Over
        gameWindow.display();
      }

      // Caso o jogador deseje sair do jogo (voltar ao menu)
      if(!gameOver.continuation()){

        // Atualiza o score do jogador no arquivo de records
        player_infos.setScore(std::to_string(hud.getLevel()));
        recordFile.updateFile(player_infos);
        
        // Abertura do menu
        delete menu;
        menu = createMenu();
        menu->runWindow();
        
      }

      // Reset do time out e level
      hud.resetTimer();
      hud.resetLevel();

      // Atualiza o mapa
      map.updateMap();

      //reseta posição do jogador para o meio do mapa
      player.resetPosition();
    }

    // Atualiza o FPS
    hud.updateFps(clock);

    // Verificação de necessidade de fechar o jogo
    sf::Event event;
    while (gameWindow.pollEvent(event)) {
      
      if (event.type == sf::Event::Closed){

        // Atualiza o score do jogador no arquivo de records
        player_infos.setScore(std::to_string(hud.getLevel()));
        recordFile.updateFile(player_infos);

        // Fecha a janela do jogo
        gameWindow.close();
      }
      
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){

        // Atualiza o score do jogador no arquivo de records
        player_infos.setScore(std::to_string(hud.getLevel()));
        recordFile.updateFile(player_infos);

        // Fecha a janela do jogo
        gameWindow.close();
      }
    }

    // Limpeza da tela
    gameWindow.clear(sf::Color{27,115,0});

    // Desenho do céu do mapa
    gameWindow.draw(skybox);

    // Renderização do raycaster
    std::vector<ray> render =  raycast.renderLines(gameWindow, player, map);
    raycast.draw3D(gameWindow, render);

    // Atualização do jogador (movimentação)
    player.rotatePlayer(map);
    player.updatePlayer(hud.getFps());
    
    // Verifica se jogador chegou na saída do mapa
    if(player.checkExit(map)){ // Caso sim:

      // Incrementa o nível do jogo
      hud.updateLevel();

      // Diminui o tempo restante para o jogador completar o nível
      hud.timerOfLevel();    

      // Limpeza da tela para abertura da interface entre níveis
      gameWindow.clear({0,0,0});
      
      // Enquanto não selecionar sair do jogo ou continuar, exibe a interface de interlevel
      while(!iLevel.select()){

        // Atualiza a interface de interlevel
        iLevel.navegation();  // verifica e trata a navegação na tela
        iLevel.select();      // verifica e trata se o jogador selecionou alguma opção

        // Exibição da interface de interlevel
        iLevel.iLevelDraw(gameWindow, hud.getLevel(), hud.getTimer());

        // Atualiza a tela de interlevel
        gameWindow.display();
      }

      // Caso o jogador deseje sair do jogo (voltar ao menu)
      if(!iLevel.continuation()){
        
        // Atualiza o score do jogador no arquivo de records
        player_infos.setScore(std::to_string(hud.getLevel()));
        recordFile.updateFile(player_infos);
        
        // Reset do time out e do level
        hud.resetTimer();
        hud.resetLevel();
        
        // Abertura do menu
        delete menu;
        menu = createMenu();
        menu->runWindow();
        
      }
      
      // Atualiza o mapa
      map.updateMap();

      //reseta posição do jogador para o meio do mapa
      player.resetPosition();

    }

    // Desenho e exibição da interface do jogo
    hud.hudDraw(gameWindow,map, raycast, render, player);
    gameWindow.display();
  }
}

