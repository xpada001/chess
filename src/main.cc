#include <iostream>
#include "Game.h"
#include "ScoreBoard.h"

using namespace std;

int main(void) {
	string command;
	string player1;
	string player2;

	ScoreBoard sb;
	while (cin >> command) {
		if (cin.eof()) {
			break;
		}
		if (command == "game") {
			cin >> player1;
			cin >> player2;
			Game g{player1, player2, &sb};
			string cmd;
			while (cin >> cmd) {
				if (cin.eof()) {
					break;
				}
				if (cmd == "setup") {
					g.setup();
					g.start();
					break;
				} else {
					cout << "Invalid command." << endl;
				}
			}
		} else if (command == "seed") {
			int seed;
			cin >> seed;
			srand(seed);
		} else {
			cout << "Invalid command." << endl;
		}
	}
	cout << sb;
}
