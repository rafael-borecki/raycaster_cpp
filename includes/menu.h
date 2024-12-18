#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;

// Classe base para criação de uma janela
class Window {
protected:
    float _height, _width;      // Em porcentagem (0 a 1): sobre a tela do usuário
    string _windowName;         // Nome da janela
    string _archieveImageName;  // Nome do arquivo da imagem (background)
    sf::RenderWindow *_window;  // Ponteiro para objeto da classe RenderWindow
    sf::Texture *_image;        // Ponteiro para objeto da classe Texture
    sf::Sprite *_bg;            // Ponteiro para objeto da classe Sprite
    virtual void drawAll();     // Função para desenhar os objetos SFML na tela
    virtual void setValues();   // Atribuir os valores iniciais para as variáveis e configurar os elementos
public:
    Window(float height, float width, string archieveImageName, string windowName); 
    virtual ~Window();
    void loadImage(string archieveName);    // Configura a imagem
    virtual void runWindow();               // Função para executar a janela
};

// Herda de Window e adiciona os atributos e métodos necessários para a janela do Menu
class MenuWindow : public Window {
private:
    int _position;                      // Posição de seleção
    bool _pressed;                      // Se há alguma das opções marcadas
    bool _selected;                     // Se alguma opção foi selecionada (enter)
    string _archieveFontName;           // Nome do arquivo de fonte
    sf::Font *_font;                    // Ponteiro para objeto Font
    vector<string> _options;            // Vector para armazenar todos os textos inclusos na tela
    vector<sf::Vector2f> _cordinates;   // Coordenadas dos textos
    vector<sf::Text> _texts;            // Textos em formato Text
    vector<size_t> _fontSizes;          // Tamanho dos textos (fontes)
protected:
    void setValues() override;          // Sobrepõe a setValues de Window
    void loopEvents(int numTexts);      // Controla os eventos da janela, como seleção da opção
    void drawAll() override;            // Sobrepõe a drawAll de Window
public:
    MenuWindow(float height, float width, string archieveImageName, string windowName, 
        string archiveNameFont, vector<string> &texts, vector<sf::Vector2f> &cordinates, vector<size_t> &fontSizes);
    ~MenuWindow();
    void runWindow() override;          // Sobrepõe a runWindow de Window
};

// Herda de Window e adiciona os atributos e métodos necessários para a janela do Record
class RecordWindow : public Window {
private:
    sf::Font *_font;            // Ponteiro para objeto Font
    string _archieveFontName;   // Nome do arquivo da fonte
    string _scoreFileName;      // Nome do arquivo de pontuações
    string _score;              // Pontuação a ser mostrada
    sf::Text _text;             // Texto em formato Text
    size_t _fontSize;           // Tamanho dos textos (fontes)
protected:
    void setValues() override;  // Sobrepõe a setValues de Window
    void loopEvents();          // Controla os eventos da janela
    void drawAll() override;    // Sobrepõe a drawAll de Window
public:
    RecordWindow(float height, float width, string archieveImageName, string windowName, string scoreFileName,
        size_t fontSize, string archiveNameFont);
    ~RecordWindow();
    void runWindow() override;  // Sobrepõe a runWindow de Window
};

Window *createMenu();       // Função para facilitar a criação do menu na main
