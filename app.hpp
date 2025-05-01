#ifndef APP_HPP
#define APP_HPP
#include <QApplication>
#include <QTextStream>
#include "GameActors/game.hpp"
#include <iostream>

class App : public QApplication
{
public:
    inline bool getIsConsole() const { return m_is_console; };
    static App &getInstance(int argc = 0, char *argv[] = nullptr);
    App(const App &tar) = delete;
    App &operator=(const App &tar) = delete;
    int exec();
    App();
    ~App();

private:
    Game *m_game;
    bool m_is_console = false;
    App(int argc, char *argv[]);
};

#endif // APP_HPP
