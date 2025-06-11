QT += widgets

DISTFILES += \
    .gitignore \
    Assets/* \
    Assets/ListTiles.lst \
    Assets/Paysage \
    Assets/Paysage/Tiles.lst \
    Assets/Paysage/Tokens.lst \
    Assets/StarterTiles.csv \
    PlanTile

CONFIG += console

SOURCES += $$files($$PWD/*.cpp, true)

HEADERS += $$files($$PWD/*.hpp, true)


RESOURCES += \
    ressources.qrc
