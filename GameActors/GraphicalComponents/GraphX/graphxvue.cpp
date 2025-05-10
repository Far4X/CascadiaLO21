#include "graphxvue.hpp"
#include "gplayerboard.hpp"


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
    m_view = new QGraphicsView(m_scene);
    m_view->setDragMode(QGraphicsView::ScrollHandDrag);  // clic-gauche pour dragger
    m_view->setRenderHint(QPainter::Antialiasing);
    m_view->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    m_right_panel_layout->addWidget(m_view);



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
    proxies.push_back(proxy);
    //m_layout->addWidget(board);
}

void GraphXVue::show(){
    if(!boards.empty()){
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
}





















