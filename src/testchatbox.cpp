#include "chatbox.h"
int main() {
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "SFML Textbox Example");
    chatBox chatbox = chatBox(100, 100, 500, 500, 700, 700, 200, 200);
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            chatbox.handleEvent(event);
        }
        window.clear(sf::Color::Cyan);
        chatbox.draw(&window);
        window.display();
    }

    return 0;
}