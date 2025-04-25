#include "ResultScreenRus.h"
#include "RusGame.h"
#include "UI MainMenuScreen.h" // <-- если у тебя есть главный экран
#include "DifficultyScreen_RusGame.h"
#include <sstream>
#include <fstream>      // для std::wifstream
#include <sstream>      // для std::wstringstream
#include <string>       // для std::wstring
#include <iostream>     // для std::wcout (если нужно)

ResultScreenRus::ResultScreenRus(sf::Font& font, std::function<void(Screen*)> switchScreenCallback, int finalScore)
    : font(font), switchScreenCallback(switchScreenCallback), finalScore(finalScore)
{
    titleText.setFont(font);
    titleText.setCharacterSize(32);
    titleText.setString(L"Игра окончена!");
    titleText.setFillColor(sf::Color::Black);
    titleText.setPosition(300, 100);

    scoreText.setFont(font);
    scoreText.setCharacterSize(24);
    scoreText.setString(L"Ваш счёт: " + std::to_wstring(finalScore));
    scoreText.setFillColor(sf::Color::Blue);
    scoreText.setPosition(300, 160);

    // --- Добавим вывод рейтинга ---
    ratingText.setFont(font);
    ratingText.setCharacterSize(20);
    ratingText.setFillColor(sf::Color::Black);
    ratingText.setPosition(300, 210); // немного ниже счёта

    std::wifstream file(L"rating.txt");
    std::wstringstream ss;

    if (file.is_open()) {
        std::wstring line;
        while (std::getline(file, line)) {
            ss << line << L"\n" << "\n";
        }
        file.close();
    }
    else {
        ss << L"Рейтинг пока пуст или не удалось открыть файл.\n";
    }

    ratingText.setString(ss.str());

    playAgainButton = new Button({ 300, 450 }, font, L"Сыграть снова");
    mainMenuButton = new Button({ 300, 520 }, font, L"В главное меню");
}

ResultScreenRus::~ResultScreenRus() {
    delete playAgainButton;
    delete mainMenuButton;
}

void ResultScreenRus::draw(sf::RenderWindow& window) {
    window.draw(titleText);
    window.draw(scoreText);
    playAgainButton->draw(window);
    mainMenuButton->draw(window);
    window.draw(ratingText); // после draw(scoreText)
}

void ResultScreenRus::handleInput(sf::Event& event, sf::RenderWindow& window) {
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        sf::Vector2f mousePos(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y));

        if (playAgainButton->isClicked(mousePos)) {
            switchScreenCallback(new DifficultyScreen_RusGame(font, switchScreenCallback)); // или другой уровень сложности
        }
        else if (mainMenuButton->isClicked(mousePos)) {
            switchScreenCallback(new MainMenuScreen(font, switchScreenCallback)); // если у тебя есть меню
        }
    }
}

void ResultScreenRus::update(float deltaTime) {
    // можно добавить анимации позже
}
