#ifndef SENSOREELETTRODOMESTICO_H
#define SENSOREELETTRODOMESTICO_H

#include <QtWidgets>
#include "sensoreelettricita.h"

class SensoreElettrodomestico : public SensoreElettricita
{
private:
    QString classeEnergetica;

public:
    SensoreElettrodomestico();
    SensoreElettrodomestico(const QString &nome,
                     const QString &unitaMisura,
                     const QString &icona,
                     QString classeEnergetica,
                     double potenzaMax,
                     double valore);
};

#endif // SENSOREELETTRODOMESTICO_H
