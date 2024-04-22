#ifndef SENSORETEMPERATURA_H
#define SENSORETEMPERATURA_H

#include <QWidget>
#include "sensore.h"

class SensoreTemperatura: public Sensore
{
private:
    double valoreTarget,tempMin, tempMax;

public:
    SensoreTemperatura();
    SensoreTemperatura(const QString &nome,
                   const QString &unitaMisura,
                   const QString &icona,
                   double valoreTarget,
                   double tempMin,
                   double tempMax,
                   double valore);
    double getValoreTarget() const;
};

#endif // SENSORETEMPERATURA_H
