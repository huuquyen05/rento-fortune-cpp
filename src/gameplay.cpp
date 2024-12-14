#include "gameplay.h"
#include "chatbox.h"
#include "button.h"
#include <unistd.h>
 
GamePlay::GamePlay() {
    if(!(this -> font).loadFromFile("../fonts/Montserrat-Black.ttf")) {
        std::cerr << "Error loading font!" << std::endl;
    }
    if(!(this -> music).openFromFile("../assets/bgm.wav")) {
        std::cerr << "Error loading bgm!" << std::endl;
    }
    this -> mainWindow = new sf::RenderWindow(sf::VideoMode::getDesktopMode(), "Main Window", sf::Style::Fullscreen );
    this -> mainWindow->setFramerateLimit(30);
    this -> music.play();
    this -> music.setLoop(true);
    std::cout << "OK init\n";
}

void GamePlay::renderTitleScreen() {

    // Video mode and fullscreen setup
    sf::VideoMode fullscreenMode = sf::VideoMode::getDesktopMode();
    
    // Create title screen background
    sf::RectangleShape titleScreen(sf::Vector2f(fullscreenMode.width, fullscreenMode.height));
    sf::Texture titleScreenTexture;
    if(!titleScreenTexture.loadFromFile("../assets/title-screen.png")) {
        std::cout << "Error loading bg for title\n";
    }   
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
    std::cout << "OK init title\n";

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
            30,
            "Enter your name:",
            pos.x + (recWidth - 400) / 2, 
            pos.y + recHeight - 250
        );
    } 

    buttonWithText welcome[4], namePlate[4];
     for(int i = 0; i < 4; ++i) {
        sf::Vector2f pos = rect[i].getPosition();
        welcome[i] = buttonWithText(
            400,
            200,
            30,
            "Welcome!",
            pos.x + (recWidth - 400) / 2, 
            pos.y + recHeight - 300
        );
        namePlate[i] = buttonWithText(
            400,
            200,
            30,
            "",
            pos.x + (recWidth - 400) / 2, 
            pos.y + recHeight - 200,
            playerColor[i]
        );
    } 

    buttonWithText controls[2];
    std::string controlsTexts[2] = {"Go back", "Start!"};
    int pad = 50;
    controls[0] = buttonWithText(300, 80, 50, controlsTexts[0], fullscreenMode.width / 2 - pad - 300, fullscreenMode.height - 150);
    controls[1] = buttonWithText(300, 80, 50, controlsTexts[1], fullscreenMode.width / 2 + pad, fullscreenMode.height - 150);

    std::string name[4] = {""};
    int nameEntered = 0;

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
                if((int)(name[i].size()) > 0) continue;
                std::string tmp = nameHolder[i].handleEvent(event);
                if(tmp != "") {
                    name[i] = tmp;
                    std::cout << i << " " << name[i] << std::endl;
                    namePlate[i].setText(name[i]);
                    ++nameEntered;
                }
            }
        }

        auto [x, y] = sf::Mouse::getPosition();

        if(nameEntered < 4) controls[1].setTextColor(sf::Color(120, 120, 120));
        else {
            if(controls[1].isHovering(x, y)) {
                controls[1].changeColor();
                if(controls[1].isClicked(x, y)) {
                    // Do some shit
                    renderGameScreen(name);
                }
            }
            else controls[1].returnColor();
        }

        if(controls[0].isHovering(x, y)) {
            controls[0].changeColor();
            if(controls[0].isClicked(x, y)) {
                renderTitleScreen();
            }
        }
        else controls[0].returnColor();

        this -> mainWindow -> clear(sf::Color::Black);

        // Draw the title screen background
        this -> mainWindow -> draw(selectionScreen);

        for (int i = 0; i < 4; ++i) {
            this -> mainWindow -> draw(rect[i]);
            this -> mainWindow -> draw(avatar[i]);
            if(name[i].size() == 0) {
                nameHolder[i].drawFromTop(this -> mainWindow);
                enterName[i].draw(this -> mainWindow);
            }
            else {
                welcome[i].draw(this -> mainWindow);
                namePlate[i].draw(this -> mainWindow);
            }
        }

        for(int i = 0; i < 2; ++i) {
            controls[i].draw(this -> mainWindow);
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

    buttonWithText backButton = buttonWithText(300, 80, 50, "Go back", (fullscreenMode.width - 300) / 2, fullscreenMode.height - 150);

    std::string state[2] = {"Off", "On"};
    buttonWithText onOff = buttonWithText(300, 80, 40, state[0], (fullscreenMode.width - 300) - 300, 200);
    int curState = 1; // initially On

    buttonWithText soundText = buttonWithText(300, 80, 40, "Sound", 300, 200);
    
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

        auto [x, y] = sf::Mouse::getPosition();
        if(backButton.isHovering(x, y)) {
            backButton.changeColor();
            if(backButton.isClicked(x, y)) {
                renderTitleScreen();
            }
        }
        else backButton.returnColor();
        if(onOff.isHovering(x, y)) {
            onOff.changeColor();
            if(onOff.isClicked(x, y)) {
                usleep(300000);
                curState ^= 1;
                if(curState == 1) {this -> music.play(); this -> music.setLoop(true);}
                else this -> music.stop();
            }
        }
        else onOff.returnColor();

        onOff.setText(state[curState]);

        this -> mainWindow -> clear(sf::Color::Black);

        // Draw the title screen background
        this -> mainWindow -> draw(settingScreen);

        backButton.draw(this -> mainWindow);
        onOff.draw(this -> mainWindow);
        soundText.draw(this -> mainWindow);

        title.draw(this -> mainWindow);

        this -> mainWindow -> display();
    }
}

