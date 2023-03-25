#pragma once
#include <string>

class Player
{
    private:
        std::string name;
    public:
        Player(std::string name);
        Player(){}
        //~Player();
        int stacksize();
        int cardesTaken();
};

