#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <cctype>
#include <string>

using namespace std;

bool processInput(sf::Event ev, string &text) {
    if (ev.type == sf::Event::TextEntered) {
        auto ch = ev.text.unicode;       // get the char
        if (ch == 8 && !text.empty()) {  // is BACKSPACE and has a char?
            text.pop_back();             // Remove last char
        } else if (ch == 13)             // is ENTER?
            return false;                // Cancel editing
        else if (isprint(ch))            // Is it a printable char?
            text.push_back(ch);          // Insert the new char
    }
    return true;  // Continue editing
}

int main() {
    sf::RenderWindow window(sf::VideoMode(500, 300), "Text input example");
    sf::Event ev;
    sf::Font font;
    font.loadFromFile("OpenSans-Regular.ttf");  // From https://fonts.google.com/specimen/Open+Sans

    sf::Text nameDisplay("", font, 30);  // size=30
    nameDisplay.setPosition(60, 150);
    nameDisplay.setFillColor(sf::Color::Green);

    string playerName;
    bool isEditing = true;
    while (window.isOpen()) {
        while (window.pollEvent(ev)) {
            if (ev.type == sf::Event::Closed || (ev.type == sf::Event::KeyPressed && ev.key.code == sf::Keyboard::Escape)) {
                window.close();
                return 0;
            } else if (isEditing) {
                isEditing = processInput(ev, playerName);  // this function does the job
            }
        }

        window.clear();
        if (isEditing) {
            nameDisplay.setString("Nick: " + playerName);
            window.draw(nameDisplay);
        }
        window.display();
    }
    return 0;
}
