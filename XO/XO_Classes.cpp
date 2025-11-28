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

MathXO_UI::MathXO_UI() : UI<int>("", 3) {}

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
        cout << "Computer plays number " << number << " at position (" << x << "," << y << ")\n";
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

ReverseXO_UI::ReverseXO_UI() : UI<char>("", 3) {}

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
        ReverseXO_Board* reverse_board = dynamic_cast<ReverseXO_Board*>(player->get_board_ptr());
        do {
            x = rand() % player->get_board_ptr()->get_rows();
            y = rand() % player->get_board_ptr()->get_columns();
        } while (reverse_board->get_board_matrix()[x][y] != '.');

        cout << "Computer plays at position (" << x << "," << y << ")\n";
    }

    return new Move<char>(x, y, player->get_symbol());
}

ObstacleXO_Board::ObstacleXO_Board() : Board(6, 6) {
    for (auto& row : board)
        for (auto& cell : row)
            cell = blank_symbol;
}

bool ObstacleXO_Board::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
    char mark = move->get_symbol();

    if (x < 0 || x >= rows || y < 0 || y >= columns ||
        board[x][y] != blank_symbol) {
        return false;
    }
    n_moves++;
    board[x][y] = toupper(mark);

    if (n_moves % 2 == 0) {
        round_count++;
        add_random_obstacles();
    }
    return true;
}

void ObstacleXO_Board::add_random_obstacles() {
    int obstacles_added = 0;
    int max_attempts = 20;
    while (obstacles_added < 2 && max_attempts-- > 0) {
        int x = rand() % rows;
        int y = rand() % columns;

        if (board[x][y] == blank_symbol) {
            board[x][y] = obstacle_symbol;
            obstacles_added++;
        }
    }
}

bool ObstacleXO_Board::is_win(Player<char>* player) {
    char symbol = player->get_symbol();
    return has_four_in_row(symbol);
}

bool ObstacleXO_Board::has_four_in_row(char symbol) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j <= columns - 4; ++j) {
            if (board[i][j] == symbol && board[i][j + 1] == symbol &&
                board[i][j + 2] == symbol && board[i][j + 3] == symbol) {
                return true;
            }
        }
    }
    for (int j = 0; j < columns; ++j) {
        for (int i = 0; i <= rows - 4; ++i) {
            if (board[i][j] == symbol && board[i + 1][j] == symbol &&
                board[i + 2][j] == symbol && board[i + 3][j] == symbol) {
                return true;
            }
        }
    }
    for (int i = 0; i <= rows - 4; ++i) {
        for (int j = 0; j <= columns - 4; ++j) {
            if (board[i][j] == symbol && board[i + 1][j + 1] == symbol &&
                board[i + 2][j + 2] == symbol && board[i + 3][j + 3] == symbol) {
                return true;
            }
        }
    }
    for (int i = 0; i <= rows - 4; ++i) {
        for (int j = 3; j < columns; ++j) {
            if (board[i][j] == symbol && board[i + 1][j - 1] == symbol &&
                board[i + 2][j - 2] == symbol && board[i + 3][j - 3] == symbol) {
                return true;
            }
        }
    }

    return false;
}

bool ObstacleXO_Board::is_draw(Player<char>* player) {
    int empty_cells = 0;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            if (board[i][j] == blank_symbol) {
                empty_cells++;
            }
        }
    }
    return (empty_cells == 0 && !is_win(player));
}

bool ObstacleXO_Board::game_is_over(Player<char>* player) {
    return is_win(player) || is_draw(player);
}

ObstacleXO_UI::ObstacleXO_UI() : UI<char>("", 3) {}

Player<char>* ObstacleXO_UI::create_player(string& name, char symbol, PlayerType type) {
    cout << "Creating " << (type == PlayerType::HUMAN ? "human" : "computer")
        << " player: " << name << " (" << symbol << ")\n";
    return new Player<char>(name, symbol, type);
}

