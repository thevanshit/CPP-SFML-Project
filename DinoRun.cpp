#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <string>

enum class GameState {
    Ready,
    Playing,
    GameOver
};

struct Cactus {
    sf::RectangleShape shape;
};

struct Cloud {
    sf::RectangleShape shape;
};

int main() {
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    sf::RenderWindow window(sf::VideoMode(900, 300), "Dino Run", sf::Style::Close);
    window.setFramerateLimit(60);

    // Colors
    sf::Color skyTop(200, 230, 255);
    sf::Color skyBottom(160, 210, 250);
    sf::Color groundColor(80, 80, 80);
    sf::Color dinoColor(30, 30, 30);
    sf::Color dinoEye(240, 240, 240);
    sf::Color dinoAccent(60, 60, 60);
    sf::Color cactusColor(34, 139, 34);
    sf::Color uiColor(30, 30, 30);

    // Background gradient (two rectangles)
    sf::RectangleShape skyTopRect(sf::Vector2f(900, 150));
    skyTopRect.setPosition(0, 0);
    skyTopRect.setFillColor(skyTop);

    sf::RectangleShape skyBottomRect(sf::Vector2f(900, 150));
    skyBottomRect.setPosition(0, 150);
    skyBottomRect.setFillColor(skyBottom);

    // Ground line
    float groundY = 230.f;
    sf::RectangleShape ground(sf::Vector2f(900, 4));
    ground.setPosition(0, groundY);
    ground.setFillColor(groundColor);

    // Scrolling ground segments
    std::vector<sf::RectangleShape> groundSegments;
    for (int i = 0; i < 20; ++i) {
        sf::RectangleShape seg(sf::Vector2f(40, 3));
        seg.setFillColor(groundColor);
        seg.setPosition(i * 50.f, groundY + 8.f + (i % 3));
        groundSegments.push_back(seg);
    }

    // Dino
    sf::RectangleShape dinoBody(sf::Vector2f(40, 40));
    dinoBody.setFillColor(dinoColor);
    dinoBody.setPosition(80, groundY - 40);

    sf::RectangleShape dinoLeg1(sf::Vector2f(10, 16));
    sf::RectangleShape dinoLeg2(sf::Vector2f(10, 16));
    dinoLeg1.setFillColor(dinoAccent);
    dinoLeg2.setFillColor(dinoAccent);

    sf::CircleShape dinoEyeShape(3);
    dinoEyeShape.setFillColor(dinoEye);

    float dinoVelY = 0.f;
    const float gravity = 0.7f;
    bool onGround = true;
    bool legToggle = false;
    sf::Clock legClock;

    // Cacti
    std::vector<Cactus> cacti;
    float cactusSpeed = 7.f;
    sf::Clock cactusSpawnClock;
    float cactusSpawnMin = 0.9f;
    float cactusSpawnMax = 1.6f;
    float nextCactusSpawn = 1.0f;

    // Clouds
    std::vector<Cloud> clouds;
    for (int i = 0; i < 4; ++i) {
        Cloud c;
        c.shape = sf::RectangleShape(sf::Vector2f(60, 20));
        c.shape.setFillColor(sf::Color(250, 250, 250, 200));
        c.shape.setPosition(static_cast<float>(std::rand() % 900),
                            40.f + static_cast<float>(std::rand() % 60));
        clouds.push_back(c);
    }

    // Font & UI
    sf::Font font;
    if (!font.loadFromFile("Poppins-Regular.ttf")) {
        std::cout << "Poppins-Regular.ttf not found!\n";
        return 1;
    }

    int score = 0;
    int highScore = 0;
    sf::Clock scoreClock;

    sf::Text scoreText;
    scoreText.setFont(font);
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(uiColor);
    scoreText.setPosition(20, 10);

    sf::Text hiScoreText;
    hiScoreText.setFont(font);
    hiScoreText.setCharacterSize(18);
    hiScoreText.setFillColor(uiColor);
    hiScoreText.setPosition(20, 40);

    sf::Text msgText;
    msgText.setFont(font);
    msgText.setCharacterSize(28);
    msgText.setFillColor(uiColor);
    msgText.setString("Press SPACE to start");
    msgText.setPosition(260, 120);

    GameState state = GameState::Ready;

    // Helper lambdas
    auto resetGame = [&]() {
        cacti.clear();
        cactusSpeed = 7.f;
        score = 0;
        cactusSpawnClock.restart();
        scoreClock.restart();
        nextCactusSpawn = 1.0f;
        dinoBody.setPosition(80, groundY - 40);
        dinoVelY = 0;
        onGround = true;
        state = GameState::Playing;
    };

    auto spawnCactus = [&]() {
        Cactus c;
        float width = 18.f + static_cast<float>(std::rand() % 15);
        float height = 35.f + static_cast<float>(std::rand() % 25);
        c.shape = sf::RectangleShape(sf::Vector2f(width, height));
        c.shape.setFillColor(cactusColor);
        c.shape.setPosition(900, groundY - height);
        cacti.push_back(c);
    };

    auto updateDinoLegs = [&]() {
        if (legClock.getElapsedTime().asMilliseconds() > 120) {
            legToggle = !legToggle;
            legClock.restart();
        }
        sf::Vector2f bp = dinoBody.getPosition();
        if (onGround) {
            if (legToggle) {
                dinoLeg1.setPosition(bp.x + 4, bp.y + 40);
                dinoLeg2.setPosition(bp.x + 26, bp.y + 34);
            } else {
                dinoLeg1.setPosition(bp.x + 4, bp.y + 34);
                dinoLeg2.setPosition(bp.x + 26, bp.y + 40);
            }
        } else {
            dinoLeg1.setPosition(bp.x + 6, bp.y + 38);
            dinoLeg2.setPosition(bp.x + 24, bp.y + 38);
        }
        dinoEyeShape.setPosition(bp.x + 26, bp.y + 8);
    };

    // GAME LOOP
    while (window.isOpen()) {
        // -------------- EVENTS --------------
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape)
                    window.close();

                if (event.key.code == sf::Keyboard::Space) {
                    if (state == GameState::Ready) {
                        resetGame();
                    } else if (state == GameState::Playing) {
                        if (onGround) {
                            dinoVelY = -13.f;
                            onGround = false;
                        }
                    } else if (state == GameState::GameOver) {
                        state = GameState::Ready;
                        msgText.setString("Press SPACE to start");
                    }
                }
            }
        }

        // -------------- UPDATE --------------
        if (state == GameState::Playing) {
            // Dino physics
            dinoVelY += gravity;
            dinoBody.move(0, dinoVelY);

            if (dinoBody.getPosition().y >= groundY - 40) {
                dinoBody.setPosition(dinoBody.getPosition().x, groundY - 40);
                dinoVelY = 0;
                onGround = true;
            }

            // Clouds movement
            for (auto& c : clouds) {
                c.shape.move(-1.2f, 0);
                if (c.shape.getPosition().x + c.shape.getSize().x < 0) {
                    c.shape.setPosition(900.f, 40.f + static_cast<float>(std::rand() % 60));
                }
            }

            // Ground segments scroll
            for (auto& g : groundSegments) {
                g.move(-cactusSpeed * 0.7f, 0);
                if (g.getPosition().x + g.getSize().x < 0)
                    g.setPosition(900.f, g.getPosition().y);
            }

            // Spawn cactus
            if (cactusSpawnClock.getElapsedTime().asSeconds() > nextCactusSpawn) {
                spawnCactus();
                cactusSpawnClock.restart();
                nextCactusSpawn = cactusSpawnMin +
                                  static_cast<float>(std::rand()) / RAND_MAX *
                                  (cactusSpawnMax - cactusSpawnMin);
            }

            // Move cactus & collision
            for (std::size_t i = 0; i < cacti.size(); ) {
                cacti[i].shape.move(-cactusSpeed, 0);

                if (cacti[i].shape.getPosition().x + cacti[i].shape.getSize().x < 0) {
                    cacti.erase(cacti.begin() + i);
                    continue;
                }

                if (dinoBody.getGlobalBounds().intersects(cacti[i].shape.getGlobalBounds())) {
                    state = GameState::GameOver;
                    msgText.setString("GAME OVER  -  Press SPACE");
                    if (score > highScore) highScore = score;
                    break;
                }

                ++i;
            }

            // Score
            if (scoreClock.getElapsedTime().asMilliseconds() > 80) {
                score++;
                scoreClock.restart();
            }

            cactusSpeed = 7.f + static_cast<float>(score) / 200.f;
        }

        updateDinoLegs();

        // Update UI text
        scoreText.setString("Score: " + std::to_string(score));
        hiScoreText.setString("High: " + std::to_string(highScore));

        // -------------- DRAW --------------
        window.clear();

        // Gradient sky
        window.draw(skyTopRect);
        window.draw(skyBottomRect);

        // Clouds
        for (auto& c : clouds) window.draw(c.shape);

        // Ground
        window.draw(ground);
        for (auto& g : groundSegments) window.draw(g);

        // Dino
        window.draw(dinoBody);
        window.draw(dinoLeg1);
        window.draw(dinoLeg2);
        window.draw(dinoEyeShape);

        // Cacti
        for (auto& c : cacti) window.draw(c.shape);

        // UI
        window.draw(scoreText);
        window.draw(hiScoreText);

        if (state != GameState::Playing)
            window.draw(msgText);

        window.display();
    }

    return 0;
}
