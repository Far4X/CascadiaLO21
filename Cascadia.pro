QT += widgets

DISTFILES += \
    .gitignore \
    Assets/* \
    Assets/ListTiles.lst \
    Assets/StarterTiles.csv \
    PlanTile

CONFIG += console

SOURCES += $$files($$PWD/*.cpp, true) \
    scoring/variants/familyvariant.cpp \
    scoring/variants/intermediatevariant.cpp

HEADERS += $$files($$PWD/*.hpp, true) \
    scoring/variants/familyvariant.hpp \
    scoring/variants/intermediatevariant.hpp

RESOURCES += \
    ressources.qrc
