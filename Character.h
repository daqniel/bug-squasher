#ifndef _CHARACTER_H
#define _CHARACTER_H

#include "Tile.h"
#include "Board.h"
#include <unordered_map>
enum class Status {NONE, FROZEN, DEAD};

class Character : public Tile
{

public:

	Character();
	~Character();

	Position move(Board* board, int num, chtype ch);

	void Remove();

	void set_status(Status s) { status_ = s; }

	bool in_range(Position pos, int range);

	virtual void set_in_range(bool) = 0;

	virtual int get_id() const = 0;

	virtual Position Update(Board* board, int ch, const std::vector<Character*>& cvec) = 0;

	virtual std::string get_bug_type() const = 0;

	Status get_stat() const { return status_; }
protected: 
	Status status_ = Status::NONE;
	int move_speed;
};

#endif
