#ifndef SENSOREARIA_H
#define SENSOREARIA_H

#include <QtWidgets>
#include <QtCharts>
#include "sensore.h"

class SensoreAria: public Sensore
{
private:
    int sogliaMassima;

public slots:
    void onButton1Clicked();
    void onButton2Clicked();

public:
    SensoreAria();
    SensoreAria(const unsigned int id,
                const QString &name,
                const QString &unitaMisura,
                const QString &icona,
                const QString gruppo,
                int sogliaMassima,
                double valore);
    Valore getRandom(const QDateTime &dataOra) override;
    static void modificaData(QDateTime &data);
    virtual Sensore *clone() const override;
};



#endif // SENSOREARIA_H
