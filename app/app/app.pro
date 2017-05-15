QT += core
QT -= gui

CONFIG += c++11

TARGET = app
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp


win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../src/release/ -lUber
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../src/debug/ -lUber
else:unix: LIBS += -L$$OUT_PWD/../../src/ -lUber

INCLUDEPATH += $$PWD/../../src
DEPENDPATH += $$PWD/../../src
