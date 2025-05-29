#include "graphxvue.hpp"
#include "gplayerboard.hpp"
#include <iostream>


GraphXVue* GraphXVue::s_instance = nullptr;


GraphXVue::GraphXVue(QObject *parent)
    : QObject{parent}
{
    //Main Window
    m_window = new QWidget;
    m_main_layout = new QHBoxLayout(m_window);

    //Left panel
    m_left_panel = new QWidget;
    m_left_panel->setFixedWidth(150);
    m_left_panel_layout = new QVBoxLayout(m_left_panel);
    m_main_layout->addWidget(m_left_panel);

    //Right panel
    m_right_panel = new QWidget;
    m_right_panel_layout = new QVBoxLayout(m_right_panel);
    m_main_layout->addWidget(m_right_panel);

    //Onglet joueurs
    m_onglet = new QTabBar;
    m_onglet->setExpanding(true);
    connect(m_onglet, &QTabBar::currentChanged, this, &GraphXVue::onTabChanged);
    m_right_panel_layout->addWidget(m_onglet);

    //Scene et vue plateaux
    m_scene = new QGraphicsScene();
    m_view = new GraphXView(m_scene);
    m_view->setDragMode(GraphXView::ScrollHandDrag);  // clic-gauche pour dragger
    m_view->setRenderHint(QPainter::Antialiasing);
    m_view->setTransformationAnchor(GraphXView::AnchorUnderMouse);
    m_right_panel_layout->addWidget(m_view);
    QRectF sceneRect(0, 0, 2600, 2600);  //plus tard remplacer par de vrai fonction qui permettent de gérer le zoom dezoom
    m_scene->setSceneRect(sceneRect);
    connect(m_view, &GraphXView::rightClickAt, this, &GraphXVue::onRightClickAt);

    currentboard = 0;

}


GraphXVue* GraphXVue::instance(){
    if(!s_instance){
        s_instance = new GraphXVue;
    }
    return s_instance;

}

void GraphXVue::addPlayerBoard(GPlayerBoard* board){
    boards.push_back(board);
    m_onglet->addTab(QString("Joueu %1").arg(boards.size()));

    //On s'assure que chaque board n'a pas d'autre parent;
    board->setParent(nullptr);
    QGraphicsProxyWidget* proxy = m_scene->addWidget(board);
    proxy->setVisible(false);
    //proxy->setPos(200,100); // a revoir c trop fais main si on change quoi que ce soit ça
    proxies.push_back(proxy);
    //m_layout->addWidget(board);
}

void GraphXVue::show(){
    if(!boards.empty() && !proxies.empty()){
        proxies[0]->setVisible(true);
        m_view->centerOn(proxies[0]);
    }
    m_window->show();
}

void GraphXVue::onTabChanged(int index)
{
    if (index < 0 || index >= static_cast<int>(proxies.size()))
        return;

    for (size_t i = 0; i < proxies.size(); ++i) {
        proxies[i]->setVisible(i == static_cast<size_t>(index));
    }
    m_view->centerOn(proxies[index]);
    currentboard = index;
}

void GraphXVue::onRightClickAt(const QPointF& scenePos)
{
    int col = static_cast<int>(scenePos.x() / xOffset);
    float yAdjusted = scenePos.y();

    if (col % 2 == 1) {
        yAdjusted -= yOffset;  // décale vers le haut pour les colonnes impaires
    }

    int row = static_cast<int>(yAdjusted / tileHeight);

    // Debug
    std::cout<<currentboard<<" ";
    qDebug() << "Clique droit sur row:" << row << "col:" << col;
    HexCell::Offset off(row,col);
    HexCell hex (PlayerBoard::offsetToAxial(off));
    qDebug() << "Clique droit sur r:" << PlayerBoard::offsetToAxial(off).getR() << "q:" << PlayerBoard::offsetToAxial(off).getQ();
    boards[currentboard]->setPointedCell(hex);
    boards[currentboard]->getTarget()->notifyInterface(4); // j'ai cliqué sur le plateau est ce que je peux poser | 3 une fois qu'on a select toekn et carte
    return;
}


void GraphXVue::addMenu(QWidget* menu){
    m_right_panel_layout->addWidget(menu);

}



















