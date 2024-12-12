#include "gameplay.h"
#include "chatbox.h"

GamePlay::GamePlay() {
    if(!(this -> font).loadFromFile("../fonts/Montserrat-Black.ttf")) {
        std::cerr << "Error loading font!" << std::endl;
    }
    if(!(this -> music).openFromFile("../assets/bgm.wav")) {
        std::cerr << "Error loading bgm!" << std::endl;
    }
    this -> mainWindow = new sf::RenderWindow(sf::VideoMode::getDesktopMode(), "Main Window", sf::Style::Fullscreen);
    this -> mainWindow->setFramerateLimit(60);
    this -> music.play();
    this -> music.setLoop(true);
}

void GamePlay::renderTitleScreen() {

    // Video mode and fullscreen setup
    sf::VideoMode fullscreenMode = sf::VideoMode::getDesktopMode();
    
    // Create title screen background
    sf::RectangleShape titleScreen(sf::Vector2f(fullscreenMode.width, fullscreenMode.height));
    sf::Texture titleScreenTexture;
    titleScreenTexture.loadFromFile("../assets/title-screen.png");
    titleScreen.setTexture(&titleScreenTexture);

    // Define button size and positions
    int buttonWidth = 300, buttonHeight = 80;
    int buttonSpacing = 30;
    std::string buttonLabels[4] = {"Load Game", "New Game", "Settings", "Quit"};
    buttonWithText button[4];

    // Setup buttons and texts
    for (int i = 0; i < 4; ++i) {
        button[i] = buttonWithText(
            buttonWidth, 
            buttonHeight, 
            40, 
            buttonLabels[i], 
            (fullscreenMode.width - buttonWidth) / 2,
            (fullscreenMode.height - (buttonHeight * 3 + buttonSpacing * 2)) / 3 * 2 + (buttonHeight + buttonSpacing) * i
        );
    }
    std::cout << "OK title\n";

    // Main event and rendering loop for the title screen
    while (this -> mainWindow -> isOpen()) {
        sf::Event event;
        while (this -> mainWindow -> pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                this -> mainWindow -> close();
                exit(0);
            }
            else if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape) {
                    this -> mainWindow -> close();
                    exit(0);  // Exit the function if the escape key is pressed
                }
            }
        }

        // Mouse interaction detection (hover and click)
        sf::Vector2i mousePos = sf::Mouse::getPosition(*(this -> mainWindow));

        for (int i = 0; i < 4; ++i) {
            if (button[i].isHovering(mousePos.x, mousePos.y)) {
                button[i].changeColor();  // Change text color on hover

                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                    // Handle button click
                    if(i == 0) {
                        std::cout << "Load Game Button Clicked!" << std::endl;
                        // do random shit
                    }
                    else if (i == 1) {
                        std::cout << "New Game Button Clicked!" << std::endl;
                        this -> renderSelectionScreen();
                    }
                    else if (i == 2) {
                        std::cout << "Settings Button Clicked!" << std::endl;
                        this -> renderSettingScreen();
                    }
                    else if (i == 3) {
                        std::cout << "Quit Button Clicked!" << std::endl;
                        this -> mainWindow -> close();  // Close the window on "Quit" button click
                        exit(0);  // Exit the function after quitting
                    }
                }
            }
            else {
                button[i].returnColor();  // Reset text color when not hovered
            }
        }

        this -> mainWindow -> clear(sf::Color::Black);

        // Draw the title screen background
        this -> mainWindow -> draw(titleScreen);

        // Draw the buttons and their texts
        for (int i = 0; i < 4; ++i) {
            button[i].draw(this -> mainWindow);  // Draw the button
        }

        this -> mainWindow -> display();
    }
}

