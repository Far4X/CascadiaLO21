#include "hexcell.hpp"

const std::vector<HexCell> HexCell::directions = {
    HexCell(0, -1), HexCell(+1, -1), HexCell(+1, 0),  // N, NE, SE
	 HexCell(0, +1), HexCell(-1, +1), HexCell(-1, 0)  // S, SW, NW
};

HexCell HexCell::operator+(const HexCell& other) const {
    return HexCell(m_q + other.m_q, m_r + other.m_r);
}

HexCell HexCell::operator-(const HexCell& other) const {
	return HexCell(m_q - other.m_q, m_r - other.m_r);
}
/*
 Puisque les cellules hexagonales ne vont pas bouger, ces operateurs ne servent a rien, je les garde au cas ou
 j'en ai besoin pour une autre classe qui va etre composee et non pas heritee de HexCell


HexCell HexCell::operator+=(const HexCell& other) {
	m_q += other.m_q;
	m_r += other.m_q;
	return *this;
}

HexCell HexCell::operator-=(const HexCell& other)  {
	m_q -= other.m_q;
	m_r -= other.m_q;
	return *this;
}
*/

HexCell HexCell::getDirection(Direction d) const {
    return directions[d];
}

HexCell HexCell::getNeighbors(Direction d) const {
    return (*this + getDirection(d));
}

std::vector<HexCell> HexCell::getNeighbors() const {
    std::vector<HexCell> neighbors;
	for (int i = 0; i < 6; i++) {
		neighbors.push_back(*this + getDirection(static_cast<Direction>(i)));  // on genere un vecteur contenant les voisins de le tuile
	}
	return neighbors;
}
