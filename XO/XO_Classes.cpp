#include <iostream>
#include <iomanip>
#include <cctype>
#include "XO_Classes.h"

using namespace std;

MathXO_Board::MathXO_Board() : Board(3, 3){
    for (auto& row : board)
        for (auto& cell : row)
            cell = blank_symbol;
    available_odds = { 1, 3, 5, 7, 9 };
    available_evens = { 2, 4, 6, 8 };
}


ReverseXO_Board::ReverseXO_Board() : Board(3, 3)
{
    for (auto& row : board)
        for (auto& cell : row)
            cell = blank_symbol;
}

bool MathXO_Board::update_board(Move<int>* move) {
    int x = move->get_x();
    int y = move->get_y();
    int num = move->get_symbol();
    if (x < 0 || x >= rows || y < 0 || y >= columns || board[x][y] != blank_symbol) {
        return false;
    }
    n_moves++;
    board[x][y] = num;
    if (num % 2 == 1) {
        auto i = find(available_odds.begin(), available_odds.end(), num);
        if (i != available_odds.end()) {
            available_odds.erase(i);
        }
    }
    else {
        auto i = find(available_evens.begin(), available_evens.end(), num);
        if (i != available_evens.end()) {
            available_evens.erase(i);
        }
    }
    return true;
}

bool ReverseXO_Board::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
    char symbol = move->get_symbol();
    if (!(x < 0 || x >= rows || y < 0 || y >= columns) &&
        (board[x][y] == blank_symbol || symbol == 0)) {

        if (symbol == 0) {
            n_moves--;
            board[x][y] = blank_symbol;
        }
        else {
            n_moves++;
            board[x][y] = toupper(symbol);
        }
        return true;
    }
    return false;
}

bool MathXO_Board::is_win(Player<int>* player) {
    int sum = 15;
    for (int i = 0; i < 3; ++i) {
        int rows = board[i][0] + board[i][1] + board[i][2];
        if (rows == sum && board[i][0] != blank_symbol &&
            board[i][1] != blank_symbol && board[i][2] != blank_symbol) {
            return true;
        }
    }
    for (int j = 0; j < 3; ++j) {
        int cols = board[0][j] + board[1][j] + board[2][j];
        if (cols == sum && board[0][j] != blank_symbol &&
            board[1][j] != blank_symbol && board[2][j] != blank_symbol) {
            return true;
        }
    }
    int diag1 = board[0][0] + board[1][1] + board[2][2];
    int diag2 = board[0][2] + board[1][1] + board[2][0];

    if ((diag1 == sum && board[0][0] != blank_symbol && board[1][1] != blank_symbol && board[2][2] != blank_symbol)
        || (diag2 == sum && board[0][2] != blank_symbol && board[1][1] != blank_symbol && board[2][0] != blank_symbol))
    {
        return true;
    }
    return false;
}

bool ReverseXO_Board::is_win(Player<char>* player) {
    return false;
}

bool ReverseXO_Board::is_lose(Player<char>* player) {
    const char sym = player->get_symbol();

    auto all_equal = [&](char a, char b, char c) {
        return a == b && b == c && a != blank_symbol;
        };

    for (int i = 0; i < rows; ++i) {
        if ((all_equal(board[i][0], board[i][1], board[i][2]) && board[i][0] == sym) ||
            (all_equal(board[0][i], board[1][i], board[2][i]) && board[0][i] == sym))
            return true;
    }

    if ((all_equal(board[0][0], board[1][1], board[2][2]) && board[1][1] == sym) ||
        (all_equal(board[0][2], board[1][1], board[2][0]) && board[1][1] == sym))
        return true;

    return false;
}

bool MathXO_Board::is_draw(Player<int>* player) {
    return (n_moves == 9 && !is_win(player));
}

bool ReverseXO_Board::is_draw(Player<char>* player) {
    return (n_moves == 9 && !is_lose(player) && !is_win(player));
}

