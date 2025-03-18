#include "app.hpp"

App::App(int argc, char* argv[]) : QApplication(argc, argv){
    for (int i = 0; i < argc; i++){
        if (argv[i][0] == 'k' && argv[i][1] == '\0'){
            m_is_console = true;
            std::cout << "Console" << std::endl;
        }
    }
    if (!m_is_console){
        std::cout << "GraphX" << std::endl;
    }
}
