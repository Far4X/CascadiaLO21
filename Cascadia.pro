QT += widgets

DISTFILES += \
    .gitignore \
    PlanTile
CONFIG += console

# Fichiers sources
SOURCES += $$files($$PWD/*.cpp, true) \
    GameActors/GraphicalComponents/Console/cdecktile.cpp \
    GameActors/GraphicalComponents/GraphX/gdecktile.cpp \
    GameActors/cplayerboard.cpp \
    GameActors/gplayerboard.cpp \
    Gametools/Abstract/decktile.cpp
# Fichiers d'en-tête
HEADERS += $$files($$PWD/*.hpp, true) \
    GameActors/GraphicalComponents/Console/cdecktile.hpp \
    GameActors/GraphicalComponents/GraphX/gdecktile.hpp \
    GameActors/cplayerboard.hpp \
    GameActors/gplayerboard.hpp \
    Gametools/Abstract/decktile.hpp
