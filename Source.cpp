#include <iostream>
#include <windows.h>
#include <time.h>
#include <conio.h>
#include <vector>
#include <thread>
#include <conio.h>
#include <chrono>
#include <vector>
//COLOUR DEFINITIONS
#define CYN "\x1B[36m"
#define YLW "\x1B[33m"
#define GRN "\x1B[32m"
#define RED "\x1B[31m"
#define MAG "\x1B[35m"
#define WHT "\x1B[37m"
#define NRM "\x1B[0m"
//OTHER DEFINITIONS
#define waitMilli(numOfMilliseconds) this_thread::sleep_for(chrono::milliseconds(numOfMilliseconds))

//HOW TO SNAKE
//function for getting wasd input
//function for snake stuff
//function for random placements of food
//settings function
//pretty function

void ClearScreen() {
	// Function which cleans the screen without flickering
	COORD cursorPosition;   cursorPosition.X = 0;   cursorPosition.Y = 0;   SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPosition);
}

using namespace std;

struct PieceOfTrail {
	int x;
	int y;
	bool vertical;
};
vector<PieceOfTrail> RedTrail;

void wasdInput();
void whereIsFood();
void display();
bool isOnScreen(int x, int y);
bool trailVertical();

const int x_BOARD_SIZE = 40; //200
const int y_BOARD_SIZE = 40; //46
char Background[x_BOARD_SIZE][y_BOARD_SIZE];
char Screen[x_BOARD_SIZE][y_BOARD_SIZE];

bool gameOver;

#define MIDDLE_OF_BOARD(halfOfSentence) for(int forInt = 0; forInt<=x_BOARD_SIZE/2-halfOfSentence; forInt++) {cout<<' ';} //devides board length by 2, minus length of following sentence, to get to middle of board

int x_Food;
int y_Food;

int x_RedSheep;
int y_RedSheep;
int length_RedSheep = 3;

void wasdInput()
{
	char buttonPressed = ' ';
	char currentDirection = ' ';
	char previousDirection = ' ';
	while (!gameOver) {
		if (_kbhit()) { //if keyboard pressed
			buttonPressed = _getch(); //get button pressed
			previousDirection = currentDirection; //saves last direction to limit next one
		}
		currentDirection = buttonPressed; //saves input as current direction

		//PieceOfTrail* newPiece = &*RedTrail.begin(); //makes pointer to newest piece of RedTrail
		//newPiece->x = x_RedSheep;
		//newPiece->y = y_RedSheep;

		switch (currentDirection) {
		case 'w':
			if (previousDirection != 's') {
				y_RedSheep -= 1;
			}
			else {
				currentDirection = previousDirection;
				y_RedSheep += 1;
			}
			//newPiece->vertical = true;
			break;
		case 'a':
			if (previousDirection != 'd') {
				x_RedSheep -= 1;
			}
			else {
				currentDirection = previousDirection;
				x_RedSheep += 1;
			}
			//newPiece->vertical = false;
			break;
		case 's':
			if (previousDirection != 'w') {
				y_RedSheep += 1;
			}
			else {
				currentDirection = previousDirection;
				y_RedSheep -= 1;
			}
			//newPiece->vertical = true;
			break;
		case 'd':
			if (previousDirection != 'a') {
				x_RedSheep += 1;
			}
			else {
				currentDirection = previousDirection;
				x_RedSheep -= +1;
			}
			//newPiece->vertical = false;
			break;
		default:
			break;
		}
		waitMilli(100);
	}
}

int main()
{
	srand(time(NULL)); //gets the time at the time of use to configure rand function

	thread wasdInput(wasdInput); //begins thread for wasdInput

	//create background
	for (int i = 0; i < y_BOARD_SIZE; i++) {
		for (int j = 0; j < x_BOARD_SIZE; j++) {
			Background[j][i] = ' '; //default background character

			if ((j == 0 && i == 0) || (j == x_BOARD_SIZE - 1 && i == 0)) {
				Background[j][i] = ' '; //changes top corners to spacebar
			}
			else if (j == 0 || j == x_BOARD_SIZE - 1)
				Background[j][i] = '|'; //vertical walls
			else if (i == 0 || i == y_BOARD_SIZE - 1)
				Background[j][i] = '_'; //horizontal walls
		}
	}

	x_RedSheep = x_BOARD_SIZE/2;
	y_RedSheep = y_BOARD_SIZE/2;
	whereIsFood();
	while (!gameOver) {
		display();
		cout << x_RedSheep << ' ' << y_RedSheep;
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
	memcpy(&Screen, &Background, sizeof(Screen)); //clears entities

	ClearScreen();
	cout << "     ";
	MIDDLE_OF_BOARD(5)
		cout << CYN << "SHEEP GAME" << NRM << endl;

	if (isOnScreen(x_RedSheep, y_RedSheep))
		Screen[x_RedSheep][y_RedSheep] = 'O'; //draw sheep if on screen
	Screen[x_Food][y_Food] = 'B'; //draw food yum yum

	for (int i = 0; i < y_BOARD_SIZE; i++) {
		cout << "     ";
		for (int j = 0; j < x_BOARD_SIZE; j++) {
			char currentCharacter = Screen[j][i];
			if (currentCharacter == 'O') //red sheep
				cout << RED << currentCharacter << NRM;
			else if (currentCharacter == 'B') //green food
				cout << GRN << currentCharacter << NRM;
			else //white walls
				cout << currentCharacter;
		}
		cout << endl;
	}

	/*vector<int> x_RedTrail;
	vector<int> y_RedTrail;

	ClearScreen();
	cout << "     ";
	MIDDLE_OF_BOARD(5)
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
				x_RedTrail.push_back(j); //saving x location for trail
				y_RedTrail.push_back(i); //saving y location for trail
				cout << RED << 'O' << NRM;
			}
			else for (int y = 0; y < length_RedSheep; y++) {
				if (j == x_RedTrail[y] && i == y_RedTrail[y]) {
					switch (red_TrailDirection[y]) { //prints trail based on direction
					case 'w':
					case 's':
						cout << RED << '|' << NRM;
						break;
					case 'a':
					case 'd':
						cout << RED << '-' << NRM;
						break;
					}
				}
				if (x_RedTrail.size() == length_RedSheep) { //if trail reached max size, erase back of trail
					x_RedTrail.erase(x_RedTrail.begin());
					y_RedTrail.erase(y_RedTrail.begin());
				}
			}
			else if (j == x_Food && i == y_Food) {
				cout << GRN << 'B' << NRM;
			}
			else {
				cout << ' ';
			}
		}
		cout << endl;
	}*/
}

bool isOnScreen(int x, int y)
{
	if (x < 0 || x > x_BOARD_SIZE - 1 || y < 0 || y > y_BOARD_SIZE - 1)
		return false;
	return true;
}

bool trailVertical()
{
	return true;
}
