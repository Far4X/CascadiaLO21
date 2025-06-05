#ifndef CPLAYERBOARD_HPP
#define CPLAYERBOARD_HPP


#include "../../../Gametools/Abstract/playerboard.hpp"

class CPlayerBoard : public PlayerBoard{
    unsigned short int const m_max_height = 42;
    unsigned short int const m_max_width = 140;
    unsigned short int m_size_tile = 3;
    int m_x_swift = (MAX_SIZE-2)*m_size_tile*3/2;
    int m_y_swift = (MAX_SIZE-2)*m_size_tile ;
    unsigned int step = 10;
public:
    CPlayerBoard(NotifiableInterface *tar);
    CPlayerBoard(NotifiableInterface *tar, const std::string& def);

    void show() override;
    void reprBoard();
};

#endif // CPLAYERBOARD_HPP
