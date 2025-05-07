#ifndef WILDLIFETOKEN_HPP
#define WILDLIFETOKEN_HPP

#include <initializer_list>

enum Wildlife {Bear, Salmon, Hawk, Elk, Fox};
inline std::initializer_list<Wildlife> Animals = { Wildlife::Bear, Wildlife::Salmon, Wildlife::Hawk, Wildlife::Elk, Wildlife::Fox };

class WildlifeToken {
    Wildlife m_type;
    int m_xdprintpos; //Décalage de la position d'affichage par rapport au centre du holder
    int m_ydprintpos;
public:
    WildlifeToken(Wildlife type, int x_dpos = 0, int y_dpos = 0);
    Wildlife getWildlifeType() const { return m_type; }
    bool matchesType(Wildlife type) const { return m_type == type; }
};

#endif // WILDLIFETOKEN_HPP
