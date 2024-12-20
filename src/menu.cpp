#include "menu.h"
#include "file.h"

// Atribuir os valores iniciais para as variáveis e configurar os elementos
void Window::setValues() {       
    sf::VideoMode userVideo = sf::VideoMode::getDesktopMode();  // Pega as dimensões da tela do usuário
    float screenWidth = userVideo.width;                        // Largura da tela do usuário
    float screenHeight = userVideo.height;                      // Altura da tela do usuário
    
    // Multiplicação pelas porcentagens passadas
    unsigned int newWidth = static_cast<unsigned int>(screenWidth * _width);        
    unsigned int newHeight = static_cast<unsigned int>(screenHeight * _height);

    // Criação da janela com as dimensões atualizadas
    _window->create(sf::VideoMode(newWidth, newHeight), _windowName, sf::Style::Titlebar | sf::Style::Close);
    _window->setPosition(sf::Vector2i(0, 0));

    // Carregamento da imagem
    _image->loadFromFile(_archieveImageName);
    _bg->setTexture(*_image);

    // Pega os tamanhos da imagem e da janela
    sf::Vector2u imageSize = _image->getSize(); 
    sf::Vector2u windowSize = _window->getSize(); 

    // Configura a imagem para ter o mesmo tamanho da janela, tornando-a background
    float scaleX = static_cast<float>(windowSize.x) / imageSize.x;
    float scaleY = static_cast<float>(windowSize.y) / imageSize.y;
    _bg->setScale(scaleX, scaleY); 
}

// Construtor: recebe alguns parâmetros e atualiza seus valores. Chama a setValues.
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

// Destrutor: destrói os ponteiros, caso alocados
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

// Desenha a imagem na tela
void Window::drawAll() {
    _window->clear();
    _window->draw(*_bg);

    _window->display();
}

// Desenha a imagem na tela e, em loop, verifica o fechamento
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



// Construtor: recebe alguns parâmetros e atualiza seus valores. Chama a setValues.
RecordWindow::RecordWindow(float height, float width, string archieveImageName, string windowName,string scoreFileName, 
        size_t fontSize, string archiveNameFont) : Window(height, width, archieveImageName, windowName) {
            _scoreFileName = scoreFileName;
            _fontSize = fontSize;
            _archieveFontName = archiveNameFont;

        this->setValues();
}

void RecordWindow::setValues() {       
    sf::VideoMode userVideo = sf::VideoMode::getDesktopMode();  // Pega as dimensões da tela do usuário
    float screenWidth = userVideo.width;                        // Largura da tela do usuário
    float screenHeight = userVideo.height;                      // Altura da tela do usuário
    
    // Multiplicação pelas porcentagens passadas
    unsigned int newWidth = static_cast<unsigned int>(screenWidth * _width);        
    unsigned int newHeight = static_cast<unsigned int>(screenHeight * _height);

    // Criação da janela com as dimensões atualizadas
    _window->create(sf::VideoMode(newWidth, newHeight), _windowName, sf::Style::Titlebar | sf::Style::Close);
    _window->setPosition(sf::Vector2i(0, 0));

    // Carregamento da imagem
    _image->loadFromFile(_archieveImageName);
    _bg->setTexture(*_image);

    // Carregamento da fonte
    _font = new sf::Font;
    _font->loadFromFile(_archieveFontName);

    // Pega os tamanhos da imagem e da janela
    sf::Vector2u imageSize = _image->getSize(); 
    sf::Vector2u windowSize = _window->getSize(); 

    // Configura a imagem para ter o mesmo tamanho da janela, tornando-a background
    float scaleX = static_cast<float>(windowSize.x) / imageSize.x;
    float scaleY = static_cast<float>(windowSize.y) / imageSize.y;
    _bg->setScale(scaleX, scaleY);  

    PlayerInfo record_infos;                // Objeto para armazenar as informações do record
    RecordFile recordFile("./assets/files/records.txt");   // Objeto para manusear o arquivo de record

    // Pega o record e armazena em _score
    record_infos = recordFile.getRecord();
    string _score = record_infos.getName() + " " + record_infos.getScore();

    // Configura o texto
    _text.setFont(*_font);
    _text.setString(_score);
    _text.setOutlineColor(sf::Color::White);
    _text.setCharacterSize(_fontSize);

    // Faz com que o texto sempre esteja localizado no meio horizontalmente, e um pouco abaixo do meio, verticalmente
    float textWidth = _text.getLocalBounds().width;  
    float posX = (windowSize.x - textWidth) / 2.0f; 
    float textHeight = _text.getLocalBounds().height;  
    float posY = (windowSize.y - textHeight) / 1.5f;  
    _text.setPosition(posX, posY);
}

// Desenha o texto e a imagem
void RecordWindow::drawAll() {
    _window->clear();
    _window->draw(*_bg);
    _window->draw(_text);
    
    _window->display();
}

