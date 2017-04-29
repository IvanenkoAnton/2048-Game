/*******************************************************************************
    Game 2048, Alpha Version
	Created by Anton Ivanenko,January 2017
	I wrote this to train using SFML Graphics library
*******************************************************************************/

#pragma once

#include <SFML/Graphics.hpp>
#include "Field.h"

void SaveMessage(sf::RenderWindow &, sf::Vector2i, bool &, bool &);

void LoseMessage(sf::RenderWindow &, sf::Vector2i, Field &, bool &, bool &, int &);

void WinMessage(sf::RenderWindow &, sf::Vector2i, bool &, int &);

void NoSaveMessage(sf::RenderWindow &, sf::Vector2i, bool &);

bool CheckFile();

void ShowScoreFile();
