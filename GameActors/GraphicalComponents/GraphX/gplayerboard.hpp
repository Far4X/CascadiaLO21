#ifndef GPLAYERBOARD_HPP
#define GPLAYERBOARD_HPP

#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QMouseEvent>
#include <QVBoxLayout>
#include <QFrame>

//#include "widgethexboard.hpp"
#include "Gametools/Abstract/playerboard.hpp"



const int tileWidth = 64;  // Largeur de la tuile hexagonale
const int tileHeight = 64; // Hauteur de la tuile hexagonale
const int xOffset = tileWidth * 3 / 4; // Décalage horizontal entre les tuiles
const int yOffset = tileHeight / 2;    // Décalage vertical pour les lignes impaires


class GPlayerBoard : public PlayerBoard,public QWidget{
public:
    GPlayerBoard(QWidget *parent = nullptr,int size = 41);
    ~GPlayerBoard() = default;;

    void initHexTiles();
    void addGxTile(int x,int y); // x,y de la matrice pas q,r !

    QWidget* getWidget() const;
private:
    int max_size;
    QWidget* m_widget = nullptr; // widget principal
    QWidget* m_gridWidget = nullptr; // widget qui contient la grille
    QVBoxLayout* m_layout = nullptr;  // Grid pour organiser les widgets

};

#endif // GPLAYERBOARD_HPP
