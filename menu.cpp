#include "menu.h"
#include "file.h"

void Window::setValues() {       
    sf::VideoMode userVideo = sf::VideoMode::getDesktopMode();
    float screenWidth = userVideo.width;   
    float screenHeight = userVideo.height; 
    unsigned int newWidth = static_cast<unsigned int>(screenWidth * _width);
    unsigned int newHeight = static_cast<unsigned int>(screenHeight * _height);

    _window->create(sf::VideoMode(newWidth, newHeight), _windowName, sf::Style::Titlebar | sf::Style::Close);
    _window->setPosition(sf::Vector2i(0, 0));

    _image->loadFromFile(_archieveImageName);
    _bg->setTexture(*_image);

    sf::Vector2u imageSize = _image->getSize(); 
    sf::Vector2u windowSize = _window->getSize(); 

    float scaleX = static_cast<float>(windowSize.x) / imageSize.x;
    float scaleY = static_cast<float>(windowSize.y) / imageSize.y;

    _bg->setScale(scaleX, scaleY); 
}

Window::Window(float height, float width, string archieveImageName, string windowName) {
    _image = new sf::Texture;
    _bg = new sf::Sprite;
    _window = new sf::RenderWindow();
    
    _height = height;
    _width = width;
    _windowName = windowName;
    _archieveImageName = archieveImageName;

    this->setValues();
}

Window::~Window() {
    if(_image) {
        delete _image;
        _image = nullptr;
    }
    if(_bg) {
        delete _bg;
        _bg = nullptr;
    }
    if(_window) {
        delete _window;
        _window = nullptr;
    }
}

void Window::drawAll() {
    _window->clear();
    _window->draw(*_bg);

    _window->display();
}

void Window::runWindow() {
    drawAll();
    while(_window->isOpen()) {
        sf::Event event;
        while (_window->pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                _window->close();
            }
        }
    }
}

// -----------------------------

RecordWindow::RecordWindow(float height, float width, string archieveImageName, string windowName,string scoreFileName, 
        size_t fontSize, string archiveNameFont) : Window(height, width, archieveImageName, windowName) {
            _scoreFileName = scoreFileName;
            _fontSize = fontSize;
            _archieveFontName = archiveNameFont;

        this->setValues();
}

void RecordWindow::setValues() {       
    sf::VideoMode userVideo = sf::VideoMode::getDesktopMode();
    float screenWidth = userVideo.width;   
    float screenHeight = userVideo.height; 
    unsigned int newWidth = static_cast<unsigned int>(screenWidth * _width);
    unsigned int newHeight = static_cast<unsigned int>(screenHeight * _height);

    _window->create(sf::VideoMode(newWidth, newHeight), _windowName, sf::Style::Titlebar | sf::Style::Close);
    _window->setPosition(sf::Vector2i(0, 0));

    _font = new sf::Font;
    _font->loadFromFile(_archieveFontName);

    _image->loadFromFile(_archieveImageName);
    _bg->setTexture(*_image);

    sf::Vector2u imageSize = _image->getSize(); 
    sf::Vector2u windowSize = _window->getSize(); 

    float scaleX = static_cast<float>(windowSize.x) / imageSize.x;
    float scaleY = static_cast<float>(windowSize.y) / imageSize.y;

    _bg->setScale(scaleX, scaleY); 

    PlayerInfo record_infos;
    RecordFile recordFile("records.txt");
    record_infos = recordFile.getRecord();
    string _score = record_infos.getName() + " " + record_infos.getScore();
    _text.setFont(*_font);
    _text.setString(_score);
    _text.setOutlineColor(sf::Color::White);
    _text.setCharacterSize(_fontSize);

    float textWidth = _text.getLocalBounds().width;  
    float posX = (windowSize.x - textWidth) / 2.0f; 
    float textHeight = _text.getLocalBounds().height;  
    float posY = (windowSize.y - textHeight) / 1.5f;  

    _text.setPosition(posX, posY);
}

void RecordWindow::drawAll() {
    _window->clear();
    _window->draw(*_bg);
    _window->draw(_text);
    
    _window->display();
}

RecordWindow::~RecordWindow() {
    if(_image) {
        delete _image;
        _image = nullptr;
    }
    if(_bg) {
        delete _bg;
        _bg = nullptr;
    }
    if(_window) {
        delete _window;
        _window = nullptr;
    }
    if(_font) {
        delete _font;
        _font = nullptr;
    }
}

void RecordWindow::runWindow() {
    drawAll();
    while(_window->isOpen()) {
        sf::Event event;
        while (_window->pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                _window->close();
            }
        }
    }
}


// ------------------------------

