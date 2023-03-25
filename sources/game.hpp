#include "player.hpp"

class Game
{
private:
    Player player1, player2;
public:
    //constructor
    Game(Player player1, Player player2);
    //destructor
    //~Game();
    //methods
    void playTurn();
    void printLastTurn();
    void playAll();
    void printWiner();
    void printLog();
    void printStats();

};




