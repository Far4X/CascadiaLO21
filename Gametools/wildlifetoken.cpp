#include "wildlifetoken.hpp"

unsigned int WildlifeToken::currentId = 0;

WildlifeToken::WildlifeToken(Wildlife type, int x_dpos, int y_dpos) : m_type(type), m_xdprintpos(x_dpos),  m_ydprintpos(y_dpos), m_id(currentId){
    currentId++;
}
