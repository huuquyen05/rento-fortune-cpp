#ifndef gameplay_h
#define gameplay_h

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "button.h"

class GamePlay {
private:
    sf::RenderWindow* mainWindow;
    sf::Font font;
    sf::Music music;
    sf::Color defaultTextColor = sf::Color::Black;
    sf::Color hoverTextColor = sf::Color::Red;
    sf::Color playerColor[4] = {sf::Color::Red, sf::Color::Green, sf::Color::Blue, sf::Color(242, 107, 15)};
public:
    GamePlay();
    void renderTitleScreen();
    void renderSelectionScreen();
    void renderSettingScreen();
};

#endif