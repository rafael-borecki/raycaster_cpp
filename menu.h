#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;

class Window {
protected:
    float _height, _width;      // em porcentagem -> sobre a tela
    string _windowName;
    string _archieveImageName;
    sf::RenderWindow *_window;
    sf::Texture *_image;
    sf::Sprite *_bg;
    virtual void drawAll();
    virtual void setValues();
public:
    Window(float height, float width, string archieveImageName, string windowName);
    virtual ~Window();
    void loadImage(string archieveName);
    virtual void runWindow();
};

class MenuWindow : public Window {
private:
    int _position;
    bool _pressed;
    bool _selected;
    string _archieveFontName;
    sf::Font *_font;
    vector<string> _options;
    vector<sf::Vector2f> _cordinates;
    vector<sf::Text> _texts;
    vector<size_t> _fontSizes;
protected:
    void setValues() override;
    void loopEvents(int numTexts);
    void drawAll() override;
public:
    MenuWindow(float height, float width, string archieveImageName, string windowName, 
        string archiveNameFont, vector<string> &texts, vector<sf::Vector2f> &cordinates, vector<size_t> &fontSizes);
    ~MenuWindow();
    void runWindow() override;
};

class RecordWindow : public Window {
private:
    sf::Font *_font;
    string _archieveFontName;
    string _scoreFileName;
    string _score;
    sf::Text _text;
    size_t _fontSize;
protected:
    void setValues() override;
    void loopEvents();
    void drawAll() override;
public:
    RecordWindow(float height, float width, string archieveImageName, string windowName, string scoreFileName,
        size_t fontSize, string archiveNameFont);
    ~RecordWindow();
    void runWindow() override;
};

MenuWindow *createMenu();
