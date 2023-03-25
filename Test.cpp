#include "doctest.h"
#include <stdexcept>
#include <iostream>
#include <stddef.h>

#include "game.hpp"
#include "player.hpp"

//Player functions
TEST_CASE("Player constructor"){
    //check that we can't define a null value
    CHECK_THROWS(Player(nullptr));
    //check that we can't define an empty string
    CHECK_THROWS(Player (""));

}
TEST_CASE("Player stacksize method") {
    Player  p1("player1");
    //defining variables for the game
    Player  p2("player2");
    Game game(p1,p2);
    //check that at the beginng the number of cards is 26
    bool start = (p1.stacksize() == 26) && (p2.stacksize() == 26);
    CHECK(start);
    //check the amont of cards after one turn
    game.playTurn();
    bool oneTurn = (p1.stacksize()%2 == 1) && (p1.stacksize() == p2.stacksize());
    CHECK(oneTurn);
    //check that after five turns the amount of cards is maximum 20
    for (int i=0;i<5;i++) {
        game.playTurn();
    }
    bool sixTurns = (p1.stacksize()<=20) && (p2.stacksize()<=20) && (p1.stacksize() == p2.stacksize());
    CHECK(sixTurns);
}
TEST_CASE("Player cardesTaken method") {
    //defining variables for the game
    Player  p1("player1");
    Player  p2("player2");
    Game game(p1,p2);
    //check that at the beginng the number of cards which have taken is 0
    bool start = (p1.cardesTaken() == 0) && (p2.cardesTaken() == 0);
    CHECK(start);
    //check the amont of cards after one turn
    game.playTurn();
    bool player1Win = (p1.cardesTaken() == (26-p1.stacksize())*2) && (p2.cardesTaken() == 0);
    bool player2Win = (p2.cardesTaken() == (26-p2.stacksize())*2) && (p1.cardesTaken() == 0);
    bool oneTurn = player1Win || player2Win;
    CHECK(oneTurn);
    //make another check the amont of cards after one turn
    player1Win = (p1.cardesTaken() >= 2) && (p2.cardesTaken() == 0);
    player2Win = (p2.cardesTaken()>= 2) && (p1.cardesTaken() == 0);
    oneTurn = player1Win || player2Win;
    CHECK(oneTurn);
    //check the amount of taken cards after six turns 
    for (int i=0;i<5;i++) {
        game.playTurn();
    }
    //check that the amount of taken cards is even
    bool sixTurnsEven = (p1.cardesTaken() %2 == 0) && (p2.cardesTaken() %2 == 0);
    CHECK(sixTurnsEven);
    bool sixTurns = p1.cardesTaken() + p2.cardesTaken() == (26 - p1.stacksize()) * 2;
    CHECK(sixTurns);
}

//Game functions
TEST_CASE("Game constructor") {
    //defining variables for the game
    Player  p1("player1");
    Player  p2("player2");
    Game game1(p1,p2);
    //check that p1 and p2 can't play in another game
    CHECK_THROWS(Game(p1,p2));
    //check that ap1 can't play with another player
    Player  p3("player3");
    CHECK_THROWS(Game(p1,p3));
    //check that new playhers can play, when a game is still going on
    Player  p4("player4");
    CHECK_NOTHROW(Game game2(p3,p4));
    //check that after the players have done to play, they can play in another game
    game1.playAll();
    Player  p5("player5");
    CHECK_NOTHROW(Game game3(p1,p5));
    //check that one player can't play with himself
    Player  p6("player6");
    CHECK_THROWS(Game(p6,p6));
}
TEST_CASE("Game playTurn method") {
    //defining variables for the game
    Player  p1("player1");
    Player  p2("player2");
    Game game(p1,p2);
    //check that after the game is over we can't play a turn
    game.playAll();
    CHECK_THROWS(game.playTurn());
}
TEST_CASE("Game printLastTurn method") {
    Player  p1("player1");
    //check that at the beginng the number of cards is 26
}
TEST_CASE("Game playAll method") {
    //defining variables for the game
    Player  p1("player1");
    Player  p2("player2");
    Game game(p1,p2);
    //check that after the function the amount of cards in the stack is 0
    bool stacksize = (p1.stacksize() == 0) && (p2.stacksize() == 0);
    CHECK(stacksize);
    //check that after the function the amount of cards were taken is 52
    bool cardesTaken = (p1.cardesTaken() + p2.cardesTaken() == 52);
    CHECK(cardesTaken);
    //check that after the game is over we can't play
    game.playAll();
    CHECK_THROWS(game.playAll());
    
}
TEST_CASE("Game print methods") {
    //defining variables for the game
    Player  p1("player1");
    Player  p2("player2");
    Game game(p1,p2);
    //check that we can't print anything before the game has started
    CHECK_THROWS(game.printLastTurn());
    CHECK_THROWS(game.printLog());
    CHECK_THROWS(game.printStats());
    CHECK_THROWS(game.printWiner());
    //check that after one turn we can print: LastTurn, Log and Stats  but can't print:  Winer
    game.playTurn();
    CHECK_NOTHROW(game.printLastTurn());
    CHECK_NOTHROW(game.printLog());
    CHECK_NOTHROW(game.printStats());
    CHECK_THROWS(game.printWiner());
    //check that at the end of the game we can use all the print methods
    game.playAll();
    CHECK_NOTHROW(game.printLastTurn());
    CHECK_NOTHROW(game.printLog());
    CHECK_NOTHROW(game.printStats());
    CHECK_NOTHROW(game.printWiner());
}


