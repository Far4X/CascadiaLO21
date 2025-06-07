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

    m_lcd = new QLCDNumber(m_left_panel);
    m_lcd->setDigitCount(2);
    m_lcd->setSegmentStyle(QLCDNumber::Filled);
    m_lcd->setFixedHeight(40);
    m_lcd->display(m_turn_count);
    m_left_panel_layout->addWidget(m_lcd, 0);

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
    m_view->setRenderHint(QPainter::SmoothPixmapTransform); // éviter la pixellisation
    m_view->setTransformationAnchor(GraphXView::AnchorUnderMouse);
    m_right_panel_layout->addWidget(m_view);
    QRectF sceneRect(0, 0, 2600, 2600);
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

void GraphXVue::show(int playerIndex){
    if (boards.empty() || proxies.empty())return;

    if(!boards.empty() && !proxies.empty()){
        proxies[0]->setVisible(true);
        m_view->centerOn(proxies[0]);
    }
    if(playerIndex != -1){ // -1 pour skip l'update d'onglet
    boards[playerIndex]->updateHexTiles();
    m_onglet->setCurrentIndex(playerIndex);
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

QPointF offsetToScenePos(HexCell::Offset offset) {
    int row = offset.getRow();
    int col = offset.getCol();

    float x = col * xOffset;
    float y = row * tileHeight;

    if (col % 2 == 1) {
        y += yOffset;
    }

    return QPointF(x, y);
}

void GraphXVue::onRightClickAt(const QPointF& scenePos)
{
    // On tente de deviner la tuile
    int row = static_cast<int>(scenePos.x() / xOffset);  // horizontal (colonne)
    float yAdjusted = scenePos.y();

    if (row % 2 == 1)yAdjusted -= yOffset;

    int col = static_cast<int>(yAdjusted / tileHeight);  // vertical (ligne)

    HexCell::Offset guessed(row, col);

    // NE FONCTIONNE PAS ENCORE

    /*
    QPointF center = offsetToScenePos(guessed);
    float radius = tileHeight; // 2.0f; // on va verif si on a bien guess

    if (!isPointInHex(scenePos, center, radius)) {
        // tester les 6 voisines
        std::vector<HexCell::Offset> neighbors = {
            {row - 1, col}, {row + 1, col},
            {row, col - 1}, {row, col + 1},
            {col % 2 == 0 ? row - 1 : row + 1, col - 1},
            {col % 2 == 0 ? row - 1 : row + 1, col + 1}
        };

        for (const auto& neighbor : neighbors) {
            QPointF neighCenter = offsetToScenePos(neighbor);
            if (isPointInHex(scenePos, neighCenter, radius)) {
                guessed = neighbor;
                break;
            }
        }
    }
    */

    // Debug
    std::cout<<currentboard<<" ";
    qDebug() << "Clique droit sur row:" << guessed.getRow() << "col:" << guessed.getCol();
    HexCell hex (PlayerBoard::offsetToAxial(guessed));
    qDebug() << "Clique droit sur r:" << PlayerBoard::offsetToAxial(guessed).getR() << "q:" << PlayerBoard::offsetToAxial(guessed).getQ();
    boards[currentboard]->setPointedCell(hex);
    boards[currentboard]->getTarget()->notifyInterface(4); // j'ai cliqué sur le plateau est ce que je peux poser | 3 une fois qu'on a select toekn et carte
    return;
}


void GraphXVue::addMenu(QWidget* menu){
    m_right_panel_layout->addWidget(menu);

}

void GraphXVue::addDeck(QWidget* deck){
    m_left_panel_layout->addWidget(deck);
}

void GraphXVue::nextTurn() {
    if (m_turn_count > 0) {
        m_turn_count--;
        m_lcd->display(m_turn_count);
    }
}




















