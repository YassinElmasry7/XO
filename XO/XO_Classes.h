#ifndef XO_CLASSES_H
#define XO_CLASSES_H

#include "BoardGame_Classes.h"
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

class MathXO_UI : public UI<int> {
public:
    MathXO_UI();
    ~MathXO_UI() {};
    Player<int>* create_player(string& name, int symbol, PlayerType type);
    virtual Move<int>* get_move(Player<int>* player);
    virtual Player<int>** setup_players();
};

#endif // XO_CLASSES_H
