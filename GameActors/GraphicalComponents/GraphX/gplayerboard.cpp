#include "gplayerboard.hpp"
#include <iostream>
#include <QMouseEvent>

GPlayerBoard::GPlayerBoard() : PlayerBoard() {

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


    m_widget = new QWidget(); // Crée un widget interne pour l'affichage
    m_layout = new QVBoxLayout(m_widget); // Initialise le layout principal pour le widget
    m_btn_quit = new QPushButton("Quitter", m_widget); // Crée le bouton quitter et le label de bienvenue
    m_label = new QLabel("Bienvenue sur le plateau de jeu!", m_widget);

    // Créer l'objet HexagonalBoard pour contenir les tuiles
    m_board = new WidgetHexBoard(m_widget);  // Initialise ton objet de tuiles hexagonales

    // Ajout des widget au layout principal
    m_layout->addWidget(m_label);
    m_layout->addWidget(m_btn_quit);
    m_layout->addWidget(m_board); // Ajoute l'objet HexagonalBoard au layout du widget principal

    // Connecte le bouton Quitter pour fermer la fenêtre
    QObject::connect(m_btn_quit, &QPushButton::clicked, m_widget, &QWidget::close);
    }



GPlayerBoard::~GPlayerBoard() {
    delete m_layout;
    delete m_btn_quit;
    delete m_label;
    delete m_gridLayout;
    delete m_gridWidget;
    delete m_widget;
    delete m_board;
}

void GPlayerBoard::show() {
    m_widget->show();
}
