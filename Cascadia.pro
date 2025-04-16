QT += widgets

DISTFILES += \
    .gitignore
CONFIG += console

# Fichiers sources
SOURCES += $$files($$PWD/*.cpp, true)
# Fichiers d'en-tête
HEADERS += $$files($$PWD/*.hpp, true)
