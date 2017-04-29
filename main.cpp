
/*******************************************************************************
    Game 2048, Alpha Version
	Created by Anton Ivanenko,January 2017
	I wrote this to train using SFML Graphics library
*******************************************************************************/
#include <SFML/Graphics.hpp>

#include <iostream>
#include <sstream>
#include <cstdlib>
#include <windows.h>
#include "Field.h"
#include "Messages.h"

using namespace sf;

void menu(RenderWindow &, Vector2i);
void StartGame(RenderWindow &, Vector2i, bool);
void Score(RenderWindow &, Vector2i);
void Settings(RenderWindow &, Vector2i);

int main() {
	Vector2i Resolution = { 800, 600 };
	RenderWindow window(VideoMode(Resolution.x,Resolution.y), " Game 2048 ", Style::Close);
	FreeConsole();


	Image Icon;
	Icon.loadFromFile("images/2048.png");
	window.setIcon(512, 512, Icon.getPixelsPtr());

	menu(window,Resolution);

	return 0;
}

void menu(RenderWindow &window, Vector2i Resolution){

	Font font;
	font.loadFromFile("fonts/arial.ttf");
	std::string MenuItem[5] = { "Start", "Load", "Score", "Settings", "Exit" };
	Text MenuText[5];

	Image MenuImg;
	MenuImg.loadFromFile("images/Menu.jpg");
	Texture MenuTxt;
	MenuTxt.loadFromImage(MenuImg);
	Sprite MenuSprt;
	MenuSprt.setTexture(MenuTxt);
	MenuSprt.setPosition(300,100);

	bool isMenu = true;
	bool load = false;
	bool isMessage = false;
	int Position = 0;

	for (int i = 0; i < 5; i++) {
		MenuText[i].setFont(font);
		MenuText[i].setString(MenuItem[i]);
		MenuText[i].setCharacterSize(30);
		MenuText[i].setPosition(50,50 + 40*i);
	}
//	ShowScoreFile();

	while (isMenu) {

		window.clear(Color(251, 248, 239));

		for (int i = 0; i < 5; i++) {
			if (Position == i) {
				MenuText[i].setFillColor(Color(239, 97, 0));
			}
			else {
				MenuText[i].setFillColor(Color(189, 173, 160));
			}
		}

		Event event;
		while (window.pollEvent(event)) {

			if (event.type == Event::Closed) {
				isMenu = false;
				Position = 4;
				window.close();
			}

			if (!isMessage) {
				if (event.type == Event::KeyPressed) {
					if (event.key.code == Keyboard::Up) {
						Position--;
					}
					if (event.key.code == Keyboard::Down) {
						Position++;
					}
					if (event.key.code == Keyboard::Return) {
						isMenu = false;
					}
					if (event.key.code == Keyboard::Escape) {
						isMenu = false;
						Position = 4;
					}
				}
			}
		}

		if (!isMessage) {
			if (IntRect(50, 50, 80, 45).contains(Mouse::getPosition(window))) {
				Position = 0;
				if (Mouse::isButtonPressed(Mouse::Left)) {
					isMenu = false;
				}
			}
			if (IntRect(50, 90, 80, 45).contains(Mouse::getPosition(window))) {
				Position = 1;
				if (Mouse::isButtonPressed(Mouse::Left)) {
					isMenu = false;
				}
			}
			if (IntRect(50, 120, 80, 45).contains(Mouse::getPosition(window))) {
				Position = 2;
				if (Mouse::isButtonPressed(Mouse::Left)) {
					isMenu = false;
				}
			}
			if (IntRect(50, 160, 100, 45).contains(Mouse::getPosition(window))) {
				Position = 3;
				if (Mouse::isButtonPressed(Mouse::Left)) {
					isMenu = false;
				}
			}
			if (IntRect(50, 200, 70, 45).contains(Mouse::getPosition(window))) {
				Position = 4;
				if (Mouse::isButtonPressed(Mouse::Left)) {
					isMenu = false;
				}
			}
		}
	

		if (Position > 4) {
			Position = 0;
		}

		if (Position < 0) {
			Position = 4;
		}

		for (int i = 0; i < 5; i++) {
			window.draw(MenuText[i]);
		}

		window.draw(MenuSprt);

		if (!isMenu && Position == 1 && !CheckFile()) {
			isMenu = true;
			isMessage = true;
		}

		if (isMessage) {
			NoSaveMessage(window, Resolution, isMessage);
		}

		window.display();
	}

	switch (Position) {
	case 0: {StartGame(window, Resolution, load); break; }
	case 1: {load = true; StartGame(window, Resolution, load); break;}
	case 2: {Score(window, Resolution); break; }
	case 3: {Settings(window, Resolution); break; }
	}
}

