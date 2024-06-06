#ifndef CHART_H
#define CHART_H

#include <QtCharts>
#include <QVector>
#include "../headers/sensore.h"

class Chart : public QObject {
    Q_OBJECT

private:
    QScatterSeries *markerSeries;
    QChart *chart;
    QChartView *chartView;
    QLineSeries *series;
    QCategoryAxis *axisX;
    QValueAxis *axisY;
    QVector<Valore> valori;

    void chartAnno(int currentMonth, int &max, int &min, QVector<QString> mesi);
    void chartMese(int &max, int &min, int giorniMese, bool lampadina, bool dimmer);
    void chartSettimana(int &max, int &min, bool lampadina, bool dimmer);
    void chartGiorno(int &max, int &min);

    Valore mediaLampadina(int &counter, bool dimmer);

public:
    Chart();
    QChartView* getChart(const Sensore &s, QString tipo);

private slots:
    void onClick(const QPointF &point);
};

#endif // CHART_H
