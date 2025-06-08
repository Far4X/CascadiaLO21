#ifndef WILDLIFETOKEN_HPP
#define WILDLIFETOKEN_HPP

#include <initializer_list>

enum Wildlife {Bear, Elk, Hawk, Fox, Salmon};
inline std::initializer_list<Wildlife> Animals = { Wildlife::Bear, Wildlife::Elk, Wildlife::Hawk, Wildlife::Fox, Wildlife::Salmon};

class WildlifeToken {
    /*Représente un token de faune*/
    Wildlife m_type;
    int m_xdprintpos; //Décalage de la position d'affichage par rapport au centre du holder
    int m_ydprintpos;
public:
    WildlifeToken(Wildlife type, int x_dpos = 0, int y_dpos = 0);
    Wildlife getWildlifeType() const { return m_type; }
};

#endif // WILDLIFETOKEN_HPP
