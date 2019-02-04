#ifndef _HUD_H
#define _HUD_H

#include <curses.h>
#include <vector>
#include <string>
enum class HudChanged { CHANGED, NOT };
class Character;
class HUD
{
public:
	HUD();
	~HUD();
	void init();
	void UpdateNear(const std::vector<Character*>& near_map);
	void UpdateInRange(const std::vector<Character*>& in_range_map);
	void draw();

	void WriteToLog(std::string s);

	void lose_resolve() { resolve_--; }
	void gain_resolve() { resolve_++; }

	void set_changed(HudChanged change) { change_ = change; }
	void set_num_bugs(int i) { num_bugs_on_map_ = i; }

	int get_num_bugs() const { return num_bugs_on_map_; }
	HudChanged get_changed() const { return change_;}
private: 
	HudChanged change_ = HudChanged::NOT;
	int resolve_ = 5;
	int num_bugs_on_map_ = -1;
	std::vector<Character*> near_map_;
	std::vector<Character*> in_range_map_;
	std::vector<std::string> log_;
	int action_count_ = 0;
};

#endif
