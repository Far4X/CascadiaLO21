QT += widgets

DISTFILES += \
    .gitignore \
    PlanTile
CONFIG += console

SOURCES += $$files($$PWD/*.cpp, true)
HEADERS += $$files($$PWD/*.hpp, true)
