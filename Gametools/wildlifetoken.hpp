#ifndef WILDLIFETOKEN_HPP
#define WILDLIFETOKEN_HPP

enum Wildlife {Bear, Salmon, Hawk, Elk, Fox};

class WildlifeToken {
    Wildlife m_type;
    int m_xdprintpos; //Décalage de la position d'affichage par rapport au centre du holder
    int m_ydprintpos;
    const unsigned int m_id;
    static unsigned int currentId;
public:
    static constexpr int MAX_ID = 100;
    WildlifeToken(Wildlife type, int x_dpos = 0, int y_dpos = 0);
    Wildlife getWildlifeType() const { return m_type; }
    bool matchesType(Wildlife type) const { return m_type == type; }
    inline unsigned int getId() const {return m_id;}
};

#endif // WILDLIFETOKEN_HPP