Move<char>* ObstacleXO_UI::get_move(Player<char>* player) {
    int x, y;

    if (player->get_type() == PlayerType::HUMAN) {
        cout << "\n" << player->get_name() << "'s turn (" << player->get_symbol() << ")\n";
        cout << "Enter coordinates (row column, 0-5): ";
        cin >> x >> y;
    }
    else if (player->get_type() == PlayerType::COMPUTER) {
        ObstacleXO_Board* obstacle_board = dynamic_cast<ObstacleXO_Board*>(player->get_board_ptr());
        do {
            x = rand() % 6;
            y = rand() % 6;
        } while (obstacle_board->get_board_matrix()[x][y] != '.');

        cout << "Computer plays at position (" << x << "," << y << ")\n";
    }
    return new Move<char>(x, y, player->get_symbol());
}

FiveXFive_Board::FiveXFive_Board() : Board(5, 5) {
    for (auto& row : board)
        for (auto& cell : row)
            cell = blank_symbol;
}

bool FiveXFive_Board::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
    char symbol = move->get_symbol();

    if (x < 0 || x >= rows || y < 0 || y >= columns || board[x][y] != blank_symbol) {
        return false;
    }

    n_moves++;
    board[x][y] = toupper(symbol);
    return true;
}

int FiveXFive_Board::count_three_in_row(char symbol) {
    int count = 0;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
           
            if (j <= columns - 3) {
                if (board[i][j] == symbol && board[i][j + 1] == symbol && board[i][j + 2] == symbol)
                    count++;
            }
            
            if (i <= rows - 3) {
                if (board[i][j] == symbol && board[i + 1][j] == symbol && board[i + 2][j] == symbol)
                    count++;
            }
         
            if (i <= rows - 3 && j <= columns - 3) {
                if (board[i][j] == symbol && board[i + 1][j + 1] == symbol && board[i + 2][j + 2] == symbol)
                    count++;
            }
      
            if (i <= rows - 3 && j >= 2) {
                if (board[i][j] == symbol && board[i + 1][j - 1] == symbol && board[i + 2][j - 2] == symbol)
                    count++;
            }
        }
    }
    return count;
}

void FiveXFive_Board::calculate_final_scores() {
    if (final_scoreX == 0) { 
        final_scoreX = count_three_in_row('X');
        final_scoreO = count_three_in_row('O');
    }
}

bool FiveXFive_Board::is_win(Player<char>* player) {
    if (n_moves < 24) return false;

    calculate_final_scores();

    if (player->get_symbol() == 'X') {
        return final_scoreX > final_scoreO;
    }
    else {
        return final_scoreO > final_scoreX;
    }
}

bool FiveXFive_Board::is_draw(Player<char>* player) {
    if (n_moves < 24) return false;

    calculate_final_scores();
    return final_scoreX == final_scoreO;
}

bool FiveXFive_Board::game_is_over(Player<char>* player) {
    return (n_moves == 24);
}

int FiveXFive_Board::get_player_score(char symbol) {
    calculate_final_scores();
    return (symbol == 'X') ? final_scoreX : final_scoreO;
}

FiveXFive_UI::FiveXFive_UI() : UI<char>("", 3) {}

Player<char>* FiveXFive_UI::create_player(string& name, char symbol, PlayerType type) {
    cout << "Creating " << (type == PlayerType::HUMAN ? "human" : "computer")
        << " player: " << name << " (" << symbol << ")\n";
    return new Player<char>(name, symbol, type);
}

Move<char>* FiveXFive_UI::get_move(Player<char>* player) {
    int x, y;

    if (player->get_type() == PlayerType::HUMAN) {
        cout << "\n" << player->get_name() << "'s turn (" << player->get_symbol() << ")\n";
        cout << "Enter coordinates (row column, 0-4): ";
        cin >> x >> y;
    }
    else if (player->get_type() == PlayerType::COMPUTER) {
        do {
            x = rand() % 5;
            y = rand() % 5;
        } while (dynamic_cast<FiveXFive_Board*>(player->get_board_ptr())->get_board_matrix()[x][y] != '.');
        cout << "Computer plays at position (" << x << "," << y << ")\n";
    }
    return new Move<char>(x, y, player->get_symbol());
}

FourXFour_Board::FourXFour_Board() : Board(4, 4) {
    for (auto& row : board)
        for (auto& cell : row)
            cell = blank_symbol;

    initializeStartingPositions();
}