void StartGame(RenderWindow &window, Vector2i Resolution, bool loadGame) {
	Field gamefield(Resolution);

	Font font;
	font.loadFromFile("fonts/arial.ttf");
	Text ScoreText("", font, 20), BestScoreText("", font, 20), RestartText("Restart", font, 20), StepBackText("Step Back", font, 20), MenuBackText("Quit", font, 20);
	ScoreText.setStyle(sf::Text::Bold);
	BestScoreText.setStyle(sf::Text::Bold);
	RestartText.setStyle(sf::Text::Bold);
	StepBackText.setStyle(sf::Text::Bold);
	MenuBackText.setStyle(sf::Text::Bold);
	ScoreText.setFillColor(Color(189, 173, 160));
	BestScoreText.setFillColor(Color(189, 173, 160));

	ScoreText.setPosition(gamefield.GetCoordinateX() - 110, gamefield.GetCoordinateY() - 15);
	BestScoreText.setPosition(gamefield.GetCoordinateX() + 200, gamefield.GetCoordinateY() - 15);
	RestartText.setPosition(gamefield.GetCoordinateX() - 110, gamefield.GetCoordinateY() + 530);
	StepBackText.setPosition(gamefield.GetCoordinateX() + 550, gamefield.GetCoordinateY() + 530);
	MenuBackText.setPosition(gamefield.GetCoordinateX() + 600, gamefield.GetCoordinateY() - 15);

	int direction, messageCode = 0;
	bool status2048 = false;

	bool isGame = true, ReturnMenu = true, isMessage = false;
	bool isEsc = false;
	bool saveFile = false;

	if (loadGame) {
		gamefield.LoadFromFile();
	}


	while (isGame) {

		if (!status2048 && gamefield.Check2048()) {
			isMessage = true;
			status2048 = true;
			messageCode = 3;
		}
		
		RestartText.setFillColor(Color(189, 173, 160));
		StepBackText.setFillColor(Color(189, 173, 160));
		MenuBackText.setFillColor(Color(189, 173, 160));
		direction = -1;
		window.clear(Color(251, 248, 239));
		Event event;

		gamefield.CheckScore();
		if (!gamefield.CheckGame()) {
			isMessage = true;
			messageCode = 2;
		}

		while (window.pollEvent(event)) {

			if (event.type == Event::Closed) {
				window.close();
				isGame = false;
				ReturnMenu = false;
			}
			if (event.type == Event::KeyReleased) {
				if (!isMessage) {
					if ((event.key.code == Keyboard::W) || (event.key.code == Keyboard::Up)) {
						direction = 2;
					}
					if ((event.key.code == Keyboard::S) || (event.key.code == Keyboard::Down)) {
						direction = 3;
					}
					if ((event.key.code == Keyboard::A) || (event.key.code == Keyboard::Left)) {
						direction = 1;
					}
					if ((event.key.code == Keyboard::D) || (event.key.code == Keyboard::Right)) {
						direction = 0;
					}
					if (event.key.code == Keyboard::R) {
						gamefield.Restart();
					}
					if (event.key.code == Keyboard::BackSpace) {
						gamefield.StepBack();
					}
				}
				if (event.key.code == Keyboard::Escape) {
					if (!isEsc) {
						messageCode = 1;
						isEsc = true;
						isMessage = true;
					}
					else {
						messageCode = 0;
						isEsc = false;
						isMessage = false;
					}
				}
			}
		}

		if (!isMessage) {
			if (Keyboard::isKeyPressed(Keyboard::R)) { RestartText.setFillColor(Color(239, 97, 0)); }
			if (Keyboard::isKeyPressed(Keyboard::BackSpace)) { StepBackText.setFillColor(Color(239, 97, 0)); }
			if (Keyboard::isKeyPressed(Keyboard::Escape)) { MenuBackText.setFillColor(Color(239, 97, 0)); }

			if (IntRect(gamefield.GetCoordinateX() - 110, gamefield.GetCoordinateY() + 530, 80, 25).contains(Mouse::getPosition(window))) {
				RestartText.setFillColor(Color(239, 97, 0));
				if (Mouse::isButtonPressed(Mouse::Left)) {
					gamefield.Restart();
				}
			}
			if (IntRect(gamefield.GetCoordinateX() + 550, gamefield.GetCoordinateY() + 530, 100, 25).contains(Mouse::getPosition(window))) {
				StepBackText.setFillColor(Color(239, 97, 0));
				if (Mouse::isButtonPressed(Mouse::Left)) {
					gamefield.StepBack();
				}
			}
			if (IntRect(gamefield.GetCoordinateX() + 600, gamefield.GetCoordinateY() - 15, 45, 25).contains(Mouse::getPosition(window))) {
				MenuBackText.setFillColor(Color(239, 97, 0));
				if (Mouse::isButtonPressed(Mouse::Left)) {
					messageCode = 1;
					isEsc = true;
					isMessage = true;
				}
			}
		}

		window.draw(gamefield.fieldSprite);
		gamefield.Update(direction, window);
		std::ostringstream PlayerScoreString, BestScoreString;
		PlayerScoreString << gamefield.GetScore();
		ScoreText.setString("Score: " + PlayerScoreString.str());
		BestScoreString << gamefield.GetBestScore();
		BestScoreText.setString("Best Score: " + BestScoreString.str());
		window.draw(ScoreText);
		window.draw(BestScoreText);
		window.draw(RestartText);
		window.draw(StepBackText);
		window.draw(MenuBackText);
		switch(messageCode) {
		case 1: {SaveMessage(window, Resolution, isGame, saveFile); break; }
		case 2: {LoseMessage(window, Resolution, gamefield, isGame, isMessage, messageCode); break; }
		case 3: {WinMessage(window, Resolution, isMessage, messageCode); break; }
		}
		window.display();

	}

	if (saveFile) {
		gamefield.SaveToFile();
	}

	if (ReturnMenu){
		gamefield.SaveFileScore();
		menu(window, Resolution);
	}
	
}

