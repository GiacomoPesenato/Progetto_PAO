#ifndef SENSOREARIA_H
#define SENSOREARIA_H

#include <QtWidgets>
#include <QtCharts>
#include "sensore.h"

class SensoreAria: public Sensore
{
private:
    double sogliaMassima;

public:
    SensoreAria();
    SensoreAria(const QString &nome,
                       const QString &unitaMisura,
                       const QString &icona,
                       double sogliaMassima,
                       double valore);
    Valore getRandom(const QDateTime &dataOra) override;
    void modificaData(QDateTime &data, int hours);
    QChartView* createBarChart(const vector<Valore> &vectValori);
};

#endif // SENSOREARIA_H
