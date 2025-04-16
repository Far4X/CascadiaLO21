#ifndef GMENU_HPP
#define GMENU_HPP
#include <QWidget>
#include "../menu.hpp"
#include "../../Gametools/Abstract/notifiableinterface.hpp"

template <typename T>
class GMenu : public QWidget, public Menu<T>{
    unsigned int m_size_x;
    unsigned int m_size_y;
    unsigned int m_pos_x;
    unsigned int m_pos_y;
protected :
    NotifiableInterface* m_target = nullptr;

public:
    GMenu(NotifiableInterface* target, QWidget* parent = nullptr, unsigned int size_x = 800, unsigned int size_y = 600, unsigned int pos_x = 600, unsigned int pos_y = 600);
    void actualize();
    void show();
    inline void setSizeX(unsigned int x){m_size_x = x;actualize();}
    inline void setSizeY(unsigned int y){m_size_y = y;actualize();}
    inline unsigned int getSizeX() const {return m_size_x;}
    inline unsigned int getSizeY() const {return m_size_y;}
    inline void setPosX(unsigned int x){m_pos_x = x;actualize();}
    inline void setPosY(unsigned int y){m_pos_y = y;actualize();}
    inline unsigned int getPosX() const {return m_pos_x;}
    inline unsigned int getPosY() const {return m_pos_y;}
};

#endif // GMENU_HPP
