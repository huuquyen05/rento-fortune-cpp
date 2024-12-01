#ifndef gameplay_h
#define gameplay_h

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

struct buttonWithText {
    /**
     * A button object with centered text inside
     * Support some functions while hovering, clicking, etc.
     */
    int buttonWidth, buttonHeight, coorX, coorY, textSize;
    std::string buttonLabel;
    sf::RectangleShape button;
    sf::Text buttonText;
    sf::Color backgroundColor;
    sf::Color defaultTextColor;
    sf::Color hoverTextColor;
    sf::Font textFont;
    sf::FloatRect textRect;

    buttonWithText() {}

    // This constructor is for title screen, selection screen etc.
    buttonWithText(int width, int height, int size, std::string label, int x, int y) {

        buttonWidth = width;
        buttonHeight = height;
        buttonLabel = label;
        textSize = size;
        backgroundColor = sf::Color(255, 255, 255, 0);
        defaultTextColor = sf::Color::Black;
        hoverTextColor = sf::Color::Red;
        if(!(textFont.loadFromFile("fonts/Montserrat-Black.ttf"))) {
            std::cerr << "Error loading font!" << std::endl;
        }
        coorX = x;
        coorY = y;

        // Set up button position
        button.setSize(sf::Vector2f(buttonWidth, buttonHeight));
        button.setFillColor(backgroundColor);
        button.setPosition(x, y);

         // Set up the text for each button
        buttonText.setFont(textFont);  // Set font
        buttonText.setString(buttonLabel);  // Set text
        buttonText.setCharacterSize(textSize);  // Set text size
        buttonText.setFillColor(defaultTextColor);  // Text color

        // Center the text inside the button
        textRect = buttonText.getLocalBounds();
        buttonText.setOrigin(textRect.left + textRect.width / 2, textRect.top + textRect.height / 2);
        buttonText.setPosition(
            button.getPosition().x + buttonWidth / 2,  // Center horizontally
            button.getPosition().y + buttonHeight / 2  // Center vertically
        );
    }

    // Return whether or not the mouse is hovering on the button.
    bool isHovering(int x, int y) {
        return button.getGlobalBounds().contains(x, y);
    }

    // Change text color to hoverTextColor
    void changeColor() {
        buttonText.setFillColor(hoverTextColor);
    }

    // Change back color
    void returnColor() {
        buttonText.setFillColor(defaultTextColor);
    }

    // Draw the button
    void draw(sf::RenderWindow* mainWindow) {
        mainWindow -> draw(button);
        buttonText.setFont(textFont);
        mainWindow -> draw(buttonText);
    }
};

class GamePlay {
private:
    sf::RenderWindow* mainWindow;
    sf::Font font;
    sf::Music music;
    sf::Color defaultTextColor = sf::Color::Black;
    sf::Color hoverTextColor = sf::Color::Red;
public:
    GamePlay();
    void renderTitleScreen();
    void renderSelectionScreen();
    void renderSettingScreen();
};

#endif