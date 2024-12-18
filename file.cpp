#include "file.h"
#include <algorithm>

// Construtor: salva o nome do arquivo e chama leitura dele
RecordFile::RecordFile(string name) {
    _archieveName = name;
    // Realizar a leitura do arquivo e armazenar no vector
    this->readRecordFile();
}

// Destrutor: desaloca os ponteiros para objetos PlayerInfo do vector e fecha o arquivo, caso ele esteja aberto
RecordFile::~RecordFile() {
    if(!_players.empty()) {
        int numPlayers = _players.size();
        for(int i = 0; i < numPlayers; i++)
            delete _players[i];
    }

    if(_file) _file.close();
}

/* 
Funcão que auxilia a leitura do arquivo das pontuações. Recebe uma linha do arquivo, composta por um nome e uma pontuação
separados por um espaço. Ela separa ambos em duas strings diferentes e retorna um pair.
*/
pair<string,string> divideString(string line) {
    pair<string,string> values;
    values.first = "";
    values.second = "";
    if(!line.empty()) {
        int tam = line.size();
        int pos = 0;
        for(int i = 0; i < tam; i++) {
            if(pos == 0 && line[i] != ' ')
                values.first += line[i];
            else pos = 1;
            if(pos == 1 && line[i] != '\n' && line[i] != ' ')
                values.second += line[i];
        }
    }

    return values;
}

// Realiza a leitura do arquivo de pontuações
void RecordFile::readRecordFile() {
    pair<string,string> values;
    int cont = 0;

    // Abre o arquivo caso não esteja aberto
    if(!_file.is_open()) {
        _file.open(_archieveName, ios::in | ios::out);
        if(!_file.is_open()) {
            cerr << "Falhou na abertura do arquivo " << _archieveName << endl;
            exit(-1);
        }
    }
    
    // Leitura
    string line;
    while(getline(_file, line)) {
        values = divideString(line);    // Separa nome e pontuação
        _players.push_back(new PlayerInfo());
        _players[cont]->setName(values.first);
        _players[cont++]->setScore(values.second);
    }

    _file.close();
}

// Comparação de dois objetos PlayerInfo para verificar a maior pontuação entre eles
bool operator >(const PlayerInfo &a, const PlayerInfo &b) {
    string scoreA = a.getScore();
    string scoreB = b.getScore();
    int sizeA = scoreA.size();
    int sizeB = scoreB.size();

    if(sizeA > sizeB) return true;
    if(sizeB > sizeA) return false;

    // Tamanhos são iguais
    for(int i = 0; i < sizeA; i++) {
        if(scoreA[i] > scoreB[i]) return true;
        if(scoreB[i] > scoreA[i]) return false;
    }

    return false;
}

// Regra para ordenação
bool ruleSort(const PlayerInfo *a, const PlayerInfo *b) {
    return *a > *b;
}

/*
Função para atualizar o arquivo de pontuações devido à finalização da jogada atual. Recebe as informações por
um objeto PlayerInfo, adiciona ele no vector (que contém a as demais pontuações dada a leitura do arquivo), e o ordena.
O vector é, então, escrito no arquivo. 
*/
void RecordFile::updateFile(const PlayerInfo& atual) {
    pair<string,string> values;
    int cont = 0;

    if(!_file.is_open()) {
        _file.open(_archieveName, ios::in | ios::out);
        if(!_file.is_open()) {
            cerr << "Falhou na abertura do arquivo " << _archieveName << endl;
            exit(-1);
        }
    }
    
    // Realiza a leitura para garantir que os dados correspondem aos do arquivo
    if(!_players.empty()) _players.clear();
    this->readRecordFile();

    // Adiciona o atual ao vector
    int tam = _players.size();
    _players.push_back(new PlayerInfo);
    _players[tam]->setName(atual.getName());
    _players[tam]->setScore(atual.getScore());

    // Ordenação
    sort(_players.begin(), _players.end(), ruleSort);

    if(_file) _file.close(); 
    _file.open(_archieveName, ios::out); // Modo de escrita, o conteúdo anterior será apagado

    if (!_file.is_open()) {
        cerr << "Erro ao reabrir o arquivo!" << std::endl;
        exit(-1); 
    }

    // Escrever 10 linhas ou a quantidade existente
    int numData = _players.size();
    int param = min(10,numData);
    for(int i = 0; i < param; ++i) {
        string send = _players[i]->getName() + " " + _players[i]->getScore();
        _file << send << endl;
    }

    _file.close(); // Fechar o arquivo após a escrita
}

/*
Função que retorna o recorde. Neste caso, o primeiro elemento do vector (garantido que estará ordenado).
Caso não haja nada no vector, retorna um objeto PlayerInfo vazio.
*/ 
PlayerInfo RecordFile::getRecord() {
    if(!_players.empty())
        return *_players[0];
    PlayerInfo modelNull;
    modelNull.setName("");
    modelNull.setScore("");
    return modelNull;
}
