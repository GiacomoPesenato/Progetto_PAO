#ifndef CHART_H
#define CHART_H

#include <QVector>
#include <QtCharts>
#include "valore.h"
#include "sensore.h"

class Chart
{
public:
    Chart();
    static QChartView *getChart(const Sensore &s, QString tipo);
    static void chartAnno(const QVector<Valore> &valori, QLineSeries *series, QScatterSeries *markerSeries, QCategoryAxis *axisX, QVector<QString> mesi, int currentMonth, int &maxMedia, int &minMedia);
    static void chartMese(const QVector<Valore> &valori, QLineSeries *series, QScatterSeries *markerSeries, QCategoryAxis *axisX, int &max, int &min, int giorniMese, bool lampadina);
    static Valore mediaLampadina(const QVector<Valore> &valori, int &counter);
    static void chartSettimana(const QVector<Valore> &valori, QLineSeries *series, QScatterSeries *markerSeries, QCategoryAxis *axisX, int &max, int &min, bool lampadina);
    static void chartGiorno(const QVector<Valore> &valori, QLineSeries *series, QScatterSeries *markerSeries, QCategoryAxis *axisX, int &max, int &min);
    ~Chart();
};

#endif // CHART_H
