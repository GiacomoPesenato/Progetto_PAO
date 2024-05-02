#ifndef SENSORELAMPADINA_H
#define SENSORELAMPADINA_H

#include <QtWidgets>
#include "sensoreelettricita.h"

class SensoreLampadina: public SensoreElettricita
{
private:
    bool dimm;

public:
    SensoreLampadina();
    SensoreLampadina(const unsigned int id,
                     const QString &name,
                     const QString &unitaMisura,
                     const QString &icona,
                     const QString gruppo,
                     bool dimm,
                     double potenzaMax,
                     double valore);
};

#endif // SENSORELAMPADINA_H