// Destrutor: desaloca todos os ponteiros alocados
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

// Executa a janela: desenha e espera o fechamento
void RecordWindow::runWindow() {
    drawAll();
    while(_window->isOpen()) {
        sf::Event event;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
	  _window->close();
	}
	while (_window->pollEvent(event)) {
	  if (event.type == sf::Event::Closed) {
	    _window->close();
	  }
	}
    }
}



// Construtor: recebe alguns parâmetros e atualiza seus valores. Chama a setValues.
MenuWindow::MenuWindow(float height, float width, string archieveImageName, string windowName, string archiveNameFont, 
    vector<string>& texts, vector<sf::Vector2f> &cordinates, vector<size_t> &fontSizes) : Window(height, width, archieveImageName, windowName) {
  _position = 0;
  _pressed = false;
  _selected = false;

  _archieveFontName = archiveNameFont;

  // Preenche os vectors com os dados
  int numTexts = texts.size();    // Mesmo tamanho das coordenadas e tamanho das fontes
  _texts.resize(numTexts);
  for(int i = 0; i < numTexts; i++) {
    _options.push_back(texts[i]);
    _cordinates.push_back({cordinates[i].x*_width, cordinates[i].y*_height});
    _fontSizes.push_back(fontSizes[i]);
  }

  this->setValues();
}

// Destrutor: desaloca todos os ponteiros alocados
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
  sf::VideoMode userVideo = sf::VideoMode::getDesktopMode();  // Pega as dimensões da tela do usuário
  float screenWidth = userVideo.width;                        // Largura da tela do usuário
  float screenHeight = userVideo.height;                      // Altura da tela do usuário

  // Multiplicação pelas porcentagens passadas
  unsigned int newWidth = static_cast<unsigned int>(screenWidth * _width);        
  unsigned int newHeight = static_cast<unsigned int>(screenHeight * _height);

  // Criação da janela com as dimensões atualizadas
  _window->create(sf::VideoMode(newWidth, newHeight), _windowName, sf::Style::Titlebar | sf::Style::Close);
  _window->setPosition(sf::Vector2i(0, 0));

  // Carregamento da imagem
  _image->loadFromFile(_archieveImageName);
  _bg->setTexture(*_image);

  // Carregamento da fonte
  _font = new sf::Font;
  _font->loadFromFile(_archieveFontName);

  // Pega os tamanhos da imagem e da janela
  sf::Vector2u imageSize = _image->getSize(); 
  sf::Vector2u windowSize = _window->getSize(); 

  // Configura a imagem para ter o mesmo tamanho da janela, tornando-a background
  float scaleX = static_cast<float>(windowSize.x) / imageSize.x;
  float scaleY = static_cast<float>(windowSize.y) / imageSize.y;
  _bg->setScale(scaleX, scaleY);  

  // Acerta as configurações dos textos
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

// Configura e capta os eventos
void MenuWindow::loopEvents(int numTexts) {
  sf::Event event;
  while(_window->pollEvent(event)) {
    // Fechamento
    if(event.type == sf::Event::Closed) {
      _window->close();
    }

    // Seta para baixo
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

    // Seta para cima
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

    // Enter: seleção da opção
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && !_selected) {
      _selected = true;

      // Exit
      if(_position == 3) {
	_window->close();
	exit(0);
      }

      // Seleção do About
      if(_position == 2) {
	// Roda a janela do about
	Window *about = new Window(0.7,0.4,"./assets/images/_about.png","About"); 
	about->runWindow();
	delete about;
      }
      // Seleção do Record
      if(_position == 1) {
	// Roda a janela do Record
	Window *record = new RecordWindow(0.15, 0.3, "./assets/images/record.png", "Record","qlqcoisa", 30, "./assets/fonts/GAMERIA.ttf");
	record->runWindow();
	delete record;
      }
      // Play
      if(_position == 0)  _window->close();  // Será executada uma nova janela
    }

  }
}

// Desenha a imagem e os textos
void MenuWindow::drawAll() {
  _window->clear();
  _window->draw(*_bg);
  for(auto t : _texts) {
    _window->draw(t);
  }

  _window->display();
}

// Executa a janela: agora, dada a existência de eventos, a janela é continuamente atualizada
void MenuWindow::runWindow() {
  int numTexts = _options.size();
  while(_window->isOpen()) {
    loopEvents(numTexts);
    drawAll();
  } 
}

// Função para concatenar o fluxo necessário para criação do menu do jogo.
Window *createMenu() {
  vector<string> texts = {"Play", "Record", "About", "Exit"};
  vector<sf::Vector2f> cordinates = {{935,570},{935,620},{935,670},{935,720}};
  vector<size_t> fontSizes = {33,33,33,33};

  // Polimorfismo
  Window *about = new MenuWindow(1,1,"./assets/images/background.png","Game","./assets/fonts/GAMERIA.ttf", texts, cordinates, fontSizes);

  return about;
}
