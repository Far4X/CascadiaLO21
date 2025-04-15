#ifndef CMENU_HPP
#define CMENU_HPP

#include <iostream>

class CMenu{
    bool m_espect_answer;
    unsigned int m_x_size = 40;
public:
    inline CMenu(bool espect_answer = false) : m_espect_answer(espect_answer){};
    inline bool getEspectAnswser() const{return m_espect_answer;};
    virtual void print() const = 0;
    inline void setX(unsigned int x){m_x_size = x;}
    inline unsigned int getX() const {return m_x_size;}
};

#endif // CMENU_HPP
