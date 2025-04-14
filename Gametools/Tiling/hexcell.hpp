#pragma once
//#include "hextile.hpp"
#include <vector>
#include "../Abstract/baseclass.hpp"

enum Direction {N, NE, SE, S, SW, NW};

class HexCell : public BaseClass {
    int m_q;
    int m_r;
    static const std::vector<HexCell> m_directions;
    //HexTile* m_tile;

public:
    HexCell(int q, int r) : m_q(q), m_r(r) {}
	int getQ() const { return m_q; };
	int getR() const { return m_r; };
    int getS() const { return -m_q - m_r; };  // useless

    inline void setQ(const int& q){m_q = q;}
    inline void setR(const int& r){m_r = r;}
    HexCell operator+(const HexCell& other) const;
    HexCell operator-(const HexCell& other) const;

	// HexCell operator+=(const HexCell& other);
	// HexCell operator-=(const HexCell& other);

    HexCell getDirection(Direction d) const;
    HexCell getNeighbors(Direction d) const;  // retourne le voisin de direction d
    std::vector<HexCell> getNeighbors() const;  // overloaded : retourne tous les voisins (les 6)
};
