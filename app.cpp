#include "app.hpp"
#include <QWidget>
#include "GameActors/gameactors.hpp"
#include <iostream>

App& App::getInstance(int argc, char* argv[]){
    static App ins(argc, argv);
    return ins;
}


App::App(int argc, char* argv[]) : QApplication(argc, argv){
    std::cout << "Created app" << std::endl;
    for (int i = 0; i < argc; i++){
        if (argv[i][0] == 'k' && argv[i][1] == '\0'){
            m_is_console = true;
            std::cout << "Console" << std::endl;
        }
    }
    if (!m_is_console){
        std::cout << "GraphX" << std::endl;
    }

    //Tests :
    m_is_console = true;
}

int App::exec(){
    /*QTextStream qtin(stdin);
    QString line = qtin.readLine();  // This is how you read the entire line

    QString word;
    qtin >> word;*/

    if (m_is_console){
        CPlayerMenu player_menu;
        player_menu.show();
        std::cout << "Results : " << std::endl;
        for (CPlayerMenu::Iterator it = player_menu.getIterator(); !it.isDone(); it++){
            std::cout << it.getValue() << std::endl;
        }
    }
    return QApplication::exec();
}