void GamePlay::renderSelectionScreen() {

    // Video mode and fullscreen setup
    sf::VideoMode fullscreenMode = sf::VideoMode::getDesktopMode();
    
    // Create selection screen background
    sf::RectangleShape selectionScreen(sf::Vector2f(fullscreenMode.width, fullscreenMode.height));
    sf::Texture selectionScreenTexture;
    selectionScreenTexture.loadFromFile("../assets/background.png");
    selectionScreen.setTexture(&selectionScreenTexture);

    int buttonWidth = 300, buttonHeight = 100;
    buttonWithText title = buttonWithText(
        buttonWidth,
        buttonHeight,
        50,
        "Selection Phase",
        (fullscreenMode.width - buttonWidth) / 2,
        fullscreenMode.height * 5 / 100
    );  

    int recWidth = 400, recHeight = 500;
    float spaceBetween = (fullscreenMode.width - 4 * recWidth) / 5.0f;

    sf::RectangleShape rect[4];
    for(int i = 0; i < 4; ++i) {
        rect[i].setPosition(spaceBetween * (i + 1) + i * recWidth, (fullscreenMode.height - recHeight) / 2.5f);
        rect[i].setFillColor(sf::Color(255, 255, 255, 100));
        rect[i].setSize(sf::Vector2f(recWidth, recHeight));
    }

    sf::RectangleShape avatar[4];
    int avtSize = 150;
    for(int i = 0; i < 4; ++i) {
        avatar[i].setPosition(rect[i].getPosition().x + (recWidth - avtSize) / 2, rect[i].getPosition().y + 50);
        avatar[i].setFillColor(playerColor[i]);
        avatar[i].setSize(sf::Vector2f(avtSize, avtSize));
        avatar[i].setOutlineColor(sf::Color::Black);
        avatar[i].setOutlineThickness(5);
    }

    buttonWithText enterName[4];

    inputBox nameHolder[4];
    int nameHeight = 40, nameWidth = 200;
    for(int i = 0; i < 4; ++i) {
        sf::Vector2f pos = rect[i].getPosition();
        nameHolder[i] = inputBox(pos.x + (recWidth - nameWidth) / 2, pos.y + recHeight - 100, nameWidth, nameHeight, nameHeight - 10, 1);
        enterName[i] = buttonWithText(
            400,
            200,
            20,
            "Enter your name:",
            pos.x + (recWidth - 400) / 2, 
            pos.y + recHeight - 250
        );
    } 

    std::string name[4];

    std::cout << "OK selection\n";

    // Main event and rendering loop for the title screen
    while (this -> mainWindow -> isOpen()) {
        sf::Event event;
        while (this -> mainWindow -> pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                this -> mainWindow -> close();
                exit(0);
            }
            else if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape) {
                    this -> mainWindow -> close();
                    exit(0);  // Exit the function if the escape key is pressed
                }
            }
            for(int i = 0; i < 4; ++i) {
                std::string tmp = nameHolder[i].handleEvent(event);
                if(tmp != "") {
                    name[i] = tmp;
                    std::cout << i << " " << name[i] << std::endl;
                }
            }
        }

        this -> mainWindow -> clear(sf::Color::Black);

        // Draw the title screen background
        this -> mainWindow -> draw(selectionScreen);

        for (int i = 0; i < 4; ++i) {
            this -> mainWindow -> draw(rect[i]);
            this -> mainWindow -> draw(avatar[i]);
            nameHolder[i].drawFromTop(this -> mainWindow);
            enterName[i].draw(this -> mainWindow);
        }

        title.draw(this -> mainWindow);

        this -> mainWindow -> display();
    }
}

void GamePlay::renderSettingScreen() {
    // Video mode and fullscreen setup
    sf::VideoMode fullscreenMode = sf::VideoMode::getDesktopMode();
    
    // Create setting screen background
    sf::RectangleShape settingScreen(sf::Vector2f(fullscreenMode.width, fullscreenMode.height));
    sf::Texture settingScreenTexture;
    settingScreenTexture.loadFromFile("../assets/background.png");
    settingScreen.setTexture(&settingScreenTexture);

    int buttonWidth = 300, buttonHeight = 100;
    buttonWithText title = buttonWithText(
        buttonWidth,
        buttonHeight,
        50,
        "Settings",
        (fullscreenMode.width - buttonWidth) / 2,
        fullscreenMode.height * 5 / 100
    );  

    // Main event and rendering loop for the title screen
    while (this -> mainWindow -> isOpen()) {
        sf::Event event;
        while (this -> mainWindow -> pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                this -> mainWindow -> close();
                exit(0);
            }
            else if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape) {
                    this -> mainWindow -> close();
                    exit(0);  // Exit the function if the escape key is pressed
                }
            }
        }

        this -> mainWindow -> clear(sf::Color::Black);

        // Draw the title screen background
        this -> mainWindow -> draw(settingScreen);

        title.draw(this -> mainWindow);

        this -> mainWindow -> display();
    }
}