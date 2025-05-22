#ifndef PLAYERBOARD_HPP
#define PLAYERBOARD_HPP

#define MAX_SIZE 41

#include "tileholder.hpp"

class PlayerBoard : public TileHolder {
    unsigned short int m_q_center;
    unsigned short int m_r_center;
public:
    /*struct Offset {
        int getCol() const {return col;}
        int getRow() const {return row;}
        Offset(int c, int r) : col(c), row(r) {};
    private:
        int col;
        int row;
    };
    static int floorDiv(int n);
    static Offset axialToOffset(const HexCell& hex);
    static HexCell offsetToAxial(const Offset& off);*/

    static inline HexCell::Offset axialToOffset(const HexCell& hex) { return HexCell::axialToOffset(hex, MAX_SIZE); }
    static inline HexCell offsetToAxial(const HexCell::Offset& off) { return HexCell::offsetToAxial(off, MAX_SIZE); }
    GameTile* getNeighborTile(const GameTile& tile, Direction d) const;
    std::vector<GameTile*> getNeighborTiles(const GameTile& tile) const;
    PlayerBoard();
    void show() override;
    std::string getSaveString() const override;
    void moveHz(short int step = 1);
    void moveVt(short int step = 1);
    void addTile(GameTile& tile,int* q,int* r, bool overwrite);
    bool hasNeighbour(unsigned short int x, unsigned short int y);
};

#endif // PLAYERBOARD_HPP
