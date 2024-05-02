#include "../headers/sensorepannelli.h"
#include "../headers/sensoreelettricita.h"
#include <QtWidgets>


SensorePannelli::SensorePannelli():SensoreElettricita(), nPannelli(65535), potenzaPannello(0) {}

SensorePannelli::SensorePannelli(const unsigned int id,
                                 const QString &nome,
                                 const QString &unitaMisura,
                                 const QString &icona,
                                 const QString gruppo,
                                 int nPannelli,
                                 double potenzaPannello,
                                 double potenzaMax,
                                 double valore
                                 )
    : SensoreElettricita(id, nome, unitaMisura, icona, gruppo, potenzaMax, valore), nPannelli(nPannelli), potenzaPannello(potenzaPannello) {}
