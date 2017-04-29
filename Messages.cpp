/*******************************************************************************
    Game 2048, Alpha Version
	Created by Anton Ivanenko,January 2017
	I wrote this to train using SFML Graphics library
*******************************************************************************/

#include "Messages.h"
#include <iostream>
#include <sstream>
#include <SFML/Graphics.hpp>

using namespace sf;

void SaveMessage(sf::RenderWindow &window, sf::Vector2i Resolution, bool &isGame, bool &saveFile){
	sf::RectangleShape background(Vector2f(Resolution.x, Resolution.y));
	sf::RectangleShape message(Vector2f(400, 200));
	background.setFillColor(Color(251, 248, 239, 150));
	message.setFillColor(Color(187, 173, 160, 200));
	message.setPosition((Resolution.y - 200) / 2, (Resolution.x - 400) / 2);
	Font font;
	font.loadFromFile("fonts/arial.ttf");
	Text MessageText(" Do you want to save game?\nPrevious file will be rewrited", font, 25), YesText("Yes", font, 20), NoText("No", font, 20);
	YesText.setStyle(sf::Text::Bold);
	YesText.setFillColor(sf::Color::White);
	NoText.setFillColor(sf::Color::White);
	MessageText.setStyle(sf::Text::Bold);
	NoText.setStyle(sf::Text::Bold);

	MessageText.setPosition((Resolution.y - 200) / 2 + 30, (Resolution.x - 400) / 2 + 30);
	YesText.setPosition((Resolution.y - 200) / 2 + 40, (Resolution.x - 400) / 2 + 150);
	NoText.setPosition((Resolution.y - 200) / 2 + 330, (Resolution.x - 400) / 2 + 150);

	if (IntRect((Resolution.y - 200) / 2 + 40, (Resolution.x - 400) / 2 + 150, 30, 25).contains(Mouse::getPosition(window))) {
		YesText.setFillColor(Color(239, 97, 0));
		if (Mouse::isButtonPressed(Mouse::Left)) {
			isGame = false;
			saveFile = true;
		}
	}
	if (IntRect((Resolution.y - 200) / 2 + 330, (Resolution.x - 400) / 2 + 150, 30, 25).contains(Mouse::getPosition(window))) {
		NoText.setFillColor(Color(239, 97, 0));
		if (Mouse::isButtonPressed(Mouse::Left)) {
			isGame = false;
		}
	}


	window.draw(background);
	window.draw(message);
	window.draw(MessageText);
	window.draw(YesText);
	window.draw(NoText);
}

void LoseMessage(sf::RenderWindow &window, sf::Vector2i Resolution, Field &Game, bool &isGame, bool &isMessage, int &messageCode){

	sf::RectangleShape background(Vector2f(Resolution.x, Resolution.y));
	sf::RectangleShape message(Vector2f(400, 200));
	std::ostringstream ScoreString;
	ScoreString << Game.GetScore();
	background.setFillColor(Color(251, 248, 239, 150));
	message.setFillColor(Color(187, 173, 160, 200));
	message.setPosition((Resolution.y - 200) / 2, (Resolution.x - 400) / 2);
	Font font;
	font.loadFromFile("fonts/arial.ttf");
	Text MessageText(" Game Over!\n", font, 30), RestartText("Restart", font, 20), MenuText("Menu", font, 20), ScoreText("Your score:\n", font, 25), ResultText("", font, 25);;
	RestartText.setStyle(sf::Text::Bold);
	RestartText.setFillColor(sf::Color::White);
	MenuText.setFillColor(sf::Color::White);
	MessageText.setStyle(sf::Text::Bold);
	MenuText.setStyle(sf::Text::Bold);

	ResultText.setString(ScoreString.str());
	MessageText.setPosition((Resolution.y - 200) / 2 + 110, (Resolution.x - 400) / 2 + 30);
	RestartText.setPosition((Resolution.y - 200) / 2 + 40, (Resolution.x - 400) / 2 + 150);
	ScoreText.setPosition((Resolution.y - 200) / 2 + 140, (Resolution.x - 400) / 2 + 65);
	MenuText.setPosition((Resolution.y - 200) / 2 + 310, (Resolution.x - 400) / 2 + 150);
	ResultText.setPosition((Resolution.y - 200) / 2 + (400 - ScoreString.str().size()*10)/2, (Resolution.x - 400) / 2 + 100);

	if (IntRect((Resolution.y - 200) / 2 + 40, (Resolution.x - 400) / 2 + 150, 65, 25).contains(Mouse::getPosition(window))) {
		RestartText.setFillColor(Color(239, 97, 0));
		if (Mouse::isButtonPressed(Mouse::Left)) {
			Game.SaveFileScore();
			Game.Restart();
			isMessage = false;
			messageCode = 0;
		}
	}
	if (IntRect((Resolution.y - 200) / 2 + 310, (Resolution.x - 400) / 2 + 150, 50, 25).contains(Mouse::getPosition(window))) {
		MenuText.setFillColor(Color(239, 97, 0));
		if (Mouse::isButtonPressed(Mouse::Left)) {
			isGame = false;
			isMessage = false;
		}
	}


	window.draw(background);
	window.draw(message);
	window.draw(MessageText);
	window.draw(RestartText);
	window.draw(MenuText);
	window.draw(ScoreText);
	window.draw(ResultText);

}

