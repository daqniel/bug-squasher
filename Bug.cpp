#include "Bug.h"



Bug::Bug()
{
	move_speed = 1;
}


Bug::~Bug()
{
}
void Bug::init(chtype symbol, int hp, Position pos,  int id, std::string s)
{
	set_tile_symbol(symbol);

	pos_ = pos;
	id_ = id;
	type_ = s;
}
Position Bug::Update(Board * board, int ch, const std::vector<Character*>& cvec)
{

	if (status_ == Status::FROZEN) {
		return Position(0, 0);
	}


	if (in_range(board->get_player_pos(), FLYING_WINGS_RANGE_)) {
		if ((rand() % 100 + 1) <= FLYING_WINGS_CHANCE_) {
	
			return Position(-1,0);
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
		int random;
		Position temp = get_pos();
		if (opts.size() != 0) {
			random = rand() % opts.size() + 1;
		
			temp = move(board, move_speed, opts[random - 1]);
		}

		

	return temp;
}


