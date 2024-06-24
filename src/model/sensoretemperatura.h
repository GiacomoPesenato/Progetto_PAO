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
    SensoreTemperatura(const unsigned int id,
                       const QString &name,
                       const QString &unitaMisura,
                       const QString &icona,
                       const QString gruppo,
                       double valoreTarget,
                       double tempMin,
                       double tempMax,
                       double valore);

    double getValoreTarget() const;
    void setValoreTarget(const double &value);
    double getTempMin() const;
    void setTempMin(const double &value);
    double getTempMax() const;
    void setTempMax(const double &value);
    Valore getRandom(const QDateTime &dataOra) override;

    virtual Sensore *clone() const override;
    ~SensoreTemperatura() = default;

};

#endif // SENSORETEMPERATURA_H
