/*******************************************************************************
    Game 2048, Alpha Version
	Created by Anton Ivanenko,January 2017
	I wrote this to train using SFML Graphics library
*******************************************************************************/

#include "Field.h"
#include <cstdlib>
#include <ctime>
#include <cstdlib>


Field::Field(sf::Vector2i Resolution, int NewSize){

	size = NewSize;
	Score = 0;
	PrevScore = 0;
	BestScore = OpenFileScore();
	fieldMas = NULL;
	fieldImage.loadFromFile("images/2048Field.jpg");
	fieldTexture.loadFromImage(fieldImage);
	fieldSprite.setTexture(fieldTexture);
	fieldSprite.setTextureRect(sf::IntRect(0,0,548,549));
	x = (Resolution.x - 548) / 2;
	y = (Resolution.y - 549) / 2;
	fieldSprite.setPosition(x,y);

	numbersImage.loadFromFile("images/numbers.jpg");
	numbersTexture.loadFromImage(numbersImage);
	numbersSprite.setTexture(numbersTexture);

	fieldMas = (int **)malloc(size * sizeof(int*));
	for (int i = 0; i < size; i++) {
		fieldMas[i] = (int *)malloc(size * sizeof(int));
	}

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			fieldMas[i][j] = 0;
		}
	}

	PreviousState = (int **)malloc(size * sizeof(int*));
	for (int i = 0; i < size; i++) {
		PreviousState[i] = (int *)malloc(size * sizeof(int));
	}

	RandGenerate24();
	RandGenerate24();

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			PreviousState[i][j] = fieldMas[i][j];
		}
	}
}

int Field::GetScore() {
	return Score;
}

int Field::GetBestScore() {
	return BestScore;
}

int Field::OpenFileScore() {

	FILE *filescore = NULL;
	int sizef, scoremas;
	int max = 0;

	filescore = fopen("save/score.svf", "rb");
	if (filescore) {
		fread(&sizef, sizeof(int), 1, filescore);
		for (int i = 0; i < sizef; i++) {
			fread(&scoremas, sizeof(int), 1, filescore);
			if (scoremas > max) {
				max = scoremas;
			}
		}
		fclose(filescore);
	}

	return max;

}

int Field::GetCoordinateX() {
	return x;
}

int Field::GetCoordinateY() {
	return y;
}

void Field::RandGenerate24() {
	int i, j;
	float prob;
	srand(time(NULL));
	do {
		i = rand() % size;
		j = rand() % size;
	} while (fieldMas[i][j] != 0);
	prob = (float)( 1 + rand() % 100) / 100 ;
	if (prob <= 0.1) {
		fieldMas[i][j] = 4;
	}
	else {
		fieldMas[i][j] = 2;
	}
}

