QT += widgets

DISTFILES += \
    .gitignore \
    Assets/* \
    PlanTile

CONFIG += console

SOURCES += $$files($$PWD/*.cpp, true) \
    GameActors/GraphicalComponents/GraphX/ghexboard.cpp
HEADERS += $$files($$PWD/*.hpp, true) \
    GameActors/GraphicalComponents/GraphX/ghexboard.hpp

RESOURCES += \
    ressources.qrc
