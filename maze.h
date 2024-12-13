#ifndef MAZE_H
#define MAZE_H

// Includes

#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>
#include <random>
#include "globals.h"

/////////////////////////////// Geração de labirinto /////////////////////////////////

char *getEmptyMap(int map_x, int map_y);
char *getFilledMap(int map_x, int map_y);


class Maze{

	int _mazeX; // Tamanho do labirinto em X
	int _mazeY; // Tamanho do labirinto em Y

	char *_maze;
	
public:

    // Construtor da classe
	Maze(int map_x, int map_y){
		_mazeX = map_x;
		_mazeY = map_y;
		_maze = getFilledMap(map_x, map_y);
	}

    // Método que implementa a busca em profundidade para gerar o labirinto
	void DFS(int x_origin, int y_origin){

        // Número que representa a direção e sentido da próxima célula
        int d = 0;

        // Vetor de possíveis direções da próxima célula
        std::vector<int> v{0,1,2,3};

        // Motor com semente gerada por `rd`.
        std::random_device r;
        std::mt19937 R(r());

        // Embaralha o vetor `v` usando o motor de números aleatórios `g`.
        std::shuffle(v.begin(), v.end(), R);


		_maze[y_origin*_mazeX + x_origin] = 0;

		for(int i = 0; i < 4; i++){

			int x = x_origin;
			int y = y_origin;

            d = v[i];

			switch(d){
				case 0: x += 2; break;
				case 1: x -= 2; break;
				case 2: y += 2; break;
				case 3: y -= 2; break;
			}

			if(x <= 0 || x >= _mazeX -1 || y <= 0 || y >= _mazeY -1)
				continue;

			if(_maze[y*_mazeX + x] == 0)
				continue;

			switch(d){
				case 0: _maze[y*_mazeX + x-1] = 0; break;
				case 1: _maze[y*_mazeX + x+1] = 0; break;
				case 2: _maze[(y-1)*_mazeX + x] = 0; break;
				case 3: _maze[(y+1)*_mazeX + x] = 0; break;
			}
			

			DFS(x, y);
		}

	}

    // Método que gera um labirinto aleatório
	void toRandomMaze(){
		// começa busca em profundidade a partir do meio do labirinto
		DFS(_mazeX/2, _mazeY/2);
	}

    // Método que retorna o mapa gerado na forma de uma string padrão de c
	char* getMazeMap(){
		toRandomMaze();
		return _maze;
	}
};

// Função que gera um mapa vazio (apenas com as paredes laterais)
char* getEmptyMap(int map_x, int map_y){
	char* emptyMap = new char[map_x*map_y + 50];
	
	for(int x = 0; x < map_x; x++){

		for(int y = 0; y < map_y; y++){
			
			if(x == 0 || x == map_x-1 || y == 0 || y == map_y-1)
				emptyMap[y*map_x+x] = 1;
			
			else
				emptyMap[y*map_x+x] = 0;
		}
	}
	return emptyMap;
}

// Função que gera um mapa cheio (com paredes em todas as células)
char* getFilledMap(int map_x, int map_y){
	char* filledMap = new char[map_x*map_y + 50];
	
	for(int x = 0; x < map_x; x++){

		for(int y = 0; y < map_y; y++){
			
			if(x == 0 || x == map_x-1 || y == 0 || y == map_y-1)
				filledMap[y*map_x+x] = 1;
			
			else
				filledMap[y*map_x+x] = 2;
		}
	}
	return filledMap;
}

#endif