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
    SensoreElettricita(const QString &nome,
                   const QString &unitaMisura,
                   const QString &icona,
                   double potenzaMax,
                   double valore);
};

#endif // SENSOREELETTRICITA_H
