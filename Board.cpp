#include "Board.h"
#include "LevelReader.h"
#include "Tile.h"

#include "Player.h"



Board::Board() : board_(0, std::vector<Tile>())
{
}


Board::~Board()
{
}

void Board::Load(std::string fpath)
{

	//reads file into buffer
	std::vector<std::string> buffer;
	Dimensions dims = LevelReader::ReadFileToBuffer(fpath, buffer);

	std::vector<Tile> temp;
for(size_t i = 0; i < dims.height; i++){
	for (size_t x = 0; x < dims.width; x++) {

		switch (buffer[i].c_str()[x]) {
		case '-':
			temp.emplace_back(TileType::NOT_TRAVERSABLE,TileType::INVISIBLE , ACS_BLOCK, Position(x,i), 4);

			break;
		case '.':
			temp.emplace_back(TileType::TRAVERSABLE, TileType::INVISIBLE, ACS_BOARD, Position(x, i), 5);
			break;
		case ',':

			temp.emplace_back(TileType::TRAVERSABLE, TileType::INVISIBLE, ACS_BOARD, Position(x, i), 2);

			break;
		case '*':
			temp.emplace_back(TileType::NOT_TRAVERSABLE, TileType::INVISIBLE, ACS_DIAMOND, Position(x, i), 5);
			player_pos_ = Position(x, i);

			break;
		case '@':
			temp.emplace_back(TileType::NOT_TRAVERSABLE, TileType::INVISIBLE, ACS_LANTERN, Position(x, i), 5);
			init_bug_positions_.emplace_back(Position(x,i));

			break;
		case 'o':
			temp.emplace_back(TileType::NOT_TRAVERSABLE, TileType::INVISIBLE, ACS_DEGREE, Position(x, i), 3);

			break;
		case '0':
			temp.emplace_back(TileType::NOT_TRAVERSABLE, TileType::INVISIBLE, ' ', Position(x, i));
			break;
		case 'R':
			temp.emplace_back(TileType::NOT_TRAVERSABLE, TileType::INVISIBLE, ACS_CKBOARD, Position(x, i));
			break;
		case 'w':
			temp.emplace_back(TileType::NOT_TRAVERSABLE, TileType::INVISIBLE, ACS_CKBOARD, Position(x, i), 1);
			break;
		default:
			temp.emplace_back(TileType::NOT_TRAVERSABLE, TileType::INVISIBLE, ACS_BULLET , Position(x, i));
			break;
			}
	
		}
	
	board_.push_back(temp);
	temp.clear();
	temp.resize(0);
	}

changed_ = BoardChanged::CHANGED;

}

void Board::Update()
{
	
		
	
}

void Board::Draw(Player* player)
{
	addch('\n');
	for (size_t r = 0; r< board_.size(); r++) {
		addch(' ');
		for (size_t c = 0; c< board_[r].size(); c++) {
			if (board_[r][c].get_visible() == vis_
				|| player->in_range(board_[r][c].get_pos(),player->get_vis_range())
				 ){
				if (board_[r][c].get_color_pair() != -1) {
					attron(COLOR_PAIR(board_[r][c].get_color_pair()));
				}
				
				addch(board_[r][c].get_tile_symbol());
				attroff(COLOR_PAIR(board_[r][c].get_color_pair()));
			}
			else {
				addch(' ');
			}
		}
		printw("\n");
		
		
	}
	
	changed_ = BoardChanged::NO;
}

void Board::ExitBoard()
{
	board_.clear();
	board_.resize(0);
}

bool Board::is_changed()
{

	if (changed_ == BoardChanged::CHANGED) {
		return true;
	}
	return false;
}

void Board::SetChanged()
{
	changed_ = BoardChanged::CHANGED;
}

bool Board::TileIsTraversable(Position pos)
{
	if (board_[pos.y][pos.x].get_type() == TileType::TRAVERSABLE) {
		
		return true;
	}
	
	return false;
}


bool Board::SetTileType(Position pos, chtype type)
{
	return false;
}

void Board::SwitchTiles(Position pos1, Position pos2)
{
	chtype tempch = board_[pos1.y][pos1.x].get_tile_symbol();
	board_[pos1.y][pos1.x].set_tile_symbol(board_[pos2.y][pos2.x].get_tile_symbol());
	board_[pos2.y][pos2.x].set_tile_symbol(tempch);

	changed_ = BoardChanged::CHANGED;
}