void FourXFour_Board::initializeStartingPositions() {

    board[0][0] = 'X'; board[0][1] = 'O'; board[0][2] = 'X'; board[0][3] = 'O';
    board[3][0] = 'O'; board[3][1] = 'X'; board[3][2] = 'O'; board[3][3] = 'X';
    playerX_pieces = { {0,0}, {0,2}, {3,1}, {3,3} };
    playerO_pieces = { {0,1}, {0,3}, {3,0}, {3,2} };
}

bool FourXFour_Board::isAdjacent(int from_x, int from_y, int to_x, int to_y) {

    int dx = abs(from_x - to_x);
    int dy = abs(from_y - to_y);
    return (dx == 1 && dy == 0) || (dx == 0 && dy == 1);
}

bool FourXFour_Board::isValidMove(int from_x, int from_y, int to_x, int to_y, char symbol) {

    if (from_x < 0 || from_x >= rows || from_y < 0 || from_y >= columns ||
        to_x < 0 || to_x >= rows || to_y < 0 || to_y >= columns) {
        return false;
    }

    if (board[from_x][from_y] != symbol) {
        return false;
    }

    if (board[to_x][to_y] != blank_symbol) {
        return false;
    }

    if (!isAdjacent(from_x, from_y, to_x, to_y)) {
        return false;
    }

    return true;
}

bool FourXFour_Board::update_board(Move<char>* move) {
    int combined_x = move->get_x();
    int combined_y = move->get_y();
    char symbol = move->get_symbol();


    int from_x = combined_x / 10;
    int to_x = combined_x % 10;
    int from_y = combined_y / 10;
    int to_y = combined_y % 10;


    if (!isValidMove(from_x, from_y, to_x, to_y, symbol)) {
        return false;
    }

    board[from_x][from_y] = blank_symbol;
    board[to_x][to_y] = symbol;
    n_moves++;

    if (symbol == 'X') {
        for (auto& piece : playerX_pieces) {
            if (piece.first == from_x && piece.second == from_y) {
                piece.first = to_x;
                piece.second = to_y;
                break;
            }
        }
    }
    else {
        for (auto& piece : playerO_pieces) {
            if (piece.first == from_x && piece.second == from_y) {
                piece.first = to_x;
                piece.second = to_y;
                break;
            }
        }
    }

    return true;
}

bool FourXFour_Board::has_three_in_row(char symbol) {

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j <= columns - 3; j++) {
            if (board[i][j] == symbol && board[i][j + 1] == symbol && board[i][j + 2] == symbol)
                return true;
        }
    }

    for (int j = 0; j < columns; j++) {
        for (int i = 0; i <= rows - 3; i++) {
            if (board[i][j] == symbol && board[i + 1][j] == symbol && board[i + 2][j] == symbol)
                return true;
        }
    }

    for (int i = 0; i <= rows - 3; i++) {
        for (int j = 0; j <= columns - 3; j++) {
            if (board[i][j] == symbol && board[i + 1][j + 1] == symbol && board[i + 2][j + 2] == symbol)
                return true;
        }
    }

    for (int i = 0; i <= rows - 3; i++) {
        for (int j = 2; j < columns; j++) {
            if (board[i][j] == symbol && board[i + 1][j - 1] == symbol && board[i + 2][j - 2] == symbol)
                return true;
        }
    }

    return false;
}

bool FourXFour_Board::is_win(Player<char>* player) {
    return has_three_in_row(player->get_symbol());
}

bool FourXFour_Board::is_draw(Player<char>* player) {

    return n_moves > 50;
}

bool FourXFour_Board::game_is_over(Player<char>* player) {
    return is_win(player) || is_draw(player);
}

vector<pair<int, int>> FourXFour_Board::get_player_pieces(char symbol) {
    vector<pair<int, int>> pieces;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            if (board[i][j] == symbol) {
                pieces.push_back({ i, j });
            }
        }
    }
    return pieces;
}

FourXFour_UI::FourXFour_UI() : UI<char>("", 3) {}

Player<char>* FourXFour_UI::create_player(string& name, char symbol, PlayerType type) {
    cout << "Creating " << (type == PlayerType::HUMAN ? "human" : "computer")
        << " player: " << name << " (" << symbol << ")\n";
    return new Player<char>(name, symbol, type);
}

