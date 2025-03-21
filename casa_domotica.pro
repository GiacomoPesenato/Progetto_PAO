QT  += core gui widgets charts

CONFIG += c++17

TARGET = casa_domotica

SOURCES += \
    src/view/chart.cpp \
    src/main.cpp \
    src/model/sensore.cpp \
    src/model/sensorearia.cpp \
    src/model/sensoreelettricita.cpp \
    src/model/sensoreelettrodomestico.cpp \
    src/model/sensorelampadina.cpp \
    src/model/sensorepannelli.cpp \
    src/model/sensoretemperatura.cpp \
    src/model/sensoreumidita.cpp \
    src/model/valore.cpp \
    src/model/Converter/json.cpp \
    src/model/Converter/jsonVisitor.cpp \
    src/model/Converter/reader.cpp \
    src/model/DataMapper/jsonFile.cpp \
    src/model/Repository/jsonRepo.cpp \
    src/view/widgetsensore.cpp \
    src/view/mainwindow.cpp \
    src/view/schermatasensore.cpp \
    src/view/schermatasensori.cpp \
    src/view/sidebar.cpp \
    src/view/schermatanuovosensore.cpp \
    src/view/schermatamodificasensore.cpp


HEADERS += \
    src/model/sensorevisitor.h \
    src/view/chart.h \
    src/main.h \
    src/model/sensore.h \
    src/model/sensorearia.h \
    src/model/sensoreelettricita.h \
    src/model/sensoreelettrodomestico.h \
    src/model/sensorelampadina.h \
    src/model/sensorepannelli.h \
    src/model/sensoretemperatura.h \
    src/model/sensoreumidita.h \
    src/model/valore.h \
    src/model/Converter/json.h \
    src/model/Converter/jsonVisitor.h \
    src/model/Converter/reader.h \
    src/model/Converter/sensoreLettura.h \
    src/model/DataMapper/jsonFile.h \
    src/model/Repository/jsonRepo.h \
    src/model/Repository/sensoreRepo.h \
    src/view/widgetsensore.h \
    src/view/mainwindow.h \
    src/view/schermatasensore.h \
    src/view/schermatasensori.h \
    src/view/sidebar.h \
    src/view/schermatanuovosensore.h \
    src/view/schermatamodificasensore.h

RESOURCES += \
    resources.qrc
