#pragma once
#include "map.h"
#include "player.h"
#include "globals.h"
#include <SFML/Graphics.hpp>
#include <math.h>

typedef struct {
  sf::Vector2f coordinates;
  int horv;
  int color;
  int index;
  float distance;
  float lineHeight;
} ray;

class Raycaster {
  public:
    
    void draw3D(sf::RenderWindow &window, std::vector<ray> rays) 
    {
      for(int i = 0; i < 60; i ++)
      {
		window.draw(renderStrip(rays.at(i), (i * MAP_SCALE) * SCREEN_WIDTH / (MAP_SCALE * 60), SCREEN_HEIGHT/2));
      }
    }

    sf::RectangleShape renderStrip(ray nearest, float xPos, float yPos) {
    	sf::RectangleShape rect;
    	rect.setSize(sf::Vector2f(MAP_SCALE, nearest.lineHeight/2));
    	rect.setOrigin(0, nearest.lineHeight / 4);
    	rect.setPosition(xPos, yPos);
	
    	if (nearest.color == 1) {
			rect.setFillColor(sf::Color{92,34,0});
			if(nearest.horv == 1) {
			  rect.setFillColor(sf::Color{76,20,0});
			}
    	  }
    	if (nearest.color == 2) {
			rect.setFillColor(sf::Color{0,255,0});
			if(nearest.horv == 1) {
			  rect.setFillColor(sf::Color{0,180,0});
			}
    	}
    	if (nearest.color == 3) {
			rect.setFillColor(sf::Color{0,0,255});
			if(nearest.horv == 1) {
			  rect.setFillColor(sf::Color{0,0,180});
			}
    	}
    	if (nearest.color == 4) {
			rect.setFillColor(sf::Color{255,255,0});
			if(nearest.horv == 1) {
			  rect.setFillColor(sf::Color{180,180,0});
			}
    	}
    	if (nearest.color == 5) {
			rect.setFillColor(sf::Color{255,0,255});
			if(nearest.horv == 1) {
			  rect.setFillColor(sf::Color{180,0,180});
			}
    	}
		if (nearest.color == 7) {
			rect.setFillColor(sf::Color{137,180,210});
			if(nearest.horv == 1) {
			  rect.setFillColor(sf::Color{137,180,210});
			}
    	}
      	return rect;
    }

    std::vector<ray> renderLines(sf::RenderWindow &window, Player player, Map map)
    {
      ray horizontal;
      ray vertical;
      std::vector<ray> nearest;
      float one_rad = ONE_RAD;
      float pAng = (- player.playerSprite.getRotation() + (FOV / 2)) * one_rad;
      float fixFishEye;

      for(int i = (FOV/2); i > - (FOV/2); i--){
	pAng -= one_rad;
	fixFishEye = player.pAng + pAng;
	if(fixFishEye < 0) { fixFishEye += 2* PI;}
	if(fixFishEye > 2 * PI) { fixFishEye -= 2* PI;}
	horizontal = scanHorizontal(window, player, map,  pAng);
	vertical   = scanVertical(window, player, map, pAng);

	if(horizontal.distance < vertical.distance){
	  horizontal.distance = horizontal.distance * cos(- fixFishEye);
	  horizontal.lineHeight = (MAP_SCALE * 1024) / (horizontal.distance);
	  horizontal.color = map.worldMap[horizontal.index];
	  nearest.push_back(horizontal);
	}
	if(horizontal.distance > vertical.distance){
	  vertical.distance = vertical.distance * cos(- fixFishEye);
	  vertical.lineHeight = (MAP_SCALE * 1024) / (vertical.distance);
	  vertical.color = map.worldMap[vertical.index];
	  nearest.push_back(vertical);
	}
      }
      return nearest;
    }

    void drawLines(sf::RenderWindow &window, sf::Vector2f playerPos, std::vector<ray> rayPos, sf::Color color)
    {
      for(int i = 0; i < rayPos.size(); i++)
      {
	sf::Vertex line[2];
	line[0] = sf::Vertex(sf::Vector2f(playerPos.x/2, playerPos.y/2),color);
	line[1] = sf::Vertex(sf::Vector2f(rayPos.at(i).coordinates.x/2, rayPos.at(i).coordinates.y/2),color);
	window.draw(line,2,sf::Lines);
      }
    }