void GamePlay::setTokenPosition(int index, sf::CircleShape &c,buttonWithText &curSlot) {
    auto [x1, x2, y1, y2] = curSlot.getPos();
    float radius = c.getRadius();

    int x, y;
    float dist = radius * 2 + 5;

    float dx = (x2 - x1 - dist) / 2;
    if(index < 2) x = x1 + dx;
    else x = x2 - dx;

    float dy = (y2 - y1 - dist) / 2;
    if(index % 2 == 0) y = y1 + dy;
    else y = y2 - dy;

    c.setPosition(sf::Vector2f(x, y));
}

void GamePlay::renderGameScreen(std::string names[4]) {
    int slotNUm = -1;
    int inTurnPlayer = -1;
    bool diceThrown=0;
    std::vector<int> playerNumber(4);
    Game game(names);
    int linkList[40]={
        0,30,20,10,
        9,8,7,6,5,4,3,2,1,
        39,38,37,36,35,34,33,32,31,
        21,22,23,24,25,26,27,28,29,
        11,12,13,14,15,16,17,18,19
    };
    //--------------------------------------------------------------------------------------------

    sf::VideoMode fullscreenMode = sf::VideoMode::getDesktopMode();

    float screenHeight = fullscreenMode.height;
    float squareSide = screenHeight * (18.0f / 20.0f);  
    float ss = screenHeight * (3.0f / 20.0f); 
    float sss = screenHeight * (3.0f / 40.0f); 
    float fix = screenHeight * (1.0f / 120.0f); 
    float margin = squareSide / 18.0f;
    float fontSizeMultiplier = screenHeight / 1440;                   

    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("../assets/background.png")) {  // 替换为你的图片路径
        std::cerr << "Error: Failed to load background image!" << std::endl;
    }

    // 创建背景精灵
    sf::Sprite backgroundSprite;
    backgroundSprite.setTexture(backgroundTexture);

    // 调整背景图片的大小以适配窗口
    sf::Vector2u textureSize = backgroundTexture.getSize();   // 获取图片原始大小
    sf::Vector2u windowSize = mainWindow -> getSize();               // 获取窗口大小
    float scaleX = static_cast<float>(windowSize.x) / textureSize.x;
    float scaleY = static_cast<float>(windowSize.y) / textureSize.y;
    backgroundSprite.setScale(scaleX, scaleY); 

    //----------------------------------------------------------------------------------above is screen

    buttonWithText button[40];
    
    button[0]=buttonWithText(ss,ss,80 * fontSizeMultiplier,"GO",margin, margin+8*sss+ss);
    button[1]=buttonWithText(ss,ss,40 * fontSizeMultiplier,"GO TO\nJail",margin+8*sss+ss, margin+8*sss+ss);
    button[2]=buttonWithText(ss,ss,40 * fontSizeMultiplier,"FREE\nPARKING",margin+8*sss+ss, margin);
    button[3]=buttonWithText(ss,ss,80 * fontSizeMultiplier,"Jail",margin, margin);
    std::string nameList[40]={
        "","","","",
        "WHITECHAPEL\nROAD","BOW\nSTREET","CHANCE","LEICESTER\nSQUARE",
        "MARYLEBONE\nSTATION",
        "INCOME\nTAX","CONVENTRY\nSTREET","COMMUNITY\nCHEST","VINE\nSTREET",
        "MAY-\nFAIR","SUPER\nTAX","PARK\nLANE","CHANCE",
        "LIVER-\nPOOL\nST.\nSTA-\nTION",
        "OXFORD\nSTREET","COM-\nMUNITY\nCHEST","PICCA-\nDILLY","EUSTON\nROAD",
        "WHITEHALL","CHANCE","PENTONVILLE\nROAD","PALL\nMALL",
        "KINGS CROSS\nSTATION","BOND\nSTREET","STRAND","WATER\nWORKS","REGENT\nSTREET",
        "THE\nANGEL\nIS-\nLING-\nTON","ELEC-\nTRIC\nCOM-\nPANY","TRA-\nFAL\nGAR\nSQUARE",
        "NORTH-\nUMRL'D\nSQUARE","FEN-\nCHURCH\nST.\nSTATION","M'BO-\nROUGH\nSTREET",
        "COM-\nMUNITY\nCHEST","FLEET\nSTREET","OLD\nKENT\nROAD"
    };
    sf::Color colorList[40]={
        sf::Color::Black,sf::Color::Black,sf::Color::Black,sf::Color::Black,
        sf::Color::Cyan,sf::Color::Cyan,sf::Color::Black,sf::Color::Cyan,
        sf::Color::Black,
        sf::Color::Black,sf::Color(139, 69, 19),sf::Color::Black,sf::Color(139, 69, 19),
        sf::Color::Blue,sf::Color::Black,sf::Color::Blue,
        sf::Color::Black,sf::Color::Black,
        sf::Color::Green,sf::Color::Black,sf::Color::Green,sf::Color::Green,
        sf::Color(255, 192, 203),sf::Color::Black,sf::Color(255, 192, 203),sf::Color(255, 192, 203),
        sf::Color::Black,
        sf::Color::Yellow,sf::Color::Yellow,sf::Color::Black,sf::Color::Yellow,
        sf::Color(128, 0, 128),sf::Color::Black,sf::Color(128, 0, 128),sf::Color(128, 0, 128),
        sf::Color::Black,
        sf::Color(255, 165, 0),sf::Color::Black,sf::Color(255, 165, 0),sf::Color(255, 165, 0),
    };
    for(int i=4;i<=12;i++){
        button[i]=buttonWithText(ss,sss-fix,20 * fontSizeMultiplier,nameList[i],margin,margin+ss+(i-4)*(sss-fix),colorList[i]);
    }
    for(int i=13;i<=21;i++){
        button[i]=buttonWithText(sss-fix,ss,15 * fontSizeMultiplier,nameList[i],margin+ss+(i-13)*(sss-fix),margin+ss+9*(sss-fix),colorList[i]);
    }
    for(int i=22;i<=30;i++){
        button[i]=buttonWithText(ss,sss-fix,20 * fontSizeMultiplier,nameList[i],margin+ss+9*(sss-fix),margin+ss+(i-22)*(sss-fix),colorList[i]);
    }
    for(int i=31;i<=39;i++){
        button[i]=buttonWithText(sss-fix,ss,15 * fontSizeMultiplier,nameList[i],margin+ss+(i-31)*(sss-fix),margin,colorList[i]);
    }

    buttonWithText quit=buttonWithText(sss,sss,30 * fontSizeMultiplier,"quit",1.7*margin, -1*margin/4);
    buttonWithText save=buttonWithText(sss,sss,30 * fontSizeMultiplier,"save",0.2*margin, -1*margin/4);
    buttonWithText throwDice=buttonWithText(ss,sss,30 * fontSizeMultiplier,"Throw the Dices",margin+ss+(3.4)*(sss-fix),margin+ss+5*(sss-fix));
    buttonWithText endTurn=buttonWithText(ss,sss,30 * fontSizeMultiplier,"End Your Turn",margin+ss+(3.4)*(sss-fix),margin+ss+6.5*(sss-fix));
    //----------------------------------------------------------------------------------above is button

    sf::RectangleShape square[45];
    sf::RectangleShape player[10];
    sf::RectangleShape uplayer[10];sf::RectangleShape dplayer[10];
    sf::Vector2f playerSize(ss, ss);sf::Vector2f otherSize(ss, sss/2);

    //------------------------------------------------------------------------------------------------------------------------------------
    TextBox info=TextBox(margin*2+2*ss+8*sss, 2*margin+sss+ss,fullscreenMode.width-margin*3-2*ss-8*sss,fullscreenMode.height-margin*3-ss/2-3*sss-ss);
    TextBox textbox=TextBox(margin*2+2*ss+8*sss, 2*margin+sss+ss+fullscreenMode.height-margin*3-ss/2-3*sss-ss,fullscreenMode.width-margin*3-2*ss-8*sss,ss/2+2*sss);
    info.setFont("../fonts/Montserrat-Black.ttf");
    //------------------------------------------------------------------------------------------------------------------------------------

    sf::Color colorForAva[4]={
        sf::Color::Red, sf::Color::Green, sf::Color::Blue, sf::Color(242, 107, 15)
    };

    sf::CircleShape tokens[4];
    for(int i = 0; i < 4; ++i) {
        tokens[i].setRadius(margin / 6);
        tokens[i].setFillColor(colorForAva[i]);
        tokens[i].setOutlineColor(sf::Color::Black);
        tokens[i].setOutlineThickness(1);
        tokens[i].setOrigin(tokens[i].getRadius(), tokens[i].getRadius());
        setTokenPosition(i, tokens[i], button[10]);
    }

    int curPos[4] = {0}; // temp
    buttonWithText namePlates[4];

    for(int i=0;i<=3;i++){
        uplayer[i].setSize(otherSize);
        uplayer[i].setFillColor(sf::Color(143, 188, 143));
        uplayer[i].setOutlineThickness(5.0f);             
        uplayer[i].setOutlineColor(sf::Color::Black);
        uplayer[i].setPosition(2*margin+(2+i)*ss+8*sss+i*((fullscreenMode.width-margin*3-6*ss-8*sss)/3), margin); 

        namePlates[i] = buttonWithText(
            (int)otherSize.x,
            (int)otherSize.y,
            20,
            names[i],
            2*margin+(2+i)*ss+8*sss+i*((fullscreenMode.width-margin*3-6*ss-8*sss)/3),
            margin
        );

        player[i].setSize(playerSize);
        player[i].setFillColor(colorForAva[i]);
        player[i].setOutlineThickness(5.0f);                         
        player[i].setOutlineColor(sf::Color::Black);
        player[i].setPosition(2*margin+(2+i)*ss+8*sss+i*((fullscreenMode.width-margin*3-6*ss-8*sss)/3), margin+sss/2); 
        
        dplayer[i].setSize(otherSize);
        dplayer[i].setFillColor(sf::Color(143, 188, 143));
        dplayer[i].setOutlineThickness(5.0f);                         
        dplayer[i].setOutlineColor(sf::Color::Black);
        dplayer[i].setPosition(2*margin+(2+i)*ss+8*sss+i*((fullscreenMode.width-margin*3-6*ss-8*sss)/3), margin+sss/2+ss); 
    }
    
    sf::Vector2f newSize(squareSide, squareSide);
    square[0].setSize(newSize);
    square[0].setFillColor(sf::Color(143, 188, 143));
    square[0].setOutlineThickness(5.0f);                         
    square[0].setOutlineColor(sf::Color::Black); 
    square[0].setPosition(margin, margin);  

    sf::Vector2f Newsize(ss, ss);
    square[40].setSize(Newsize);
    square[40].setFillColor(sf::Color(143, 188, 143));
    square[40].setOutlineThickness(5.0f);                         
    square[40].setOutlineColor(sf::Color::Black); 
    square[40].setPosition(margin, margin);  

    square[41].setSize(Newsize);
    square[41].setFillColor(sf::Color(143, 188, 143));
    square[41].setOutlineThickness(5.0f);                         
    square[41].setOutlineColor(sf::Color::Black); 
    square[41].setPosition(margin+8*sss+ss, margin);  

    square[42].setSize(Newsize);
    square[42].setFillColor(sf::Color(143, 188, 143));
    square[42].setOutlineThickness(5.0f);                         
    square[42].setOutlineColor(sf::Color::Black); 
    square[42].setPosition(margin,margin+8*sss+ss);  

    square[43].setSize(Newsize);
    square[43].setFillColor(sf::Color(143, 188, 143));
    square[43].setOutlineThickness(5.0f);                         
    square[43].setOutlineColor(sf::Color::Black); 
    square[43].setPosition(margin+8*sss+ss, margin+8*sss+ss);  

    sf::Vector2f Sizenew(ss, sss-fix);
    for(int i=2;i<=8;i+=2){
        square[i].setSize(Sizenew);
        square[i].setFillColor(sf::Color(143, 188, 143));
        square[i].setOutlineThickness(5.0f);                         
        square[i].setOutlineColor(sf::Color::Black);
        square[i].setPosition(margin, margin+(i-2)*(sss-fix)+ss); 
        square[i+1].setSize(Sizenew);
        square[i+1].setFillColor(sf::Color(143, 188, 143));
        square[i+1].setOutlineThickness(5.0f);                         
        square[i+1].setOutlineColor(sf::Color::Black);
        square[i+1].setPosition(margin, margin+(i-1)*(sss-fix)+ss);
    }
    square[34].setSize(Sizenew);
    square[34].setFillColor(sf::Color(143, 188, 143));
    square[34].setOutlineThickness(5.0f);                         
    square[34].setOutlineColor(sf::Color::Black);
    square[34].setPosition(margin, margin+8*(sss-fix)+ss);
    for(int i=10;i<=16;i+=2){
        square[i].setSize(Sizenew);
        square[i].setFillColor(sf::Color(143, 188, 143));
        square[i].setOutlineThickness(5.0f);                         
        square[i].setOutlineColor(sf::Color::Black); 
        square[i].setPosition(margin+ss+9*(sss-fix), margin+(i-10)*(sss-fix)+ss); 
        square[i+1].setSize(Sizenew);
        square[i+1].setFillColor(sf::Color(143, 188, 143));
        square[i+1].setOutlineThickness(5.0f);                         
        square[i+1].setOutlineColor(sf::Color::Black);
        square[i+1].setPosition(margin+ss+9*(sss-fix), margin+(i-9)*(sss-fix)+ss);
    }
    square[35].setSize(Sizenew);
    square[35].setFillColor(sf::Color(143, 188, 143));
    square[35].setOutlineThickness(5.0f);                         
    square[35].setOutlineColor(sf::Color::Black);
    square[35].setPosition(margin+ss+9*(sss-fix), margin+(8)*(sss-fix)+ss);
    sf::Vector2f sizeNew(sss-fix, ss);
    for(int i=18;i<=24;i+=2){
        square[i].setSize(sizeNew);
        square[i].setFillColor(sf::Color(143, 188, 143));
        square[i].setOutlineThickness(5.0f);                         
        square[i].setOutlineColor(sf::Color::Black);
        square[i].setPosition(margin+(i-18)*(sss-fix)+ss, margin); 
        square[i+1].setSize(sizeNew);
        square[i+1].setFillColor(sf::Color(143, 188, 143));
        square[i+1].setOutlineThickness(5.0f);                         
        square[i+1].setOutlineColor(sf::Color::Black);
        square[i+1].setPosition(margin+(i-17)*(sss-fix)+ss, margin);
    }
    square[36].setSize(sizeNew);
    square[36].setFillColor(sf::Color(143, 188, 143));
    square[36].setOutlineThickness(5.0f);                         
    square[36].setOutlineColor(sf::Color::Black);
    square[36].setPosition(margin+(8)*(sss-fix)+ss, margin);
    for(int i=26;i<=32;i+=2){
        square[i].setSize(sizeNew);
        square[i].setFillColor(sf::Color(143, 188, 143));
        square[i].setOutlineThickness(5.0f);                         
        square[i].setOutlineColor(sf::Color::Black);
        square[i].setPosition(margin+(i-26)*(sss-fix)+ss, margin+ss+9*(sss-fix)); 
        square[i+1].setSize(sizeNew);
        square[i+1].setFillColor(sf::Color(143, 188, 143));
        square[i+1].setOutlineThickness(5.0f);                         
        square[i+1].setOutlineColor(sf::Color::Black);
        square[i+1].setPosition(margin+(i-25)*(sss-fix)+ss, margin+ss+9*(sss-fix));
    }
    square[37].setSize(sizeNew);
    square[37].setFillColor(sf::Color(143, 188, 143));
    square[37].setOutlineThickness(5.0f);                         
    square[37].setOutlineColor(sf::Color::Black);
    square[37].setPosition(margin+(8)*(sss-fix)+ss, margin+ss+9*(sss-fix));

    while (mainWindow -> isOpen()) {
        sf::Event event;
        while (mainWindow -> pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                mainWindow -> close();
            }
            else if(event.type == sf::Event::KeyPressed) {
                if(event.key.code == sf::Keyboard::Escape) {
                    mainWindow -> close();
                    break;
                }
            }
        }
        if(!mainWindow -> isOpen()) break;
        sf::Vector2i mousePosition = sf::Mouse::getPosition(*mainWindow);
        sf::Vector2f mousePositionF(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y));
        for(int i=1;i<=44;i++){
            float outlineThickness = square[i].getOutlineThickness();
            sf::FloatRect globalBounds = square[i].getGlobalBounds();
            sf::FloatRect innerBounds(
                globalBounds.left + outlineThickness,                    
                globalBounds.top + outlineThickness,                     // 内部上边界
                globalBounds.width - 2 * outlineThickness,               // 内部宽度
                globalBounds.height - 2 * outlineThickness               // 内部高度
            );
            if (innerBounds.contains(mousePositionF)) {
            square[i].setFillColor(sf::Color(112, 163, 204));  // 鼠标悬浮时变为红色
            }else {
            square[i].setFillColor(sf::Color(143, 188, 143));  // 鼠标离开时恢复为白色
            }
        }
        for(int i=0;i<=3;i++){
            float outlineThickness = player[i].getOutlineThickness();
            sf::FloatRect globalBounds = player[i].getGlobalBounds();
            sf::FloatRect innerBounds(
                globalBounds.left + outlineThickness,                    
                globalBounds.top + outlineThickness,                     // 内部上边界
                globalBounds.width - 2 * outlineThickness,               // 内部宽度
                globalBounds.height - 2 * outlineThickness               // 内部高度
            );
            if (innerBounds.contains(mousePositionF)) {
            player[i].setOutlineColor(sf::Color(135, 206, 235));
            uplayer[i].setOutlineColor(sf::Color(135, 206, 235));
            dplayer[i].setOutlineColor(sf::Color(135, 206, 235));  // 鼠标悬浮时变为红色
            }else {
            player[i].setOutlineColor(sf::Color::Black);
            uplayer[i].setOutlineColor(sf::Color::Black);
            dplayer[i].setOutlineColor(sf::Color::Black);  // 鼠标离开时恢复为白色
            }
        }
        if(quit.isHovering((mousePosition.x), (mousePosition.y))) {
            quit.changeColor();
            if(quit.isClicked((mousePosition.x), (mousePosition.y))) {
                renderTitleScreen();
            }
        }
        else quit.returnColor();
        if(save.isHovering((mousePosition.x), (mousePosition.y))) save.changeColor();
        else save.returnColor();
        if(endTurn.isHovering((mousePosition.x), (mousePosition.y))) endTurn.changeColor();
        else endTurn.returnColor();
        if(throwDice.isHovering((mousePosition.x), (mousePosition.y))) throwDice.changeColor();
        else throwDice.returnColor();
        for(int i=0;i<=40;i++){
            if(button[i].isHovering((mousePosition.x), (mousePosition.y))){
                button[i].changeColor();
            } 
            else button[i].returnColor();
            if(button[i].isClicked((mousePosition.x), (mousePosition.y))){
                std::stringstream sstream;
                sstream << slots[linkList[i]]->getName();
                info.clear();
                info.addString((sstream).str());
            }
        }
        textbox.handleEvent(event);
        info.handleEvent(event);
        // 绘制主窗口内容
        mainWindow -> clear();
        mainWindow -> draw(backgroundSprite);
        for(int i=0;i<=44;i++){
            mainWindow -> draw(square[i]);
        }
        for(int i=0;i<=9;i++){
            mainWindow -> draw(uplayer[i]);
            mainWindow -> draw(dplayer[i]);
            mainWindow -> draw(player[i]);
        }
        for(int i = 0; i < 4; ++i) {
            namePlates[i].draw(mainWindow);
        }
        //mainWindow -> draw(chatBox);
        textbox.drawFromTop(mainWindow);
        info.drawFromTop(mainWindow);
        for(int i=0;i<=39;i++) button[i].draw(mainWindow);

        // remove this later
        for(int i = 0; i < 4; ++i) {
            curPos[i] = (curPos[i] + 1) % 40;
            for(int j = 0; j < 40; ++j) {
                if(curPos[i] == linkList[j]) {
                    setTokenPosition(i, tokens[i], button[j]);
                }
            }
        }
        //

        for(int i = 0; i < 4; ++i) mainWindow -> draw(tokens[i]);
        save.draw(mainWindow);
        quit.draw(mainWindow);
        throwDice.draw(mainWindow);
        endTurn.draw(mainWindow);
        mainWindow -> display();
        usleep(100000);
    }
}