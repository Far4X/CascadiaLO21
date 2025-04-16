QT += widgets

DISTFILES += \
    .gitignore
CONFIG += console

# Fichiers sources
SOURCES += $$files($$PWD/*.cpp, true) \
    GameActors/Menus/GXMenus/gmenu.cpp
# Fichiers d'en-tête
HEADERS += $$files($$PWD/*.hpp, true) \
    GameActors/Menus/GXMenus/gmenu.hpp
