//============================================================================
// Name        : Main.cpp
// Author      : Alberto Quesada
// Version     : 1.0
// Copyright   : Alberto Quesada @2021
// Description : Main program
//============================================================================

#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>

using namespace std;

//Variables
const int W = 20, H = 20;
int headPos[2], foodPos[2], score;
int tailPosX[100], tailPosY[100], tailLength;

enum directionEnum { STOP = 0, LEFT, RIGHT, UP, DOWN };
directionEnum snakeDirection;

bool finished;

//Methods
void init()
{
	finished = false;
	snakeDirection = STOP;
	headPos[0] = W /2;
	headPos[1] = H / 2;
	foodPos[0] = rand() % W;
	foodPos[1] = rand() % H;
	score = 0;
}


void render()
{
	system("cls"); //Linux -> system ("clear")

	//Render top
	for(int i = 0; i < W + 2; i++)
	{
		cout<<"#";
	}
	cout<<endl;

	//Render intermediate parts
	for(int i = 0; i < H; i++)
	{
		for(int j = 0; j < W; j++)
		{
			if(j == 0) //Left wall
				cout<<"#";

			if(j == headPos[0] && i == headPos[1]) //Snake head
				cout<<"O";

			else if(j == foodPos[0] && i == foodPos[1]) //Food
				cout<<"*";

			else
			{
				bool printTail = false;

				for(int k = 0; k < tailLength; k++) //Tail
				{

					if(tailPosX[k] == j && tailPosY[k] == i)
					{
						cout<<"o";
						printTail = true;
					}
				}

				if(!printTail) //White space
					cout<<" ";
			}

			if(j == W - 1) //Right wall
				cout<<"#";
		}

		cout<<endl;
	}

	//Render bottom
	for(int i = 0; i < W + 2; i++)
	{
		cout<<"#";
	}

	cout<<endl<<endl;

	cout<<"Score: "<<score<<endl;
}


void input()
{
	if(_kbhit()) //True if the user pressed a key
	{
		switch(_getch()) //Get the key pressed in keyboard
		{
			case 'a':
				snakeDirection = LEFT;
				break;
			case 'd':
				snakeDirection = RIGHT;
				break;
			case 'w':
				snakeDirection = UP;
				break;
			case 's':
				snakeDirection = DOWN;
				break;
			case 'q':
				finished = true;
				break;
		}
	}
}


void gameLogic()
{
	//Tail movement logic
	int prevTailPosX = tailPosX[0];
	int prevTailPosY = tailPosY[0];
	int prevTailPos2X, prevTailPos2Y;

	tailPosX[0] = headPos[0];
	tailPosY[0] = headPos[1];

	for(int i = 1; i < tailLength; i++)
	{
		prevTailPos2X = tailPosX[i];
		prevTailPos2Y = tailPosY[i];

		tailPosX[i] = prevTailPosX;
		tailPosY[i] = prevTailPosY;

		prevTailPosX = prevTailPos2X;
		prevTailPosY = prevTailPos2Y;
	}

	//Move the snake
	switch(snakeDirection)
	{
		case STOP:
			break;

		case LEFT:
			headPos[0]--;
			break;

		case RIGHT:
			headPos[0]++;
			break;

		case UP:
			headPos[1]--;
			break;

		case DOWN:
			headPos[1]++;
			break;
	}

	//Check collisions with the walls
	if(headPos[0] >= W || headPos[0] < 0 || headPos[1] >= H || headPos[1] < 0)
		finished = true;

	//Check collisions with the tail
	for(int i = 0; i < tailLength; i++)
	{
		if(tailPosX[i] == headPos[0] && tailPosY[i] == headPos[1])
			finished = true;
	}

	//Check if eaten
	if(headPos[0] == foodPos[0] && headPos[1] == foodPos[1])
	{
		score += 10;
		foodPos[0] = rand() % W;
		foodPos[1] = rand() % H;

		tailLength++;
	}
}


//Main
int main()
{
	srand(time(0));

	init();

	while(!finished)
	{
		render();
		Sleep(50); //Make the game slower

		input();
		gameLogic();
	}

	return 0;
}
