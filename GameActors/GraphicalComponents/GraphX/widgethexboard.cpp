#include "widgethexboard.hpp"
#include <iostream>

WidgetHexBoard::WidgetHexBoard(QWidget *parent,int size)
    : QWidget{parent}, max_size(size)
{}

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
