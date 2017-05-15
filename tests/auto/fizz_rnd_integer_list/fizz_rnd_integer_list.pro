QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += tst_fizz_rnd_integer_list.cpp

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../../src/release/ -lUber
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../../src/debug/ -lUber
else:unix: LIBS += -L$$OUT_PWD/../../../src/ -lUber

INCLUDEPATH += $$PWD/../../../src
DEPENDPATH += $$PWD/../../../src
