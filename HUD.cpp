#include "HUD.h"
#include <string>
#include "Character.h"

HUD::HUD()
{
}


HUD::~HUD()
{
}

void HUD::init() 
{
	
	log_.resize(0);
	
	change_ = HudChanged::CHANGED;
}

void HUD::UpdateNear(const std::vector<Character*>& near_map)
{
	near_map_ = near_map;

}
void HUD::UpdateInRange(const std::vector<Character*>& in_range_map) 
{

	in_range_map_ = in_range_map;

}

void HUD::draw()
{
	// Border around game box
	for (int i = 0; i < 90; i++) {
		mvaddch(31, 1+i, ACS_HLINE);
		mvaddch(0, 1 + i, ACS_HLINE);
	}
	for (int i = 0; i < 30; i++) {
		mvaddch(30 - i, 0, ACS_VLINE);
		mvaddch(30 - i, 91, ACS_VLINE);
	}
	mvaddch(31, 0, ACS_LLCORNER);
	mvaddch(31, 91, ACS_LRCORNER);
	mvaddch(0, 91, ACS_URCORNER);
	mvaddch(0, 0, ACS_ULCORNER);
	mvaddstr(32, 1, "Resolve: ");
	
	//Draw resolve hearts
	for (int i = 0; i < resolve_;i++) {
		
		init_pair(4, COLOR_RED , COLOR_BLACK);

		attron(COLOR_PAIR(4));
		mvaddch(32 , 10 + i * 7, '/'|A_BOLD);
		mvaddch(32 , 11 + i * 7, 'V'|A_BOLD);
		mvaddch(32 , 12 + i * 7, '\\' | A_BOLD);

		mvaddch(33, 10 + i * 7, '\\' | A_BOLD);
		mvaddch(33, 11 + i * 7, '_' | A_BOLD);
		mvaddch(33, 12 + i * 7, '/' | A_BOLD);
		attroff(COLOR_PAIR(4));
		

	}


	//Draw number of bugs on map
	mvaddstr(35, 1, "Bugs Left: ");
	attron(COLOR_PAIR(6));
	attron(A_BOLD);
	mvaddstr(35, 12, std::to_string(num_bugs_on_map_).c_str());
	attroff(COLOR_PAIR(6));
	attroff(A_BOLD);

	// Draw nearby enemy info
	mvaddstr(2, 95, "Nearby Enemies");
	mvaddstr(3, 95, "--------------");
	if (near_map_.size() > 0) {
		for (size_t i = 0; i < near_map_.size(); i++) {
			std::string temp =""+std::to_string(i+1)+". "+near_map_[i]->get_bug_type()+" "+ std::to_string(near_map_[i]->get_id()) + " ";
			
			mvaddstr(4 + i, 96, temp.c_str());
			addch(near_map_[i]->get_tile_symbol());
		}
	}

	// Draw in range enemy info
	mvaddstr(12, 95, "Targetable Enemies");
	mvaddstr(13, 95, "------------------");
	if (in_range_map_.size() > 0) {
		for (size_t i = 0; i < in_range_map_.size(); i++) {
			std::string temp = "" + std::to_string(i + 1) + ". " + in_range_map_[i]->get_bug_type() + " " + std::to_string(in_range_map_[i]->get_id()) + " ";

			mvaddstr(14 + i, 96, temp.c_str());
			addch(in_range_map_[i]->get_tile_symbol());
		}
	}


	
	//Draw actionlog
	mvaddstr(32, 55, "Action Log");
	for (size_t i = 0; i < log_.size(); i++) {
		
		mvaddstr(34 + i, 55, log_[i].c_str());
	}

	//Draw controls
	mvaddstr(37, 1, "Controls:");
	mvaddstr(38, 1, "Numpad for movement.");
	mvaddstr(39, 1, "Press Z and then the target # to use RAID Spray.");
	mvaddstr(40, 1, "Press X and then the target # to use Foot Stomp.");
	mvaddstr(41, 1, "Q and W to toggle "); attron(COLOR_PAIR(7)); attron(A_BOLD); addstr("THE SUN"); attroff(COLOR_PAIR(7)); attroff(A_BOLD); addch('.');
	refresh();
}

void HUD::WriteToLog(std::string s)
{	
	
	log_.push_back(s);

	if (log_.size() == 7) {
		log_.erase(log_.begin());
	}
	change_ = HudChanged::CHANGED;
	
}
