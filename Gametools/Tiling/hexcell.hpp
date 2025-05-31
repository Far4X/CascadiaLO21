#pragma once
//#include "hextile.hpp"
#include <vector>
#include "../Abstract/baseclass.hpp"

enum Direction {N, NE, SE, S, SW, NW};

class HexCell : public BaseClass {
    int m_q;
    int m_r;

public:
    struct Offset {
        int getCol() const {return col;}
        int getRow() const {return row;}
        Offset(int c, int r) : col(c), row(r) {};
    private:
        int col;
        int row;
    };
    static Offset axialToOffset(const HexCell& hex, unsigned int size);
    static HexCell offsetToAxial(const Offset& off, unsigned int size);
    static int floorDiv(int n);
    static HexCell directionTo(const HexCell& a, const HexCell& b);

    HexCell(int q, int r) : m_q(q), m_r(r) {}
    HexCell() : m_q(0), m_r(0){}
	int getQ() const { return m_q; };
	int getR() const { return m_r; };
    int getS() const { return -m_q - m_r; };  // useless
    static const std::vector<HexCell> directions;

    inline void setQ(const int& q){m_q = q;}
    inline void setR(const int& r){m_r = r;}
    HexCell operator+(const HexCell& other) const;
    HexCell operator-(const HexCell& other) const;
    bool operator==(const HexCell& other) const;
    bool operator<(const HexCell& other) const;
    HexCell rotate60() const;
    HexCell operator+=(const HexCell& other);
    HexCell operator-=(const HexCell& other);

    HexCell getDirection(Direction d) const;
    HexCell getNeighbor(Direction d) const;  // retourne le voisin de direction d
    std::vector<HexCell> getNeighbors() const;  // overloaded : retourne tous les voisins (les 6)
};
char** getRepresentationCell(const HexCell* cell, unsigned short int size, unsigned int max_size);

