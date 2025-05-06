#ifndef GPLAYERBOARD_HPP
#define GPLAYERBOARD_HPP

#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QMouseEvent>
#include <QVBoxLayout>
#include <QFrame>

#include "widgethexboard.hpp"
#include "Gametools/Abstract/playerboard.hpp"


class GPlayerBoard : public PlayerBoard{
public:
    /*GPlayerBoard();
    ~GPlayerBoard();
    QWidget* getWidget() const;
    void show() override;
private:

    QWidget* m_widget = nullptr; // widget principal
    QWidget* m_gridWidget = nullptr; // widget qui contient la grille
    QGridLayout* m_gridLayout = nullptr;  // Grid pour organiser les widgets
    QVBoxLayout* m_layout = nullptr;      // Main layout
    QPushButton* m_btn_quit = nullptr;  // Bouton Quit
    QLabel* m_label = nullptr;  // Label
    WidgetHexBoard* m_board = nullptr; // Contient le tableau

    int tileWidth = 20;
    int tileHeight = 20;
    const int xOffset = tileWidth * 3 / 4;  // Décalage horizontal des hexagones
    const int yOffset = tileHeight / 2;    // Décalage vertical des hexagones*/
};

#endif // GPLAYERBOARD_HPP
