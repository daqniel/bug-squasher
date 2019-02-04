#include "Game.h"
#include <ctime>
#include <iostream>
#include <ncurses.h>
#include <string>

bool xd = true;

Game::Game() {}

Game::~Game() {
  for (auto &it : character_arr) {
    delete it.second;
  }
  character_arr.clear();
  delete board_;
  delete player_;
}

void Game::Init() {
  // sets up curses
  std::srand(time(0));
  initscr();

  start_color();
  cbreak();
  noecho();

  // color pairs
  init_pair(1, COLOR_WHITE, COLOR_BLUE);
  init_pair(2, COLOR_WHITE, COLOR_GREEN);
  init_pair(3, COLOR_WHITE, COLOR_YELLOW);
  init_pair(4, COLOR_RED, COLOR_BLACK);
  init_pair(5, COLOR_WHITE, COLOR_YELLOW);
  init_pair(6, COLOR_GREEN, COLOR_BLACK);
  init_pair(7, COLOR_YELLOW, COLOR_BLACK);

  nodelay(stdscr, TRUE);
  keypad(stdscr, TRUE);
  curs_set(0);

  refresh();
  board_ = new Board();
  board_->Load("Levels/level1.txt");
  Position temp_pos = board_->get_player_pos();
  player_ = new Player();
  player_->init(
      board_->get_board_()[0][temp_pos.y][temp_pos.x].get_tile_symbol(), 100, 5,
      temp_pos);

  int id = 1;

  if (board_->get_bug_position().size() != 0) {
    for (auto &it : board_->get_bug_position()) {

      Bug *bug;
      int r = rand() % 10 + 1;
      if (r > 8) {
        bug = new SmartBug();
      } else {
        bug = new Bug();
      }
      if (bug->is_smart()) {
        bug->init(board_->get_board_()[0][it.y][it.x].get_tile_symbol(), 100,
                  it, id, "Smarter");
      } else {
        bug->init(board_->get_board_()[0][it.y][it.x].get_tile_symbol(), 100,
                  it, id, "Stupid");
      }

      character_arr[id] = bug;
      id++;
    }
  }

  hud_.init();
}
void Game::Update() {

  if (board_->is_changed()) {
    erase();
    board_->Draw(player_);
  }
  if (hud_.get_changed() == HudChanged::CHANGED) {
    hud_.draw();
  }
}

std::vector<Character *> Game::CheckNear(bool clear) {
  static std::vector<Character *> cvec; // useful for storing bugs near player
  if (clear) {
    cvec.clear();
    cvec.resize(0);
  }
  for (auto &it : character_arr) {
    if (player_->in_range(it.second->get_pos(), 4)) {

      cvec.push_back(it.second);
    }
  }
  return cvec;
}

std::vector<Character *> Game::CheckInRange(bool clear) {
  static std::vector<Character *>
      cvec; // useful for storing bugs in range of player
  if (clear) {
    cvec.clear();
    cvec.resize(0);

    for (auto &it : character_arr) {
      if (player_->in_range(it.second->get_pos(), 1)) {

        cvec.push_back(it.second);
      }
    }
  }
  return cvec;
}

