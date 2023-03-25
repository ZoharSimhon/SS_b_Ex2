#include "player.hpp"
#include <string>

Player::Player(std::string name)
{
    this->name = name;
}

//Player::~Player(){}

int Player::stacksize(){
    return 1;
}

int Player::cardesTaken(){
    return 1;
}

