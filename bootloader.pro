TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        CMDs.c \
        SERIAL.c \
        main.c

HEADERS += \
    CMDs.h \
    FLASH.h \
    REG.h \
    SERIAL.h \
    iodefine.h
