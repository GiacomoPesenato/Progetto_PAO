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
    SensoreUmidita(const unsigned int id,
                   const QString &name,
                   const QString &unitaMisura,
                   const QString &icona,
                   const QString gruppo,
                   double valoreTarget,
                   double valore);
    double getValoreTarget() const;
    void setValoreTarget(const double &value);
    Valore getRandom(const QDateTime &dataOra) override;

    virtual Sensore *clone() const override;
    ~SensoreUmidita() = default;
    virtual void accept(sensoreVisitor& visitor) const override;
};

#endif // SENSOREUMIDITA_H