void Field::Move(int dir) {
	/* vector,which keeps state of cell. If 1, this cell has already been created, cant create new*/
	int status[4];
	bool movement = false;
	switch (dir) {
		// Right
	case 0: {
		for (int i = 0; i < size; i++) {
		    for (int t = 0; t < size; t++) status[t] = 0;
			for (int  j = 0; j < size - 1; j++) {
				for (int k = size - 2; k >= j; k--) {
					if ((fieldMas[i][k] == fieldMas[i][k + 1]) && (fieldMas[i][k] != 0) && (status[k + 1] == 0) && (status[k] == 0)) {
						fieldMas[i][k + 1] += fieldMas[i][k];
						Score += fieldMas[i][k + 1];
						fieldMas[i][k] = 0;
						status[k + 1] = 1;
						movement = true;
					}
					if (fieldMas[i][k + 1] == 0){
						if (fieldMas[i][k] != 0) {
							movement = true;
						}
						fieldMas[i][k + 1] = fieldMas[i][k];
						fieldMas[i][k] = 0;
					}
				}
			}
		}
		break;
	}
			//Left
	case 1: {
		for (int i = 0; i < size; i++) {
			for (int t = 0; t < size; t++) status[t] = 0;
			for (int j = size - 1; j > 0; j--) {
				for (int k = 1; k <= j; k++) {
					if ((fieldMas[i][k] == fieldMas[i][k - 1]) && (fieldMas[i][k] != 0) && (status[k - 1] == 0) && (status[k] == 0)) {
						fieldMas[i][k - 1] += fieldMas[i][k];
						Score += fieldMas[i][k - 1];
						fieldMas[i][k] = 0;
						status[k - 1] = 1;
						movement = true;
					}
					if (fieldMas[i][k - 1] == 0)  {
						if (fieldMas[i][k] != 0) {
							movement = true;
						}
						fieldMas[i][k - 1] = fieldMas[i][k];
						fieldMas[i][k] = 0;
					}
				}
			}
		}
		break;
	}
			//Up
	case 2: {
		for (int j = 0; j < size; j++) {
			for (int t = 0; t < size; t++) status[t] = 0;
			for (int i = size - 1; i > 0 ; i--) {
				for (int k = 1; k <= i; k++) {
					if ((fieldMas[k][j] == fieldMas[k - 1][j]) && (fieldMas[k][j] != 0) && (status[k - 1] == 0) && (status[k] == 0)) {
						fieldMas[k - 1][j] += fieldMas[k][j];
						Score += fieldMas[k - 1][j];
						fieldMas[k][j] = 0;
						status[k - 1] = 1;
						movement = true;
					}
					if (fieldMas[k - 1][j] == 0){
						if (fieldMas[k][j] != 0) {
							movement = true;
						}
						fieldMas[k - 1][j] += fieldMas[k][j];
						fieldMas[k][j] = 0;
					}
				}
			}
		}
		break;
	}
			//Down
	case 3: {
		for (int j = 0; j < size; j++) {
			for (int t = 0; t < size; t++) status[t] = 0;
			for (int i = 0; i < size - 1; i++) {
				for (int k = size - 2; k >= i; k--) {
					if ((fieldMas[k][j] == fieldMas[k + 1][j]) && (fieldMas[k][j] != 0) && (status[k + 1] == 0) && (status[k] == 0)) {
						fieldMas[k + 1][j] += fieldMas[k][j];
						Score += fieldMas[k + 1][j];
						fieldMas[k][j] = 0;
						status[k + 1] = 1;
						movement = true;
					}
					if (fieldMas[k + 1][j] == 0) {
						if (fieldMas[k][j] != 0) {
							movement = true;
						}
						fieldMas[k + 1][j] += fieldMas[k][j];
						fieldMas[k][j] = 0;
					}
				}
			}
		}
		break;
	}
	}
	if (movement) {
		RandGenerate24();
	}
}

void Field::Update(int dir,sf::RenderWindow &window) {

	if (dir >= 0) {
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				PreviousState[i][j] = fieldMas[i][j];
			}
		}
		PrevScore = Score;
		Move(dir);
	}
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			numbersSprite.setPosition(fieldSprite.getPosition().x + 22 + 15 * (j + 1) + 106 * j, fieldSprite.getPosition().y + 22 + 15 * (i + 1) + 106 * i);
			switch(fieldMas[i][j]){
			case 2: {numbersSprite.setTextureRect(sf::IntRect(0, 0, 106, 105));	window.draw(numbersSprite); break;}
			case 4: {numbersSprite.setTextureRect(sf::IntRect(107, 0, 106, 105)); window.draw(numbersSprite); break; }
			case 8: {numbersSprite.setTextureRect(sf::IntRect(214, 0, 106, 105)); window.draw(numbersSprite); break; }
			case 16: {numbersSprite.setTextureRect(sf::IntRect(321, 0, 106, 105)); window.draw(numbersSprite); break; }
			case 32: {numbersSprite.setTextureRect(sf::IntRect(428, 0, 106, 105)); window.draw(numbersSprite); break; }
			case 64: {numbersSprite.setTextureRect(sf::IntRect(0, 106, 106, 105)); window.draw(numbersSprite); break; }
			case 128: {numbersSprite.setTextureRect(sf::IntRect(107, 106, 106, 105)); window.draw(numbersSprite); break; }
			case 256: {numbersSprite.setTextureRect(sf::IntRect(214, 106, 106, 105)); window.draw(numbersSprite); break; }
			case 512: {numbersSprite.setTextureRect(sf::IntRect(321, 106, 106, 105)); window.draw(numbersSprite); break; }
			case 1024: {numbersSprite.setTextureRect(sf::IntRect(428, 106, 106, 105)); window.draw(numbersSprite); break; }
			case 2048: {numbersSprite.setTextureRect(sf::IntRect(0, 212, 106, 105)); window.draw(numbersSprite); break; }
			case 4096: {numbersSprite.setTextureRect(sf::IntRect(107, 212, 106, 105)); window.draw(numbersSprite); break; }
			case 8192: {numbersSprite.setTextureRect(sf::IntRect(214, 212, 106, 105)); window.draw(numbersSprite); break; }
			case 16384: {numbersSprite.setTextureRect(sf::IntRect(321, 212, 106, 105)); window.draw(numbersSprite); break; }
			case 32768: {numbersSprite.setTextureRect(sf::IntRect(428, 212, 106, 105)); window.draw(numbersSprite); break; }
			case 65536: {numbersSprite.setTextureRect(sf::IntRect(0, 318, 106, 105)); window.draw(numbersSprite); break; }
			}
		}
	}
}

