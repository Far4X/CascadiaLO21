#include "gdecktile.hpp"
#include <iostream>

GDeckTile::GDeckTile(QObject *parent): QObject(parent){}


GDeckTile& GDeckTile::getInstance(){
    static GDeckTile ins;
    return ins;
}

void GDeckTile::construct(){
    if(widget)return; // on ne construit qu'une fois
    widget = new QWidget;

    deck = new QHBoxLayout(widget);

    tiles = new QVBoxLayout(widget);
    deck->addLayout(tiles);

    tokens = new QVBoxLayout(widget);
    deck->addLayout(tokens);

    ti1 = new ClickableLabel(widget);
    ti2 = new ClickableLabel(widget);
    ti3 = new ClickableLabel(widget);
    ti4 = new ClickableLabel(widget);
    tilesL.push_back(ti1);
    tilesL.push_back(ti2);
    tilesL.push_back(ti3);
    tilesL.push_back(ti4);

    to1 = new ClickableLabel(widget);
    to2 = new ClickableLabel(widget);
    to3 = new ClickableLabel(widget);
    to4 = new ClickableLabel(widget);
    tokenL.push_back(to1);
    tokenL.push_back(to2);
    tokenL.push_back(to3);
    tokenL.push_back(to4);

    for(int i = 0; i<4;i++)
    {
        tilesL[i]->setParent(widget); // ils seront donc libéré a la liberation du widget (je crois)
        tokenL[i]->setParent(widget);

        tiles->addWidget(tilesL[i]);
        tokens->addWidget(tokenL[i]);

        connect(tilesL[i], &ClickableLabel::clicked, [i]() {
            qDebug() << "Tuile " << i << " cliquée !";
            // Appelle ici la fonction pour prendre la tuile `i` dans la pioche
        });

        connect(tokenL[i], &ClickableLabel::clicked, [i]() {
            qDebug() << "Jeton " << i << " cliqué !";
            // Pareil pour le jeton si tu veux
        });

        connect(tilesL[i], &ClickableLabel::clicked, this, [this, i]() {
            emit tileClicked(i);  // Émet le signal quand la tuile est cliquée
        });

        connect(tokenL[i], &ClickableLabel::clicked, this, [this, i](){
            emit tokenClicked(i);
        });
    }

}

void GDeckTile::update(){
    for(int i = 0; i < 4; ++i){
        const GameTile* tile = getTile(i);
        const WildlifeToken* wild = m_displayed_tokens[i];
        if (!tile || !wild) continue;

        QPixmap pixmap = PixmapFactory::createTile(tile);
        QPixmap token = QPixmap(PixmapFactory::matchToken(wild->getWildlifeType()));

        tilesL[i]->setPixmap(pixmap);
        tilesL[i]->setFixedSize(64, 55);
        tilesL[i]->setScaledContents(true);  // Pour que l'image remplisse le QLabel

        tokenL[i]->setPixmap(token);
        tokenL[i]->setFixedSize(50, 50);
        tokenL[i]->setScaledContents(true);  // Pour que l'image remplisse le QLabel
    }
}

void GDeckTile::show(){
    construct();
    update();
    GraphXVue::instance()->addDeck(widget);
    widget->show();
}
