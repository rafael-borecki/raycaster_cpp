#pragma once

#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

// Classe para auxiliar o controle da pontuação do jogador
class PlayerInfo {
private:
    string _name;       // Nome 
    string _score;      // Pontuação
public:
    string getName() const { return _name; }
    string getScore() const { return _score; }
    void setName(string name) { _name = name; }
    void setScore(string score) { _score = score; }
    friend bool operator >(const PlayerInfo &a, const PlayerInfo &b);   // Sobrecarga do operador > para comparação da pontuação de dois jogadores
    PlayerInfo() {}
    ~PlayerInfo() {}
};

// Classe para controle do arquivo das 10 maiores pontuações
class RecordFile {
private:
    vector<PlayerInfo*> _players;   // Vector de ponteiros para PlayerInfo: armazena os PlayerInfo contidos no arquivo
    string _archieveName;           // Nome do arquivo com as pontuações e seus respectivos jogadores
    fstream _file;                  // Objeto fstream para manuseio do arquivo
    void readRecordFile();          // Leitura do arquivo de pontuações
public:
    RecordFile(string name);        
    ~RecordFile();
    void updateFile(const PlayerInfo& atual);   // Atualização do arquivo, dada a última jogada
    PlayerInfo getRecord();                     // Retorna o recorde
};

pair<string,string> divideString(string line);  // Auxilia o método de leitura do arquivo