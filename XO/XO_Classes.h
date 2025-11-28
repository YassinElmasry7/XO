#ifndef XO_CLASSES_H
#define XO_CLASSES_H

#include "BoardGame_Classes.h"
#include <vector>
#include <algorithm>
using namespace std;

class MathXO_Board : public Board<int> {
private:
    vector<int> available_odds;
    vector<int> available_evens;
    int blank_symbol = 0;

public:
    MathXO_Board();
    bool update_board(Move<int>* move);
    bool is_win(Player<int>* player);
    bool is_lose(Player<int>* player) { return false; }
    bool is_draw(Player<int>* player);
    bool game_is_over(Player<int>* player);

    bool is_number_available(int number, Player<int>* player);
    vector<int> get_available_numbers(Player<int>* player);
};

class ReverseXO_Board : public Board<char> {
private:
    char blank_symbol = '.';
public:
    ReverseXO_Board();
    bool update_board(Move<char>* move);
    bool is_win(Player<char>* player);
    bool is_lose(Player<char>* player);
    bool is_draw(Player<char>* player);
    bool game_is_over(Player<char>* player);
};

class ObstacleXO_Board : public Board<char> {
private:
    char blank_symbol = '.';
    char obstacle_symbol = '#';
    int round_count = 0;

    void add_random_obstacles();
    bool has_four_in_row(char symbol);

public:
    ObstacleXO_Board();
    bool update_board(Move<char>* move);
    bool is_win(Player<char>* player);
    bool is_lose(Player<char>* player) { return false; }
    bool is_draw(Player<char>* player);
    bool game_is_over(Player<char>* player);

    int get_round_count() const { return round_count; }
};

class FiveXFive_Board : public Board<char> {
private:
    char blank_symbol = '.';
    int final_scoreX = 0;
    int final_scoreO = 0;

    int count_three_in_row(char symbol);

    void calculate_final_scores();

public:
    FiveXFive_Board();
    bool update_board(Move<char>* move);
    bool is_win(Player<char>* player);
    bool is_lose(Player<char>* player) { return false; }
    bool is_draw(Player<char>* player);
    bool game_is_over(Player<char>* player);

    int get_player_score(char symbol);
};

class FourXFour_Board : public Board<char> {
private:
    char blank_symbol = '.';
    vector<pair<int, int>> playerX_pieces;
    vector<pair<int, int>> playerO_pieces;

    bool isValidMove(int from_x, int from_y, int to_x, int to_y, char symbol);
    bool isAdjacent(int from_x, int from_y, int to_x, int to_y);
    void initializeStartingPositions();

public:
    FourXFour_Board();
    bool update_board(Move<char>* move);
    bool is_win(Player<char>* player);
    bool is_lose(Player<char>* player) { return false; }
    bool is_draw(Player<char>* player);
    bool game_is_over(Player<char>* player);

    vector<pair<int, int>> get_player_pieces(char symbol);
    bool has_three_in_row(char symbol);
};

class ConnectFour_Board : public Board<char> {
private:
    char blank_symbol = '.';

public:
    ConnectFour_Board();
    bool update_board(Move<char>* move);
    bool is_win(Player<char>* player);
    bool is_lose(Player<char>* player) { return false; }
    bool is_draw(Player<char>* player);
    bool game_is_over(Player<char>* player);

    bool is_column_full(int col);
    int get_lowest_empty_row(int col);
    bool check_four_in_line(char symbol);
};

class MathXO_UI : public UI<int> {
public:
    MathXO_UI();
    ~MathXO_UI() {};
    Player<int>* create_player(string& name, int symbol, PlayerType type);
    virtual Move<int>* get_move(Player<int>* player);
    virtual Player<int>** setup_players();
};

class ReverseXO_UI : public UI<char> {
public:
    ReverseXO_UI();
    ~ReverseXO_UI() {};
    Player<char>* create_player(string& name, char symbol, PlayerType type);
    virtual Move<char>* get_move(Player<char>* player);
};

class ObstacleXO_UI : public UI<char> {
public:
    ObstacleXO_UI();
    ~ObstacleXO_UI() {};
    Player<char>* create_player(string& name, char symbol, PlayerType type);
    virtual Move<char>* get_move(Player<char>* player);
};

class FiveXFive_UI : public UI<char> {
public:
    FiveXFive_UI();
    ~FiveXFive_UI() {};
    Player<char>* create_player(string& name, char symbol, PlayerType type);
    virtual Move<char>* get_move(Player<char>* player);
};

class FourXFour_UI : public UI<char> {
public:
    FourXFour_UI();
    ~FourXFour_UI() {};
    Player<char>* create_player(string& name, char symbol, PlayerType type);
    virtual Move<char>* get_move(Player<char>* player);
    virtual void display_board_matrix(const vector<vector<char>>& matrix) const;
};

class ConnectFour_UI : public UI<char> {
public:
	ConnectFour_UI();
	~ConnectFour_UI() {};
    Player<char>* create_player(string& name, char symbol, PlayerType type);
    virtual Move<char>* get_move(Player<char>* player);
};

#endif // XO_CLASSES_H