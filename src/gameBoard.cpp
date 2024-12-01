#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>

int main() {
    // 获取屏幕分辨率
    sf::VideoMode fullscreenMode = sf::VideoMode::getDesktopMode();

    // 主窗口（全屏模式）
    sf::RenderWindow mainWindow(fullscreenMode, "Main Window", sf::Style::Fullscreen);

    float screenHeight = fullscreenMode.height;
    float squareSide = screenHeight * (18.0f / 20.0f);  
    float ss = screenHeight * (3.0f / 20.0f); 
    float sss = screenHeight * (3.0f / 40.0f); 
    float margin = squareSide / 18.0f;                        
    std::cout << screenHeight << '\n';

    sf::RectangleShape square[38];
    sf::RectangleShape player[10];
    sf::RectangleShape uplayer[10];sf::RectangleShape dplayer[10];
    sf::Vector2f playerSize(ss, ss);sf::Vector2f otherSize(ss, sss/2);

    sf::RectangleShape chatBox(sf::Vector2f(fullscreenMode.width-margin*3-2*ss-8*sss,fullscreenMode.height-margin*3-ss/2-sss-ss));
    chatBox.setFillColor(sf::Color(255, 239, 184));
    chatBox.setOutlineThickness(5.0f);                         
    chatBox.setOutlineColor(sf::Color(135, 206, 235)); 
    chatBox.setPosition(margin*2+2*ss+8*sss, 2*margin+sss+ss); 

    sf::RectangleShape inputBox(sf::Vector2f(fullscreenMode.width-margin*3-2*ss-8*sss-ss,ss/2));
    inputBox.setFillColor(sf::Color(255, 239, 184));
    inputBox.setOutlineThickness(5.0f);                         
    inputBox.setOutlineColor(sf::Color(135, 206, 235)); 
    inputBox.setPosition(margin*2+2*ss+8*sss+ss, 2*margin+sss+ss+fullscreenMode.height-margin*3-ss/2-sss-ss); 

    sf::RectangleShape chooseBox(sf::Vector2f(ss,ss/2));
    chooseBox.setFillColor(sf::Color(255, 239, 184));
    chooseBox.setOutlineThickness(5.0f);                         
    chooseBox.setOutlineColor(sf::Color(135, 206, 235)); 
    chooseBox.setPosition(margin*2+2*ss+8*sss, 2*margin+sss+ss+fullscreenMode.height-margin*3-ss/2-sss-ss); 

    for(int i=0;i<=3;i++){
        uplayer[i].setSize(otherSize);
        uplayer[i].setFillColor(sf::Color(143, 188, 143));
        uplayer[i].setOutlineThickness(5.0f);                         
        uplayer[i].setOutlineColor(sf::Color(135, 206, 235));
        uplayer[i].setPosition(2*margin+(2+i)*ss+8*sss+i*((fullscreenMode.width-margin*3-6*ss-8*sss)/3), margin); 

        player[i].setSize(playerSize);
        player[i].setFillColor(sf::Color(143, 188, 143));
        player[i].setOutlineThickness(5.0f);                         
        player[i].setOutlineColor(sf::Color(135, 206, 235));
        player[i].setPosition(2*margin+(2+i)*ss+8*sss+i*((fullscreenMode.width-margin*3-6*ss-8*sss)/3), margin+sss/2); 
        
        dplayer[i].setSize(otherSize);
        dplayer[i].setFillColor(sf::Color(143, 188, 143));
        dplayer[i].setOutlineThickness(5.0f);                         
        dplayer[i].setOutlineColor(sf::Color(135, 206, 235));
        dplayer[i].setPosition(2*margin+(2+i)*ss+8*sss+i*((fullscreenMode.width-margin*3-6*ss-8*sss)/3), margin+sss/2+ss); 
    }
    
    sf::Vector2f newSize(squareSide, squareSide);
    square[0].setSize(newSize);
    square[0].setFillColor(sf::Color(143, 188, 143));
    square[0].setOutlineThickness(5.0f);                         
    square[0].setOutlineColor(sf::Color::Black); 
    square[0].setPosition(margin, margin);  

    sf::Vector2f Newsize(ss, ss);
    square[34].setSize(Newsize);
    square[34].setFillColor(sf::Color(143, 188, 143));
    square[34].setOutlineThickness(5.0f);                         
    square[34].setOutlineColor(sf::Color::Black); 
    square[34].setPosition(margin, margin);  

    square[35].setSize(Newsize);
    square[35].setFillColor(sf::Color(143, 188, 143));
    square[35].setOutlineThickness(5.0f);                         
    square[35].setOutlineColor(sf::Color::Black); 
    square[35].setPosition(margin+8*sss+ss, margin);  

    square[36].setSize(Newsize);
    square[36].setFillColor(sf::Color(143, 188, 143));
    square[36].setOutlineThickness(5.0f);                         
    square[36].setOutlineColor(sf::Color::Black); 
    square[36].setPosition(margin,margin+8*sss+ss);  

    square[37].setSize(Newsize);
    square[37].setFillColor(sf::Color(143, 188, 143));
    square[37].setOutlineThickness(5.0f);                         
    square[37].setOutlineColor(sf::Color::Black); 
    square[37].setPosition(margin+8*sss+ss, margin+8*sss+ss);  

    sf::Vector2f Sizenew(ss, sss);
    for(int i=2;i<=8;i+=2){
        square[i].setSize(Sizenew);
        square[i].setFillColor(sf::Color(143, 188, 143));
        square[i].setOutlineThickness(5.0f);                         
        square[i].setOutlineColor(sf::Color::Black);
        square[i].setPosition(margin, margin+(i-2)*sss+ss); 
        square[i+1].setSize(Sizenew);
        square[i+1].setFillColor(sf::Color(143, 188, 143));
        square[i+1].setOutlineThickness(5.0f);                         
        square[i+1].setOutlineColor(sf::Color::Black);
        square[i+1].setPosition(margin, margin+(i-1)*sss+ss);
    }
    for(int i=10;i<=16;i+=2){
        square[i].setSize(Sizenew);
        square[i].setFillColor(sf::Color(143, 188, 143));
        square[i].setOutlineThickness(5.0f);                         
        square[i].setOutlineColor(sf::Color::Black); 
        square[i].setPosition(margin+ss+8*sss, margin+(i-10)*sss+ss); 
        square[i+1].setSize(Sizenew);
        square[i+1].setFillColor(sf::Color(143, 188, 143));
        square[i+1].setOutlineThickness(5.0f);                         
        square[i+1].setOutlineColor(sf::Color::Black);
        square[i+1].setPosition(margin+ss+8*sss, margin+(i-9)*sss+ss);
    }

    sf::Vector2f sizeNew(sss, ss);
    for(int i=18;i<=24;i+=2){
        square[i].setSize(sizeNew);
        square[i].setFillColor(sf::Color(143, 188, 143));
        square[i].setOutlineThickness(5.0f);                         
        square[i].setOutlineColor(sf::Color::Black);
        square[i].setPosition(margin+(i-18)*sss+ss, margin); 
        square[i+1].setSize(sizeNew);
        square[i+1].setFillColor(sf::Color(143, 188, 143));
        square[i+1].setOutlineThickness(5.0f);                         
        square[i+1].setOutlineColor(sf::Color::Black);
        square[i+1].setPosition(margin+(i-17)*sss+ss, margin);
    }
    for(int i=26;i<=32;i+=2){
        square[i].setSize(sizeNew);
        square[i].setFillColor(sf::Color(143, 188, 143));
        square[i].setOutlineThickness(5.0f);                         
        square[i].setOutlineColor(sf::Color::Black);
        square[i].setPosition(margin+(i-26)*sss+ss, margin+ss+8*sss); 
        square[i+1].setSize(sizeNew);
        square[i+1].setFillColor(sf::Color(143, 188, 143));
        square[i+1].setOutlineThickness(5.0f);                         
        square[i+1].setOutlineColor(sf::Color::Black);
        square[i+1].setPosition(margin+(i-25)*sss+ss, margin+ss+8*sss);
    }


    while (mainWindow.isOpen()) {
        sf::Event event;
        while (mainWindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                mainWindow.close();
            }
            else if(event.type == sf::Event::KeyPressed) {
                if(event.key.code == sf::Keyboard::Escape) {
                    mainWindow.close();
                    break;
                }
            }
        }
        if(!mainWindow.isOpen()) break;
        sf::Vector2i mousePosition = sf::Mouse::getPosition(mainWindow);
        sf::Vector2f mousePositionF(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y));
        for(int i=1;i<=37;i++){
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
        } else {
            square[i].setFillColor(sf::Color(143, 188, 143));  // 鼠标离开时恢复为白色
        }
        }
        // 绘制主窗口内容
        mainWindow.clear(sf::Color(255, 239, 184));
        for(int i=0;i<=37;i++){
            mainWindow.draw(square[i]);
        }
        for(int i=0;i<=9;i++){
            mainWindow.draw(uplayer[i]);
            mainWindow.draw(player[i]);
            mainWindow.draw(dplayer[i]);
        }
        mainWindow.draw(chatBox);
        mainWindow.draw(inputBox);
        mainWindow.draw(chooseBox);
        mainWindow.display();
    }

    return 0;
}
