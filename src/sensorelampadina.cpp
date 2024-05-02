#include "../headers/sensorelampadina.h"
#include "../headers/sensoreelettricita.h"
#include <QtWidgets>


SensoreLampadina::SensoreLampadina():SensoreElettricita(), dimm(false) {}

SensoreLampadina::SensoreLampadina(const unsigned int id,
                                   const QString &nome,
                                   const QString &unitaMisura,
                                   const QString &icona,
                                   const QString gruppo,
                                       bool dimm,
                                       double potenzaMax,
                                       double valore
                                       )
    : SensoreElettricita(id, nome, unitaMisura, icona, gruppo, potenzaMax,valore), dimm(dimm){}
