QT       += core gui widgets charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/chart.cpp \
    src/main.cpp \
    src/sensore.cpp \
    src/sensorearia.cpp \
    src/sensoreelettricita.cpp \
    src/sensoreelettrodomestico.cpp \
    src/sensorelampadina.cpp \
    src/sensorepannelli.cpp \
    src/sensoretemperatura.cpp \
    src/sensoreumidita.cpp \
    src/valore.cpp \
    src/widgetsensore.cpp \
    src/mainwindow.cpp \
    src/schermatasensore.cpp \
    src/schermatasensori.cpp \
    src/sidebar.cpp \
    src/schermatanuovosensore.cpp


HEADERS += \
    headers/main.h \
    headers/sensore.h \
    headers/sensorearia.h \
    headers/sensoreelettricita.h \
    headers/sensoreelettrodomestico.h \
    headers/sensorelampadina.h \
    headers/sensorepannelli.h \
    headers/sensoretemperatura.h \
    headers/sensoreumidita.h \
    headers/valore.h \
    headers/chart.h \
    headers/widgetsensore.h \
    headers/mainwindow.h \
    headers/schermatasensore.h \
    headers/schermatasensori.h \
    headers/sidebar.h \
    headers/schermatanuovosensore.h

TRANSLATIONS += \
    domotica_it_IT.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