bool Field::CheckGame() {

	if (CheckEmptyCell()) {
		return true;
	}
	else {
		return HaveMove();
	}

}

bool Field::CheckEmptyCell() {
	bool flag = false;
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (fieldMas[i][j] == 0) {
				flag = true;
			}
		}
	}

	return flag;
}

bool Field::HaveMove() {

	bool flag = false;
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size - 1; j++) {
			if (fieldMas[i][j] == fieldMas[i][j + 1]) {
				flag = true;
			}
		}
	}
	for (int j = 0; j < size; j++) {
		for (int i = 0; i < size - 1; i++) {
			if (fieldMas[i][j] == fieldMas[i + 1][j]) {
				flag = true;
			}
		}
	}

	return flag;
}

void Field::StepBack() {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			fieldMas[i][j] = PreviousState[i][j];
		}
	}
	Score = PrevScore;
}

void Field::Restart() {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			fieldMas[i][j] = 0;
		}
	}

	RandGenerate24();
	RandGenerate24();

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			PreviousState[i][j] = fieldMas[i][j];
		}
	}

	Score = 0;
	PrevScore = 0;
}

void Field::SaveFileScore() {

	FILE *filescore = NULL;
	int sizef, *scoremas = NULL;
	int minidx, min;

	filescore = fopen("save/score.svf", "rb+");
	if (filescore) {
		fread(&sizef, sizeof(int), 1, filescore);
		if (sizef >= 10) {
			scoremas = new int[sizef];
			fread(scoremas, sizeof(int), sizef, filescore);
			min = scoremas[0];
			minidx = 0;
			for (int i = 1; i < sizef; i++) {
				if (scoremas[i] < min) {
					min = scoremas[i];
					minidx = i;
				}
			}
			if (Score > scoremas[minidx]) {
				scoremas[minidx] = Score;
			}
			fseek(filescore, 0, SEEK_SET);
			fwrite(&sizef, sizeof(int), 1, filescore);
			fwrite(scoremas, sizeof(int), size, filescore);
			delete[] scoremas;
		}
		else {
			sizef++;
			fseek(filescore, 0, SEEK_SET);
			fwrite(&sizef, sizeof(int), 1, filescore);
			fseek(filescore, 0, SEEK_END);
			fwrite(&Score, sizeof(int), 1, filescore);
		}
		fclose(filescore);
	}
	else {
		sizef = 1;
		filescore = fopen("save/score.svf", "wb");
		fwrite(&sizef, sizeof(int), 1,filescore);
		fwrite(&Score, sizeof(int), 1, filescore);
		fclose(filescore);
	}

}

void Field::CheckScore() {

	if (Score > BestScore) {
		BestScore = Score;
	}
}

void Field::SaveToFile() {

	FILE *filesave = NULL;

	filesave = fopen("save/game.svf", "wb");
	fwrite(&Score, sizeof(int), 1, filesave);
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			fwrite(&fieldMas[i][j], sizeof(int), 1, filesave);
		}
	}
	fclose(filesave);

}

void Field::LoadFromFile() {

	FILE *filesave = NULL;

	if (filesave = fopen("save/game.svf", "rb")) {
		fread(&Score, sizeof(int), 1, filesave);
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				fread(&fieldMas[i][j], sizeof(int), 1, filesave);
				PreviousState[i][j] = fieldMas[i][j];
			}
		}
		PrevScore = Score;
		fclose(filesave);
	}
}

bool Field::Check2048() {

	bool flag = false;

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (fieldMas[i][j] == 2048) {
				flag = true;
			}
		}
	}

	return flag;
}

Field::~Field(){

}
