#ifndef SENSOREELETTRICITA_H
#define SENSOREELETTRICITA_H

#include <QtWidgets>
#include "sensore.h"

class SensoreElettricita: public Sensore
{
private:
    const double potenzaMax;

public:
    SensoreElettricita();
    SensoreElettricita(const unsigned int id,
                       const QString &nome,
                       const QString &unitaMisura,
                       const QString &icona,
                       const QString gruppo,
                       double potenzaMax,
                       double valore);

    double getPotenzaMax() const;

    virtual Sensore *clone() const override;
    ~SensoreElettricita() = default;
};

#endif // SENSOREELETTRICITA_H
