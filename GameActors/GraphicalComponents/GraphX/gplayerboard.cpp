#include "gplayerboard.hpp"
#include <iostream>

GPlayerBoard::GPlayerBoard() : PlayerBoard() {
    // Crée un widget interne pour l'affichage
    m_widget = new QWidget();

    // Initialise le layout et les autres widgets à l'intérieur de m_widget
    m_layout = new QGridLayout(m_widget);
    m_btn_quit = new QPushButton("Quitter", m_widget);
    m_label = new QLabel("Bienvenue sur le plateau de jeu!", m_widget);

    m_layout->addWidget(m_label, 0, 0);
    m_layout->addWidget(m_btn_quit, 1, 0);

    QObject::connect(m_btn_quit, &QPushButton::clicked, m_widget, &QWidget::close);

    m_widget->setLayout(m_layout);

    /* FOR DEBUG ONLY */

    Biome deb_biomes[6] = {River,Mountain,Prairie,Forest,Wetland,Wetland};
    GameTile* debugT = new GameTile(1,deb_biomes);
    HexCell deb_cell(0,0);
    Offset* deb_off = new Offset(axialToOffset(deb_cell));

    unsigned int deb_xs = (deb_off->getCol());
    unsigned int* deb_x = & deb_xs;

    unsigned int deb_ys = (deb_off->getRow());
    unsigned int* deb_y = & deb_ys;
    addTile(*debugT,deb_x,deb_y);
     /* FOR DEBUG ONLY */

    for(int y = 0; y<MAX_SIZE;y++)
    {
        for(int x = 0; x<MAX_SIZE;x++)
        {
            if(getTile(x,y)==nullptr)
            {
                std::cout<<"O";

            }
            else{
                std::cout<<"I";

            }

        }
        std::cout<<std::endl;
    }

}

GPlayerBoard::~GPlayerBoard() {
    // Libère la mémoire allouée
    delete m_layout;
    delete m_btn_quit;
    delete m_label;
    delete m_widget;
}

void GPlayerBoard::show() {
    m_widget->show();
}
