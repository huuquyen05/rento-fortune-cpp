#ifndef button_h
#define button_h

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

class buttonGeneral {
protected:
    int buttonWidth, buttonHeight, coorX, coorY, outlineThickness;
    sf::RectangleShape button;
    sf::Color backgroundColor;
    sf::Color outlineColor;
public:
    buttonGeneral();
    buttonGeneral(int width, int height, int x, int y, sf::Color c);
    bool isHovering(int x, int y);
    bool isClicked(int x, int y);
    virtual void changeColor(sf::Color cNew);
    virtual void draw(sf::RenderWindow* mainWindow);
};

class buttonWithText : public buttonGeneral {
private:
    int textSize;
    std::string buttonLabel;
    sf::Text buttonText;
    sf::Color defaultTextColor;
    sf::Color hoverTextColor;
    sf::Font textFont;
    sf::FloatRect textRect;
public:
    buttonWithText();
    buttonWithText(int width, int height, int size, std::string label, int x, int y);
    buttonWithText(int width, int height, int size, std::string label, int x, int y,sf::Color TextColor);
    void changeColor();
    void returnColor();
    void draw(sf::RenderWindow* mainWindow);
};

class menu {
private:
    int numChoices, coorX, coorY;
    buttonWithText config; // this will contain the config of the button, such as width, height, etc.
    std::vector <buttonWithText> choices;
public:
    menu();
    menu(int num, int x, int y, buttonWithText tmp); // tmp is the button containing some configuration.
    void handleEvent(const sf::Event& event);
    void draw(sf::RenderWindow* window);
};

#endif