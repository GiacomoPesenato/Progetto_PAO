#ifndef SENSORELAMPADINA_H
#define SENSORELAMPADINA_H

#include <QtWidgets>
#include "sensoreelettricita.h"

class SensoreLampadina: public SensoreElettricita
{
private:
    bool dimmer;

public:
    SensoreLampadina();
    SensoreLampadina(const unsigned int id,
                     const QString &name,
                     const QString &unitaMisura,
                     const QString &icona,
                     const QString gruppo,
                     bool dimmer,
                     double potenzaMax,
                     double valore);

    Valore getRandom(const QDateTime &dataOra) override;
    void generaDati() override;
    bool getDimmer() const;
    void setDimmer(bool value);

    virtual Sensore *clone() const override;
    virtual void accetta(sensoreVisitor& visitor) const override;
    ~SensoreLampadina() override = default;
};

#endif // SENSORELAMPADINA_H
