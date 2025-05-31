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

bool HexCell::operator==(const HexCell& other) const {
    return (m_q == other.getQ() && m_r == other.getR());
}

bool HexCell::operator<(const HexCell& other) const {
    return (m_q < other.getQ() || (m_q == other.getQ() && m_r < other.getR()));
}

HexCell HexCell::operator+=(const HexCell& other) {
	m_q += other.m_q;
    m_r += other.m_r;
	return *this;
}

HexCell HexCell::operator-=(const HexCell& other)  {
	m_q -= other.m_q;
    m_r -= other.m_r;
	return *this;
}

HexCell HexCell::rotate60() const {
    return HexCell(-m_r, m_q + m_r);
}

int HexCell::floorDiv(int n) {
    // fonction utilitaire pour la forumule de conversion entre hex et offset (la division normale ne marche pas avec les negatifs de notre cas)
    if (n >= 0) {
        return n / 2;
    }
    else {
        return (n - 1) / 2;
    }
}

HexCell::Offset HexCell::axialToOffset(const HexCell& hex, unsigned int size){
    int q = hex.getQ();
    int r = hex.getR();
    int col = q + size/2;
    int row = r + floorDiv(q) + size/2;
    return HexCell::Offset(col, row);
}


HexCell HexCell::offsetToAxial(const Offset& off, unsigned int size){
    int col = off.getCol();
    int row = off.getRow();
    int q = col - size/2;
    int r = row - floorDiv(q) - size/2;
    return HexCell(q, r);
}

HexCell HexCell::directionTo(const HexCell& a, const HexCell& b) {
    int q1 = a.getQ(), r1 = a.getR(), s1 = a.getS();
    int q2 = b.getQ(), r2 = b.getR(), s2 = b.getS();
    int dq = q2 - q1;
    int dr = r2 - r1;

    if (q1 == q2) {
        if (dr > 0) {
            return directions[static_cast<int>(S)];
        }
        else {
            return directions[static_cast<int>(N)];
        }
    }
    else if (r1 == r2) {
        if (dq > 0) {
            return directions[static_cast<int>(SE)];
        }
        else {
            return directions[static_cast<int>(NW)];
        }
    }
    else if (s1 == s2) {
        if (dq > 0) {
            return directions[static_cast<int>(NE)];
        }
        else {
            return directions[static_cast<int>(SW)];
        }
    }
    else {
        throw "Tiles not aligned";
    }
}

HexCell HexCell::getDirection(Direction d) const {
    return directions[d];
}

HexCell HexCell::getNeighbor(Direction d) const {
    return (*this + getDirection(d));
}

std::vector<HexCell> HexCell::getNeighbors() const {
    std::vector<HexCell> neighbors;
	for (int i = 0; i < 6; i++) {
		neighbors.push_back(*this + getDirection(static_cast<Direction>(i)));  // on genere un vecteur contenant les voisins de le tuile
	}
	return neighbors;
}

char** getRepresentationCell(const HexCell* cell, unsigned short int size, unsigned int max_size){
    unsigned short int height = 2*size+1;
    unsigned short int width = 4*size;
    char **rt = new char*[height];
    for (unsigned short int i = 0; i < height; i++){
        rt[i] = new char[width];
        for (int j = 0; j < width; j++){
            rt[i][j] = ' ';
        }
    }

    //Draw hex
    for (int i = 0; i < size; i++){
        rt[0][i+size] = '_';
        rt[height-1][i+size] = '_';
        rt[0][3*size -i -1] = '_';
        rt[height-1][3*size -i -1] = '_';



        rt[size + 1 + i][i] = '\\';
        rt[size - i][i] = '/';

        rt[size + 1 + i][4*size - i - 1] = '/';


        rt[i+1][3*size+ i] = '\\';


    }

    // Adding informations


    HexCell::Offset pos = HexCell::axialToOffset(*cell, max_size);
    rt[size][1] = char(pos.getCol() / 10) + '0';
    rt[size][2] = char(pos.getCol() % 10) + '0';
    rt[size][3] = ',';
    rt[size][4] = char(pos.getRow() / 10) + '0';
    rt[size][5] = char(pos.getRow() % 10) + '0';

    return rt;
}

