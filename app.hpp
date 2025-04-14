#ifndef APP_HPP
#define APP_HPP
#include <QApplication>
#include <iostream>


class App : public QApplication {
public:
    App(int argc, char * argv[]);
    inline bool getIsConsole() const{return m_is_console;};
private :
    bool m_is_console = false;
};

#endif // APP_HPP
