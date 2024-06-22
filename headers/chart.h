#ifndef CHART_H
#define CHART_H

#include <QtCharts>
#include <QVector>
#include "../headers/sensore.h"

#ifdef _WIN32
#define NOMINMAX // Avoid conflicts with min/max macros
#include <windows.h>
#undef byte // Undefine byte to avoid conflicts with std::byte
#include <cstddef> // For std::byte
#endif
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
    QVector<QString> mesi;
    QString tipo;

    void chartAnno(int currentMonth, int &max, int &min);
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
