#ifndef _TILE_H
#define _TILE_H

#include <curses.h>
#include "Dimensions.h"
enum class TileType{NONE, TRAVERSABLE, NOT_TRAVERSABLE, VISIBLE, INVISIBLE};
struct Position {
	Position() {

	}
	Position(int xx, int yy) {

		x = xx;
		y = yy;
	}

	friend bool operator==(const Position& pos1, const Position& pos2){

		if (pos1.x == pos2.x && pos1.y == pos2.y) {
			return true;
		}
		return false;
	}

	int x;
	int y;

};
class Tile {
public:
	Tile() {

	}

	Tile(TileType Tile_Type, TileType Visible, chtype tile_symbol, Position pos) {
		tile_type_ = Tile_Type;
		visible_ = Visible;
		tile_symbol_ = tile_symbol;
		pos_ = pos;
	}
	Tile(TileType Tile_Type, TileType Visible, chtype tile_symbol, Position pos, int col_pair) {
		tile_type_ = Tile_Type;
		visible_ = Visible;
		tile_symbol_ =tile_symbol;
		pos_ = pos;
		col_pair_ = col_pair;
	}
	TileType get_type() const { return tile_type_; }
	TileType get_visible() const { return visible_; }
	chtype get_tile_symbol() const { return tile_symbol_; }
	Position get_pos() const { return pos_; }
	int get_color_pair() const { return col_pair_; }


	void set_tile_symbol(chtype ch) { tile_symbol_ = ch; }
	void set_tile_type(TileType type) { tile_type_ = type; }
	void set_visible(TileType type) { visible_ = type; }
	void set_pos(Position pos) { pos_ = pos; }
protected:
	int col_pair_ = -1;
	TileType tile_type_ = TileType::NONE;
	TileType visible_ = TileType::NONE;
	chtype tile_symbol_;
	Position pos_;
};

#endif
