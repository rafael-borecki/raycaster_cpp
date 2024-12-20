#include "maze.h"


// Construtor da classe por parÂmetros
Maze::Maze(int map_x, int map_y){
	_mazeX = map_x;
	_mazeY = map_y;
	_maze = getEmptyMap(map_x, map_y);
}

// Destrutor da classe
Maze::~Maze(){
	delete[] _maze;	
}

// Método que implementa a busca em profundidade para gerar o labirinto
void Maze::DFS(int x_origin, int y_origin, std::vector<std::pair<int,int>> &possibOuts){

	// Número que representa a direção e sentido da próxima célula
	int d = 0;

	// Vetor de possíveis direções da próxima célula
	std::vector<int> v{0,1,2,3};

	// Motor com semente gerada por `rd`.
	std::random_device rd;
	std::mt19937 R(rd());

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
		if(x <= 0 || x >= _mazeX -1 || y <= 0 || y >= _mazeY -1){
			
			// Flag para o caso em que a célula vizinha está fora do labirinto
			bool flag = false;
			if(x < 0 || x > _mazeX -1 || y < 0 || y > _mazeY -1) flag = true;
			
			// Par da saída (célula do meio entre a atual e a vizinha, célula vizinha)
			std::pair<int, int> out;

			// De acordo com a direção e sentido da célula vizinha, adiciona-se a célula do meio
			//entre a atual e a vizinha, no primeiro elemento do par da possível saída
			switch(d){
				case 0: 
						out.first = y * _mazeX + x -1;  
						break;
				case 1: 
						out.first = y * _mazeX + x +1;
						break;
				case 2:  
						out.first = (y-1) * _mazeX + x;
						break;
				case 3:  
						out.first = (y+1) * _mazeX + x;
						break;
			}

			// Se a célula vizinha está fora do labirinto, a segunda parte é igual à célula do meio
			out.second = flag ? out.first : y * _mazeX + x;
			
			// Adiciona saída ao vetor de possíveis saídas
			possibOuts.push_back(out);
			
			// Continua para a próxima célula vizinha
			continue;
		}

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
		DFS(x, y, possibOuts);	
	}

}

// Método que gera um labirinto aleatório
//		Saída: índice da célula de saída do labirinto
int Maze::toRandomMaze(){

	// Deleta o labirinto atual
	delete[] _maze;

	// Cria-se um labirinto somente com paredes ( _maze[j] != 0 para todo j )
	_maze = getFilledMap(_mazeX, _mazeY);

	// Vetor de possíveis saídas do labirinto
	std::vector<std::pair<int,int>> possibOuts;
		
	// começa busca em profundidade a partir do meio do labirinto
	DFS(_mazeX/2, _mazeY/2, possibOuts);

	// Motor com semente gerada por `rd`.
	std::random_device rd;
	std::mt19937 R(rd());

	// Distribuição de números inteiros entre 0 e o tamanho da lista de saídas possíveis
	std::uniform_int_distribution<int> dist(0, possibOuts.size()-1);
	
	// Escolhe uma saída aleatória (formada por um par) devido a distância entre as células vizinhas
	std::pair<int,int> randomOut = possibOuts[dist(R)];

	// Marca a saída como caminho
	_maze[randomOut.first] = 7; _maze[randomOut.second] = 7;

	// Retorna índice da célula de saída do labirinto
	return randomOut.second;
}

// Método que retorna o mapa gerado na forma de uma string padrão de c
//		Saída: string padrão de C do mapa gerado
char* Maze::getMazeMap(){
	return _maze;
}

// Sobrecarga do operador por atribuição
Maze& Maze::operator =(const Maze& maze2){
	
	_mazeX = maze2._mazeX;
	_mazeY = maze2._mazeY;
	delete[] _maze;

	std::copy(_maze, _maze + _mazeX * _mazeY, maze2._maze);
	return *this;
}


/*Função que gera um mapa cheio (com paredes em todas as células)
		Saída: string padrão de C do mapa vazio
		Parâmetros: map_x -> tamanho do mapa em x	
					map_y -> tamanho do mapa em y
*/
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

/*Função que gera um mapa cheio (com paredes em todas as células)
		Saída: string padrão de C do mapa cheio
		Parâmetros: map_x -> tamanho do mapa em x	
					map_y -> tamanho do mapa em y
*/
char* getFilledMap(int map_x, int map_y) {
	char* filledMap = new char[map_x*map_y + 50];
	
	for(int x = 0; x < map_x; x++){

		for(int y = 0; y < map_y; y++){
			
			// Paredes Marrons em todas as células
			filledMap[y*map_x+x] = 1;
			
		}
	}
	return filledMap;
}
