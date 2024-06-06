#ifndef SENSOREARIA_H
#define SENSOREARIA_H

#include <QtWidgets>
#include "sensore.h"

class SensoreAria: public Sensore
{
private:
    int sogliaMassima;

public:
    SensoreAria();
    SensoreAria(const unsigned int id,
                const QString &name,
                const QString &unitaMisura,
                const QString &icona,
                const QString gruppo,
                int sogliaMassima,
                double valore);
    ~SensoreAria() = default;
    Valore getRandom(const QDateTime &dataOra) override;
    virtual Sensore *clone() const override;
    void generaDati();
    int getSogliaMassima() const;
};



#endif // SENSOREARIA_H
