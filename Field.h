/*******************************************************************************
    Game 2048, Alpha Version
	Created by Anton Ivanenko,January 2017
	I wrote this to train using SFML Graphics library
*******************************************************************************/

#pragma once

#include <SFML/Graphics.hpp>

class Field
{
	int size;
	int **fieldMas;
	int **PreviousState;
	int PrevScore,Score;
	int BestScore;
	int x, y;
	sf::Image fieldImage;
	sf::Texture fieldTexture;
	sf::Image numbersImage;
	sf::Texture numbersTexture;
	void RandGenerate24();
	void Move(int);
	bool CheckEmptyCell();
	bool HaveMove();
	int OpenFileScore();
public:
	Field(sf::Vector2i, int = 4);
	sf::Sprite fieldSprite;
	sf::Sprite numbersSprite;
	int GetScore();
	int GetBestScore();
	int GetCoordinateX();
	int GetCoordinateY();
	bool CheckGame();
	void Update(int, sf::RenderWindow &);
	void StepBack();
	void Restart();
	void SaveFileScore();
	void CheckScore();
	void SaveToFile();
	void LoadFromFile();
	bool Check2048();
	~Field();
};

