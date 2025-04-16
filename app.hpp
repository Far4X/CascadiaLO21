#ifndef APP_HPP
#define APP_HPP
#include <QApplication>
#include <iostream>
#include <QTextStream>


class App : public QApplication {
public:
    inline bool getIsConsole() const{return m_is_console;};
    static App& getInstance(int argc = 0, char* argv[] = nullptr);
    App(const App& tar) = delete;
    App& operator=(const App& tar) = delete;
    int exec();

private :
    bool m_is_console = false;
    App(int argc, char * argv[]);
};

#endif // APP_HPP
