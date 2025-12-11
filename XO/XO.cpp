 /**
  * @file main.cpp
  * @brief This is the main file to run all XO derived classes
  */
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <memory>
#include <cstdlib>
#include <ctime>
#include "BoardGame_Classes.h"
#include "XO_Classes.h"

using namespace std;

void play_math_xo(){
    cout << "\n=== Starting Mathematical X-O Game (15 Game) ===\n";
    UI<int>* game_ui = new MathXO_UI();
    Board<int>* math_board = new MathXO_Board();
    Player<int>** players = game_ui->setup_players();

    GameManager<int> game(math_board, players, game_ui);
    game.run();

    delete math_board;
    for (int i = 0; i < 2; ++i) delete players[i];
    delete[] players;
    delete game_ui;
}

void play_sus_xo() {
    cout << "SUS Game Started (Win by highest S-U-S sequences)" << endl;

    UI<char>* game_ui = new SUS_UI();
    Board<char>* game_board = new SUS_Board();
    Player<char>** players = game_ui->setup_players();

    GameManager<char> game(game_board, players, game_ui);
    game.run();

    SUS_Board* sus_board = dynamic_cast<SUS_Board*>(game_board);

    if (sus_board) {
        if (sus_board->game_is_over(nullptr)) {
            cout << "\n--- Final Results ---\n";
            cout << sus_board->get_final_result_message(players);
        }
    }

    delete sus_board;
    for (int i = 0; i < 2; ++i) delete players[i];
    delete[] players;
    delete game_ui;
}

void play_reverse_xo() {
    cout << "\n=== Starting Reverse X-O Game ===\n";
    UI<char>* game_ui = new ReverseXO_UI();
    Board<char>* reverse_board = new ReverseXO_Board();
    Player<char>** players = game_ui->setup_players();

    GameManager<char> game(reverse_board, players, game_ui);
    game.run();

    delete reverse_board;
    for (int i = 0; i < 2; ++i) delete players[i];
    delete[] players;
    delete game_ui;
}

void play_obstacle_xo() {
    cout << "\n=== Starting Obstacle X-O Game ===\n";
    UI<char>* game_ui = new ObstacleXO_UI();
    Board<char>* obstacle_board = new ObstacleXO_Board();
    Player<char>** players = game_ui->setup_players();

    GameManager<char> game(obstacle_board, players, game_ui);
    game.run();

    delete obstacle_board;
    for (int i = 0; i < 2; ++i) delete players[i];
    delete[] players;
    delete game_ui;
}

void play_five_x_five() {
    cout << "\n=== Starting 5x5 Tic Tac Toe ===\n";
    UI<char>* game_ui = new FiveXFive_UI();
    Board<char>* five_board = new FiveXFive_Board();
    Player<char>** players = game_ui->setup_players();

    GameManager<char> game(five_board, players, game_ui);
    game.run();

    FiveXFive_Board* final_board = dynamic_cast<FiveXFive_Board*>(five_board);
    int scoreX = final_board->get_player_score('X');
    int scoreO = final_board->get_player_score('O');

    cout << "\n=== FINAL SCORES ===\n";
    cout << players[0]->get_name() << " (X): " << scoreX << " three-in-a-row sequences\n";
    cout << players[1]->get_name() << " (O): " << scoreO << " three-in-a-row sequences\n";

    delete five_board;
    for (int i = 0; i < 2; ++i) delete players[i];
    delete[] players;
    delete game_ui;
}

void play_four_x_four() {
    cout << "\n=== Starting 4x4 Tic Tac Toe ===\n";
    UI<char>* game_ui = new FourXFour_UI();
    Board<char>* four_board = new FourXFour_Board();
    Player<char>** players = game_ui->setup_players();

    GameManager<char> game(four_board, players, game_ui);
    game.run();

    delete four_board;
    for (int i = 0; i < 2; ++i) delete players[i];
    delete[] players;
    delete game_ui;
}

