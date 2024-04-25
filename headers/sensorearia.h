#ifndef SENSOREARIA_H
#define SENSOREARIA_H

#include <QtWidgets>
#include <QtCharts>
#include "sensore.h"

class SensoreAria: public Sensore
{
private:
    double sogliaMassima;
    QVector<QString>mese;

public:
    SensoreAria();
    SensoreAria(const QString &nome,
                       const QString &unitaMisura,
                       const QString &icona,
                       double sogliaMassima,
                       double valore);
    Valore getRandom(const QDateTime &dataOra) override;
    void modificaData(QDateTime &data, int hours);
    QChartView* createLineChart(const vector<Valore> &vectValori);
    void displayPopupForMarkerClick(QString nomeMese, double media);
};



#endif // SENSOREARIA_H
