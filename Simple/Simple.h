// Simple.h : Include file for standard system include files,
// or project specific include files.

#pragma once
#include <iostream>
#include <cstdlib>
#include <chrono>
#include <thread>
#include <windows.h>
#include <time.h>



using namespace std;

class Cell {
public:

	int y, x;				// Coordinates of given cell
	Cell* next;				// Pointer to next cell

	Cell(int X, int Y) {

		x = X;
		y = Y;
		next = NULL;
	}
};

class Snake {
public:
	// First cell in the list
	Cell* head;

	// Initialize a Snake in specific place
	Snake(int X, int Y) {
		head = new Cell(X, Y);

	}

	// moving head in given direction
	void moveHead(int direction) {
		int newX = head->x;
		int newY = head->y;


		// Logic for snake to pass the walls v
		switch (direction)
		{
		case VK_UP: {
			newY--;
			break;
		}
		case VK_DOWN: {
			newY++;
			break;
		}
		case VK_LEFT: {
			newX--;
			break;
		}
		case VK_RIGHT: {
			newX++;
			break;
		}
		}
		if (newX >= 10) {
			newX = newX % 10;
		}
		if (newY >= 10) {
			newY = newY % 10;
		}
		if (newX < 0) {
			newX = 10 + newX;
		}
		if (newY < 0) {
			newY = 10 + newY;
		}
		// Logic for snake to pass the walls ^

		Cell* newHead = new Cell(newX, newY);
		newHead->next = head;
		head = newHead;
	}

	//returing position and deleting tail 
	int* del() {

		Cell* buffer = head;
		int coordinates[2]; //Will it dissapear?

		while (buffer->next->next != NULL)
		{
			buffer = buffer->next;
		}

		coordinates[0] = buffer->next->y;
		coordinates[1] = buffer->next->x;

		delete buffer->next;
		buffer->next = NULL;
		return coordinates;
	}




	// Get rid of all cells when deleting the object
	~Snake() {

		Cell* buffer = head->next;
		Cell* holder = NULL;

		while (buffer != NULL) {

			holder = buffer->next;
			delete buffer;
			buffer = holder;

		}
	}
};



					
// The board on which the game is played
class Board {
public:
	int size =10 ;
	char matrix[10][10];		//	TODO: Dynamic array allocation
	char background;			// Character making the board

	Board() {

		background = ' ';

		for (int i = 0; i < size; i++) {
			

			for (int j = 0; j < size; j++) {
				matrix[i][j] = background;
			}
		}
	}
};




class Engine {
public:

	
	Board* board;
	Snake* snake;

	int direction;		// direction of next move
	int apple[2];		// position of the apple
	

	Engine() 
	{
		srand(time(NULL));

		snake = new Snake(rand() % 10, rand() % 10);
		board = new Board;
		direction = VK_UP;

		apple[0] = rand() % 10;
		apple[1] = rand() % 10;
	}

	// put apple on the board but not on a snake
	void putApple() 
	{
		Cell* buffer;
		int check = 0;

		srand(time(NULL));

		buffer = snake->head;
		apple[0] = rand() % 10;
		apple[1] = rand() % 10;
	}

	// Check if head touched the body or apple  (return: 0 if no, -1 if yes , 1 if apple)
	int headCheck() 
	{
		Cell* buffer = snake->head->next;
		while (buffer != NULL)
		{
			if (buffer->x == snake->head->x && buffer->y == snake->head->y) {
				return -1;
			}

			buffer = buffer->next;
		}

		if (snake->head->x == apple[1] && snake->head->y == apple[0]) {
			return 1;
		}

		return 0;	
	}
		


	// Update state of the matrix to new data
	int update()
	{
		int* blank = NULL;

		snake->moveHead(direction);
		switch (headCheck())
		{
		case 0:
			{
			 blank = snake->del();
			 board->matrix[blank[0]][blank[1]] = ' ';
			 break;
			}
		case 1:
			{
			putApple();
			break;
			}
		case -1:
			{
			return -1;
			}
		}

		board->matrix[apple[0]][apple[1]] = '*';
		board->matrix[snake->head->y][snake->head->x] = '#';
		
	}

	


	/// Print the board
	void print()
	{
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				cout << board->matrix[i][j];
			}

			cout << endl;
		}
	
	}


};




///////////////////////// Scrap yard\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\