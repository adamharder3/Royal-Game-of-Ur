#include <iostream>
#include <vector>

class Player {
  public:
  std::vector<char> path;
  std::vector<int> pieces;
  int score;

  Player() : score(0) {
    path.resize(16, ' ');
    pieces.resize(7, 0);
  }
};

void printRules();
void printBoard(const Player&, const Player&, bool);
char printPiece(const Player&, const Player&, int, int);
void printStarts(const Player&, int);
int choice2index(char, int);
char index2piece(int, int);
