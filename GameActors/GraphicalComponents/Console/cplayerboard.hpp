#ifndef CPLAYERBOARD_HPP
#define CPLAYERBOARD_HPP

#include "Gametools/Abstract/playerboard.hpp"

class CPlayerBoard : public PlayerBoard{
    unsigned short int const m_max_height = 42;
    unsigned short int const m_max_width = 140;
    unsigned short int m_x_swift = 0;
    unsigned short int m_y_swift = 0;
public:
    CPlayerBoard();
    void show() override;
};

#endif // CPLAYERBOARD_HPP
