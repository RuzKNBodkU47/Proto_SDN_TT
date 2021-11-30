QT += sql
LIBS += -lmariadb
INCLUDEPATH += /usr/include/mysql/

TEMPLATE = app
CONFIG += console c++ll
CONFIG -= app_bundle
CONFIG -= qt

SOURCES +=  \
        BDConnection.cpp