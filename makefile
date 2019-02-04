objs=main.o Game.o Board.o LevelReader.o HUD.o Character.o Player.o Bug.o SmartBug.o



compile: $(objs)

compile_and_link: compile
	g++ *.o -lncurses -o test.out

main.o:
	g++ -c main.cpp

Game.o:
	g++ -c Game.cpp

Board.o:
	g++ -c Board.cpp

LevelReader.o:
	g++ -c LevelReader.cpp

HUD.o:
	g++ -c HUD.cpp

Character.o:
	g++ -c Character.cpp

Player.o:
	g++ -c Player.cpp

Bug.o:
	g++ -c Bug.cpp

SmartBug.o:
	g++ -c SmartBug.cpp

.PHONY: clean

clean:
	rm *.o
