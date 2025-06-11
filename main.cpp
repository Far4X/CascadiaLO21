#include <QTextStream>
#include "app.hpp"

Game* global_game = nullptr;

int main(int argc, char *argv[])
{


    return App::getInstance(argc, argv).exec();
}
