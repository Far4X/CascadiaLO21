#pragma once
#include <vector>

enum Direction { N, NE, SE, S, SW, NW };

class Hex {
	const int q;
	const int r;
	static const std::vector<Hex> directions;
public:
	Hex(int pos_q, int pos_r) : q(pos_q), r(pos_r) {}
	inline int getQ() const { return q; };
	inline int getR() const { return r; };
	inline int getS() const { return -q - r; };  // useless
	Hex operator+(const Hex& other) const;
	Hex operator-(const Hex& other) const;
	Hex getDirection(Direction d) const;
	Hex getNeighbors(Direction d) const;  // retourne le voisin de direction d
	std::vector<Hex> getNeighbors() const;  // overloaded : retourne tous les voisins (les 6)
};
