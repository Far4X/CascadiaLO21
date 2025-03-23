#include "hex.hpp"

const std::vector<Hex> Hex::directions = {
	Hex(0, -1), Hex(+1, -1), Hex(+1, 0),  // N, NE, SE
	 Hex(0, +1), Hex(-1, +1), Hex(-1, 0)  // S, SW, NW
};

Hex Hex::operator+(const Hex& other) const {
	return Hex(m_q + other.m_q, m_r + other.m_r);
}

Hex Hex::operator-(const Hex& other) const {
	return Hex(m_q - other.m_q, m_r - other.m_r);
}
/*
 Puisque les cellules hexagonales ne vont pas bouger, ces operateurs ne servent a rien, je les garde au cas ou
 j'en ai besoin pour une autre classe qui va etre composee et non pas heritee de Hex


Hex Hex::operator+=(const Hex& other) {
	m_q += other.m_q;
	m_r += other.m_q;
	return *this;
}

Hex Hex::operator-=(const Hex& other)  {
	m_q -= other.m_q;
	m_r -= other.m_q;
	return *this;
}
*/

Hex Hex::getDirection(Direction d) const {
	return directions[d];
}

Hex Hex::getNeighbors(Direction d) const {
	return *this + getDirection(d);
}

std::vector<Hex> Hex::getNeighbors() const {
	std::vector<Hex> neighbors;
	for (int i = 0; i < 6; i++) {
		neighbors.push_back(*this + getDirection(static_cast<Direction>(i)));  // on genere un vecteur contenant les voisins de le tuile
	}
	return neighbors;
}