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

// Classe de um labirito
//Por padrão: labirinto vazio (somento com paredes laterais)
//Usando o método toRandomMaze, é possível gerar um labirinto aleatório
class Maze{

	int _mazeX; // Tamanho do labirinto em X
	int _mazeY; // Tamanho do labirinto em Y

	char *_maze;
	
public:

    // Construtor da classe
	Maze(int map_x, int map_y){
		_mazeX = map_x;
		_mazeY = map_y;
		_maze = getEmptyMap(map_x, map_y);
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

        // Embaralha o vetor de direções para aumentar aleatoriedade do labirinto
        std::shuffle(v.begin(), v.end(), R);

        // marca posição atual como caminho
		_maze[y_origin*_mazeX + x_origin] = 0;

        // Busca em profundidade em células vizinhas
		for(int i = 0; i < 4; i++){

            // x e y da célula de origem
			int x = x_origin;
			int y = y_origin;

            // Direção atual do for
            d = v[i];

            // De acordo coma a direção e sentido da célula vizinha, move-se x e y
			switch(d){
				case 0: x += 2; break;
				case 1: x -= 2; break;
				case 2: y += 2; break;
				case 3: y -= 2; break;
			}
            
            // Se célula vizinha conhecidir com parede ou estiver fora do labirinto, parte-se para próxima
			if(x <= 0 || x >= _mazeX -1 || y <= 0 || y >= _mazeY -1)
				continue;

            // Se a célula vizinha já foi vizitada, parte-se para a próxima
			if(_maze[y*_mazeX + x] == 0)
				continue;

            // Caso contrário, célula entre a atual e a vizinha (2 unidades de distância), marcamos
            //célula no meio entre as duas como caminho
			switch(d){
				case 0: _maze[y*_mazeX + x-1] = 0; break;
				case 1: _maze[y*_mazeX + x+1] = 0; break;
				case 2: _maze[(y-1)*_mazeX + x] = 0; break;
				case 3: _maze[(y+1)*_mazeX + x] = 0; break;
			}
			
            // Busca em profundidade da célula vizinha
			DFS(x, y);
		}

	}

    // Método que gera um labirinto aleatório
	void toRandomMaze(){

		// Cria-se um labirinto somente com paredes ( _maze[j] != 0 para todo j )
		_maze = getFilledMap(_mazeX, _mazeY);

		// começa busca em profundidade a partir do meio do labirinto
		DFS(_mazeX/2, _mazeY/2);
	}

    // Método que retorna o mapa gerado na forma de uma string padrão de c
	char* getMazeMap(){
		return _maze;
	}
};

// Função que gera um mapa vazio (apenas com as paredes laterais)
char* getEmptyMap(int map_x, int map_y){
	char* emptyMap = new char[map_x*map_y + 50];
	
	for(int x = 0; x < map_x; x++){

		for(int y = 0; y < map_y; y++){
			
			// Paredes Marrons nas bordas
			if(x == 0 || x == map_x-1 || y == 0 || y == map_y-1)
				emptyMap[y*map_x+x] = 1;
			
			// Caminho
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
			
			// Paredez marroms nas bordas
			if(x == 0 || x == map_x-1 || y == 0 || y == map_y-1)
				filledMap[y*map_x+x] = 1;
			
			// Paredes azuis no meio
			else
				filledMap[y*map_x+x] = 3;
		}
	}
	return filledMap;
}

#endif