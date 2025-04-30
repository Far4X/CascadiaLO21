#ifndef PLAYERBOARD_HPP
#define PLAYERBOARD_HPP
#include "GameActors/player.hpp"
#define MAX_SIZE 41
#define POS_CENTER 20;

#include "../Tiling/gametile.hpp"
#include "tileholder.hpp"

class PlayerBoard : public TileHolder {
public:
    PlayerBoard();
    void show() override;
    std::string getSaveString() const override;
};

#endif // PLAYERBOARD_HPP
