#ifndef gameplay_h
#define gameplay_h

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "button.h"
#include <vector>
#include "chatbox.h"
#include "game.h"
#include "property.h"
#include "slot.h"
#include <string>
#include <sstream>
#include <unistd.h>

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
    void renderGameScreen(std::string names[4]);
    void setTokenPosition(int index, sf::CircleShape &c,buttonWithText &curSlot);
    void updatePosition(int curPos[], Game &game);
};

#endif