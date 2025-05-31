#ifndef CMENU_HPP
#define CMENU_HPP

#include "../menu.hpp"

template <typename T>
class CMenu : public Menu<T>{
    unsigned int m_x_size = 40;
public:
    CMenu(NotifiableInterface* tar);
    virtual ~CMenu() = default;
    virtual void show() = 0;
    inline void setX(unsigned int x){m_x_size = x;}
    inline unsigned int getX() const {return m_x_size;}
};

#endif // CMENU_HPP
