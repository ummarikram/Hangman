#include <iostream>
#include <Windows.h>
#include "mygraphics.h"
#include <time.h>
#include <fstream>
#include <sstream>
using namespace std;

int Guess = 4, CharCount = 0;

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
					drawLine(910, 300, 930, 360, 255);

					//left leg
					drawLine(905, 300, 885, 360, 255);
				}
			}
		}
	}

}

void DisplayWord(char*& Word, int size)
{
	cout << "GUESS THE WORD : ";
	for (int i = 0; i < size; i++)
	{
		cout << Word[i] << " ";
	}
}

void CheckCharacter(const char CorrectWord[], char*& Word, int size)
{
	bool CharFound = false;
	char Input;
	cout << "\n\nEnter a Character : ";
	cin >> Input;
	for (int i = 0; i < size; i++)
	{
		if (Input == CorrectWord[i])
		{
			CharCount++;
			Word[i] = Input;
			CharFound = true;
		}
	}

	if (!CharFound)
	{
		cout << "WRONG !";
		delay(300);
		Guess--;
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

	ReadFromFile(CorrectWord);

	system("cls");

	int MapWordSize = strlen(CorrectWord);

	char* MapWord = new char[MapWordSize + 1];

	for (int i = 0; i < MapWordSize; i++)
	{
		MapWord[i] = '*';
	}

	MapWord[MapWordSize] = '\0';

	fontsize(10, 20);

	while (GameContinue)
	{
		Shape();
		showConsoleCursor(0);
		gotoxy(0, 0);

		cout << "                        HANG-MAN" << endl;

		gotoxy(10, 10);
		DisplayWord(MapWord, MapWordSize);
		delay(1000);
		CheckCharacter(CorrectWord, MapWord, MapWordSize);
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

	cin.get();
	cin.get();

	return 0;
}


