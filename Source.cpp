#include <iostream>
#include <stdlib.h> // system("CLS") clears the terminal
#include "Field.h"
#include <conio.h> 

using namespace std;

void play_game(Field &obj);

int main() {
	
	Field field(20, 50, "=");
	play_game(field);

	return 0;
}

void play_game(Field &obj) {
	do {
		cout << "Use W, A, S, D to move around and eat the food \"*\"." << endl;
		cout << "Press Q/E to increase/decrease speed and avoid the walls \"=\"." << endl;
		cout << "Score: " << obj.snake_tail_length << " Speed: " << obj.snake_speed << endl;
		obj.display_field();
		obj.move_snake();
		if (obj.game_over_flag == false) {
			system("CLS");
		}
		else {
			cout << "Game over..." << endl;
		}
	} while (obj.game_over_flag == false);
}