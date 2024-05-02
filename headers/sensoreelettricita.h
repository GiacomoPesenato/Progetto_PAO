#ifndef SENSOREELETTRICITA_H
#define SENSOREELETTRICITA_H

#include <QtWidgets>
#include "sensore.h"

class SensoreElettricita: public Sensore
{
private:
    double potenzaMax;

public:
    SensoreElettricita();
    SensoreElettricita(const unsigned int id,
                       const QString &name,
                       const QString &unitaMisura,
                       const QString &icona,
                       const QString gruppo,
                       double potenzaMax,
                       double valore);
};

#endif // SENSOREELETTRICITA_H
