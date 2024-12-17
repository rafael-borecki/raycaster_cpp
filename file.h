#pragma once

#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

class PlayerInfo {
private:
    string _name;
    string _score;
public:
    string getName() const { return _name; }
    string getScore() const { return _score; }
    void setName(string name) { _name = name; }
    void setScore(string score) { _score = score; }
    friend bool operator >(const PlayerInfo &a, const PlayerInfo &b);
    PlayerInfo() {}
    ~PlayerInfo() {}
};

class RecordFile {
private:
    vector<PlayerInfo*> _players;
    string _archieveName;
    fstream _file;
    void readRecordFile();
public:
    RecordFile(string name);
    ~RecordFile();
    void updateFile(const PlayerInfo& atual);
    PlayerInfo getRecord();
};

pair<string,string> divideString(string line);