void play_connect_four() {
    cout << "\n=== Starting Connect Four ===\n";
    UI<char>* game_ui = new ConnectFour_UI();
    Board<char>* connect4_board = new ConnectFour_Board();
    Player<char>** players = game_ui->setup_players();

    GameManager<char> game(connect4_board, players, game_ui);
    game.run();

    delete connect4_board;
    for (int i = 0; i < 2; ++i) delete players[i];
    delete[] players;
    delete game_ui;
}

void play_diamond_xo() {
    cout << "\n=== Starting Diamond X-O Game ===\n";
	UI<char>* game_ui = new DiamondXO_UI();
    Board<char>* diamond_board = new DiamondXO_Board();
    Player<char>** players = game_ui->setup_players();

    GameManager<char> game(diamond_board, players, game_ui);
    game.run();

    delete diamond_board;
    for (int i = 0; i < 2; ++i) delete players[i];
    delete[] players;
	delete game_ui;
}
void play_word_xo() {
    cout << "\n=== Starting Word Tic-Tac-Toe ===\n";
    UI<char>* game_ui = new WordXO_UI();
    Board<char>* word_board = new WordXO_Board();
    Player<char>** players = game_ui->setup_players();

    GameManager<char> game(word_board, players, game_ui);
    game.run();

    delete word_board;
    for (int i = 0; i < 2; ++i) delete players[i];
    delete[] players;
    delete game_ui;
}
void play_pyramid_xo() {
    cout << "\n=== Starting Pyramid Tic-Tac-Toe ===\n";
    UI<char>* game_ui = new PyramidXO_UI();
    Board<char>* pyramid_board = new PyramidXO_Board();
    Player<char>** players = game_ui->setup_players();

    GameManager<char> game(pyramid_board, players, game_ui);
    game.run();

    delete pyramid_board;
    for (int i = 0; i < 2; ++i) delete players[i];
    delete[] players;
    delete game_ui;
}
void play_infinity_xo() {
    UI<char>* game_ui = new InfinityXO_UI();
    Board<char>* infinity_board = new InfinityXO_Board();
    Player<char>** players = game_ui->setup_players();

    GameManager<char> game(infinity_board, players, game_ui);
    game.run();

    delete infinity_board;
    for (int i = 0; i < 2; ++i) delete players[i];
    delete[] players;
    delete game_ui;
}

int main() {
    srand(static_cast<unsigned int>(time(0)));

    int choice;

    do {
        cout << "\n===================================== \n";
        cout << "        BOARD GAMES COLLECTION \n";
        cout << "===================================== \n";
		cout << "1. SUS X-O\n";
        cout << "2. Mathematical X-O \n";
        cout << "3. Reverse X-O \n";
        cout << "4. Obstacle X-O \n";
        cout << "5. 5x5 X-O \n";
        cout << "6. 4x4 X-O \n";
        cout << "7. Connect Four X-O\n";
        cout << "8. Diamond X-O \n";
        cout << "9. Word Tic-Tac-Toe \n";
        cout << "10. Pyramid X-O \n";
        cout << "11. Infinity Tic-Tac-Toe \n";
        cout << "12. Exit \n";
        cout << "===================================== \n";
        cout << "Enter your choice (1-12): ";

        cin >> choice;

        switch (choice) {
            case 1:
                play_sus_xo();
                break;
            case 2:
                play_math_xo();
                break;
            case 3:
                play_reverse_xo();
                break;
            case 4:
                play_obstacle_xo();
                break;
            case 5:
                play_five_x_five();
                break;
            case 6:
                play_four_x_four();
                break;
            case 7:
                play_connect_four();
                break;
            case 8:
                play_diamond_xo();
                break;
            case 9:
                play_word_xo();
                break;
            case 10:
                play_pyramid_xo();
                break;
            case 11:
                play_infinity_xo();
                break;
            case 12:
                cout << "Thank you for playing!\n";
                break;
            default:
                cout << "Invalid choice! Please try again.\n";
                break;
        }

    } while (choice != 12);

    return 0;
}