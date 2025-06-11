#include "gdecktile.hpp"
#include <iostream>

GDeckTile::GDeckTile(QObject *parent): QObject(parent){}


GDeckTile& GDeckTile::getInstance(){
    static GDeckTile ins;
    return ins;
}

void GDeckTile::construct(){
    if(widget != nullptr) delete widget;
    widget = new QWidget;

    deck = new QHBoxLayout(widget);

    tiles = new QVBoxLayout(widget);
    deck->addLayout(tiles);

    tokens = new QVBoxLayout(widget);
    deck->addLayout(tokens);

    for(int i = 0; i<4;i++)
    {
        const GameTile* tile = getTile(i);
        const WildlifeToken* wild = m_displayed_tokens[i];
        if (tile == nullptr){
            throw CustomError("Tile doesn't exists", 999);
        }
        ClickableLabel* labelTi = new ClickableLabel(widget);
        ClickableLabel* labelTo = new ClickableLabel(widget);
        QPixmap pixmap = PixmapFactory::createTile(tile);
        QPixmap token(PixmapFactory::matchToken(wild->getWildlifeType()));

        labelTi->setPixmap(pixmap);
        labelTi->setFixedSize(64, 55);
        labelTi->setScaledContents(true);  // Pour que l'image remplisse le QLabel

        labelTo->setPixmap(token);
        labelTo->setFixedSize(50, 50);
        labelTo->setScaledContents(true);  // Pour que l'image remplisse le QLabel


        tiles->addWidget(labelTi);
        tokens->addWidget(labelTo);

        connect(labelTi, &ClickableLabel::clicked, [i]() {
            qDebug() << "Tuile " << i << " cliquée !";
            // Appelle ici la fonction pour prendre la tuile `i` dans la pioche
        });

        connect(labelTo, &ClickableLabel::clicked, [i]() {
            qDebug() << "Jeton " << i << " cliqué !";
            // Pareil pour le jeton si tu veux
        });

        connect(labelTi, &ClickableLabel::clicked, this, [this, i]() {
            emit tileClicked(i);  // Émet le signal quand la tuile est cliquée
        });

        connect(labelTo, &ClickableLabel::clicked, this, [this, i](){
            emit tokenClicked(i);
        });
    }

}

void GDeckTile::show(){
    std::cout<<"k";
    construct();
    GraphXVue::instance()->addDeck(widget);
    widget->show();
    std::cout<<"ok";
}
