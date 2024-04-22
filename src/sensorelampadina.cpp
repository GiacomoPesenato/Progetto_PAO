#include "../headers/sensorelampadina.h"
#include "../headers/sensoreelettricita.h"
#include <QtWidgets>


SensoreLampadina::SensoreLampadina():SensoreElettricita(), dimm(false) {}

SensoreLampadina::SensoreLampadina(const QString &nome,
                                       const QString &unitaMisura,
                                       const QString &icona,
                                       bool dimm,
                                       double potenzaMax,
                                       double valore
                                       )
    : SensoreElettricita(nome, unitaMisura, icona, potenzaMax,valore)
    , dimm(dimm){}
