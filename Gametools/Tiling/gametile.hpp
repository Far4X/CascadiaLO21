#ifndef GAMETILE_HPP
#define GAMETILE_HPP
#include "../wildlifetoken.hpp"
#include "hexcell.hpp"
#include "../Abstract/salvablething.hpp"


enum Biome {Forest = 1, Wetland, River, Mountain, Prairie};
enum Rotation {Trigonometric, Anti_Trigonometric};

class GameTile : public HexCell, public SalvableThing{ //Or inherits public hextile; if not rename HexTile HexTileCoord
    friend class Game;
    //Hexcell m_position;
    Biome m_biomes[6]; //0 : top, 1 : topright...
    unsigned char m_rotation = 0;
    WildlifeToken *m_wltoken = nullptr;
    Wildlife *m_possible_wltoken = nullptr;
    int m_numtypes;
    const unsigned int m_id;

    //GameTile(const unsigned int id, Biome biomes[6], Wildlife *type = nullptr, int num_types = 0, int posx = 0, int posy = 0);
    GameTile(int id, std::string description);
    ~GameTile();
    GameTile& operator=(const GameTile& oth) = delete;
    GameTile(const GameTile& oth) = delete;
    std::string getSaveString() const override;

public:
    void setPos(int const &q, int const &r);
    inline int getNbWildlife() const {return m_numtypes;};
    inline Wildlife getWildlife(unsigned short int nb) const {if (nb < m_numtypes) return m_possible_wltoken[nb]; else throw CustomError("Not in range", 104);};
    GameTile(unsigned int id, Biome biomes[6], Wildlife *type, int num_types, int posx, int posy);
    void Rotate(Rotation dir = Anti_Trigonometric);
    int draw();
    Biome getBiome(unsigned short int number) const {{return m_biomes[number%6];}}
    inline unsigned int getId() const {return m_id;}
    WildlifeToken* getToken() const { return m_wltoken; }
    bool matchesType(Biome biome) const {
        for (int i = 0; i < 6; ++i) {
            if (m_biomes[i] == biome)
                return true;
        }
        return false;
    }
    bool isKeystone(const std::string& description = "") const;
};

char** getRepresentation(const GameTile* tile, unsigned short int size, unsigned int max_size, bool add_pos = true);

#endif // GAMETILE_HPP
