#include <iostream>
#include <string>
#include <vector>
#include <memory>

#include "BoardGame_Classes.h"
#include "XO_Classes.h"

using namespace std;

void play_math_xo() {
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
int main() {

    srand(static_cast<unsigned int>(time(0)));

    int choice;

    do {
        cout << "\n===================================== \n";
        cout << "        BOARD GAMES COLLECTION \n";
        cout << "===================================== \n";
        cout << "1. Mathematical X-O (15 Game) \n";
        cout << "2. Exit \n";
        cout << "===================================== \n";
        cout << "Enter your choice (1-2): ";

        cin >> choice;

        switch (choice) {
        case 1:
            play_math_xo();
            break;
        case 2:
            cout << "Thank you for playing!\n";
            break;
        default:
            cout << "Invalid choice! Please try again.\n";
            break;
        }

    } while (choice != 2);

    return 0;
}
