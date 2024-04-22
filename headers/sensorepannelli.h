#ifndef SENSOREPANNELLI_H
#define SENSOREPANNELLI_H

#include "sensoreelettricita.h"
#include <QtWidgets>
class SensorePannelli: public SensoreElettricita
{
private:
    int nPannelli;
    double potenzaPannello;

public:
    SensorePannelli();
    SensorePannelli(const QString &nome,
                     const QString &unitaMisura,
                     const QString &icona,
                     int nPannelli,
                     double potenzaPannello,
                     double potenzaMax,
                     double valore);
};

#endif // SENSOREPANNELLI_H
