QT += widgets

DISTFILES += \
    .gitignore \
    Assets/* \
    Assets/ListTiles.csv \
    Assets/StarterTiles.csv \
    PlanTile

CONFIG += console

SOURCES += $$files($$PWD/*.cpp, true)\
    GameActors/Menus/COMenus/ctokenmenu.cpp \
    GameActors/Menus/GXMenus/gtokenmenu.cpp

HEADERS += $$files($$PWD/*.hpp, true)\
    GameActors/Menus/COMenus/ctokenmenu.hpp \
    GameActors/Menus/GXMenus/gtokenmenu.hpp

RESOURCES += \
    ressources.qrc
