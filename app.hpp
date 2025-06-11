#ifndef APP_HPP
#define APP_HPP
#include <QApplication>
#include <QTextStream>
#include "GameActors/game.hpp"
#include "Gametools/Abstract/notifiableinterface.hpp"
#include <iostream>
#include <deque>

class App : public QApplication, public NotifiableInterface {
public:
    inline bool getIsConsole() const { return m_is_console; };
    static App &getInstance(int argc = 0, char *argv[] = nullptr);
    App(const App &tar) = delete;
    App &operator=(const App &tar) = delete;
    int exec();

private:
    App();
    ~App();
    Game *m_game;
    bool m_is_console = false;
    App(int argc, char *argv[]);
    std::deque<unsigned short int> m_id_notification;
    void notifyInterface(unsigned int code) override;
    void quitGame();
    void restartGame();
};

#endif // APP_HPP
