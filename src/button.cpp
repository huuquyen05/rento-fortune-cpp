#include "button.h" 

buttonGeneral::buttonGeneral() {}

buttonGeneral::buttonGeneral(int width, int height, int x, int y, sf::Color c) {
    buttonWidth = width;
    buttonHeight = height;
    coorX = x;
    coorY = y;
    backgroundColor = c;
    
    // Set up button position
    button.setSize(sf::Vector2f(buttonWidth, buttonHeight));
    button.setFillColor(backgroundColor);
    button.setPosition(x, y);
}

std::tuple <int, int, int, int> buttonGeneral::getPos() {
    return {coorX, coorX + buttonWidth, coorY, coorY + buttonHeight};
}

bool buttonGeneral::isHovering(int x, int y) {
    return coorX <= x && x <= coorX + buttonWidth && coorY <= y && y <= coorY + buttonHeight; 
}

bool buttonGeneral::isClicked(int x, int y) {
    return (this -> isHovering(x, y)) && (sf::Mouse::isButtonPressed(sf::Mouse::Left));
}

void buttonGeneral::changeColor(sf::Color cNew) {
    button.setFillColor(cNew);
}

void buttonGeneral::draw(sf::RenderWindow* mainWindow) {
    mainWindow -> draw(button);
}

buttonWithText::buttonWithText() {}

// This constructor is for title screen, selection screen etc.
buttonWithText::buttonWithText(int width, int height, int size, std::string label, int x, int y) {

    buttonWidth = width;
    buttonHeight = height;
    buttonLabel = label;
    textSize = size;
    backgroundColor = sf::Color(255, 255, 255, 0);
    defaultTextColor = sf::Color::Black;
    hoverTextColor = sf::Color::Red;
    if(!(textFont.loadFromFile("../fonts/Montserrat-Black.ttf"))) {
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

buttonWithText::buttonWithText(int width, int height, int size, std::string label, int x, int y,sf::Color TextColor) {

    buttonWidth = width;
    buttonHeight = height;
    buttonLabel = label;
    textSize = size;
    backgroundColor = sf::Color(255, 255, 255, 0);
    defaultTextColor = TextColor;
    hoverTextColor = sf::Color::Red;
    if(!(textFont.loadFromFile("../fonts/Montserrat-Black.ttf"))) {
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

// Change text color to hoverTextColor
void buttonWithText::changeColor() {
    buttonText.setFillColor(hoverTextColor);
}

// Change back color
void buttonWithText::returnColor() {
    buttonText.setFillColor(defaultTextColor);
}

// Draw the button
void buttonWithText::draw(sf::RenderWindow* mainWindow) {
    mainWindow -> draw(button);
    buttonText.setFont(textFont);
    mainWindow -> draw(buttonText);
}

void buttonWithText::setText(std::string s) {
    buttonLabel = s;
    // Set up the text for each button
    buttonText.setFont(textFont);  // Set font
    buttonText.setString(buttonLabel);  // Set text
    buttonText.setCharacterSize(textSize);  // Set text size

    // Center the text inside the button
    textRect = buttonText.getLocalBounds();
    buttonText.setOrigin(textRect.left + textRect.width / 2, textRect.top + textRect.height / 2);
    buttonText.setPosition(
        button.getPosition().x + buttonWidth / 2,  // Center horizontally
        button.getPosition().y + buttonHeight / 2  // Center vertically
    );
}

void buttonWithText::setTextColor(sf::Color c) {
    buttonText.setFillColor(c);
}

buttonWithLines::buttonWithLines(){}

buttonWithLines::buttonWithLines(int width, int height, int size, std::vector <std::string> labels, int x, int y) {
    
    buttonWidth = width;
    buttonHeight = height;
    textSize = size;
    backgroundColor = sf::Color(255, 255, 255, 0);
    defaultTextColor = sf::Color::Black;
    hoverTextColor = sf::Color::Red;
    if(!(textFont.loadFromFile("../fonts/Montserrat-Medium.ttf"))) {
        std::cerr << "Error loading font!" << std::endl;
    }
    coorX = x;
    coorY = y;

    // Set up button position
    button.setSize(sf::Vector2f(buttonWidth, buttonHeight));
    button.setFillColor(backgroundColor);
    button.setPosition(x, y);
    button.setOutlineColor(sf::Color::Black);
    button.setOutlineThickness(2);

    std::cout << button.getGlobalBounds().getPosition().y << '\n';

    // Set up the texts
    textLines = labels;

    // Set up textholders
    int s = 0;
    lines.resize((int)(labels.size()));
    for(int i = 0; i < (int)(labels.size()); ++i) {
        lines[i].setFont(textFont);
        lines[i].setString(textLines[i]);
        lines[i].setCharacterSize(textSize);
        lines[i].setFillColor(defaultTextColor);
        s += lines[i].getLocalBounds().height;
    }

    // Center the text inside the button
    int dist = (buttonHeight - s) / ((int)(labels.size()) + 1);
    int tmp = 0;
    for(int i = 0; i < (int)(labels.size()); ++i) {
        textRect = lines[i].getLocalBounds();
        lines[i].setPosition(
            x + (buttonWidth - textRect.getSize().x) / 2,  // Center horizontally
            y + dist * (i + 1) + tmp - lines[i].getGlobalBounds().top
        );
        std::cout << dist * (i + 1) + tmp << " " << tmp << " " << i << '\n';
        std::cout << lines[i].getGlobalBounds().getPosition().y - y - dist * (i + 1) + tmp << '\n';
        tmp += textRect.height;
    }
}

void buttonWithLines::changeColor() {
    for(auto &line: lines) {
        line.setFillColor(hoverTextColor);
    }
}

void buttonWithLines::returnColor() {
    for(auto &line: lines) {
        line.setFillColor(defaultTextColor);
    }
}

void buttonWithLines::draw(sf::RenderWindow* mainWindow) {
    mainWindow -> draw(button);
    for(auto line: lines) {
        mainWindow -> draw(line);
    }
}