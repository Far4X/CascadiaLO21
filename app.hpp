#ifndef APP_HPP
#define APP_HPP
#include <QApplication>
#include <iostream>

class App : public QApplication {
public:
    App(int argc, char * argv[]);
private :
    bool m_is_console = false;
};

#endif // APP_HPP
