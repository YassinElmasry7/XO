#ifndef XO_CLASSES_H
#define XO_CLASSES_H

#include "BoardGame_Classes.h"
#include <vector>
#include <string>
#include <unordered_set>
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

class DiamondXO_Board : public Board<char> {
private:
    char blank_symbol = '.';
    vector<vector<bool>> valid_cells;

    bool has_three_horizontal(char symbol);
    bool has_three_vertical(char symbol);
    bool has_three_diagonal1(char symbol); // top-left to bottom-right
    bool has_three_diagonal2(char symbol); // top-right to bottom-left

    bool has_four_horizontal(char symbol);
    bool has_four_vertical(char symbol);
    bool has_four_diagonal1(char symbol); // top-left to bottom-right
    bool has_four_diagonal2(char symbol); // top-right to bottom-left

    void initialize_diamond_shape();

public:
    DiamondXO_Board();
    bool update_board(Move<char>* move);
    bool is_win(Player<char>* player);
    bool is_lose(Player<char>* player) { return false; }
    bool is_draw(Player<char>* player);
    bool game_is_over(Player<char>* player);

    bool is_valid_cell(int x, int y) const;
    int get_diamond_size() const { return 7; }
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

class DiamondXO_UI : public UI<char> {
public:
    DiamondXO_UI();
    ~DiamondXO_UI() {};
    Player<char>* create_player(string& name, char symbol, PlayerType type);
    virtual Move<char>* get_move(Player<char>* player);
    virtual void display_board_matrix(const vector<vector<char>>& matrix) const;
};
class WordXO_Board : public Board<char> {
private:
    char blank_symbol = '.';
    unordered_set<string> dictionary;

    void load_dictionary(const string& filename);
    bool is_valid_word(const string& word) const;
    string get_cells_as_string(int x1, int y1, int x2, int y2, int x3, int y3) const;

public:
    WordXO_Board();
    bool update_board(Move<char>* move);
    bool is_win(Player<char>* player);
    bool is_lose(Player<char>* player) { return false; }
    bool is_draw(Player<char>* player);
    bool game_is_over(Player<char>* player);
};

class WordXO_UI : public UI<char> {
public:
    WordXO_UI();
    ~WordXO_UI() {};
    Player<char>* create_player(string& name, char symbol, PlayerType type);
    virtual Move<char>* get_move(Player<char>* player);
};
class PyramidXO_Board : public Board<char> {
private:
    char blank_symbol = '.';
    vector<vector<bool>> valid_cells;
    int cols = 5;

    void initialize_pyramid_shape();
    bool check_win(char symbol);

public:
    PyramidXO_Board();
    bool update_board(Move<char>* move);
    bool is_win(Player<char>* player);
    bool is_lose(Player<char>* player) { return false; }
    bool is_draw(Player<char>* player);
    bool game_is_over(Player<char>* player);

    bool is_valid_cell(int x, int y) const;
};

class PyramidXO_UI : public UI<char> {
public:
    PyramidXO_UI();
    ~PyramidXO_UI() {};
    Player<char>* create_player(string& name, char symbol, PlayerType type);
    virtual Move<char>* get_move(Player<char>* player);
    virtual void display_board_matrix(const vector<vector<char>>& matrix) const;
};

class InfinityXO_Board : public Board<char> {
private:
    char blank_symbol = '.';
    vector<pair<pair<int, int>, char>> move_history; // Track moves in chronological order
    int moves_since_last_removal = 0;

    void remove_oldest_move();
    bool has_three_in_row(char symbol);

public:
    InfinityXO_Board();
    bool update_board(Move<char>* move);
    bool is_win(Player<char>* player);
    bool is_lose(Player<char>* player) { return false; }
    bool is_draw(Player<char>* player);
    bool game_is_over(Player<char>* player);

    int get_moves_since_last_removal() const { return moves_since_last_removal; }
    int get_total_moves() const { return n_moves; }
};

class InfinityXO_UI : public UI<char> {
public:
    InfinityXO_UI();
    ~InfinityXO_UI() {};
    Player<char>* create_player(string& name, char symbol, PlayerType type);
    virtual Move<char>* get_move(Player<char>* player);
};


#endif // XO_CLASSES_H