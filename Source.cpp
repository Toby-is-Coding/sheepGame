#include <iostream>
#include <windows.h>
#include <time.h>
#include <conio.h>
#include <vector>
#include <thread>
#include <conio.h>
#include <chrono>
//COLOUR DEFINITIONS
#define CYN "\x1B[36m"
#define YLW "\x1B[33m"
#define GRN "\x1B[32m"
#define RED "\x1B[31m"
#define MAG "\x1B[35m"
#define WHT "\x1B[37m"
#define NRM "\x1B[0m"
//OTHER DEFINITIONS
#define waitMilli(numOfMilliseconds) this_thread::sleep_for(chrono::milliseconds(numOfMilliseconds));

//HOW TO SNAKE
//function for getting wasd input
//function for snake stuff
//function for random placements of food
//settings function
//pretty function

using namespace std;

void wasdInput();
void whereIsFood();
void display();

const int x_BOARD_SIZE = 200; //200
const int y_BOARD_SIZE = 46; //46

bool gameOver;

#define MIDDLE_OF_BOARD(forInt, halfOfSentence) for(int forInt = 0; forInt<=x_BOARD_SIZE/2-halfOfSentence; forInt++) {cout<<' ';} //devides board length by 2, minus length of following sentence, to get to middle of board

int x_Food;
int y_Food;

int x_RedSheep;
int y_RedSheep;
int length_RedSheep;

void wasdInput()
{
	char buttonPressed = ' ';
	char currentDirection = ' ';
	while (!gameOver) {
		if (_kbhit()) { //if keyboard pressed
			buttonPressed = _getch(); //get button pressed
		}
		if (buttonPressed == 'w' || buttonPressed == 'a' || buttonPressed == 's' || buttonPressed == 'd') {
			currentDirection = buttonPressed; //saves direction
		}
		switch (currentDirection) {
		case 'w':
			y_RedSheep -= 1;
			break;
		case 'a':
			x_RedSheep -= 1;
			break;
		case 's':
			y_RedSheep += 1;
			break;
		case 'd':
			x_RedSheep += 1;
			break;
		default:
			break;
		}
		waitMilli(300)
	}
}

int main()
{
	srand(time(NULL)); //gets the time at the time of use to configure rand function

	thread wasdInput(wasdInput);

	x_RedSheep = 100;
	y_RedSheep = 23;
	whereIsFood();
	while (!gameOver) {
		display();
		cout << x_RedSheep << ' ' << y_RedSheep;
		waitMilli(300)
	}
	return 0;
}

void whereIsFood()
{
	bool validLocation = false;
	while (validLocation == false) {
		x_Food = rand() % (x_BOARD_SIZE-2) + 1; //devides random number by x_BOARD_SIZE and saves the remainder (accounting for walls) in x_Food
		y_Food = rand() % (y_BOARD_SIZE-2) + 1; //devides random number by y_BOARD_SIZE and saves the remainder (accounting for walls) in y_Food
		if (x_Food != x_RedSheep && y_Food != y_RedSheep) { //unless food spawned on in the same spot as player, location is valid
			validLocation = true;
		}
	}
	return;
}

void display()
{
	system("cls");
	cout << "     ";
	MIDDLE_OF_BOARD(y, 5)
	cout << CYN << "SHEEP GAME" << NRM << endl;
	for (int i = 0; i < y_BOARD_SIZE; i++) { //FOR EVERY X LINE
		cout << "     "; //aligning the board to middle of screen
		for (int j = 0; j < x_BOARD_SIZE; j++) { //FOR EVERY Y LINE
			if (i == y_BOARD_SIZE - 1 && (j == 0 || j == x_BOARD_SIZE - 1)) {
				cout << WHT << '|' << NRM; //changes bottom right & left corners
			}
			else if (i == 0 || i == y_BOARD_SIZE - 1) {
				cout << WHT << '_' << NRM; //y walls (ceiling & floor)
			}
			else if (j == 0 || j == x_BOARD_SIZE - 1) {
				cout << WHT << '|' << NRM; //x walls
			}
			else if (j == x_RedSheep && i == y_RedSheep) {
				cout << RED << 'O' << NRM;
			}
			else if (j == x_Food && i == y_Food) {
				cout << GRN << 'B' << NRM;
			}
			else {
				cout << ' ';
			}
		}
		cout << endl;
	}
}
