#include "hex.hpp"

const std::vector<Hex> Hex::directions = {
	Hex(0, -1), Hex(+1, -1), Hex(+1, 0),  // N, NE, SE
	 Hex(0, +1), Hex(-1, +1), Hex(-1, 0)  // S, SW, NW
};

Hex Hex::operator+(const Hex& other) const {
	return Hex(m_q + other.m_q, m_p + other.m_p);
}

Hex Hex::operator-(const Hex& other) const {
	return Hex(m_q - other.m_q, m_p - other.m_p);
}

Hex Hex::getDirection(Direction d) const {
	return directions(d);
}

Hex Hex::getNeighbors(Direction d) const {
	return *this + getDirection(d);
}

std::vector<Hex> Hex::getNeighbors() const {
	std::vector<Hex> neighbors;
	for (int i = 0; i < 6; i++) {
		neighbors.push_back(*this + getDirection(i));  // on genere un vecteur contenant les voisins de le tuile
	}
	return neighbors;
}