void Score(RenderWindow &window, Vector2i Resolution) {
	
	Font font;
	font.loadFromFile("fonts/arial.ttf");

	FILE *filescore = NULL;

	Text *ScoreText = NULL;
	std::ostringstream *ScoreString = NULL;
	Text ReturnText("Return", font, 25), ClearText("Clear", font, 25);
	Text NoText("Score file is empty", font, 20);
	Text SText("Score: ", font, 30);

	Image MenuImg;
	MenuImg.loadFromFile("images/Menu.jpg");
	Texture MenuTxt;
	MenuTxt.loadFromImage(MenuImg);
	Sprite MenuSprt;
	MenuSprt.setTexture(MenuTxt);
	MenuSprt.setPosition(300, 100);

	bool empty, isScore = true, Return = true;
	int size;
	int tmp;

	if (filescore = fopen("save/score.svf", "rb")) {
		fread(&size, sizeof(int), 1, filescore);
		SText.setFillColor(Color(189, 173, 160));
		SText.setPosition(40, 50);
		ScoreString = new std::ostringstream[size];
		ScoreText = new Text[size];
		for (int i = 0; i < size; i++) {
			fread(&tmp, sizeof(int), 1, filescore);
			ScoreString[i] << tmp;
			ScoreText[i].setFillColor(Color(189, 173, 160));
			ScoreText[i].setFont(font);
			ScoreText[i].setCharacterSize(20);
			ScoreText[i].setString(ScoreString[i].str());
			ScoreText[i].setPosition(40, 100 + 40 * i);
		}
		fclose(filescore);
		empty = false;
	}
	else {
		empty = true;
		NoText.setFillColor(Color(189, 173, 160));
		NoText.setPosition(40, 50);
	}

	ReturnText.setPosition(40, 550);
	ClearText.setPosition(40, 500);

	while (isScore) {

		window.clear(Color(251, 248, 239));
		ReturnText.setFillColor(Color(189, 173, 160));
		ClearText.setFillColor(Color(189, 173, 160));

		Event event;
		while (window.pollEvent(event)) {

			if (event.type == Event::Closed) {
				isScore = false;
				Return = false;
				window.close();
			}
		}

		if (!empty) {
			window.draw(SText);
			for (int i = 0; i < size; i++) {
				window.draw(ScoreText[i]);
			}
		}
		else {
			window.draw(NoText);
		}

		if (IntRect(ReturnText.getPosition().x, ReturnText.getPosition().y, 80, 35).contains(Mouse::getPosition(window))) {
			ReturnText.setFillColor(Color(239, 97, 0));
			if (Mouse::isButtonPressed(Mouse::Left)) {
				isScore = false;
			}
		}

		if (IntRect(ClearText.getPosition().x, ClearText.getPosition().y, 60, 35).contains(Mouse::getPosition(window))) {
			ClearText.setFillColor(Color(239, 97, 0));
			if (Mouse::isButtonPressed(Mouse::Left)) {
				remove("save/score.svf");
				isScore = false;
			}
		}

		window.draw(MenuSprt);
		window.draw(ReturnText);
		window.draw(ClearText);
		window.display();
	}

	if (Return) {
		menu(window, Resolution);
	}
}

