#include "hextile.hpp"

const std::vector<Hex> Hex::directions = {
    HexTile(0, -1), HexTile(+1, -1), HexTile(+1, 0),  // N, NE, SE
	 Hex(0, +1), Hex(-1, +1), Hex(-1, 0)  // S, SW, NW
};

HexTile HexTile::operator+(const HexTile& other) const {
    return HexTileCoordinates(m_q + other.m_q, m_r + other.m_r);
}

HexTile HexTile::operator-(const HexTile& other) const {
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

HexTile HexTile::getDirection(Direction d) const {
	return directions[d];
}

HexTile HexTile::getNeighbors(Direction d) const {
    return (*this + getDirection(d));
}

std::vector<HexTile> HexTile::getNeighbors() const {
    std::vector<HexTile> neighbors;
	for (int i = 0; i < 6; i++) {
		neighbors.push_back(*this + getDirection(static_cast<Direction>(i)));  // on genere un vecteur contenant les voisins de le tuile
	}
	return neighbors;
}
