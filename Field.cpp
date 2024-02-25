#include "Field.h"
#include <iostream>
#include <cstdlib>  //required for rand()
#include <ctime>    //required for time()
#include <conio.h>  //get input from the terminal without pressing the enter

//Constructor
Field::Field(int horizontal_val, int vertical_val, std::string block_str) 
	:h{ horizontal_val }, v{ vertical_val }, field_block{block_str} {

	field = new std::string * [h];
	for (int i = 0; i < h; i++) {
		field[i] = new std::string[v];
	}

	for (int i{ 0 }; i < h; i++) {
		for (int j{ 0 }; j < v; j++) {
			field[i][j] = field_block;
		}
	}

	for (int i{ 1 }; i < h - 1; i++) {
		for (int j{ 1 }; j < v - 1; j++) {
			field[i][j] = " ";
		}
	}

	place_cheese();
	place_snake();
}

//Destructor
Field::~Field(){
	for (int i = 0; i < h; i++) {
		delete[] field[i];
	}
	delete[] field;
}

// Methods
void Field::display_field() const {
	for (int i{ 0 }; i < h; i++) {
		for (int j{ 0 }; j < v; j++) {
			std::cout << field[i][j];
			if (j == v - 1) {
				std::cout << std::endl;
			}
		}
	}
}

void Field::place_cheese()
{
	std::srand(time(nullptr));

	int rand_row = rand() % h;
	int rand_col = rand() % v;

	while (field[rand_row][rand_col] == field_block || field[rand_row][rand_col] == snake_tail_block
		|| field[rand_row][rand_col] == snake_head) {
		rand_row = rand() % h;
		rand_col = rand() % v;
	}
	field[rand_row][rand_col] = cheese;
}

void Field::place_snake()
{
	std::srand(time(nullptr));

	snake_coord[0] = rand() % h;
	snake_coord[1] = rand() % v;

	while (field[snake_coord[0]][snake_coord[1]] == field_block || field[snake_coord[0]][snake_coord[1]] == cheese) {
		snake_coord[0] = rand() % h;
		snake_coord[1] = rand() % v;
	}
	field[snake_coord[0]][snake_coord[1]] = snake_head;
}

void Field::move_snake()
{	
	dir = _getch();
	
	// W
	if (dir == 'W' || dir == 'w') {
		snake_head = "^";
		
		// reset field
		for (int i{ 1 }; i < h - 1; i++) {
			for (int j{ 1 }; j < v - 1; j++) {
				if (field[i][j] != cheese) {
					field[i][j] = " ";
				}
			}
		}

		snake_coord[0] += -snake_speed;
		if (snake_coord[0] > 0) {
			if (field[snake_coord[0]][snake_coord[1]] == cheese) {
				snake_tail_length += 1;
				place_cheese();
			}

			field[snake_coord[0]][snake_coord[1]] = snake_head;
			if (snake_tail_length > 0) {
				for (int i{ snake_tail_length }; i > 0; i--) {
					if ((snake_coord[0] + i) < h && field[snake_coord[0] + i][snake_coord[1]] != cheese) {
						field[snake_coord[0] + i][snake_coord[1]] = snake_tail_block;
					}
				}
			}
		}
		else {
			game_over_flag = true;
		}
		
	}
	// S
	else if (dir == 'S' || dir == 's') {
		snake_head = "v";

		// reset field
		for (int i{ 1 }; i < h - 1; i++) {
			for (int j{ 1 }; j < v - 1; j++) {
				if (field[i][j] != cheese) {
					field[i][j] = " ";
				}
			}
		}

		snake_coord[0] += snake_speed;
		if (snake_coord[0] < h-1) {
			if (field[snake_coord[0]][snake_coord[1]] == cheese) {
				snake_tail_length += 1;
				place_cheese();
			}
			field[snake_coord[0]][snake_coord[1]] = snake_head;
			if (snake_tail_length > 0) {
				for (int i{ snake_tail_length }; i > 0; i--) {
					if ((snake_coord[0] - i) > 0 && field[snake_coord[0] - i][snake_coord[1]] != cheese) {
						field[snake_coord[0] - i][snake_coord[1]] = snake_tail_block;
					}
				}
			}
		}
		else {
			game_over_flag = true;
		}
	}
	// A
	else if (dir == 'A' || dir == 'a') {
		snake_head = "<";

		// reset field
		for (int i{ 1 }; i < h - 1; i++) {
			for (int j{ 1 }; j < v - 1; j++) {
				if (field[i][j] != cheese) {
					field[i][j] = " ";
				}
			}
		}

		snake_coord[1] += -snake_speed;
		if (snake_coord[1] > 0) {

			if (field[snake_coord[0]][snake_coord[1]] == cheese) {
				snake_tail_length += 1;
				place_cheese();
			}
			field[snake_coord[0]][snake_coord[1]] = snake_head;
			if (snake_tail_length > 0) {
				for (int i{ snake_tail_length }; i > 0; i--) {
					if ((snake_coord[1] + i) < v && field[snake_coord[0]][snake_coord[1] + i] != cheese) {
						field[snake_coord[0]][snake_coord[1] + i] = snake_tail_block;
					}
				}
			}
		}
		else {
			game_over_flag = true;
		}
	}
	// D
	else if (dir == 'D' || dir == 'd') {
		snake_head = ">";
		// reset field
		for (int i{ 1 }; i < h - 1; i++) {
			for (int j{ 1 }; j < v - 1; j++) {
				if (field[i][j] != cheese) {
					field[i][j] = " ";
				}
			}
		}

		snake_coord[1] += snake_speed;
		if (snake_coord[1] < v-1) {
			if (field[snake_coord[0]][snake_coord[1]] == cheese) {
				snake_tail_length += 1;
				place_cheese();
			}
			field[snake_coord[0]][snake_coord[1]] = snake_head;
			if (snake_tail_length > 0) {
				for (int i{ snake_tail_length }; i > 0; i--) {
					if ((snake_coord[1] - i) > 0 && field[snake_coord[0]][snake_coord[1] - i] != cheese) {
						field[snake_coord[0]][snake_coord[1] - i] = snake_tail_block;
					}
				}
			}
		}
		else {
			game_over_flag = true;
		}
	}

	// Change snake speed
	else if (dir == 'Q' || dir == 'q') {
		snake_speed += 1;
	}
	else if (dir == 'E' || dir == 'e') {
		snake_speed -= 1;
	}
}



