QT += widgets

DISTFILES += \
    .gitignore \
    Assets/blank-map.jpg \
    Assets/tileOutline.png \
    PlanTile
CONFIG += console

SOURCES += $$files($$PWD/*.cpp, true)
HEADERS += $$files($$PWD/*.hpp, true)
