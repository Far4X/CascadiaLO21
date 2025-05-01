#include <QTextStream>
#include "app.hpp"

int main(int argc, char *argv[])
{
    return App::getInstance(argc, argv).exec();
}
