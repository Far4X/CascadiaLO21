#include "gplayerboard.hpp"
#include <iostream>
#include <QMouseEvent>
#include <cstdlib>
#include <ctime>
#include "graphxvue.hpp"

GPlayerBoard::GPlayerBoard(QWidget *parent,int size) : PlayerBoard(), QWidget{parent}, max_size(size) {

    // FOR DEBUG ONLY
/*
    Biome deb_biomes[6] = {River,Mountain,Prairie,Forest,Wetland,Wetland};
    GameTile* debugT = new GameTile(1,deb_biomes);
    HexCell deb_cell(0,0);
    Offset* deb_off = new Offset(axialToOffset(deb_cell));

    unsigned int deb_xs = (deb_off->getCol());
    unsigned int* deb_x = & deb_xs;

    unsigned int deb_ys = (deb_off->getRow());
    unsigned int* deb_y = & deb_ys;
    addTile(*debugT,deb_x,deb_y);
*/
    // FOR DEBUG ONLY

    setAutoFillBackground(true); // Permet de remplir l'arrière-plan
    setGeometry(0, 0, sizeHint().width(), sizeHint().height());  // Fixe la taille du widget
    m_layout = new QVBoxLayout(this);  // Optionnel : peut être utilisé si tu veux gérer des widgets enfants
    setLayout(m_layout);  // Applique le layout (mais ne sera pas utilisé pour les tuiles)

    // Exemple d'initialisation de tuiles hexagonales (image de démonstration)
    initHexTiles();

    m_manager = GraphXVue::instance();
    m_manager->addPlayerBoard(this);
    }


void GPlayerBoard::initHexTiles(){
    for (int col = 0; col < max_size; ++col) {
        for (int row = 0; row < max_size; ++row) {
            QLabel* tileLabel = new QLabel(this);  // Création d'un QLabel pour chaque tuile
            QPixmap pixmap;  // Charge une image de tuile
            if (std::rand() % 2 == 0 && col!=20 && row!=20)
                {
                QPixmap pixmapL(":/Assets/Assets/Tiles/desert.png");
                pixmap = pixmapL;
                }
            else if (col==20 && row==20){
                QPixmap pixmapL(":/Assets/Assets/tileOutline.png");
                pixmap = pixmapL;
                }
            else {
                QPixmap pixmapL(":/Assets/Assets/Tiles/lake.png");
                pixmap = pixmapL;
                }
            if (pixmap.isNull()) {std::cerr << "Erreur : l'image n'a pas pu être chargée !" << std::endl;}
            tileLabel->setPixmap(pixmap);
            tileLabel->setFixedSize(tileWidth, tileHeight);
            tileLabel->setScaledContents(true);  // Pour que l'image remplisse le QLabel

            // Calcul des positions x et y pour chaque tuile en utilisant un décalage
            int x = (col) * xOffset;
            int y = (row) * tileHeight;

            // Décalage pour les lignes impaires
            if (col % 2 == 1) {
                y += yOffset;  // Décalage vertical pour les colonnes impaires
            }

            tileLabel->move(x, y);  // Déplacement relatif au widget

        }
    }
}

void GPlayerBoard::addGxTile(int col,int row){
    QLabel* tileLabel = new QLabel(this);  // Création d'un QLabel pour chaque tuile
    QPixmap pixmap(":/Assets/Assets/Tiles/desert.png");  // Charge une image de tuile
    if (pixmap.isNull()) {
        std::cerr << "Erreur : l'image n'a pas pu être chargée !" << std::endl;
    }
    tileLabel->setPixmap(pixmap);
    tileLabel->setFixedSize(tileWidth, tileHeight);
    tileLabel->setScaledContents(true);  // Pour que l'image remplisse le QLabel

    // Calcul des positions x et y pour chaque tuile en utilisant un décalage
    int x = (col) * xOffset;
    int y = (row) * tileHeight;

    // Décalage pour les lignes impaires
    if (col % 2 == 1) {
        y += yOffset;  // Décalage vertical pour les colonnes impaires
    }

    tileLabel->move(x, y);  // Déplacement relatif au widget
}

void GPlayerBoard::show(){
    m_manager->show();
}

QSize GPlayerBoard::sizeHint() const {
    return QSize(41*tileWidth,42*tileHeight);
}














