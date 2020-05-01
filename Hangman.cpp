#include <iostream>
#include "mygraphics.h"
#include <time.h>
#include <fstream>
#include <string>
using namespace std;

int Guess = 4, CharCount = 0, WrongChar = 0;

bool GameContinue = true;

void Shape()
{
	SetConsoleWindowDimensions(1280, 720);

	//board
	drawRectangle(800, 10, 1000, 20, 0, 0, 0, 210, 105, 30);

	//rope
	drawRectangle(902, 20, 908, 100, 0, 0, 0, 165, 42, 42);

	if (Guess < 4)
	{	//head
		drawEllipse(880, 100, 930, 160, 0, 0, 0, 245, 222, 179);
		drawEllipse(890, 120, 900, 130, 0, 0, 0, 255, 255, 255);
		drawEllipse(910, 120, 920, 130, 0, 0, 0, 255, 255, 255);
		drawLine(885, 140, 915, 140, 5, 5, 5);

		//neck
		drawRectangle(901, 160, 909, 200, 0, 0, 0, 245, 222, 179);

		if (Guess < 3)
		{
			//torso
			drawEllipse(870, 200, 940, 300, 0, 0, 0, 245, 222, 179);

			if (Guess < 2)
			{
				//left arm
				drawRectangle(820, 243, 870, 246, 245, 222, 179, 245, 222, 179);

				//right arm
				drawRectangle(940, 243, 990, 246, 245, 222, 179, 245, 222, 179);

				if (Guess < 1)
				{
					//right leg
					drawLine(910, 300, 940, 360, 245, 222, 179);

					//left leg
					drawLine(905, 300, 875, 360, 245, 222, 179);
				}
			}
		}
	}
}

void DisplayWord(char*& Word, char WrongAlphabetsUsed[], int size)
{
	gotoxy(0, 0);

	cout << "\t\t\tHANG-MAN\n\n\n\n";

	cout << "\tWRONG ALPHABETS USED : ";
	for (int i = 0; i < WrongChar; i++)
	{
		cout << WrongAlphabetsUsed[i] << " ";
	}

	cout << "\n\n\tGUESS THE WORD : ";
	for (int i = 0; i < size; i++)
	{
		cout << Word[i] << " ";
	}

	cout << "\n\n\tENTER A CHARACTER : ";
}

void CheckCharacter(const char CorrectWord[], char WrongAlphabetsUsed[], char*& Word, int size)
{
	bool CharFound = false, NewChar = true;
	char Input;

	cin >> Input;

	for (int i = 0; i < WrongChar; i++)
	{
		if (Input == WrongAlphabetsUsed[i])
		{
			cout << "\tCHARACTER ALREADY USED !";
			delay(500);
			NewChar = false;
			break;
		}
	}

	if (NewChar)
	{
		for (int i = 0; i < size; i++)
		{
			if (Input == CorrectWord[i] && Word[i] == '*')
			{
				CharCount++;
				Word[i] = Input;
				CharFound = true;
			}
			else if (Input == CorrectWord[i] && Word[i] != '*')
			{
				cout << "\tCHARACTER ALREADY FILLED !";
				delay(500);
				CharFound = true;
				break;
			}
		}

		if (!CharFound)
		{
			cout << "\tWRONG !";
			delay(500);
			Guess--;
			WrongAlphabetsUsed[WrongChar++] = Input;
		}
	}
}

void ReadFromFile(char*& CorrectWord)
{
	ifstream File;

	File.open("Words.txt");

	if (File.fail())
	{
		cout << "Error in File Opening\n";
	}

	else
	{
		srand(time(NULL));

		string Word;

		while (getline(File, Word))
		{
			// get random word from file.
			if (((rand() % 11) == 4) && ((rand() % 11) == 3))
			{
				CorrectWord = new char[Word.length() + 1];

				for (unsigned int i = 0; i < Word.length(); i++)
				{
					CorrectWord[i] = Word[i];
				}

				CorrectWord[Word.length()] = '\0';

				break;
			}
		}
	}
}

int main()
{
	char* CorrectWord = NULL;

	char WrongAlphabetsUsed[4] = {};

	ReadFromFile(CorrectWord);

	system("cls");

	int MapWordSize = strlen(CorrectWord);

	char* MapWord = new char[MapWordSize + 1];

	for (int i = 0; i < MapWordSize; i++)
	{
		MapWord[i] = '*';
	}

	MapWord[MapWordSize] = '\0';

	SetConsoleStyle(10, 20);

	while (GameContinue)
	{
		Shape();
		showConsoleCursor(0);
		DisplayWord(MapWord, WrongAlphabetsUsed, MapWordSize);
		delay(100);
		CheckCharacter(CorrectWord, WrongAlphabetsUsed, MapWord, MapWordSize);
		Shape();
		cls();

		if (Guess == 0)
		{
			gotoxy(10, 10);
			cout << "PLAYER DIED\n\n\n The Correct Word Was : " << CorrectWord << "\n\n\n\n\n";
			GameContinue = false;
		}

		if (CharCount == MapWordSize)
		{
			gotoxy(10, 10);
			cout << "PLAYER SAVED\n\n\n\n\n\n\n\n";
			GameContinue = false;
		}
	}

	delay(3000);
	return 0;
}


