#include "gameplay.h"

GamePlay::GamePlay() {
    if(!(this -> font).loadFromFile("fonts/Montserrat-Black.ttf")) {
        std::cerr << "Error loading font!" << std::endl;
    }
    if(!(this -> music).openFromFile("assets/bgm.wav")) {
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
    titleScreenTexture.loadFromFile("assets/title-screen.png");
    titleScreen.setTexture(&titleScreenTexture);

    // Define button size and positions
    int buttonWidth = 300, buttonHeight = 100;
    int buttonSpacing = 30;
    std::string buttonLabels[3] = {"New Game", "Settings", "Quit"};
    buttonWithText button[3];

    // Setup buttons and texts
    for (int i = 0; i < 3; ++i) {
        button[i] = buttonWithText(
            buttonWidth, 
            buttonHeight, 
            50, 
            buttonLabels[i], 
            (fullscreenMode.width - buttonWidth) / 2,
            (fullscreenMode.height - (buttonHeight * 3 + buttonSpacing * 2)) / 3 * 2 + (buttonHeight + buttonSpacing) * i
        );
    }

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

        for (int i = 0; i < 3; ++i) {
            if (button[i].isHovering(mousePos.x, mousePos.y)) {
                button[i].changeColor();  // Change text color on hover

                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                    // Handle button click
                    if (i == 0) {
                        std::cout << "New Game Button Clicked!" << std::endl;
                        this -> renderSelectionScreen();
                    }
                    else if (i == 1) {
                        std::cout << "Settings Button Clicked!" << std::endl;
                        this -> renderSettingScreen();
                    }
                    else if (i == 2) {
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
        for (int i = 0; i < 3; ++i) {
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
    selectionScreenTexture.loadFromFile("assets/background.png");
    selectionScreen.setTexture(&selectionScreenTexture);

    // Define button size and positions
    int buttonWidth = 300, buttonHeight = 100;
    int buttonSpacing = 30;
    sf::RectangleShape gameModes[3];
    sf::Text buttonTexts[3];
    std::string buttonLabels[3] = {"Host a game", "Join a game", "Go back"};
    buttonWithText button[3];

    // Setup buttons and texts
    for (int i = 0; i < 3; ++i) {
        button[i] = buttonWithText(
            buttonWidth, 
            buttonHeight, 
            50, 
            buttonLabels[i], 
            (fullscreenMode.width - buttonWidth) / 2,
            (fullscreenMode.height - (buttonHeight * 3 + buttonSpacing * 2)) / 2 + (buttonHeight + buttonSpacing) * i
        );
    }

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

        for (int i = 0; i < 3; ++i) {
            if (button[i].isHovering(mousePos.x, mousePos.y)) {
                button[i].changeColor();  // Change text color on hover

                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                    // Handle button click
                    if (i == 0) {
                        std::cout << "Selection: Host a game Clicked!" << std::endl;
                        // TODO
                    }
                    else if (i == 1) {
                        std::cout << "Selection: Join a game Clicked!" << std::endl;
                        // TODO
                    }
                    else if (i == 2) {
                        std::cout << "Selection: Quit Button Clicked!" << std::endl;
                        this -> renderTitleScreen();
                    }
                }
            }
            else {
                button[i].returnColor();  // Reset text color when not hovered
            }
        }

        this -> mainWindow -> clear(sf::Color::Black);

        // Draw the title screen background
        this -> mainWindow -> draw(selectionScreen);

        // Draw the buttons and their texts
        for (int i = 0; i < 3; ++i) {
            button[i].draw(this -> mainWindow);  // Draw the button
            this -> mainWindow -> draw(button[i].button);
        }

        this -> mainWindow -> display();
    }
}

void GamePlay::renderSettingScreen() {
    // Video mode and fullscreen setup
    sf::VideoMode fullscreenMode = sf::VideoMode::getDesktopMode();
    
    // Create setting screen background
    sf::RectangleShape settingScreen(sf::Vector2f(fullscreenMode.width, fullscreenMode.height));
    sf::Texture settingScreenTexture;
    settingScreenTexture.loadFromFile("assets/background.png");
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