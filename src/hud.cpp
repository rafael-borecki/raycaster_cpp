#include "hud.h"

// Construtor da HUD -> configuração do HUD
HUD::HUD(std::string fontPath, int characterSize, sf::Color color)
{

    // Inicialização do FPS, timer e level
    _fps = 0.f;
    _timer = MAXTIMEOUT;
    _level = 1;

    // Setagem da fontes escolhida para o hud
    font.loadFromFile(fontPath);
    hudFps.setFont(font);
    hudTimer.setFont(font);
    hudLevels.setFont(font);

    // Setagem do tamanho dos caracteres
    hudFps.setCharacterSize(characterSize);
    hudTimer.setCharacterSize(characterSize);
    hudLevels.setCharacterSize(characterSize);

    // Setagem da cor dos caracteres
    hudFps.setFillColor(color);
    hudTimer.setFillColor(color);
    hudLevels.setFillColor(color);

    // Setagem das posições do FPS, timer e level
    hudFps.setPosition(FPS_HUDPOSITION);
    hudTimer.setPosition(TIMER_HUDPOSITION);
    hudLevels.setPosition(LEVEL_HUDPOSITION);
}

// Atualiza o FPS do jogo
void HUD::updateFps(sf::Clock &clock)
{
    _fps = 1.0f / clock.restart().asSeconds();
}

// Atualiza o timer do jogo a cada segundo
void HUD::updateTimer(sf::Clock &clock)
{

    // Atualiza o timer de acordo com a passagem do tempo de jogo em determiando level
    _timer -= clock.getElapsedTime().asSeconds();

    // Se houver menos que 120 segundos pra terminar, muda a cor do timer
    if (_timer <= 120)
        hudTimer.setFillColor(sf::Color::Yellow);

    if (_timer <= 90)
        hudTimer.setFillColor(sf::Color(255, 165, 0)); // Laranja

    if (_timer <= 30)
        hudTimer.setFillColor(sf::Color::Red);
}

// Atualiza o level do jogo
void HUD::updateLevel()
{
    _level++;
}

// Seta o time Out para p level atual de jogo
void HUD::timerOfLevel()
{
    _timer = MAXTIMEOUT / _level + MINTIMEOUT;
}

// Reset do timer
void HUD::resetTimer()
{
    _timer = MAXTIMEOUT;
}

// Reset do level
void HUD::resetLevel()
{
    _level = 1;
}

// Retorna fps do jogo
float HUD::getFps()
{
    return _fps;
}

// Retorna o tempo restante para terminar o nível
float HUD::getTimer()
{
    return _timer;
}

// Retorna o level atual do jogo
int HUD::getLevel()
{
    return _level;
}

// Desenho da HUD na tela do jogo
void HUD::hudDraw(sf::RenderWindow &window, Map map, Raycaster raycast, std::vector<ray> rays, Player player)
{

    // Set do FPS
    hudFps.setString("FPS: " + std::to_string(_fps));
    hudTimer.setString("Time out: " + std::to_string((int)_timer));
    hudLevels.setString("Level: " + std::to_string(_level));

    // Desenha o mapa
    map.drawMap(window);

    // Desenha o jogador
    window.draw(player.playerSprite);

    // Desenha as linhas do raycaster
    raycast.drawLines(window, sf::Vector2f(player.pX, player.pY), rays, sf::Color::Yellow);

    // Desenha o FPS
    window.draw(hudFps);
    window.draw(hudTimer);
    window.draw(hudLevels);
}