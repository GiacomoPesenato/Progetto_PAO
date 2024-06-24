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
    int getSogliaMassima() const;
    void setSogliaMassima(const int &value);

    void generaDati();
    ~SensoreAria() = default;
    Valore getRandom(const QDateTime &dataOra) override;
    virtual Sensore *clone() const override;
};



#endif // SENSOREARIA_H
