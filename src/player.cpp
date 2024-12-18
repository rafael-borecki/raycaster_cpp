#include "player.h"

Player::Player(float pX, float pY) : pX(pX), pY(pY) {
    playerSprite.setSize(sf::Vector2f(MAP_SCALE / 2, MAP_SCALE / 2));
    playerSprite.setPosition((MAP_SCALE / 2 * MAP_X) / 2, (MAP_SCALE / 2 * MAP_Y) / 2);
    playerSprite.setOrigin(MAP_SCALE / 4, MAP_SCALE / 4);
    pdX = 0;
    pdY = 0;
    pAng = 0;
    pAngDeg = 0;
    moveSpeed = 0.09f;
    rotSpeed = 0.9f;
}

//Metodo de movimentacao principal
void Player::rotatePlayer(Map map) {
    if(pAng > 6.29)     
        pAng = 0.01f;
    
    if(pAng < 0)    
        pAng = 2 * PI - 0.001f;
        
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        pAng += rotSpeed;
        pdX = cos(pAng);
        pdY = sin(pAng);   
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        pAng -= rotSpeed;
        pdX = cos(pAng);
        pdY = sin(pAng);
    }

    //Verificacao de colisao:
    //Quando você vai movimentar, é adicionado dX,dY no sentido que vc ta indo, na posição do jogador (pX, pY)
    //É verificado se nessa posição (pX + dX, pY + dY) o id da célula é == 0
    //Se for, o movimento é validado.
    //Se não for em x , adiciona dX , se não for em y , adiciona -dY.
    //Encerra o loop de movimento e vai para o proximo
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
      pX -= moveSpeed * pdX;
      pY -= moveSpeed * pdY;

      if(map.worldMap[map.getMapInfo('x') * (int)((pY) / MAP_SCALE) +
	  (int)((pX + 0.1 * playerSprite.getLocalBounds().width / 2) / MAP_SCALE)]) {
	pX += moveSpeed * pdX;
      }

      if(map.worldMap[map.getMapInfo('x') * (int)((pY) / MAP_SCALE) +
	  (int)((pX - 0.1 * playerSprite.getLocalBounds().width / 2) / MAP_SCALE)]) {
	pX += moveSpeed * pdX;
      }

      if(map.worldMap[map.getMapInfo('x') * (int)((pY + 0.1 * playerSprite.getLocalBounds().height / 2) / MAP_SCALE) +
	  (int)((pX) / MAP_SCALE)]) {
	pY += moveSpeed * pdY;
      }

      if(map.worldMap[map.getMapInfo('x') * (int)((pY - 0.1 * playerSprite.getLocalBounds().height / 2) / MAP_SCALE) +
	  (int)((pX) / MAP_SCALE)]) {
	pY += moveSpeed * pdY;
      }
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
      pY += moveSpeed * pdY;
      pX += moveSpeed * pdX;

      if(map.worldMap[map.getMapInfo('x') * (int)((pY) / MAP_SCALE) +
	  (int)((pX + 0.1 * playerSprite.getLocalBounds().width / 2) / MAP_SCALE)]) {
	pX -= moveSpeed * pdX;
      }

      if(map.worldMap[map.getMapInfo('x') * (int)((pY) / MAP_SCALE) +
	  (int)((pX - 0.1 * playerSprite.getLocalBounds().width / 2) / MAP_SCALE)]) {
	pX -= moveSpeed * pdX;
      }

      if(map.worldMap[map.getMapInfo('x') * (int)((pY + 0.1 * playerSprite.getLocalBounds().height / 2) / MAP_SCALE) +
	  (int)((pX) / MAP_SCALE)]) {
	pY -= moveSpeed * pdY;
      }

      if(map.worldMap[map.getMapInfo('x') * (int)((pY - 0.1 * playerSprite.getLocalBounds().height / 2) / MAP_SCALE) +
	  (int)((pX) / MAP_SCALE)]) {
	pY -= moveSpeed * pdY;
      }
    }

    //Retorna o jogador ao spawn point
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::G))
      resetPosition();
}

void Player::resetPosition(){
  pX = 300.0f;
  pY = 300.0f;
}

//Metodo para atualizar a posicao e rotacao do jogador
//A velocidade de translacao e rotacao sao normalizadas pelo fps,
//dessa forma, o resultado do jogo é o mesmo independente do computador. 
void Player::updatePlayer(float fps) {
  rotSpeed = 0.05f * FRAME_RATE / fps;
  moveSpeed = 1.f * FRAME_RATE / fps;
  pAngDeg = pAng * RADIAN;
  playerSprite.setRotation(pAngDeg);
  playerSprite.setPosition(pX / 2, pY / 2);
}

sf::RectangleShape Player::getSprite() const{
  return playerSprite; 
}

float Player::getPos(char axis) {
  if(axis == 'x')
    return pX;

  if(axis == 'y')
    return pY;

  else
    return -1;
}

float Player::getAng(char radOrDeg) {
  if(radOrDeg == 'r')
    return pAng;

  if(radOrDeg == 'd')
    return pAngDeg;

  else
    return -1;
}


//Verificacao de saida do mapa - basicamente verifica a colisao com uma parede do tipo 7
int Player::checkExit(Map map) {
  int exit = 0;

  for (int i = -1; i < 2; i = i + 2)
    for (int j = -1; j < 2; j = j + 2) {
      if(map.worldMap[map.getMapInfo('x') * (int)(((pY) / MAP_SCALE) + 0.1 * i) + (int)(((pX / MAP_SCALE) + 0.1 * j))] == 7)      
	exit = 1;
    }
  return exit;
}
