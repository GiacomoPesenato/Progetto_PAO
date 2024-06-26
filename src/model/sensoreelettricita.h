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
                       const QString &nome,
                       const QString &unitaMisura,
                       const QString &icona,
                       const QString gruppo,
                       double potenzaMax,
                       double valore);

    double getPotenzaMax() const;
    void setPotenzaMax(const double &value);

    ~SensoreElettricita() override = default;
};

#endif // SENSOREELETTRICITA_H
