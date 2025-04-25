#pragma once
#include <SFML/Graphics.hpp>
#include "UI Button.h"
#include "UI GameScreen.h"
#include <functional>
#include <string>
#include <fstream>
class ResultScreenRus : public Screen {
public:
    ResultScreenRus(sf::Font& font, std::function<void(Screen*)> switchScreenCallback, int finalScore);
    ~ResultScreenRus();

    void draw(sf::RenderWindow& window) override;
    void handleInput(sf::Event& event, sf::RenderWindow& window) override;
    void update(float deltaTime) override;

private:
    sf::Font& font;
    std::function<void(Screen*)> switchScreenCallback;
    int finalScore;

    sf::Text titleText;
    sf::Text scoreText;

    Button* playAgainButton;
    Button* mainMenuButton;
    sf::Text ratingText;
    std::wstring allText; sf::Text resultText;
};
