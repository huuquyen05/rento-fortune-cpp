#include "button.h"

int main() {
    sf::RenderWindow window = sf::RenderWindow(sf::VideoMode::getDesktopMode(), "Main Window", sf::Style::Fullscreen );
    window.setFramerateLimit(30);
    std::vector <std::string> tmp = {"This issss", "a test", "button!!!!!!!!", "fuck", "lololol"};
    std::vector <std::string> tmp2 = {"aaaaaaaaaa", "eeeeeeeeeeeeeee", "cccccccccccccccccccc"};
    buttonWithLines but = buttonWithLines(150, 150, 20, tmp, 100, 100);
    buttonWithLines but2 = buttonWithLines(300, 100, 20, tmp2, 400, 500);
    sf::RectangleShape vcl = sf::RectangleShape(sf::Vector2f(150, 100));
    vcl.setPosition(sf::Vector2f(100, 100));
    vcl.setFillColor(sf::Color::Red);
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape) {
                    window.close();
                }
            }
            auto [x, y] = sf::Mouse::getPosition();
            if(but.isHovering(x, y)) {
                but.changeColor();
                std::cout << x << " " << y << '\n';
            }
            else but.returnColor();
            if(but2.isHovering(x, y)) {
                but2.changeColor();
                std::cout << x << " " << y << '\n';
            }
            else but2.returnColor();
        }
        window.clear(sf::Color::White);
        but.draw(&window);
        but2.draw(&window);
        window.display();
    }

    return 0;
}