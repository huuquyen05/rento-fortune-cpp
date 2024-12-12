#ifndef chatbox_h
#define chatbox_h

#include <SFML/Graphics.hpp>
#include <iostream>
#include "button.h"

// A box that can hold text
class TextBox {
protected:
    int boxWidth, boxHeight, coorX, coorY, textSize;
    std::string input;
    sf::RectangleShape box;
    sf::Font font;
    std::vector <sf::Text> lines;
    float padding, lineHeight, maxWidth;
    int maxLines;
    int stLine, enLine;
    bool middleAlign;
public:
    TextBox();
    TextBox(int x, int y, int width, int height);
    void addString(std::string text);
    void updateLines();
    void drawFromTop(sf::RenderWindow* window);
    void drawFromBottom(sf::RenderWindow* window);
    bool isHovering(int x, int y);
    void handleScrolling(float delta, int x, int y);
};  

class inputBox : public TextBox {
private:
    bool isActive;
    int charLimit;
public:
    inputBox();
    inputBox(int x, int y, int width, int height);
    inputBox(int x, int y, int width, int height, int fontSize, bool aligned);
    std::string handleEvent(const sf::Event& event);
};

class chatBox {
private:
    TextBox* textbox;
    inputBox* inputbox;
public:
    chatBox();
    ~chatBox();
    chatBox(int x1, int y1, int width1, int height1, int x2, int y2, int width2, int height2);
    void handleEvent(const sf::Event& event);
    void draw(sf::RenderWindow* window);
};

#endif