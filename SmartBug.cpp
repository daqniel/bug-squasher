#include "SmartBug.h"



Position SmartBug::Update(Board * board, int ch, const std::vector<Character*>& cvec)
{
	if (status_ == Status::FROZEN) {
		return Position(0, 0);
	}

	if (in_range(board->get_player_pos(), 4)) {
		chasing_ = true;

	}
	else {
		chasing_ = false;
	}


	if (in_range(board->get_player_pos(), FLYING_WINGS_RANGE_)) {
		if ((rand() % 100 + 1) <= FLYING_WINGS_CHANCE_) {

			return Position(-1, 0);
		}

	}

	if (in_range(board->get_player_pos(), LEG_CRAWL_RANGE_)) {
		if ((rand() % 100 + 1) <= LEG_CRAWL_CHANCE_) {

			return Position(-2, 0);
		}

	}

	std::vector<chtype> opts;
	bool right, left, up, down;


	//left	
	left = board->TileIsTraversable(Position(get_pos().x - 1, get_pos().y));
	if (left) { opts.push_back('4'); }

	//right
	right = board->TileIsTraversable(Position(get_pos().x + 1, get_pos().y));
	if (right) { opts.push_back('6'); }

	//up
	up = board->TileIsTraversable(Position(get_pos().x - 1, get_pos().y - 1));
	if (up) { opts.push_back('8'); }

	//down
	down = board->TileIsTraversable(Position(get_pos().x, get_pos().y + 1));
	if (down) { opts.push_back('2'); }
	
	int random = 0;

	Position temp = get_pos();

	if (opts.size() != 0) {
		random = rand() % opts.size() + 1;
	
		if (chasing_) {
			int dif_left = abs((pos_.x - 1) - (board->get_player_pos().x));
			int dif_right = abs((pos_.x + 1) - (board->get_player_pos().x));

			int dif_up = abs((pos_.y - 1) - (board->get_player_pos().y));
			int dif_down = abs((pos_.y + 1) - (board->get_player_pos().y));

			if (dif_left > dif_right) {

				for (size_t i = 0; i < opts.size(); i++) {
					if (opts[i] == '6') {
						temp = move(board, move_speed, opts[i]);
						return temp;
					}
				}
			}else if(dif_right > dif_left){
				for (size_t i = 0; i < opts.size(); i++) {
					if (opts[i] == '4') {
						temp = move(board, move_speed, opts[i]);
						return temp;
					}
				}
			}

			if (dif_up > dif_down) {
				for (size_t i = 0; i < opts.size(); i++) {
					if (opts[i] == '2') {
						temp = move(board, move_speed, opts[i]);
						return temp;
					}
				}


			}else if (dif_down > dif_up) {
				for (size_t i = 0; i < opts.size(); i++) {
					if (opts[i] == '8') {
						temp = move(board, move_speed, opts[i]);
						return temp;
					}
				}


			}
			
		}

		temp = move(board, move_speed, opts[random - 1]);
	}



	return temp;
}

SmartBug::SmartBug()
{
	smart_ = true;
}


SmartBug::~SmartBug()
{
}
