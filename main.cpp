#include <SFML/Graphics.hpp>
#include "maze.h"
#include "map.h"
#include "player.h"
#include "raycaster.h"
#include "globals.h"
//#include "gun.h"
#include "ui.h"

int main() {
  sf::RenderWindow gameWindow(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Poo proj", sf::Style::Titlebar);
  gameWindow.setFramerateLimit(FRAME_RATE);
  gameWindow.setPosition(sf::Vector2i(2560, 50)); 

  sf::Clock clock;
  float fps = 0;
  int level = 1;
  
  int mapId = 3;
  Map map(mapId);

  Player player(300.f, 300.f);
  Raycaster raycast;
  UI ui;

  sf::RectangleShape skybox;
  skybox.setSize(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT/2));
  skybox.setOrigin(sf::Vector2f(0,0));
  skybox.setFillColor(sf::Color{137,180,210});
  
  while (gameWindow.isOpen()) {
    fps = 1.0f/clock.restart().asSeconds();

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

      //incrementa o nível do jogo
      level++;

      // AQUI DEVE ESTAR A VERIFICAÇÃO SE O JOGADOR QUER CONTINUAR OU NÃO JOGANDO!

      // Atualiza o mapa
      map.updateMap();

      //reseta posição do jogador para o meio do mapa
      player.pX = 300.f;
      player.pY = 300.f;
    }
   
   
    ui.uiDraw(gameWindow,fps, map, raycast, render, player, level, 1);
    gameWindow.display();
  }
}
