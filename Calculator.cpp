#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <cctype>

// Simple left-to-right calculator (no operator precedence)
double evaluateExpression(const std::string& expr) {
    double result = 0;
    double current = 0;
    char op = '+';

    for (size_t i = 0; i <= expr.size(); i++) {
        char c = (i < expr.size() ? expr[i] : '\0');

        if (std::isdigit(c) || c == '.') {
            current = current * 10 + (c - '0');
        } else if (c == '+' || c == '-' || c == '*' || c == '/' || c == '\0') {
            switch (op) {
                case '+': result += current; break;
                case '-': result -= current; break;
                case '*': result *= current; break;
                case '/': if (current != 0) result /= current; break;
            }
            op = c;
            current = 0;
        }
    }

    return result;
}

int main() {
    sf::RenderWindow window(sf::VideoMode(400, 550), "SFML Calculator");
    window.setFramerateLimit(60);

    sf::Font font;
    if (!font.loadFromFile("Poppins-Regular.ttf")) {
        std::cout << "Font not found!" << std::endl;
        return 1;
    }

    std::string input = "";

    // Display box
    sf::RectangleShape display(sf::Vector2f(360, 100));
    display.setFillColor(sf::Color(40, 40, 40));
    display.setPosition(20, 20);

    sf::Text displayText("", font, 36);
    displayText.setFillColor(sf::Color::White);
    displayText.setPosition(30, 40);

    struct Button {
        sf::RectangleShape shape;
        sf::Text label;
        std::string value;
    };

    std::vector<Button> buttons;

    std::vector<std::string> labels = {
        "7","8","9","/",
        "4","5","6","*",
        "1","2","3","-",
        "0","C","=","+"
    };

    float bx = 20, by = 140;
    int k = 0;

    // Create the 16 buttons
    for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 4; col++) {

            Button b;
            b.value = labels[k];

            b.shape = sf::RectangleShape(sf::Vector2f(80, 80));
            b.shape.setFillColor(sf::Color(220, 220, 220));
            b.shape.setPosition(bx + col * 90, by + row * 90);

            b.label = sf::Text(labels[k], font, 40);
            b.label.setFillColor(sf::Color::Black);
            b.label.setPosition(bx + col * 90 + 25, by + row * 90 + 15);

            buttons.push_back(b);
            k++;
        }
    }

    // Main loop
    while (window.isOpen()) {
        sf::Event event;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            // Handle button clicks
            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i mouse = sf::Mouse::getPosition(window);

                for (auto& b : buttons) {
                    if (b.shape.getGlobalBounds().contains(mouse.x, mouse.y)) {

                        if (b.value == "C") {
                            input = "";
                        } 
                        else if (b.value == "=") {
                            try {
                                double result = evaluateExpression(input);
                                input = std::to_string(result);

                                // Clean trailing zeros
                                while (!input.empty() && input.back() == '0')
                                    input.pop_back();

                                if (!input.empty() && input.back() == '.')
                                    input.pop_back();

                            } catch (...) {
                                input = "ERR";
                            }
                        } 
                        else {
                            input += b.value;
                        }
                    }
                }
            }
        }

        // Update display
        displayText.setString(input);

        // Render
        window.clear(sf::Color(60, 60, 60));
        window.draw(display);
        window.draw(displayText);

        for (auto& b : buttons) {
            window.draw(b.shape);
            window.draw(b.label);
        }

        window.display();
    }

    return 0;
}
