#ifndef GTOKENMENU_HPP
#define GTOKENMENU_HPP

#include <QVBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QSpinBox>
#include <QLabel>

#include "gmenu.hpp"
//#include "../../../Gametools/Tiling/gametile.hpp"
#include "../../../Gametools/Abstract/decktile.hpp"

class GTokenMenu : public GMenu<unsigned short int>{
    QGridLayout* m_main_layout = nullptr;


public:
    GTokenMenu(NotifiableInterface* tar, DeckTile* decktile, unsigned short int nb_token);
    ~GTokenMenu(){}
    void validateNumber(){}
    void validateNames(){}
    void show(){}
};

#endif // GTOKENMENU_HPP
