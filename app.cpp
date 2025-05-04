#include "app.hpp"
#include <QWidget>
#include <iostream>

App &App::getInstance(int argc, char *argv[]){
    static App ins(argc, argv);
    return ins;
}

App::App(int argc, char *argv[]) : QApplication(argc, argv){
    std::cout << "Created app" << std::endl;
    //m_is_console = true; //DEBUG

    for (int i = 0; i < argc; i++){
        if (argv[i][0] == 'k' && argv[i][1] == '\0'){
            m_is_console = true;
            std::cout << "Console" << std::endl;
        }
    }
    if (!m_is_console) {
        std::cout << "GraphX" << std::endl;
    }
    m_game = new Game(m_is_console);

    //Tests :
}

App::~App(){
    std::cout << "App deleted" << std::endl;
    delete m_game;
}

int App::exec(){
    m_game->play();
    std::cout << "Play out" << std::endl;
    return QApplication::exec();
}
