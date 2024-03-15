#include "util.h"

using namespace std;

void printRules() {
  system("clear");
  cout << "The Royal Game of Ur is an ancient two-player board game that originated in Mesopotamia around 2600 BCE.\n";
  cout << "The game is played on a board with 20 spaces, and each player has seven pieces.\n";
  cout << "The objective is to move all of your pieces from the start to the end of the board before your opponent does.\n";
  cout << "Players take turns rolling dice to determine their moves, and each player moves their pieces according to the number rolled.\n";
  cout << "If a player lands on an opponent's piece, the opponent's piece is sent back to the beginning of the board.\n";
  cout << "Certain spaces on the board (marked by *) are safe spaces and allow a player who lands on one to roll again.\n";
  cout << "The first player to move all their pieces to the end of the board wins the game.\n";
  cout << "In this version of the game, Player 1's pieces are represented by lowercase letters (a-g), and Player 2's pieces are represented by uppercase letters (A-G).\n\n";
  cout << "Press enter when you are ready to play...\n";
  cin.get();
}

void printBoard(const Player &p1, const Player &p2, bool score) {\
if (score) {
    cout << "Player 1 score: " << p1.score << "\n";
    cout << "Player 2 score: " << p2.score << "\n\n";
  }

  printf(" [* %c *] [  %c  ] [  %c  ] [  %c  ]                 [* %c *] [  %c  ]\n", printPiece(p1, p2, 4, 1), printPiece(p1, p2, 3, 1), printPiece(p1, p2, 2, 1), printPiece(p1, p2, 1, 1), printPiece(p1, p2, 14, 1), printPiece(p1, p2, 13, 1));
  printf(" [  %c  ] [  %c  ] [  %c  ] [* %c *] [  %c  ] [  %c  ] [  %c  ] [  %c  ]\n", printPiece(p1, p2, 5, 2), printPiece(p1, p2, 6, 2), printPiece(p1, p2, 7, 2), printPiece(p1, p2, 8, 2), printPiece(p1, p2, 9, 2), printPiece(p1, p2, 10, 2), printPiece(p1, p2, 11, 2), printPiece(p1, p2, 12, 2));
  printf(" [* %c *] [  %c  ] [  %c  ] [  %c  ]                 [* %c *] [  %c  ]\n\n", printPiece(p1, p2, 4, 3), printPiece(p1, p2, 3, 3), printPiece(p1, p2, 2, 3), printPiece(p1, p2, 1, 3), printPiece(p1, p2, 14, 3), printPiece(p1, p2, 13, 3));
}

char printPiece(const Player &p1, const Player &p2, int loc, int row) {
  if (row == 1) {
    return p2.path[loc];
  }
  else if (row == 3) {
    return p1.path[loc];
  }
  else {
    if (p1.path[loc] == ' ') {
      return p2.path[loc];
    }
    else {
      return p1.path[loc];
    }
  }
}

void printStarts(const Player& p, int turn) {
  cout << "Pieces at start: ";
  for (int i = 0; i < 7; i++) {
    if (p.pieces[i] == 0) {
      cout << index2piece(i, turn) << ' ';
    }
  }
  cout << '\n';

  cout << "Pieces at finish: ";
  for (int i = 0; i < 7; i++) {
    if (p.pieces[i] == 15) {
      cout << index2piece(i, turn) << ' ';
    }
  }
  cout << "\n\n";
}

int choice2index(char choice, int player) {
  if (player) {
    return choice - 'A';
  }
  else {
    return choice - 'a';
  }
}

char index2piece(int index, int player) {
  if (player) {
    return index + 'A';
  }
  else {
    return index + 'a';
  }
}
