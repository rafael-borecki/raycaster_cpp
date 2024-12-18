#pragma once


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

	char *_maze; // String que representa o mapa do labirinto
	
public:

    // Construtores da classe
	Maze(int map_x, int map_y);

	// Destrutor da classe
	~Maze();

    // Busca em profundidade com backtracking
	void DFS(int x_origin, int y_origin, std::vector<std::pair<int,int>> &possibOuts);

    // Método de geração de um labirinto aleatório
	int toRandomMaze();

    // Método que retorna o mapa gerado na forma de uma string padrão de c
	char* getMazeMap();

	// Sobrecarga do operador por atribuição
	Maze& operator =(const Maze& maze2);
};