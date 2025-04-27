#ifndef PLAYERBOARD_HPP
#define PLAYERBOARD_HPP
#define MAX_SIZE 41
#define POS_CENTER 20;

#include "../Gametools/Tiling/gametile.hpp"
#include "../Gametools/Abstract/tileholder.hpp"
#include "player.hpp"

class PlayerBoard : public TileHolder {
    Player *m_player;
public:
    PlayerBoard();
    void show() override;
    std::string getSaveString() const override;
};

#endif // PLAYERBOARD_HPP
