#include "Player.h"



Player::Player() 
{
	move_speed = 1;
}


Player::~Player()
{
}

void Player::init(chtype symbol, int hp, int resolve, Position pos)
{
	resolve_points_ = resolve;
	set_tile_symbol(symbol);
	pos_ = pos;
}

Position Player::Update(Board* board, int ch, const std::vector<Character*>& cvec)
{
	int tempch = ch;
	
	
	if (tempch == 122/* Z */)  {
		
		while (tempch == 122||tempch == ERR) {
			
			tempch = getch();
			
		}
		for (int i = 0; i < cvec.size(); i++) {
			
			
			if (tempch == 49 + i) {
				if (rand() % 100 + 1 < 65) {
					last_hit_ = i;
					cvec[i]->set_status(Status::FROZEN);

					
					return Position(-1, 0);
				}else{
					last_hit_ = i;
					return Position(-1, 1);
				}
			}
		}
		
		
	}else if (tempch == 120/* X */) {

		while (tempch == 120 || tempch == ERR) {

			tempch = getch();

		}
		for (int i = 0; i < cvec.size(); i++) {
			
			
			if (tempch == 49 + i) {
				if (cvec[i]->get_stat() == Status::FROZEN) {
					if (rand() % 100 + 1 < 90) {
						last_hit_ = i;
						cvec[i]->set_status(Status::DEAD);

						
						return Position(-2, 0);
					}
					else {
						last_hit_ = i;
						return Position(-2, 1);
					}
				}else{
					if (rand() % 100 + 1 < 60) {
						last_hit_ = i;
						cvec[i]->set_status(Status::DEAD);

						
						return Position(-2, 0);
					}
					else {
						last_hit_ = i;
						return Position(-2, 1);
					}
				}
			}
		}


	}
	
	Position temp = move(board, move_speed, ch);

	return temp;
}


