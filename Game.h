#ifndef _GAME_H
#define _GAME_H

#include "Board.h"
#include "Character.h"
#include "Player.h"
#include "Bug.h"
#include "SmartBug.h"
#include <vector>
#include <unordered_map>
#include "HUD.h"
enum class GameState { EXIT, RUNNING, NONE };
class Game
{
public:
	Game();
	~Game();


	//initiates stuff like sdl, curses
	void Init();

	//contains main game loop
	void Run();

	//does whatever we need to do on exit
	void ExitGame(std::string err);

	void SwitchTiles(Position pos1, Position pos2);
	
	void Update();

	void Lose();

	void Win();

	std::vector<Character*> CheckNear(bool);
	std::vector<Character*> CheckInRange(bool);
private: 
	int turn_num_ = 1;
	GameState game_state_ = GameState::NONE;
	Board* board_ = nullptr;
	bool running_ = false;
	Player* player_ = nullptr;
	std::unordered_map<unsigned int, Character*> character_arr;
	HUD hud_;
	const int PLAYER_MOVES_ = 3;
	const int BUG_MOVES_ = 2;
};

#endif
