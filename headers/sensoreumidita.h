#ifndef SENSOREUMIDITA_H
#define SENSOREUMIDITA_H

#include <QWidget>
#include "sensore.h"

class SensoreUmidita : public Sensore
{
private:
    double valoreTarget;

public:
    SensoreUmidita();
    SensoreUmidita(const QString &nome,
                   const QString &unitaMisura,
                   const QString &icona,
                   double valoreTarget,
                   double valore);
    double getValoreTarget() const;
    Valore getRandom(const QDateTime &dataOra) override;
};

#endif // SENSOREUMIDITA_H
