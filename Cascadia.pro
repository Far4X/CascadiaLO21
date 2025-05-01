QT += widgets

DISTFILES += \
    .gitignore \
    PlanTile
CONFIG += console

SOURCES += $$files($$PWD/*.cpp, true) \
    GameActors/Menus/COMenus/cgamemenu.cpp \
    GameActors/Menus/GXMenus/ggamemenu.cpp

HEADERS += $$files($$PWD/*.hpp, true) \
    GameActors/Menus/COMenus/cgamemenu.hpp \
    GameActors/Menus/GXMenus/ggamemenu.hpp

