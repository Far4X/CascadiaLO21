#ifndef MENU_HPP
#define MENU_HPP

#include "../../Gametools/Abstract/printable.hpp"
#include "../../Gametools/Abstract/notifiableinterface.hpp"

template <typename T>
class Menu : public Printable{
    /*
    La classe menu est une classe abstraite qui permet de gérer plus facilement les menus en proposant un itérateur pour récupérer les résultats
    */
    T* m_results = nullptr;
    int m_nb_result = 0;
    friend class Iterator;

protected :
    NotifiableInterface* m_target = nullptr;

public:
    class Iterator {
        const Menu& m_menu;
        int m_nb;
    public :
        inline Iterator(const Menu& tar) : m_menu(tar), m_nb(0){}
        inline bool isDone() const {return m_nb == m_menu.m_nb_result;}
        inline Iterator& operator++(int){m_nb++; return *this;}
        inline T getValue() const {return m_menu.m_results[m_nb];}
    };
    Iterator getIterator() const;
    Menu(NotifiableInterface* target = nullptr);
    virtual ~Menu();
    void addResult(const T& tar);
    virtual void show() = 0;
};

#endif // MENU_HPP
