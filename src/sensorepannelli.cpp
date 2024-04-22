#include "../headers/sensorepannelli.h"
#include "../headers/sensoreelettricita.h"
#include <QtWidgets>


SensorePannelli::SensorePannelli():SensoreElettricita(), nPannelli(65535), potenzaPannello(0) {}

SensorePannelli::SensorePannelli(const QString &nome,
                                   const QString &unitaMisura,
                                   const QString &icona,
                                   int nPannelli,
                                   double potenzaPannello,
                                   double potenzaMax,
                                   double valore
                                   )
    : SensoreElettricita(nome, unitaMisura, icona, potenzaMax, valore), nPannelli(nPannelli), potenzaPannello(potenzaPannello) {}
