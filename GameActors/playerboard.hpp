#ifndef PLAYERBOARD_HPP
#define PLAYERBOARD_HPP
#define MAX_SIZE 41
#define POS_CENTER 20;

#include "../Gametools/Tiling/gametile.hpp"
#include "../Gametools/Abstract/tileholder.hpp"

class PlayerBoard : public TileHolder {
public:
    PlayerBoard();
    GameTile* getTile(int q, int r) const;
    void print() override;
    std::string getSaveString() const override;
};

#endif // PLAYERBOARD_HPP
