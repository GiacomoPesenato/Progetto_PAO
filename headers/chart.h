#ifndef CHART_H
#define CHART_H

#include <QVector>
#include <QtCharts>
#include "valore.h"

class Chart
{
public:
    Chart();
    static QChartView *getChart(const QVector<Valore> &valori, QString &tipo);
    static void chartAnno(const QVector<Valore> &valori, QLineSeries *series, QScatterSeries *markerSeries, QCategoryAxis *axisX, QVector<QString> mesi, int currentMonth, int &maxMedia, int &minMedia);
    static void chartMese(const QVector<Valore> &valori, QLineSeries *series, QScatterSeries *markerSeries, QCategoryAxis *axisX, int &max, int &min, int giorniMese);
    static Valore mediaLampadina(const QVector<Valore> &valori, int &counter);
    ~Chart();
};

#endif // CHART_H
