#ifndef WILDLIFETOKEN_HPP
#define WILDLIFETOKEN_HPP

enum Wildlife {Bear, Salmon, Hawk, Elk, Fox};

class WildlifeToken
{
    Wildlife m_type;
    int m_xdprintpos; //Décalage de la position d'affichage par rapport au centre du holder
    int m_ydprintpos;
public:
    WildlifeToken(Wildlife type, int x_dpos = 0, int y_dpos = 0);
};

#endif // WILDLIFETOKEN_HPP
