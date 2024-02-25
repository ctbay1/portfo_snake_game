#pragma once
#include <string>
#include <vector>
class Field
{
private:
	int h{};
	int v{};
	std::string field_block{};
	std::string** field;

	std::string cheese{ "*" };
	std::string snake_head{ ">" };
	std::string snake_tail_block{ "="};

	int snake_coord[2]{ 1, 1 };	
	char dir{};

public:

	int snake_speed = 1;
	int snake_tail_length = 0;
	bool game_over_flag{ false };

	void display_field() const;
	void place_cheese();
	void place_snake();
	void move_snake();

	//Constructor
	Field(int horizontal_val = 20 , int vertical_val = 50, std::string block_str = "=");
	//Destructor
	~Field();
};