void FourXFour_UI::display_board_matrix(const vector<vector<char>>& matrix) const {
    if (matrix.empty() || matrix[0].empty()) return;

    int rows = matrix.size();
    int cols = matrix[0].size();

    cout << "\n    ";
    for (int j = 0; j < cols; ++j)
        cout << setw(cell_width + 1) << j;
    cout << "\n   " << string((cell_width + 2) * cols, '-') << "\n";

    for (int i = 0; i < rows; ++i) {
        cout << setw(2) << i << " |";
        for (int j = 0; j < cols; ++j)
            cout << setw(cell_width) << matrix[i][j] << " |";
        cout << "\n   " << string((cell_width + 2) * cols, '-') << "\n";
    }
    cout << endl;
}

Move<char>* FourXFour_UI::get_move(Player<char>* player) {
    FourXFour_Board* four_board = dynamic_cast<FourXFour_Board*>(player->get_board_ptr());
    char symbol = player->get_symbol();

    if (player->get_type() == PlayerType::HUMAN) {
        cout << "\n" << player->get_name() << "'s turn (" << symbol << ")\n";

        vector<pair<int, int>> pieces = four_board->get_player_pieces(symbol);

        cout << "Your pieces are at: ";
        for (auto& piece : pieces) {
            cout << "(" << piece.first << "," << piece.second << ") ";
        }
        cout << endl;

        int from_x, from_y, to_x, to_y;

        cout << "Enter source coordinates (row column) of piece to move: ";
        cin >> from_x >> from_y;

        cout << "Enter destination coordinates (row column): ";
        cin >> to_x >> to_y;

        if (from_x < 0 || from_x >= 4 || from_y < 0 || from_y >= 4 ||
            to_x < 0 || to_x >= 4 || to_y < 0 || to_y >= 4) {
            cout << "Invalid coordinates! Please enter values between 0-3.\n";
            return get_move(player);
        }

        int dx = abs(from_x - to_x);
        int dy = abs(from_y - to_y);

        if (!((dx == 1 && dy == 0) || (dx == 0 && dy == 1))) {
            cout << "Invalid move! You can only move to adjacent cells (horizontal or vertical).\n";
            return get_move(player);
        }

        if (four_board->get_board_matrix()[to_x][to_y] != '.') {
            cout << "Destination cell is not empty!\n";
            return get_move(player);
        }

        if (four_board->get_board_matrix()[from_x][from_y] != symbol) {
            cout << "You don't have a piece at the source location!\n";
            return get_move(player);
        }


        return new Move<char>(from_x * 10 + to_x, from_y * 10 + to_y, symbol);

    }
    else if (player->get_type() == PlayerType::COMPUTER) {

        vector<pair<int, int>> pieces = four_board->get_player_pieces(symbol);

        for (int attempts = 0; attempts < 100; attempts++) {
            int piece_idx = rand() % pieces.size();
            int from_x = pieces[piece_idx].first;
            int from_y = pieces[piece_idx].second;


            int directions[4][2] = { {0,1}, {1,0}, {0,-1}, {-1,0} };

            for (int i = 0; i < 4; i++) {
                int to_x = from_x + directions[i][0];
                int to_y = from_y + directions[i][1];

                if (to_x >= 0 && to_x < 4 && to_y >= 0 && to_y < 4 &&
                    four_board->get_board_matrix()[to_x][to_y] == '.') {
                    cout << "Computer moves piece from (" << from_x << "," << from_y
                        << ") to (" << to_x << "," << to_y << ")\n";
                    return new Move<char>(from_x * 10 + to_x, from_y * 10 + to_y, symbol);
                }
            }
        }


        return new Move<char>(0, 0, symbol);
    }

    return new Move<char>(0, 0, symbol);
}

ConnectFour_Board::ConnectFour_Board() : Board(6, 7) {
    for (auto& row : board)
        for (auto& cell : row)
            cell = blank_symbol;
}

