#ifndef _BOARD_H
#define _BOARD_H

#include "Tile.h"
#include <vector>
#include <curses.h>
#include "HUD.h"
#include <string>

enum class BoardChanged {CHANGED, NO};

class Player;
class Board
{
public:
	Board();
	~Board();

	void Load(std::string fpath);

	void Update();

	void Draw(Player* player);

	void ExitBoard();
	
	bool is_changed();

	void SetChanged();

	bool TileIsTraversable(Position pos);

	void SwitchTiles(Position pos1, Position pos2);

	bool SetTileType(Position pos, chtype type);

	std::vector<std::vector<Tile>>* get_board_() { return &board_; };

	Position get_player_pos() const { return player_pos_; }

	std::vector<Position> get_bug_position() const { return init_bug_positions_; }

	void set_player_pos(Position pos) { player_pos_ = pos; }

	void set_visible(TileType vis) { vis_ = vis; }

private:
	Position player_pos_;
	std::vector<Position> init_bug_positions_;
	BoardChanged changed_ = BoardChanged::NO;
	std::vector<std::vector<Tile>> board_;
	TileType vis_ = TileType::VISIBLE;
};

#endif
