#include "widgethexboard.hpp"
#include <iostream>
/*
WidgetHexBoard::WidgetHexBoard(QWidget *parent,int size)
    : QWidget{parent}, max_size(size)
{
    setAutoFillBackground(true); // Permet de remplir l'arrière-plan
    setGeometry(0, 0, 600, 600);  // Fixe la taille du widget
    m_layout = new QVBoxLayout(this);  // Optionnel : peut être utilisé si tu veux gérer des widgets enfants
    setLayout(m_layout);  // Applique le layout (mais ne sera pas utilisé pour les tuiles)

    // Exemple d'initialisation de tuiles hexagonales (image de démonstration)
    initHexTiles();
}

void WidgetHexBoard::initHexTiles(){
    for (int col = 0; col < max_size; ++col) {
        for (int row = 0; row < max_size; ++row) {
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
    }
}

void WidgetHexBoard::addTile(int col,int row){
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

*/
