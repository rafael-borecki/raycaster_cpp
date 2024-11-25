#include <SFML/Graphics.hpp>
#include "map.h"
#include "player.h"
#include "raycaster.h"
#include "globals.h"
//#include "gun.h"
#include "ui.h"

int main() {
  sf::RenderWindow gameWindow(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Poo proj", sf::Style::Titlebar);
  gameWindow.setFramerateLimit(FRAME_RATE);
  //gameWindow.setPosition(sf::Vector2i(2560, 50)); 

  sf::Clock clock;
  float fps = 0;
  
  int mapId = 3;
  Map map(mapId);

  Player player(300.f, 300.f);
  Raycaster raycast;
  UI ui;

  sf::RectangleShape skybox;
  skybox.setSize(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT/2));
  skybox.setOrigin(sf::Vector2f(0,0));
  skybox.setFillColor(sf::Color{137,180,210});
  //Gun gun(gameWindow);
  
  while (gameWindow.isOpen()) {
    fps = 1.0f/clock.restart().asSeconds();

    sf::Event event;
    while (gameWindow.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        gameWindow.close();
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
        gameWindow.close();
      if(sf::Keyboard::isKeyPressed(sf::Keyboard::B))
	printf("\n%f ", fps);
    }

    gameWindow.clear(sf::Color{27,115,0});
    gameWindow.draw(skybox);

    raycast.draw3D(gameWindow, raycast.renderLines(gameWindow, player, map));
    player.rotatePlayer(map);
    player.updatePlayer(fps);
    //gun.gunDraw(gameWindow, clock, &player);
    ui.uiDraw(gameWindow,fps /*,player.getAmmo()*/);
    gameWindow.display();
  }
}
