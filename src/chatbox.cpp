#include "chatbox.h"

TextBox::TextBox() {}

TextBox::TextBox(int x, int y, int width, int height)
        : textSize(15), input(""), padding(3.f), maxWidth(width - 2 * padding) {
    // Load font
    std::string fontPath = "../fonts/Montserrat-Light.ttf";
    if (!font.loadFromFile(fontPath)) {
        throw std::runtime_error("Unable to load font");
    }

    // Configure box
    boxHeight = height;
    boxWidth = width;
    coorX = x;
    coorY = y;
    box.setPosition(x, y);
    box.setSize({ width, height });
    box.setFillColor(sf::Color::White);
    box.setOutlineColor(sf::Color::Black);
    box.setOutlineThickness(2);

    // Configure initial text line
    sf::Text text;
    text.setFont(font);
    text.setPosition(x + padding, y + padding);
    text.setCharacterSize(textSize);
    text.setFillColor(sf::Color::Black);
    lines.push_back(text);

    lineHeight = text.getCharacterSize() + padding; // Set line height with padding
}

void TextBox::addString(std::string s) {
    if(input != "") input.push_back('\n');
    for(char x: s)
        input.push_back(x);
    this -> updateLines();
}

void TextBox::updateLines() {
    lines.clear();
    sf::Text line;
    line.setFont(font);
    line.setCharacterSize(textSize);
    line.setFillColor(sf::Color::Black);

    std::string currentLine = "";
    float currentLineWidth = 0;

    for (char c : input) {
        // Temporarily add character to line to measure its width
        currentLine += c;
        line.setString(currentLine);
        currentLineWidth = line.getLocalBounds().width;

        if (currentLineWidth > maxWidth || c == '\n') {
            // Line exceeds max width or last character is a newline, finalize current line and start a new one
            currentLine.pop_back(); // Remove last character
            line.setString(currentLine);

            // Start a new line with the last character
            if(c != '\n') currentLine = c;
            else currentLine = "";
            line.setPosition(coorX + padding, 
                             coorY + padding + lines.size() * lineHeight);
            lines.push_back(line);
        }
    }

    // Add the last line
    line.setString(currentLine);
    line.setPosition(coorX + padding, 
                     coorY + lines.size() * lineHeight);
    lines.push_back(line);
}

void TextBox::drawFromTop(sf::RenderWindow* window) {
    window -> draw(box);
    for (const auto& line : lines) {
        window -> draw(line);
    }
}

void TextBox::drawFromBottom(sf::RenderWindow* window) {
    window -> draw(box);
    for(int i = lines.size() - 1; i >= 0; --i) {
        sf::Text tmp = lines[i];
        tmp.setPosition(coorX + padding,
                        coorY + boxHeight - padding - (lines.size() - i) * lineHeight);
        window -> draw(tmp);
    }
}

inputBox::inputBox(int x, int y, int width, int height) {
    // Init some variables
    textSize = 15;
    input = "";
    padding = 3.f;
    maxWidth = width - 2 * padding;
    isActive = 0;

    // Load font
    std::string fontPath = "../fonts/Montserrat-Light.ttf";
    if (!font.loadFromFile(fontPath)) {
        throw std::runtime_error("Unable to load font");
    }

    // Configure box
    boxHeight = height;
    boxWidth = width;
    coorX = x;
    coorY = y;
    box.setPosition(x, y);
    box.setSize({ width, height });
    box.setFillColor(sf::Color::White);
    box.setOutlineColor(sf::Color::Black);
    box.setOutlineThickness(1);

    // Configure initial text line
    sf::Text text;
    text.setFont(font);
    text.setPosition(x + padding, y + padding);
    text.setCharacterSize(textSize);
    text.setFillColor(sf::Color::Black);
    lines.push_back(text);

    lineHeight = text.getCharacterSize() + padding; // Set line height with padding
}

std::string inputBox::handleEvent(const sf::Event& event) {
    if (event.type == sf::Event::MouseButtonPressed) {
        // Check if the textbox is clicked
        sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
        isActive = box.getGlobalBounds().contains(mousePos);
    }

    // Update outline thickness based on focus
    box.setOutlineThickness(isActive ? 2 : 1);

    // Handle text input
    if (isActive && event.type == sf::Event::TextEntered) {
        if (event.text.unicode == '\b') { // Handle backspace
            if (!input.empty()) {
                input.pop_back();
                updateLines();
            }
        } else if (event.text.unicode < 128) { // Handle ASCII characters
            input += static_cast<char>(event.text.unicode);
            updateLines();
        }
    }

    // Handle Enter key for submitting the input
    if (isActive && event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
        std::string tmp = input;
        input.clear(); // Clear the input after submission
        updateLines();
        return tmp; // Return the submitted text
    }

    return "";
}


chatBox::chatBox(){}

chatBox::chatBox(int x1, int y1, int width1, int height1, int x2, int y2, int width2, int height2) {
    textbox = new TextBox(x1, y1, width1, height1);
    inputbox = new inputBox(x2, y2, width2, height2);
}

chatBox::~chatBox() {
    delete textbox;
    delete inputbox;
}

void chatBox::handleEvent(const sf::Event& event) {
    std::string tmp = inputbox -> handleEvent(event);
    if(tmp == "") return;
    this -> textbox -> addString("User: " + tmp);
}

void chatBox::draw(sf::RenderWindow* window) {
    this -> textbox -> drawFromBottom(window);
    this -> inputbox -> drawFromTop(window);
}