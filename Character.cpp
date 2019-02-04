#include "Character.h"
#include <algorithm>
#include <cmath>
Character::Character()
{
}


Character::~Character()
{
}

Position Character::move(Board* board, int num, chtype ch)
{
	
	switch (ch) {
	// LEFT
	case '4': {
		in_range(pos_, 2);
		Position left_pos(pos_.x - num, pos_.y);
		if (left_pos.x >= 0 && left_pos.y >= 0) {
			return left_pos;
		}
	}
		break;
	// RIGHT
	case '6': {

		Position right_pos(pos_.x + num, pos_.y);
		if (right_pos.x >= 0 && right_pos.y >= 0) {
			return right_pos;
		}
	}
		break;
	// UP
	case '8': {

		Position up_pos(pos_.x , pos_.y - num);
		if (up_pos.x >= 0 && up_pos.y >= 0) {
			return up_pos;
		}
	}
		break;
	// DOWN
	case '2': {

		Position down_pos(pos_.x, pos_.y + num);
		if (down_pos.x >= 0 && down_pos.y >= 0) {
			return down_pos;
		}
	}
		break;
	// UPLEFT
	case '7': {

		Position down_pos(pos_.x-num, pos_.y - num);
		if (down_pos.x >= 0 && down_pos.y >= 0) {
			return down_pos;
		}
	}
				   break;
	 // UPRIGHT
	case '9': {

		Position down_pos(pos_.x + num, pos_.y - num);
		if (down_pos.x >= 0 && down_pos.y >= 0) {
			return down_pos;
		}
	}
			  break;
	 // DOWNLEFT
	case '1': {

		Position down_pos(pos_.x - num, pos_.y + num);
		if (down_pos.x >= 0 && down_pos.y >= 0) {
			return down_pos;
		}
	}
			  break;
	 // DOWNRIGHT
	case '3': {

		Position down_pos(pos_.x + num, pos_.y + num);
		if (down_pos.x >= 0 && down_pos.y >= 0) {
			return down_pos;
		}
	}
			  break;
	


	}

	 return pos_;
	
}

void Character::Remove()
{
}

bool Character::in_range(Position pos, int range)
{

	int distance = sqrt(pow((pos_.x - pos.x), 2) + pow((pos_.y - pos.y), 2));
	
			if (distance <= range) {
				return true;
			
			}

	return false;
}