void WinMessage(sf::RenderWindow &window, sf::Vector2i Resolution, bool &isMessage, int &messageCode) {
	sf::RectangleShape background(Vector2f(Resolution.x, Resolution.y));
	sf::RectangleShape message(Vector2f(400, 200));
	background.setFillColor(Color(251, 248, 239, 150));
	message.setFillColor(Color(187, 173, 160, 200));
	message.setPosition((Resolution.y - 200) / 2, (Resolution.x - 400) / 2);
	Font font;
	font.loadFromFile("fonts/arial.ttf");
	Text MessageText(" You Win!\n", font, 30), MText("You can continue this game\n     to reach better score", font, 20), YesText("Yes", font, 20);
	MText.setStyle(sf::Text::Bold);
	MessageText.setFillColor(sf::Color::Green);
	YesText.setFillColor(sf::Color::White);
	MessageText.setStyle(sf::Text::Bold);
	YesText.setStyle(sf::Text::Bold);
	MText.setStyle(sf::Text::Bold);

	MessageText.setPosition((Resolution.y - 200) / 2 + 130, (Resolution.x - 400) / 2 + 30);
	MText.setPosition((Resolution.y - 200) / 2 + 60, (Resolution.x - 400) / 2 + 80);
	YesText.setPosition((Resolution.y - 200) / 2 + 180, (Resolution.x - 400) / 2 + 150);

	if (IntRect((Resolution.y - 200) / 2 + 180, (Resolution.x - 400) / 2 + 150, 35, 25).contains(Mouse::getPosition(window))) {
		YesText.setFillColor(Color(239, 97, 0));
		if (Mouse::isButtonPressed(Mouse::Left)) {
			isMessage = false;
			messageCode = 0;
		}
	}


	window.draw(background);
	window.draw(message);
	window.draw(MessageText);
	window.draw(MText);
	window.draw(YesText);

}

void NoSaveMessage(sf::RenderWindow &window, sf::Vector2i Resolution, bool &isMessage) {

	sf::RectangleShape background(Vector2f(Resolution.x, Resolution.y));
	sf::RectangleShape message(Vector2f(400, 200));
	background.setFillColor(Color(251, 248, 239, 150));
	message.setFillColor(Color(187, 173, 160, 200));
	message.setPosition((Resolution.y - 200) / 2, (Resolution.x - 400) / 2);
	Font font;
	font.loadFromFile("fonts/arial.ttf");
	Text MText("You don't have game to load!", font, 20), YesText("Yes", font, 20);
	MText.setStyle(sf::Text::Bold);
	YesText.setFillColor(sf::Color::White);
	YesText.setStyle(sf::Text::Bold);
	MText.setStyle(sf::Text::Bold);

	MText.setPosition((Resolution.y - 200) / 2 + 60, (Resolution.x - 400) / 2 + 60);
	YesText.setPosition((Resolution.y - 200) / 2 + 180, (Resolution.x - 400) / 2 + 150);

	if (IntRect((Resolution.y - 200) / 2 + 180, (Resolution.x - 400) / 2 + 150, 35, 25).contains(Mouse::getPosition(window))) {
		YesText.setFillColor(Color(239, 97, 0));
		if (Mouse::isButtonPressed(Mouse::Left)) {
			isMessage = false;
		}
	} 

	if (Keyboard::isKeyPressed(Keyboard::Y)) {
		YesText.setFillColor(Color(239, 97, 0));
		isMessage = false;
	}

	window.draw(background);
	window.draw(message);
	window.draw(MText);
	window.draw(YesText);

}

bool CheckFile() {
	FILE *filesave = NULL;
	bool flag = false;

	if (filesave = fopen("save/game.svf", "rb")) {
		flag = true;
		fclose(filesave);
	}

	return flag;
}

void ShowScoreFile() {

	FILE *filescore = NULL;
	int *scoremas, size;

	if (filescore = fopen("save/score.svf", "rb")) {
		fread(&size, sizeof(int), 1, filescore);
		scoremas = new int[size];
		fread(scoremas, sizeof(int), size, filescore);
		std::cout << size << std::endl;
		std::cout << "-------" << std::endl;
		for (int i = 0; i < size; i++) {
			std::cout << scoremas[i] << std::endl;
		}
		std::cout << "-------" << std::endl;
		fclose(filescore);
	}

}


