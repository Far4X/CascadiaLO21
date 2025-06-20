#ifndef CDECKCARD_HPP
#define CDECKCARD_HPP

#include "../../../Gametools/Abstract/decktile.hpp"

class CDeckTile : public DeckTile{
    unsigned short int const m_max_height = 15;
    unsigned short int const m_max_width = 80;
    unsigned short int const m_size_tile = 3;

    CDeckTile(const CDeckTile &tar) = delete;
    CDeckTile &operator=(const CDeckTile &tar) = delete;
    CDeckTile();
    ~CDeckTile() = default;
public:
    void show() override;
    static CDeckTile& getInstance();

};

#endif // CDECKCARD_HPP
