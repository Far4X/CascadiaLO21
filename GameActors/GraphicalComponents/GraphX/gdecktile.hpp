#ifndef GDECKCARD_HPP
#define GDECKCARD_HPP
#include "../../../Gametools/Abstract/decktile.hpp"


class GDeckTile : public DeckTile{
private:
    GDeckTile();

    GDeckTile(const GDeckTile &tar) = delete;
    GDeckTile &operator=(const GDeckTile &tar) = delete;
    ~GDeckTile() = default;
public:
    void show() override;
    static GDeckTile& getInstance();

};

#endif // GDECKCARD_HPP