    ray scanHorizontal( sf::RenderWindow &window, Player player, Map map, float rayAng){
      ray horizontal;
      float rayX;
      float rayY;
      int mX, mY, index;
      float xOffset, yOffset;
      int depth = 0;
      float Tan = 1/tan(rayAng);

      if(sin(rayAng) > 0.001)
      { 
	//rayY = (((int) player.pY >> 6) << 6 ) - 0.0001;
	rayY = (((int) player.pY / MAP_SCALE) * MAP_SCALE) - 0.001f;
	rayX = (player.pY-rayY)*Tan+player.pX; yOffset=-MAP_SCALE; xOffset=-yOffset*Tan;
      }//looking up 

      else if(sin(rayAng) < -0.001)
      { 
	//rayY = (((int) player.pY >> 6) << 6) + MAP_SCALE;
	rayY = (((int) player.pY / MAP_SCALE) * MAP_SCALE) + MAP_SCALE;
	rayX = (player.pY - rayY) * Tan + player.pX;
	yOffset = MAP_SCALE; xOffset= -yOffset * Tan;
      }//looking down

      else if ((-(rayAng) < 0.001f) || (-(rayAng) > 2 * PI - 0.001f))
      {
	rayX = player.pX; 
	rayY = player.pY;
	xOffset = MAP_SCALE;
	yOffset = 0;
      }

      else if ((-(rayAng) > PI - 0.001f) && (-(rayAng) < PI + 0.001f))
      {
	rayX = player.pX; 
	rayY = player.pY;
	xOffset = - MAP_SCALE;
	yOffset = 0;
      }

      else{
	rayX = player.pX;
	rayY = player.pY;
	depth = MAP_X;
      }

      while(depth < MAP_X){ 
	//mX = (int)(rayX) >> 6;
	//mY = (int)(rayY) >> 6;
	mX = (int) (rayX / MAP_SCALE);
	mY = (int) (rayY / MAP_SCALE);
	index = mY * MAP_X + mX;                          

	if(index > 0 && index < MAP_X * MAP_Y && map.worldMap[index] != 0){
	  depth = MAP_X;
	}//hit         

	else{ 
	  rayX +=xOffset;
	  rayY += yOffset; 
	  depth += 1;
	} 
      }

      horizontal.coordinates.x = rayX;
      horizontal.coordinates.y = rayY;
      horizontal.distance = dist(player.pX, player.pY, rayX, rayY);
      horizontal.horv = 0;
      horizontal.index = index;
      //drawLines(window, sf::Vector2f(player.pX, player.pY), horizontal.coordinates, sf::Color::Green);
      return horizontal;
    }

    ray scanVertical(sf::RenderWindow &window, Player player, Map map, float rayAng)
    {
      ray vertical;
      float rayX;
      float rayY;
      int mX, mY, index;
      float xOffset, yOffset;
      int depth = 0;
      float nTan = tan(rayAng);

      if (cos(rayAng) > 0.001)
      {
	rayX = (((int) player.pX / MAP_SCALE) * MAP_SCALE) + MAP_SCALE;
	//rayX = (((int) player.pX >>6 ) << 6) + MAP_SCALE;
	rayY =(player.pX - rayX) * nTan + player.pY; 
	xOffset = MAP_SCALE; 
	yOffset = -xOffset * nTan;
      }

      else if (cos(rayAng) < - 0.001)
      { 
	//rayX = (((int)player.pX >> 6) << 6) - 0.0001; 
	rayX = (((int) player.pX / MAP_SCALE) * MAP_SCALE) -0.001f;
	rayY = (player.pX - rayX) * nTan + player.pY; 
	xOffset = -MAP_SCALE; 
	yOffset = -xOffset * nTan;
      }

      else if( (-(rayAng) > (PI / 2) - 0.001) && (-(rayAng) < (PI / 2) + 0.001f))
      {
	rayX = player.pX; 
	rayY = player.pY; 
	yOffset = MAP_SCALE;
	xOffset = 0;
      }

      else if( (-(rayAng) > (3 * PI / 2) - 0.001f) && ( -(rayAng) < (3 * PI / 2) + 0.001f))
      {
	rayX = player.pX; 
	rayY = player.pY; 
	yOffset = - MAP_SCALE;
	xOffset = 0;
      }

      else
      {
	rayX = player.pX;
	rayY = player.pY;
	depth = MAP_X;
      }

      while(depth < MAP_X)
      {

	//mX = (int) (rayX) >> 6;
	//mY = (int) (rayY) >> 6; 
	mX = (int) (rayX / MAP_SCALE);
	mY = (int) (rayY / MAP_SCALE);
	index=mY * MAP_X + mX; 

	mX = (int) rayX / MAP_SCALE;
	mY = (int) rayY / MAP_SCALE;
	index = mY * MAP_X + mX;

	if(index > 0 && index < (MAP_X * MAP_X) && map.worldMap[index] != 0)
	{
	  depth = MAP_X; // Encontrou uma parede
	}

	else
	{
	  rayX += xOffset;
	  rayY += yOffset;
	  depth += 1;
	}
      }

      vertical.coordinates.x = rayX;
      vertical.coordinates.y = rayY;
      vertical.distance = dist(player.pX, player.pY, rayX, rayY);
      vertical.horv = 1;
      vertical.index= index;
      //drawLines(window, sf::Vector2f(player.pX, player.pY), vertical.coordinates, sf::Color::Red);
      return vertical;
    }

    /*   sf::RectangleShape renderRectangle(float height, float length, float x_pos, float y_pos, int hOrV) {
	 sf::RectangleShape rect;
	 sf::Vector2f rectSize;
	 rect.setOrigin(0, height / 2);
	 rect.setPosition(x_pos, y_pos);
	 rectSize.x = length;
	 rectSize.y = height;
	 rect.setSize(rectSize);

	 if (hOrV == 0){
	 rect.setOutlineColor(sf::Color{0, 0, 0});
	 rect.setFillColor(sf::Color{111, 116, 122});
	 }
	 if (hOrV == 1){
	 rect.setOutlineColor(sf::Color{0, 0, 0});
	 rect.setFillColor(sf::Color{140, 146, 156});
	 }
	 if (hOrV == 2){
	 rect.setOrigin(0,0);
	 rect.setPosition(x_pos, y_pos);
	 rect.setFillColor(sf::Color{92, 75, 59});
	 }
	 if (hOrV == 3){
	 rect.setOrigin(0,0);
	 rect.setPosition(0, 0);
	 rect.setFillColor(sf::Color{0, 161, 15MAP_X});
	 }
	 return rect;
	 }*/
};