bool ConnectFour_Board::update_board(Move<char>* move) {
    int column = move->get_y();
    char symbol = move->get_symbol();

    if (column < 0 || column >= columns || is_column_full(column)) {
        return false;
    }

    int row = get_lowest_empty_row(column);
    if (row == -1) {
        return false;
    }

    n_moves++;
    board[row][column] = toupper(symbol);
    return true;
}

bool ConnectFour_Board::is_column_full(int col) {
    return board[0][col] != blank_symbol;
}

int ConnectFour_Board::get_lowest_empty_row(int col) {
    for (int row = rows - 1; row >= 0; row--) {
        if (board[row][col] == blank_symbol) {
            return row;
        }
    }
    return -1;
}

bool ConnectFour_Board::check_four_in_line(char symbol) {
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col <= columns - 4; col++) {
            if (board[row][col] == symbol && board[row][col + 1] == symbol &&
                board[row][col + 2] == symbol && board[row][col + 3] == symbol) {
                return true;
            }
        }
    }
    for (int row = 0; row <= rows - 4; row++) {
        for (int col = 0; col < columns; col++) {
            if (board[row][col] == symbol &&board[row + 1][col] == symbol &&
                board[row + 2][col] == symbol && board[row + 3][col] == symbol) {
                return true;
            }
        }
    }
    for (int row = 0; row <= rows - 4; row++) {
        for (int col = 0; col <= columns - 4; col++) {
            if (board[row][col] == symbol &&board[row + 1][col + 1] == symbol &&
                board[row + 2][col + 2] == symbol &&board[row + 3][col + 3] == symbol) {
                return true;
            }
        }
    }
    for (int row = 0; row <= rows - 4; ++row) {
        for (int col = 3; col < columns; ++col) {
            if (board[row][col] == symbol &&board[row + 1][col - 1] == symbol &&
                board[row + 2][col - 2] == symbol &&board[row + 3][col - 3] == symbol) {
                return true;
            }
        }
    }
    return false;
}

bool ConnectFour_Board::is_win(Player<char>* player) {
    return check_four_in_line(player->get_symbol());
}

bool ConnectFour_Board::is_draw(Player<char>* player) {
    for (int col = 0; col < columns; col++) {
        if (!is_column_full(col)) {
            return false;
        }
    }
    return !is_win(player);
}

bool ConnectFour_Board::game_is_over(Player<char>* player) {
    return is_win(player) || is_draw(player);
}

ConnectFour_UI::ConnectFour_UI() :UI<char>("", 3){}

Player<char>* ConnectFour_UI::create_player(string& name, char symbol, PlayerType type) {
    cout << "Creating " << (type == PlayerType::HUMAN ? "human" : "computer")
        << " player: " << name << " (" << symbol << ")\n";
    return new Player<char>(name, symbol, type);
}

Move<char>* ConnectFour_UI::get_move(Player<char>* player) {
    int col;
    ConnectFour_Board* connect4_board = dynamic_cast<ConnectFour_Board*>(player->get_board_ptr());

    if (player->get_type() == PlayerType::HUMAN) {
        cout << "\n" << player->get_name() << "'s turn (" << player->get_symbol() << ")\n";
        cout << "Available columns: ";
        for (int c = 0; c < 7; ++c) {
            if (!connect4_board->is_column_full(c)) {
                cout << c << " ";
            }
        }
        cout << endl;
        cout << "Enter column number (0-6): ";
        cin >> col;

        if (col < 0 || col >= 7 || connect4_board->is_column_full(col)) {
            cout << "Invalid column! Please choose an available column.\n";
            return get_move(player);
        }

        int row = connect4_board->get_lowest_empty_row(col);
        cout << "Placing piece at column " << col << ", row " << row << endl;

    }
    else if (player->get_type() == PlayerType::COMPUTER) {
        vector<int> available_columns;
        for (int c = 0; c < 7; ++c) {
            if (!connect4_board->is_column_full(c)) {
                available_columns.push_back(c);
            }
        }

        if (available_columns.empty()) {
            col = 0;
        }
        else {
            col = available_columns[rand() % available_columns.size()];
        }

        int row = connect4_board->get_lowest_empty_row(col);
        cout << "Computer plays at column " << col << endl;
    }
    return new Move<char>(0, col, player->get_symbol());
}