void Game::Run() {
  game_state_ = GameState::RUNNING;
  Init();
  int ch = 0;
  int player_actions = 0;
  int bug_actions = 0;
  hud_.UpdateNear(CheckNear(true));
  hud_.UpdateInRange(CheckInRange(true));
  while (game_state_ == GameState::RUNNING) {

    // win condition
    if (hud_.get_num_bugs() == 0) {
      Win();
    }

    hud_.set_num_bugs(character_arr.size());
    resize_term(42, 120);
    std::string tempstr = "Turn " + std::to_string(turn_num_);

    hud_.WriteToLog(tempstr);
    board_->SetChanged();
    Update();
    while (player_actions < PLAYER_MOVES_) {

      if (player_->get_status() == Status::FROZEN) {
        std::string tempstr = "You are stunned!";

        hud_.WriteToLog(tempstr);
        board_->SetChanged();
        Update();
        player_actions++;
      } else {
        ch = getch();
        if (ch != ERR && ch != 113 && ch != 119) {

          Position temp = player_->get_pos();
          Position temp2 = player_->Update(board_, ch, CheckInRange(true));

          if (temp2.x == -1 && temp2.y == 0) {

            std::string temp =
                "Success! Sprayed " +
                CheckInRange(false)[player_->get_last_hit()]->get_bug_type() +
                " Bug " +
                std::to_string(
                    CheckInRange(false)[player_->get_last_hit()]->get_id());

            hud_.WriteToLog(temp);
            board_->SetChanged();
            player_actions++;

          } else if (temp2.x == -1 && temp2.y == 1) {
            std::string temp =
                "Failure... RAID missed " +
                CheckInRange(false)[player_->get_last_hit()]->get_bug_type() +
                " Bug " +
                std::to_string(
                    CheckInRange(false)[player_->get_last_hit()]->get_id());

            hud_.WriteToLog(temp);
            board_->SetChanged();
            player_actions++;

          } else if (temp2.x == -2 && temp2.y == 0) {

            std::string temp =
                "Success! Squashed " +
                CheckInRange(false)[player_->get_last_hit()]->get_bug_type() +
                " Bug " +
                std::to_string(
                    CheckInRange(false)[player_->get_last_hit()]->get_id());

            Position tempp =
                character_arr[CheckInRange(false)[player_->get_last_hit()]
                                  ->get_id()]
                    ->get_pos();
            board_->get_board_()[0][tempp.y][tempp.x].set_tile_type(
                TileType::TRAVERSABLE);
            board_->get_board_()[0][tempp.y][tempp.x].set_tile_symbol(
                ACS_BOARD);

            character_arr.erase(
                CheckInRange(false)[player_->get_last_hit()]->get_id());

            hud_.WriteToLog(temp);
            board_->SetChanged();
            player_actions++;

          } else if (temp2.x == -2 && temp2.y == 1) {

            std::string temp =
                "Failure... STOMP missed " +
                CheckInRange(false)[player_->get_last_hit()]->get_bug_type() +
                " Bug " +
                std::to_string(
                    CheckInRange(false)[player_->get_last_hit()]->get_id());

            hud_.WriteToLog(temp);
            board_->SetChanged();
            player_actions++;

          }

          else if ((board_->TileIsTraversable(temp2))) {
            SwitchTiles(temp, temp2);
            player_->set_pos(temp2);
            board_->set_player_pos(temp2);
            player_actions++;
          }

          hud_.UpdateNear(CheckNear(true));
          hud_.UpdateInRange(CheckInRange(true));
          Update();

        } else if (ch == 113) {

          board_->set_visible(TileType::INVISIBLE);
          board_->SetChanged();
          Update();

        } else if (ch == 119) {
          board_->set_visible(TileType::VISIBLE);
          board_->SetChanged();
          Update();
        }
      }
    }
    while (bug_actions < BUG_MOVES_) {
      player_->set_status(Status::NONE);

      for (auto &it : character_arr) {

        Position temp = it.second->get_pos();
        Position temp2 = it.second->Update(board_, NULL, CheckNear(true));

        // frozen
        if (temp2.x == 0) {

          std::string temp = it.second->get_bug_type() + " Bug " +
                             std::to_string(it.second->get_id()) +
                             " is stunned and can't move!";

          hud_.WriteToLog(temp);
          board_->SetChanged();
          if (bug_actions == 1) {
            it.second->set_status(Status::NONE);
          }

        }
        // flying wing attack
        else if (temp2.x == -1) {

          player_->set_resolve_points(player_->get_resolve_points() - 1);
          player_->set_status(Status::FROZEN);
          hud_.lose_resolve();

          std::string temp = it.second->get_bug_type() + " Bug " +
                             std::to_string(it.second->get_id()) +
                             " hit with Flying Wing Attack!";

          hud_.WriteToLog(temp);
          board_->SetChanged();

        }
        // leg crawl assault
        else if (temp2.x == -2) {

          player_->set_resolve_points(player_->get_resolve_points() - 1);
          hud_.lose_resolve();

          std::string temp = it.second->get_bug_type() + " Bug " +
                             std::to_string(it.second->get_id()) +
                             " hit with Leg Crawl Assault!";

          hud_.WriteToLog(temp);
          board_->SetChanged();
        } else if ((board_->TileIsTraversable(temp2))) {

          SwitchTiles(temp, temp2);
          it.second->set_pos(temp2);
        }

        hud_.UpdateNear(CheckNear(true));
        hud_.UpdateInRange(CheckInRange(true));
        if (player_->get_resolve_points() == 0) {
          Lose();
        }
        Update();
        delay_output(100);
      }
      bug_actions++;
    }
    turn_num_++;
    player_actions = 0;
    bug_actions = 0;
    flushinp();
  }

  ExitGame("");
}

void Game::Lose() { ExitGame("YOU LOSE"); }
void Game::Win() { ExitGame("YOU WIN"); }

void Game::ExitGame(std::string why) {

  clear();
  mvaddstr(18, 55, why.c_str());
  refresh();
  board_->ExitBoard();

  // ends curses
  endwin();

  for (auto &it : character_arr) {
    delete it.second;
  }
  character_arr.clear();
  std::cout << "\n Press return to exit...";
  std::cin.get();
  exit(69);
}

void Game::SwitchTiles(Position pos1, Position pos2) {

  TileType tempt = board_->get_board_()[0][pos1.y][pos1.x].get_type();
  TileType tempv = board_->get_board_()[0][pos1.y][pos1.x].get_visible();

  if (!(board_->get_board_()[0][pos2.y][pos2.x].get_visible() ==
        TileType::VISIBLE)) {

    chtype tempch = board_->get_board_()[0][pos1.y][pos1.x].get_tile_symbol();
    board_->get_board_()[0][pos1.y][pos1.x].set_tile_symbol(
        board_->get_board_()[0][pos2.y][pos2.x].get_tile_symbol());
    board_->get_board_()[0][pos2.y][pos2.x].set_tile_symbol(tempch);
  }
  board_->get_board_()[0][pos1.y][pos1.x].set_tile_type(
      board_->get_board_()[0][pos2.y][pos2.x].get_type());
  board_->get_board_()[0][pos2.y][pos2.x].set_tile_type(tempt);

  board_->get_board_()[0][pos1.y][pos1.x].set_visible(
      board_->get_board_()[0][pos2.y][pos2.x].get_visible());
  board_->get_board_()[0][pos2.y][pos2.x].set_visible(tempv);

  board_->SetChanged();
}
