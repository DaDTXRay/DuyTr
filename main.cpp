#include <iostream>
#include <conio.h>
#include <windows.h>
#include "input.h"
using namespace std;
bool gameOver;
const int width = 20;
const int height = 20;
int x, y, fruitX, fruitY, score;
int tailX[400], tailY[400];
int tailLength;
enum eDirection { STOP = 0,LEFT,RIGHT,UP,DOWN};
eDirection dir;
void Setup()
{
	srand(time(0));
	gameOver = false;
	dir = STOP;
	x = width / 2;
	y = height / 2;
	fruitX = rand() % width;
	fruitY = rand() % height;
	score = 0;
}
void Draw()
{
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0,0 });
	for (int i = 0; i < width+2; i++)
	{
		cout << "#";
	}
	cout << "\n";
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (j == 0)
			{
				cout << "#";
			}
			if (i == y && j == x)
			{
				cout << "O";
			}
			else if (i == fruitY && j == fruitX)
			{
				cout << "a";
			}
			else
			{
				bool printTail = false;
				for (int t = 0; t < tailLength; t++)
				{
					if (tailX[t] == j && tailY[t] == i)
					{
						cout << "o";
						printTail = true;
					}
					
				}
				if (!printTail)
					cout << " ";
				
				
			}
			if (j == width-1)
			{
				cout << "#";
			}
		}
		cout << "\n";
	}
	for (int i = 0; i < width+2; i++)
	{
		cout << "#";
	}
	cout << "\n";
	cout << "Score: \n" << score;

}
void Input()
{
	if (_kbhit())
	{
		switch (_getch())
		{
		case 'w':
			dir = UP;
			break;
		case 's':
			dir = DOWN;
			break;
		case 'a':
			dir = LEFT;
			break;
		case 'd':
			dir = RIGHT;
			break;
		case 'x':
			gameOver=true;
			break;
		}
	}
}
void Logic()
{
	int prevX = tailX[0];
	int prevY = tailY[0];
	int prev2X, prev2Y;
	tailX[0] = x;// the first segment follow the X cordinate of the head
	tailY[0] = y; // the first segment follow the Y cordinate of the head
	for (int i = 1; i < tailLength; i++)
	{
		prev2X = tailX[i];
		prev2Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}

	switch (dir)
	{
	case UP:
		y--;
		STOP;
		break;
	case DOWN:
		y++;
		break;
	case LEFT:
		x--;
		break;
	case RIGHT:
		x++;
		break;
	default:
		break;
	}
	if (x < 0) x = width - 1; if (x > width) x = 0;
	if (y < 0) y = height - 1; if (y > height) y = 0;
	for (int i = 0; i < tailLength; i++)
	{
		if (tailX[i] == x && tailY[i] == y)
		{
			cout << "\n\tYou've eaten yourself.GAME OVER!\n";
			gameOver = true;
		}
	}
	if (x == fruitX && y == fruitY)
	{

		score += 10;
		fruitX = rand() % width;
		fruitY = rand() % height;
		tailLength++;
	}
}
int main()
{
	do
	{
		system("cls");
		cout << "\nWelcome to my snake game(DT). 01/03/2024";
		cout << "\n---------------------------------------------------\n";
		cout << "\nChoose game difficulty: \n";
		cout << "\n\tA.Easy";
		cout << "\n\tB.Medium";
		cout << "\n\tC.Hard";
		cout << "\n---------------------------------------------------\n";
		cout << "\n\tE.Exit";

		switch (toupper(inputChar("\n\tOption: ", static_cast<string>("ABCE"))))
		{
		case'E':exit(0);
		//Bug: The game froze at the previous "Game over screen" when choose another option.
		case'A':
		{
			system("cls");
			gameOver = false;
			Setup();
			while (!gameOver)
			{
				Draw();
				Input();
				Logic();
				Sleep(100);
			}
			system("pause");
			break;
			
		}
		case 'B':
		{
			system("cls");
			gameOver = false;
			Setup();
			while (!gameOver)
			{
				Draw();
				Input();
				Logic();
				Sleep(50);
			}
			
			break;
		}
		case'C':
		{
			system("cls");
			gameOver = false;
			Setup();
			while (!gameOver)
			{
				Draw();
				Input();
				Logic();
				Sleep(25);
			}
			break;
		}
		}



		
	} while (true);
	return 0;
}