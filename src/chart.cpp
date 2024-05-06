#include <QtCharts>
#include <QVector>
#include <iostream>
#include "../headers/chart.h"

using namespace std;

Chart::Chart() {}

QChartView* Chart::getChart(const QVector<Valore>& valori, QString &tipo) {
    QLineSeries *series = new QLineSeries;
    QScatterSeries *markerSeries = new QScatterSeries;
    QChart *chart = new QChart();
    QChartView *chartView = new QChartView(chart);
    QCategoryAxis *axisX = new QCategoryAxis();
    QValueAxis *axisY = new QValueAxis();
    int currentMonth = valori[0].getDataOra().date().month();
    int max = -1, min = -1;
    QVector<QString> mesi = {
        "Gennaio", "Febbraio", "Marzo", "Aprile", "Maggio", "Giugno",
        "Luglio", "Agosto", "Settembre", "Ottobre", "Novembre", "Dicembre"
    };

    if(tipo == "anno"){
        chartAnno(valori, series, markerSeries, axisX, mesi, currentMonth, max, min);
        axisY->setRange(min, max);
        axisY->setTickCount(int((max - min) / 10) + 1);
    } else if (tipo == "mese"){
        int giorniMese = valori[0].getDataOra().date().daysInMonth();
        chartMese(valori, series, markerSeries, axisX, max, min, giorniMese);
        axisY->setRange(min, max);
        axisY->setTickCount(int((max - min) / 5) + 1);
    } else if (tipo == "settimana"){
        chartSettimana(valori, series, markerSeries, axisX, max, min);
        axisY->setRange(min, max);
        axisY->setTickCount(int((max - min) / 2) + 1);
    } else if (tipo == "giorno"){
        chartGiorno(valori, series, markerSeries, axisX, max, min);
        axisY->setRange(min,max);
        axisY->setTickCount(int((max - min) / 2) + 1);
    }

    markerSeries->setMarkerSize(10);
    markerSeries->setMarkerShape(QScatterSeries::MarkerShapeCircle);
    markerSeries->setColor(Qt::red);

    chart->addAxis(axisX, Qt::AlignBottom);
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisX);
    series->attachAxis(axisY);
    chart->addSeries(series);
    chart->addSeries(markerSeries);
    chart->legend()->hide();
    chart->setTitle("Media per mese");
    chartView->setRenderHint(QPainter::Antialiasing);

    return chartView;
}

void Chart::chartAnno(const QVector<Valore> &valori, QLineSeries *series, QScatterSeries *markerSeries,QCategoryAxis *axisX, QVector<QString> mesi,int currentMonth, int &maxMedia, int &minMedia){
    int somma = 0, media = 0, count = 0, pos = 1;
    for (const Valore &value : valori) {
        if (value.getDataOra().date().month() == currentMonth) {
            somma += value.getValore();
            ++count;
        } else {
            media = (count > 0) ? somma / count : 0;
            QPointF point(pos, media);
            series->append(point);
            markerSeries->append(point);

            if (media > maxMedia || maxMedia == -1){
                maxMedia = media;
            }
            if (media < minMedia || minMedia == -1){
                minMedia = media;
            }

            pos++;
            currentMonth = value.getDataOra().date().month();
            somma = value.getValore();
            count = 1;
        }
    }
    axisX->setRange(0, 12);
    for (int i = 0; i < 12; i++) {
        axisX->append(mesi[(i + currentMonth - 1) % 12], i + 1);
    }
}

void Chart::chartMese(const QVector<Valore> &valori, QLineSeries *series, QScatterSeries *markerSeries, QCategoryAxis *axisX, int &max, int &min, int giorniMese){
    axisX->setRange(0,31);
    int dayOne = valori[0].getDataOra().date().day();
    int dayTwo = valori[1].getDataOra().date().day();
    bool lampadina = false;
    int counter = 0;
    Valore value = valori[0];
    //controllo che ad un valore corrisponda un giorno, se non è così sono nel sensore lampadina e chiamo una funzione per gestirmi i 24 dati di ogni giorno
    if (dayOne == dayTwo){
        lampadina = true;
    }
    cout << lampadina << endl;
    for (int i = 1; i <= giorniMese; i++) {
        if (lampadina){
            value = mediaLampadina(valori, counter);
            counter = 24*i;
            //cout<<value.getValore()<<" "<<value.getDataOra().toString("dd/MM/yyyy").toStdString()<<endl;
            //cout<<counter<<endl;
        }else{
            value = valori[counter+i-1];
        }
        QPointF point(i, value.getValore());
        series->append(point);
        markerSeries->append(point);
        if (value.getValore() > max || max == -1){
            max = value.getValore();
        }
        if (value.getValore() < min || min == -1){
            min = value.getValore();
        }
        axisX->append(QString::number(i),i);

    }
}

void Chart::chartSettimana(const QVector<Valore> &valori, QLineSeries *series, QScatterSeries *markerSeries, QCategoryAxis *axisX, int &max, int &min){
    axisX->setRange(0,7);
    int dayOne = valori[0].getDataOra().date().day();
    int dayTwo = valori[1].getDataOra().date().day();
    bool lampadina = false;
    int counter = 0;
    Valore value = valori[0];
    //controllo che ad un valore corrisponda un giorno, se non è così sono nel sensore lampadina e chiamo una funzione per gestirmi i 24 dati di ogni giorno
    if (dayOne == dayTwo){
        lampadina = true;
    }
    cout << lampadina << endl;
    for (int i = 1; i <= 7; i++) {
        if (lampadina){
            value = mediaLampadina(valori, counter);
            counter = 24*i;
            //cout<<value.getValore()<<" "<<value.getDataOra().toString("dd/MM/yyyy").toStdString()<<endl;
            //cout<<counter<<endl;
        }else{
            value = valori[counter+i-1];
        }
        QPointF point(i, value.getValore());
        series->append(point);
        markerSeries->append(point);
        if (value.getValore() > max || max == -1){
            max = value.getValore();
        }
        if (value.getValore() < min || min == -1){
            min = value.getValore();
        }
        axisX->append(QString::number(i),i);

    }
}

void Chart::chartGiorno(const QVector<Valore> &valori, QLineSeries *series, QScatterSeries *markerSeries, QCategoryAxis *axisX, int &max, int &min){
    axisX->setRange(0,24);
    for (int i = 0; i < 24; i++) {
        QPointF point(i, valori[i].getValore());
        series->append(point);
        markerSeries->append(point);
        if (valori[i].getValore() > max || max == -1){
            max = valori[i].getValore();
        }
        if (valori[i].getValore() < min || min == -1){
            min = valori[i].getValore();
        }
        axisX->append(QString::number(i),i);

    }
}

Valore Chart::mediaLampadina(const QVector<Valore> &valori, int &counter){
    int somma = 0;
    for (int i = 0; i < 24; i++){
        //cout<<valori[counter+i].getValore()<<" "<<valori[counter+i].getDataOra().toString("dd/MM/yyyy HH:ss:mm").toStdString()<<endl;
        somma += valori[counter+i].getValore();
    }
    Valore value = valori[counter];
    value.setValore(somma/24);
    return value;
}
