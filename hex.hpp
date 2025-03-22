#pragma once
#include <vector>

enum Direction { N, NE, SE, S, SW, NW };

class Hex {
	const int m_q;
	const int m_r;
	static const std::vector<Hex> directions;
public:
	Hex(int pos_q, int pos_r) : m_q(q), m_r(r) {}
	inline int getQ() const { return m_q; };
	inline int getR() const { return m_r; };
	inline int getS() const { return -m_q - m_r; };  // useless
	Hex operator+(const Hex& other) const;
	Hex operator-(const Hex& other) const;
	Hex getDirection(Direction d) const;
	Hex getNeighbors(Direction d) const;  // retourne le voisin de direction d
	std::vector<Hex> getNeighbors() const;  // overloaded : retourne tous les voisins (les 6)
};
