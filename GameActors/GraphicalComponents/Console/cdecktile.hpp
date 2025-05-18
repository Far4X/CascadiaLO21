#ifndef CDECKCARD_HPP
#define CDECKCARD_HPP

#include "../../../Gametools/Abstract/decktile.hpp"

class CDeckTile : public DeckTile{
    unsigned short int const m_max_height = 42;
    unsigned short int const m_max_width = 80;
public:
    CDeckTile();
    void show() override;
};

#endif // CDECKCARD_HPP