void Settings(RenderWindow &window, Vector2i Resolution) {

	Font font;
	font.loadFromFile("fonts/arial.ttf");

	FILE *filescore = NULL;

	Text *ScoreText = NULL;
	std::ostringstream *ScoreString = NULL;
	Text ReturnText("Return", font, 25);
	Text NoText("Score file is empty", font, 20);
	Text SText("Settings: ", font, 30);

	Image MenuImg;
	MenuImg.loadFromFile("images/Menu.jpg");
	Texture MenuTxt;
	MenuTxt.loadFromImage(MenuImg);
	Sprite MenuSprt;
	MenuSprt.setTexture(MenuTxt);
	MenuSprt.setPosition(300, 100);

	bool empty, isSettings = true, Return = true;
	int size;
	int tmp;

	ReturnText.setPosition(40, 550);
	SText.setPosition(50,50);
	SText.setFillColor(Color(189, 173, 160));

	while (isSettings) {

		window.clear(Color(251, 248, 239));
		ReturnText.setFillColor(Color(189, 173, 160));

		Event event;
		while (window.pollEvent(event)) {

			if (event.type == Event::Closed) {
				isSettings = false;
				Return = false;
				window.close();
			}
		}


		if (IntRect(ReturnText.getPosition().x, ReturnText.getPosition().y, 80, 35).contains(Mouse::getPosition(window))) {
			ReturnText.setFillColor(Color(239, 97, 0));
			if (Mouse::isButtonPressed(Mouse::Left)) {
				isSettings = false;
			}
		}

		window.draw(MenuSprt);
		window.draw(ReturnText);
		window.draw(SText);
		window.display();
	}

	if (Return) {
		menu(window, Resolution);
	}
}
