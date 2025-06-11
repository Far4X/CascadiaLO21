#include "app.hpp"
#include <QWidget>
#include <iostream>

App &App::getInstance(int argc, char *argv[]){
    static App ins(argc, argv);
    return ins;
}

App::App(int argc, char *argv[]) : QApplication(argc, argv){
    std::cout << "Created app" << std::endl;
    m_is_console = true; //DEBUG

    for (int i = 0; i < argc; i++){
        if (argv[i][0] == 'k' && argv[i][1] == '\0'){
            m_is_console = true;
            std::cout << "Console" << std::endl;
        }
    }
    if (!m_is_console) {
        std::cout << "GraphX" << std::endl;
    }
    m_game = new Game(this, m_is_console);
    //Tests :
}

App::~App(){
    std::cout << "App deleted" << std::endl;
    delete m_game;
}

int App::exec(){
    if (!m_is_console){
        m_game->init();
        return QApplication::exec();
    }

    m_game->init();
    while(m_game->getGameStatus() == GameStatus::Running){
        if (m_id_notification.size() == 0){
            throw 99;
        }
        std::cout << "Reading : " << m_id_notification.front() << std::endl;;
        m_game->readNotification(m_id_notification.front());
        m_id_notification.pop_front();
    }
    m_game->init();
    std::cout << "Game Over" << std::endl;
    return QApplication::exec();
}


void App::notifyInterface(unsigned int code){
    m_id_notification.push_back(code);
    std::cout << "App received : " << code << std::endl;
}

void App::quitGame(){
    if (m_game){
        m_game->quit();
    }
}

void App::restartGame(){
    if (m_game){
        m_game->restart();
    }
}
