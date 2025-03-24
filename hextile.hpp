#pragma once
#include <vector>

enum Direction {N, NE, SE, S, SW, NW};

#define Hex HexTile

class HexTile {
	const int m_q;
	const int m_r;
    static const std::vector<HexTile> directions;

public:
    HexTile(int q, int r) : m_q(q), m_r(r) {}
	int getQ() const { return m_q; };
	int getR() const { return m_r; };
	int getS() const { return -m_q - m_r; };  // useless
    HexTile operator+(const HexTile& other) const;
    HexTile operator-(const HexTile& other) const;

	/*
	Hex operator+=(const Hex& other) ;
	Hex operator-=(const Hex& other) ;
	*/
    HexTile getDirection(Direction d) const;
    HexTile getNeighbors(Direction d) const;  // retourne le voisin de direction d
    std::vector<HexTile> getNeighbors() const;  // overloaded : retourne tous les voisins (les 6)
};
