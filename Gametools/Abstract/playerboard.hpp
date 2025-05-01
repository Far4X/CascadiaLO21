#ifndef PLAYERBOARD_HPP
#define PLAYERBOARD_HPP

#define MAX_SIZE 41

#include "../Tiling/gametile.hpp"
#include "tileholder.hpp"

class PlayerBoard : public TileHolder {
    unsigned short int m_q_center;
    unsigned short int m_r_center;
public:
    PlayerBoard();
    void show() override;
    std::string getSaveString() const override;
    void moveHz(short int step = 1);
    void moveVt(short int step = 1);
};

#endif // PLAYERBOARD_HPP
