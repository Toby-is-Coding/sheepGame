#include <iostream>
#include <windows.h>
#include <time.h>
#include <conio.h>
#include <vector>
#include <thread>
//COLOUR DEFINITIONS
#define CYN "\x1B[36m"
#define YLW "\x1B[33m"
#define GRN "\x1B[32m"
#define RED "\x1B[31m"
#define MAG "\x1B[35m"
#define WHT "\x1B[37m"
#define NRM "\x1B[0m"

//HOW TO SNAKE
//function for getting wasd input
//function for snake stuff
//function for random placements of food
//settings function
//pretty function

using namespace std;

char wasdInput();
void snakery();
void whereIsFood();
void display();

const int x_BOARD_SIZE = 200;
const int y_BOARD_SIZE = 45;

#define MIDDLE_OF_BOARD(forInt, halfOfSentence) for(int forInt = 0; forInt<=x_BOARD_SIZE/2-halfOfSentence; forInt++) {cout<<' ';} //copyPasteCode

int x_Food;
int y_Food;

int x_RedSheep;
int y_RedSheep;
int length_RedSheep;

int main()
{
	x_RedSheep = 70; //DEBUG
	y_RedSheep = 44; //DEBUG
	display(); //DEBUG
	return 0;
}

void display()
{
	cout << "     ";
	MIDDLE_OF_BOARD(y, 5);
	cout << CYN << "SHEEP GAME" << NRM << endl;
	for (int i = 0; i < y_BOARD_SIZE; i++) { //FOR EVERY X LINE
		cout << "     ";
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
			else if (j == x_RedSheep -1 && i == y_RedSheep -1) { //DOESN'T WORK
				cout << RED << 'O' << NRM << endl;
			}
			else {
				cout << ' ';
			}
		}
		cout << endl;
	}
}
