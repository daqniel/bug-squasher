
#include "Game.h"
/*
Created by: Daniel Quintero
For class: COP1334, Prof Meyer


I changed the chances of the bugs' attacks happening to make for better gameplay.
For an easy win, replace all the @ symbols in the .txt file with periods, then move a few steps.

COOL (Extra Credit?) STUFF:
- Obstacles in grid
- Game at night, can only see 3 tiles around (toggleable for testing)
- Direct keyboard input
- Color
- A working HUD
- Seperation of Classes into different files
- Use of external library
- Can make custom level by editing the txt file. 
- maybe more
*/
int main() {
	Game game;
	game.Run();
	return 0;
}