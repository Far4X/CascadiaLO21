#ifndef GPLAYERBOARD_HPP
#define GPLAYERBOARD_HPP

#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QMouseEvent>
#include <QVBoxLayout>
#include <QFrame>
#include "ghexboard.hpp"


#include "Gametools/Abstract/playerboard.hpp"

class GPlayerBoard : public PlayerBoard{
public:
    GPlayerBoard();
    ~GPlayerBoard();
    QWidget* getWidget() const;
    void show() override;
private:

    QWidget* m_widget; // widget principal
    QWidget* m_gridWidget; // widget qui contient la grille
    QGridLayout* m_gridLayout;  // Grid pour organiser les widgets
    QVBoxLayout* m_layout;      // Main layout
    QPushButton* m_btn_quit;  // Bouton Quit
    QLabel* m_label;  // Label
    GHexBoard* m_board; // Contient le tableau

    int tileWidth = 20;
    int tileHeight = 20;
    const int xOffset = tileWidth * 3 / 4;  // Décalage horizontal des hexagones
    const int yOffset = tileHeight / 2;    // Décalage vertical des hexagones
};

#endif // GPLAYERBOARD_HPP
