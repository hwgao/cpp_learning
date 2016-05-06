TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += C++14

# QMAKE_LFLAGS += -lpthread

CONFIG(debug, debug|release) {
    QMAKE_CXXFLAGS += -Wall
    QMAKE_CXXFLAGS += -Wextra
    QMAKE_CXXFLAGS += -ggdb
    QMAKE_CXXFLAGS += -fsanitize=address
}

SOURCES += main.cpp

HEADERS += \
    printtuple.hpp \
    printable.hpp \
    make_unique.hpp \
    optional.hpp