MenuWindow::MenuWindow(float height, float width, string archieveImageName, string windowName, string archiveNameFont, 
    vector<string>& texts, vector<sf::Vector2f> &cordinates, vector<size_t> &fontSizes) : Window(height, width, archieveImageName, windowName) {
        _position = 0;
        _pressed = false;
        _selected = false;
        
        _archieveFontName = archiveNameFont;
        
        int numTexts = texts.size();
        _texts.resize(numTexts);
        for(int i = 0; i < numTexts; i++) {
            _options.push_back(texts[i]);
            _cordinates.push_back({cordinates[i].x*_width, cordinates[i].y*_height});
            _fontSizes.push_back(fontSizes[i]);
        }

        this->setValues();
}

MenuWindow::~MenuWindow() {
    if(_image) {
        delete _image;
        _image = nullptr;
    }
    if(_bg) {
        delete _bg;
        _bg = nullptr;
    }
    if(_window) {
        delete _window;
        _window = nullptr;
    }
}

void MenuWindow::setValues() {       
    sf::VideoMode userVideo = sf::VideoMode::getDesktopMode();
    float screenWidth = userVideo.width;   
    float screenHeight = userVideo.height; 
    unsigned int newWidth = static_cast<unsigned int>(screenWidth * _width);
    unsigned int newHeight = static_cast<unsigned int>(screenHeight * _height);

    _window->create(sf::VideoMode(newWidth, newHeight), _windowName, sf::Style::Titlebar | sf::Style::Close);
    _window->setPosition(sf::Vector2i(0, 0));

    _font = new sf::Font;
    _font->loadFromFile(_archieveFontName);

    _image->loadFromFile(_archieveImageName);
    _bg->setTexture(*_image);

    sf::Vector2u imageSize = _image->getSize(); 
    sf::Vector2u windowSize = _window->getSize(); 

    float scaleX = static_cast<float>(windowSize.x) / imageSize.x;
    float scaleY = static_cast<float>(windowSize.y) / imageSize.y;

    _bg->setScale(scaleX, scaleY); 

    int numTexts = _options.size();
    for(int i = 0; i < numTexts; i++) {
        _texts[i].setFont(*_font);
        _texts[i].setString(_options[i]);
        _texts[i].setOutlineColor(sf::Color::White);
        _texts[i].setCharacterSize(_fontSizes[i]);

        // Centralizar horizontalmente
        float textWidth = _texts[i].getLocalBounds().width;
        float centerX = (windowSize.x - textWidth) / 2.0f;
        float centerY = windowSize.y / 2.0f + (i*50) + 40;

        _texts[i].setPosition(centerX, centerY);
    }
}

void MenuWindow::loopEvents(int numTexts) {
    sf::Event event;
    while(_window->pollEvent(event)) {
        if(event.type == sf::Event::Closed) {
            _window->close();
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !_pressed) {
            if(_position < numTexts-1) {
                _position++;
                _pressed = true;
                _texts[_position].setOutlineColor(sf::Color::Black);
                _texts[_position].setOutlineThickness(7);
                _texts[_position-1].setOutlineThickness(0);
                _pressed = false;
            } else {
                _position = 0;
                _pressed = true;
                _texts[_position].setOutlineColor(sf::Color::Black);
                _texts[_position].setOutlineThickness(7);
                _texts[numTexts-1].setOutlineThickness(0);
                _pressed = false;
            }
            _selected = false;
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !_pressed) {
            if(_position > 0) {
                _position--;
                _pressed = true;
                _texts[_position].setOutlineColor(sf::Color::Black);
                _texts[_position].setOutlineThickness(7);
                _texts[_position+1].setOutlineThickness(0);
                _pressed = false;
            } else {
                _position = numTexts-1;
                _pressed = true;
                _texts[_position].setOutlineColor(sf::Color::Black);
                _texts[_position].setOutlineThickness(7);
                _texts[0].setOutlineThickness(0);
                _pressed = false;
            }
            _selected = false;
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && !_selected) {
            _selected = true;
            if(_position == 3) {
                _window->close();
                exit(0);
            }
            if(_position == 2) {
                Window *about = new Window(0.7,0.4,"images/_about.png","About"); 
                about->runWindow();
                delete about;
            }
            if(_position == 1) {
                Window *record = new RecordWindow(0.15, 0.3, "images/record.png", "Record","qlqcoisa", 30, "fonts/GAMERIA.ttf");
                record->runWindow();
                delete record;
            }
            if(_position == 0)  _window->close();
        }
    }
}

void MenuWindow::drawAll() {
    _window->clear();
    _window->draw(*_bg);
    for(auto t : _texts) {
        _window->draw(t);
    }

    _window->display();
}

void MenuWindow::runWindow() {
    int numTexts = _options.size();
    while(_window->isOpen()) {
        loopEvents(numTexts);
        drawAll();
    }   
}

MenuWindow *createMenu() {
    vector<string> texts = {"Play", "Record", "About", "Exit"};
    vector<sf::Vector2f> cordinates = {{935,570},{935,620},{935,670},{935,720}};
    vector<size_t> fontSizes = {33,33,33,33};
    MenuWindow *about = new MenuWindow(1,1,"images/background.png","Game","fonts/GAMERIA.ttf", texts, cordinates, fontSizes);

    return about;
}