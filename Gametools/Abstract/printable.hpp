#ifndef PRINTABLE_HPP
#define PRINTABLE_HPP

#include "baseclass.hpp"

class Printable : BaseClass{
    //Classe qui représente un truc affichable à l'écran
    bool m_is_graphic();
public:
    virtual void show() = 0;
    Printable();
};

#endif // PRINTABLE_HPP
