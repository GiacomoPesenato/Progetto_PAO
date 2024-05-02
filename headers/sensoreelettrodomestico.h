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
    SensoreElettrodomestico(const unsigned int id,
                            const QString &name,
                            const QString &unitaMisura,
                            const QString &icona,
                            const QString gruppo,
                            QString classeEnergetica,
                            double potenzaMax,
                            double valore);
};

#endif // SENSOREELETTRODOMESTICO_H
