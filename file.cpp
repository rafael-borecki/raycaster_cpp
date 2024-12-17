#include "file.h"
#include <algorithm>

RecordFile::RecordFile(string name) {
    _archieveName = name;
    // Realizar a leitura do arquivo e armazenar no vector
    this->readRecordFile();
}

RecordFile::~RecordFile() {
    if(!_players.empty()) {
        int numPlayers = _players.size();
        for(int i = 0; i < numPlayers; i++)
            delete _players[i];
    }

    if(_file) _file.close();
}

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

void RecordFile::readRecordFile() {
    pair<string,string> values;
    int cont = 0;

    if(!_file.is_open()) {
        _file.open(_archieveName, ios::in | ios::out);
        if(!_file.is_open()) {
            cerr << "Falhou na abertura do arquivo " << _archieveName << endl;
            exit(-1);
        }
    }
    
    string line;
    while(getline(_file, line)) {
        values = divideString(line);
        _players.push_back(new PlayerInfo());
        _players[cont]->setName(values.first);
        _players[cont++]->setScore(values.second);
    }

    _file.close();
}

bool operator >(const PlayerInfo &a, const PlayerInfo &b) {
    string scoreA = a.getScore();
    string scoreB = b.getScore();
    int sizeA = scoreA.size();
    int sizeB = scoreB.size();

    if(sizeA > sizeB) return true;
    if(sizeB > sizeA) return false;

    // tamanhos são iguais
    for(int i = sizeA-1; i >= 0; i--) {
        if(int(scoreA[i] - '0') > int(scoreB[i] - '0')) return true;
        if(int(scoreB[i] - '0') > int(scoreA[i] - '0')) return false;
    }

    return false;
}

bool ruleSort(const PlayerInfo *a, const PlayerInfo *b) {
    if(a->getScore() > b->getScore())
        return true;
    else return false;
}

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
    

    if(!_players.empty()) _players.clear();
    this->readRecordFile();
    int tam = _players.size();
    _players.push_back(new PlayerInfo);
    _players[tam]->setName(atual.getName());
    _players[tam]->setScore(atual.getScore());

    for(auto p : _players) {
        cout << p->getName() << " " << p->getScore() << endl;
    }

    sort(_players.begin(), _players.end(), ruleSort);

    if(_file) _file.close(); 
    _file.open(_archieveName, ios::out); // Modo de escrita, o conteúdo anterior será apagado

    if (!_file.is_open()) {
        cerr << "Erro ao reabrir o arquivo!" << std::endl;
        exit(-1); // Erro ao reabrir
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

PlayerInfo RecordFile::getRecord() {
    if(!_players.empty())
        return *_players[0];
    PlayerInfo modelNull;
    modelNull.setName("");
    modelNull.setScore("");
    return modelNull;
}
