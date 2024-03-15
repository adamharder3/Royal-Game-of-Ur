#include <string>
#include <cstdlib>
#include <limits>
#include "util.h"

using namespace std;

void playGame();
void doTurn(Player&, Player&, int);
bool checkValidity(Player &, Player &, int, char, int);
void doMove(Player &, Player &, int, char, int);

int main() {
  cout << "Welcome to The Royal Game of Ur\n\n";
  cout << "If you would like an explanation of how the game works, please enter 'help'\n";
  cout << "Otherwise, press enter\n";
  string helpIn;
  getline(cin, helpIn);
  if (helpIn == "help") {
    printRules();
  }

  char decision = 'Y';

  while (decision == 'Y') {
    system("clear");
    playGame();
    cout << "Would you like to play again? (Y/N)\n";
    cin >> decision;
    decision = toupper(decision);
  }

  system("clear");
  cout << "Thanks for playing!\n";
  cout << "Press enter to exit...\n";
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  cin.get();
}

void playGame() {
  int turn = 0;
  bool gameOver = 0;
  Player p1;
  Player p2;

  while (!gameOver) {
    system("clear");
    doTurn(p1, p2, turn);
    if (p1.score == 7) {
      cout << "\nPlayer 1 wins!\n\n";
      gameOver = 1;
    }
    else if (p2.score == 7) {
      cout << "Player 2 wins!\n\n";
      gameOver = 1;
    }

    if (turn) {
      turn = 0;
    }
    else {
      turn = 1;
    }
  }

  printBoard(p1, p2, 1);

}

void doTurn(Player &p1, Player &p2, int turn) {
  printBoard(p1, p2, 1);

  cout << "It is Player " << (turn + 1) << "'s turn\n";

  if (turn) {
    printStarts(p2, turn);
  }
  else {
    printStarts(p1, turn);
  }
  
  cout << "Press enter to roll...";
  cin.get();
  int roll = rand() % 5;
  cout << "You rolled a " << roll << "\n\n";
  if (roll) {
    bool valid = 0;
    char choice = ' ';
    cout << "Please enter a piece you would like to move (A/a - G/g)\n";
    while (!valid) {
      choice = cin.get();
      if (turn) {
        valid = checkValidity(p2, p1, turn, choice, roll);
      }
      else {
        valid = checkValidity(p1, p2, turn, choice, roll);
      }
      
      if (!valid) {
        cout << "\nInvalid move! Please enter a valid move (A/a - G/g)\n";
      }

    }
    if (turn) {
      doMove(p2, p1, turn, choice, roll);
    }
    else {
      doMove(p1, p2, turn, choice, roll);
    }
    
  }
  else {
    cout << "Press enter to continue\n";
    cin.get();
  }
}

bool checkValidity(Player &mover, Player &opp, int turn, char choice, int roll) {
  if (choice == '\n') {
    cout << "Are you sure you want to do nothing?\n";
    cout << "Press enter again to confirm, otherwise enter a piece to move\n";
    choice = cin.get();
    if (choice == '\n') {
      return 1;
    }
  }

  cin.ignore(numeric_limits<streamsize>::max(), '\n');

  if (!(choice >= 'a' && choice <= 'g') && !(choice >= 'A' && choice <= 'G')) {
    return 0;
  }

  if (turn) {
    choice = toupper(choice);
  }
  else {
    choice = tolower(choice);
  }

  int index = choice2index(choice, turn);
  if (mover.pieces[index] + roll > 15) {
    return 0;
  }
  else if (mover.path[mover.pieces[index] + roll] != ' ') {
    return 0;
  }
  else if (mover.pieces[index] + roll == 8 && opp.path[8] != ' ') {
    return 0;
  }

  return 1;
}

void doMove(Player &mover, Player &opp, int turn, char choice, int roll) {
  if (choice == '\n') {
    return;
  }

  if (turn) {
    choice = toupper(choice);
  }
  else {
    choice = tolower(choice);
  }

  int index = choice2index(choice, turn);

  if (opp.path[mover.pieces[index] + roll] != ' ' && mover.pieces[index] + roll >= 5 && mover.pieces[index] + roll <= 12) {
    opp.pieces[choice2index(opp.path[mover.pieces[index] + roll], !turn)] = 0;
    opp.path[mover.pieces[index] + roll] = ' ';
  }

  mover.path[mover.pieces[index]] = ' ';
  mover.path[mover.pieces[index] + roll] = choice;
  mover.pieces[index] = mover.pieces[index] + roll;

  if (mover.pieces[index] == 15) {
    ++mover.score;
  }

  if (mover.pieces[index] == 4 || mover.pieces[index] == 8 || mover.pieces[index] == 14) {
    cout << "\nYou landed on double-roll space and get to roll again!\n\n";
    if (turn) {
      doTurn(opp, mover, turn);
    }
    else {
      doTurn(mover, opp, turn);
    }
  }
}
