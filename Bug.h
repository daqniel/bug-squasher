#ifndef _BUG_H
#define _BUG_H

#include "Character.h"
class Bug : public Character
{
public:
	Bug();
	~Bug();

	// Inherited via Character
	virtual Position Update(Board * board, int ch, const std::vector<Character*>& cvec);

	void init(chtype symbol, int hp, Position pos, int id, std::string s);

	void set_in_range(bool b) { is_in_range_ = b; }

	int get_id() const { return id_; }

	bool is_smart() const { return smart_; }
	std::string get_bug_type() const { return type_; }
protected:
	const int LEG_CRAWL_RANGE_ = 1;
	const int FLYING_WINGS_RANGE_ = 2;

	const int LEG_CRAWL_CHANCE_ = 72;
	const int FLYING_WINGS_CHANCE_ = 15;//changed for better gameplay
	bool is_in_range_ = false;
	int id_ = -1;
	bool smart_ = false;
	std::string type_ = "";
};

#endif
