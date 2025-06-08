#ifndef GPLAYERBOARD_HPP
#define GPLAYERBOARD_HPP

#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QMouseEvent>
#include <QVBoxLayout>
#include <QFrame>
#include <vector>


//#include "widgethexboard.hpp"
#include "../../../Gametools/Abstract/playerboard.hpp"


class GraphXVue;

const int tileWidth = 64;  // Largeur de la tuile hexagonale
const int tileHeight = 55; // Hauteur de la tuile hexagonale
const int xOffset = tileWidth * 3 / 4; // Décalage horizontal entre les tuiles
const int yOffset = tileHeight / 2;    // Décalage vertical pour les lignes impaires


class GPlayerBoard : public PlayerBoard, public QWidget{
public:
    GPlayerBoard(NotifiableInterface* tar, QWidget *parent = nullptr,int size = 41);
    GPlayerBoard(NotifiableInterface *tar, const std::string& def, QWidget *parent = nullptr,int size = 41);

    ~GPlayerBoard() = default;;

    void initHexTiles();
    void updateHexTiles();
    void addGxTile(int x,int y); // x,y de la matrice pas q,r !

    QSize sizeHint() const override;
    void show() override;

    QWidget* getWidget() const;
    GraphXVue* m_manager = nullptr;
private:
    int max_size;
    QWidget* m_widget = nullptr; // widget principal
    QVBoxLayout* m_layout = nullptr;  // Grid pour organiser les widgets
    QPoint m_last_mouse_pos;
    std::vector<std::vector <QLabel*>> tiles;
    bool m_dragging = false;
    void setHighlight();
    std::vector<GameTile*> posed;

};

#endif // GPLAYERBOARD_HPP
