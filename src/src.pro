
QT -= gui
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = lib
TARGET = Uber

SOURCES += \
    fizz_rnd_float_list.cpp \
    stats.cpp \
    fizz_rnd_integer_list.cpp \
    fake_random_number_generator.cpp \
    random_number_generator.cpp

HEADERS += \
    fizz_rnd_float_list.h \
    stats.h \
    fizz_rnd_integer_list.h \
    i_random_number_generator.h \
    random_number_generator.h \
    fake_random_number_generator.h
