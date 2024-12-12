#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdio.h>
#include <vector>
#include "globals.h"

// Funções de geração de mapa
char* getEmptyMap();
char* getRandomMap();

class Map {
  public:

    int mapX = MAP_X;
    int mapY = MAP_Y;
    int mapS = MAP_SCALE;
    char worldMap[MAP_Y * MAP_X + 50];
    
    Map(int id){

    	if (id == 1) {
    	    char tempMap[] = {
    	        1, 1, 1, 1, 1, 1, 1, 1,
    	        1, 0, 0, 0, 0, 0, 0, 1,
    	        1, 0, 1, 1, 0, 0, 0, 1,
    	        1, 0, 1, 0, 0, 1, 0, 1,
    	        1, 0, 1, 0, 0, 1, 0, 1,
    	        1, 0, 0, 0, 0, 1, 1, 1,
    	        1, 0, 0, 0, 0, 0, 0, 1,
    	        1, 1, 1, 1, 1, 1, 1, 1
    	    };
    	    std::copy(std::begin(tempMap), std::end(tempMap), worldMap);
    	} 

		else if (id == 2) {
    	        char tempMap[] = {
    	            1, 0, 0, 0, 0, 0, 0, 1,
    	            1, 0, 0, 0, 0, 0, 0, 1,
    	            1, 0, 0, 0, 0, 0, 0, 1,
    	            1, 0, 0, 0, 2, 0, 0, 1,
    	            1, 0, 0, 0, 0, 0, 0, 1,
    	            1, 0, 0, 0, 0, 0, 0, 1,
    	            1, 0, 0, 0, 0, 0, 0, 1,
    	            1, 1, 1, 1, 1, 1, 1, 1
		    };
		    std::copy(std::begin(tempMap), std::end(tempMap), worldMap);
		}

		else if (id == 3) {
		  char tempMap[] = {
		    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		    1,0,2,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		    1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1,
		    1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1,
		    1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1,
		    1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1,
		    1,0,0,0,0,0,2,5,0,2,2,1,0,0,0,3,0,3,0,3,0,0,0,1,
		    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		    1,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		    1,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		    1,0,0,4,0,0,5,0,0,0,0,0,0,0,0,2,0,4,0,5,0,3,0,1,
		    1,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		    1,0,0,4,4,4,4,4,0,0,0,0,0,0,0,2,0,4,0,5,0,3,0,1,
		    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		    1,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
		  };
		  std::copy(std::begin(tempMap), std::end(tempMap), worldMap);
	
		}
		
		else if (id == 4) {
		  char tempMap[] = {
		    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
			1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
			1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
			1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
			1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
			1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
			1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
			1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
			1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
			1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
			1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
			1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
			1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
			1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
			1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
			1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
			1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
			1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
			1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
			1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
			1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
			1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
			1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
			1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
		  };
		  std::copy(std::begin(tempMap), std::end(tempMap), worldMap);
	
		}

		else if(id == 5){
		  char* tempMap = getEmptyMap();
		  std::copy(tempMap, tempMap + MAP_X*MAP_Y, worldMap);
		}

		else if(id == 6){
			char* tempMap = getRandomMap();
			std::copy(tempMap, tempMap + MAP_X*MAP_Y, worldMap);
		}

    }

    void drawMap(sf::RenderWindow &window){
      for(int x = 0; x < mapX; x ++){
		for(int y = 0; y < mapY; y ++){
		  if(worldMap[y*mapX+x] == 5){
		    drawRectangle(x,y,window,sf::Color{255,0,255});
		  }
		  if(worldMap[y*mapX+x] == 4){
		    drawRectangle(x,y,window,sf::Color{255,255,0});
		  }
		  if(worldMap[y*mapX+x] == 3){
		    drawRectangle(x,y,window,sf::Color{0,0,255});
		  }
		  if(worldMap[y*mapX+x] == 2){
		    drawRectangle(x,y,window,sf::Color{0,255,0});
		  }
		  if(worldMap[y*mapX+x] == 1){
		    drawRectangle(x,y,window,sf::Color{92,34,0});
		  }
		  if(worldMap[y*mapX+x] == 0){
		    drawRectangle(x,y,window,sf::Color{180,180,180});
		  }
		}
      }
    }

    void drawRectangle(int i, int j, sf::RenderWindow &window, sf::Color color){
      sf::RectangleShape rect;
      rect.setFillColor(color);
      rect.setSize(sf::Vector2f(MAP_SCALE/2,MAP_SCALE/2));
      rect.setPosition(static_cast <float> (i*MAP_SCALE/2), static_cast <float> (j*MAP_SCALE/2));
      window.draw(rect);
    }
};

// Função que gera um mapa vazio (apenas com as paredes laterais)
char* getEmptyMap(){
	char* emptyMap = new char[MAP_X*MAP_Y + 50];
	
	for(int x = 0; x < MAP_X; x++){

		for(int y = 0; y < MAP_Y; y++){
			
			if(x == 0 || x == MAP_X-1 || y == 0 || y == MAP_Y-1)
				emptyMap[y*MAP_X+x] = 1;
			
			else
				emptyMap[y*MAP_X+x] = 0;
		}
	}
	return emptyMap;
}
// Função que gera um mapa aleatório (teste -> função nada útil)
char* getRandomMap(){
	char* randomMap = new char[MAP_X*MAP_Y + 50];

	for(int x = 0; x < MAP_X; x++){
		
		for(int y = 0; y < MAP_Y; y++){
			
			if(x == 0 || x == MAP_X-1 || y == 0 || y == MAP_Y-1)
				randomMap[y*MAP_X+x] = 1;
			
			else
				randomMap[y*MAP_X+x] = rand() % 6;
		}
	}
	return randomMap;
}
