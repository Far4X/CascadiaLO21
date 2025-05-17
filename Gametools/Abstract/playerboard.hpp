#ifndef PLAYERBOARD_HPP
#define PLAYERBOARD_HPP

#define MAX_SIZE 41

#include "../Tiling/gametile.hpp"
#include "tileholder.hpp"

class PlayerBoard : public TileHolder {
    unsigned short int m_q_center;
    unsigned short int m_r_center;
public:
    struct Offset {
        int getCol() const {return col;}
        int getRow() const {return row;}
        Offset(int c, int r) : col(c), row(r) {};
    private:
        int col;
        int row;
    };
    static int floorDiv(int n);
    static Offset axialToOffset(const HexCell& hex);
    static HexCell offsetToAxial(const Offset& off);
    PlayerBoard();
    void show() override;
    std::string getSaveString() const override;
    void moveHz(short int step = 1);
    void moveVt(short int step = 1);
    void addTile(GameTile& tile,int* q,int* r, bool overwrite);
};

#endif // PLAYERBOARD_HPP
