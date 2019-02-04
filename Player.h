#ifndef _PLAYER_H
#define _PLAYER_H

#include "Character.h"
#include <unordered_map>
class Player :
	public Character
{
public:
	Player();
	~Player();
	void init(chtype symbol, int hp, int resolve, Position pos);
	/*virtual*/ Position Update(Board* board, int ch, const std::vector<Character*>& cvec);

	int get_vis_range() const { return vis_range;}
	int get_resolve_points() const { return resolve_points_; }
	int get_id() const { return id_; }
	std::string get_bug_type() const{ return ""; }
	int get_last_hit() const { return last_hit_; }
	Status get_status() const { return status_; }


	void set_in_range(bool b) { is_in_range = b; }
	void set_vis_range(int i) { vis_range = i; }
	void set_resolve_points(int i) { resolve_points_ = i; }
private: 
	std::vector<Character*> bugs_in_range;
	int vis_range = 3;
	bool is_in_range = false;
	int resolve_points_ = 0;
	int id_ = -1;
	int last_hit_ = -1;
};

#endif
