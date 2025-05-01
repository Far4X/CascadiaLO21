#ifndef PLAYERBOARD_HPP
#define PLAYERBOARD_HPP
#define MAX_SIZE 41
#define POS_CENTER 20;

#include "../Tiling/gametile.hpp"
#include "tileholder.hpp"

class PlayerBoard : public TileHolder {
    unsigned short int m_q_center;
    unsigned short int m_r_center;
public:
    PlayerBoard();
    void show() override;
    std::string getSaveString() const override;
    void swiftQ(short int step = 3);
    void swiftR(short int step = 3);
};

#endif // PLAYERBOARD_HPP
