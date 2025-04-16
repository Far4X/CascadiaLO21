#include "app.hpp"
#include <QTextStream>

int main(int argc, char* argv[]) {
    return App::getInstance(argc, argv).exec();
}
