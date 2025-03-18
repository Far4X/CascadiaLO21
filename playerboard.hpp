#ifndef PLAYERBOARD_HPP
#define PLAYERBOARD_HPP
#define MAX_SIZE 41

#include "gametile.hpp"

class PlayerBoard {
    GameTile table[MAX_SIZE][MAX_SIZE];
public:
    PlayerBoard();
};

#endif // PLAYERBOARD_HPP