bool MathXO_Board::game_is_over(Player<int>* player) {
    return is_win(player) || is_draw(player);
}

bool ReverseXO_Board::game_is_over(Player<char>* player) {
    return is_win(player) || is_lose(player) || is_draw(player);
}

bool MathXO_Board::is_number_available(int number, Player<int>* player)
{
    if (player->get_symbol() == 1) {
        return find(available_odds.begin(), available_odds.end(), number) != available_odds.end();
    }
    else { 
        return find(available_evens.begin(), available_evens.end(), number) != available_evens.end();
    }
}

vector<int> MathXO_Board::get_available_numbers(Player<int>* player)
{
    if (player->get_symbol() == 1) {
        return available_odds;
    }
    else {
        return available_evens;
    }
}

MathXO_UI::MathXO_UI() :UI<int>("", 3) {}

Player<int>* MathXO_UI::create_player(string& name, int symbol, PlayerType type)
{
    cout << "Creating " << (type == PlayerType::HUMAN ? "human" : "computer")
        << " player: " << name << " (uses " <<
        (symbol == 1 ? "odd numbers: 1,3,5,7,9" : "even numbers: 2,4,6,8") << ")\n";

    return new Player<int>(name, symbol, type);
}

Move<int>* MathXO_UI::get_move(Player<int>* player) {
    int x, y, number;
    MathXO_Board* math_board = dynamic_cast<MathXO_Board*>(player->get_board_ptr());

    if (player->get_type() == PlayerType::HUMAN) {
        vector<int> available_nums = math_board->get_available_numbers(player);

        cout << "\n" << player->get_name() << "'s turn, Available numbers: ";
        for (int num : available_nums) {
            cout << num << " ";
        }
        cout <<endl;
        cout << "Enter coordinates (row column, 0-2): ";
        cin >> x >> y;
        cout << "Enter number to place: ";
        cin >> number;

        if (!math_board->is_number_available(number, player)) {
            cout << "Number " << number << " is not available or invalid for your set!\n";
            return get_move(player);
        }
    }
    else if (player->get_type() == PlayerType::COMPUTER) {
        vector<int> available_nums = math_board->get_available_numbers(player);
        do {
            x = rand() % 3;
            y = rand() % 3;
        } while (math_board->get_board_matrix()[x][y] != 0);
        number = available_nums[rand() % available_nums.size()];
        cout << "Computer plays : \n";
    }

    return new Move<int>(x, y, number);
}

Player<int>** MathXO_UI::setup_players() {
    Player<int>** players = new Player<int>*[2];
    vector<string> type_options = { "Human", "Computer" };

    string name1 = get_player_name("Player 1 (Odds)");
    PlayerType type1 = get_player_type_choice("Player 1", type_options);
    players[0] = create_player(name1, 1, type1);

    string name2 = get_player_name("Player 2 (Evens)");
    PlayerType type2 = get_player_type_choice("Player 2", type_options);
    players[1] = create_player(name2, 2, type2);

    return players;
}

ReverseXO_UI::ReverseXO_UI() :UI<char>("", 3) {}

Player<char>* ReverseXO_UI::create_player(string& name, char symbol, PlayerType type) {
    cout << "Creating " << (type == PlayerType::HUMAN ? "human" : "computer")
        << " player: " << name << " (" << symbol << ")\n";
    return new Player<char>(name, symbol, type);
}

Move<char>* ReverseXO_UI::get_move(Player<char>* player) {
    int x, y;

    if (player->get_type() == PlayerType::HUMAN) {
        cout << "\n" << player->get_name() << "'s turn\n";
        cout << "Enter your move x and y (0 to 2): ";
        cin >> x >> y;
    }
    else if (player->get_type() == PlayerType::COMPUTER) {
        x = rand() % player->get_board_ptr()->get_rows();
        y = rand() % player->get_board_ptr()->get_columns();
        cout << "Computer plays : \n";
    }
    return new Move<char>(x, y, player->get_symbol());
}