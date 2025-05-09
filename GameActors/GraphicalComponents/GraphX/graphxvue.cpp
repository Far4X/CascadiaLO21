#include "graphxvue.hpp"
#include "gplayerboard.hpp"


GraphXVue* GraphXVue::s_instance = nullptr;

GraphXVue::GraphXVue(QObject *parent)
    : QObject{parent}
{
    m_window = new QWidget;
    m_layout = new QVBoxLayout(m_window);
}


GraphXVue* GraphXVue::instance(){
    if(!s_instance){
        s_instance = new GraphXVue;
    }
    return s_instance;
}

void GraphXVue::addPlayerBoard(GPlayerBoard* board){
    m_layout->addWidget(board);
}

void GraphXVue::show(){
    m_window->show();
}
