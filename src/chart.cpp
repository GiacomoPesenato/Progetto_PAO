#include <QtCharts>
#include <QVector>
#include <QObject>
#include <iostream>
#include "../headers/chart.h"
#include "../headers/sensorelampadina.h"

#define OFFSET 0.5
using namespace std;

Chart::Chart()  {}

QChartView* Chart::getChart(const Sensore &s, QString tipo) {
    markerSeries = new QScatterSeries;
    chart = new QChart();
    chartView = new QChartView(chart);
    series = new QLineSeries;
    axisX = new QCategoryAxis();
    axisY = new QValueAxis();
    valori = s.getValori();
    int currentMonth = valori[0].getDataOra().date().month();
    int max = -1, min = -1;
    bool lampadina = false, dimmer = false;
    QVector<QString> mesi = {
        "Gennaio", "Febbraio", "Marzo", "Aprile", "Maggio", "Giugno",
        "Luglio", "Agosto", "Settembre", "Ottobre", "Novembre", "Dicembre"
    };

    if (const SensoreLampadina *lamp = dynamic_cast<const SensoreLampadina*>(&s)) {
        lampadina = true;
        dimmer = lamp->getDimmer();
    }
    if(tipo == "anno"){
        chartAnno(currentMonth, max, min, mesi);
        axisY->setRange(min - 10, max + 10);
        axisY->setTickCount(int((max - min) / 10) + 1);
    } else if (tipo == "mese"){
        int giorniMese = valori[0].getDataOra().date().daysInMonth();
        chartMese(max, min, giorniMese, lampadina, dimmer);
        axisY->setRange(min - 10, max + 10);
        axisY->setTickCount(int((max - min) / 5) + 1);
    } else if (tipo == "settimana"){
        chartSettimana(max, min, lampadina, dimmer);
        axisY->setRange(min - 10, max + 10);
        axisY->setTickCount(int((max - min) / 5) + 1);
    } else if (tipo == "giorno"){
        chartGiorno(max, min);
        axisY->setRange(min - 10, max + 20);
        axisY->setTickCount(int((max - min) / 5) + 1);
    }

    axisY->setLabelFormat("%d");

    markerSeries->setMarkerSize(10);
    markerSeries->setMarkerShape(QScatterSeries::MarkerShapeCircle);
    markerSeries->setColor(Qt::red);

    chart->addSeries(series);
    chart->addSeries(markerSeries);

    chart->addAxis(axisX, Qt::AlignBottom);
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisX);
    series->attachAxis(axisY);
    markerSeries->attachAxis(axisX);
    markerSeries->attachAxis(axisY);

    chart->legend()->hide();
    chart->setTitle("Media per mese");
    chartView->setRenderHint(QPainter::Antialiasing);

    connect(markerSeries, &QScatterSeries::clicked, this, &Chart::onClick);

    return chartView;
}


void Chart::chartAnno(int currentMonth, int &maxMedia, int &minMedia, const QVector<QString> mesi){
    int somma = 0, media = 0, count = 0, pos = 0;
    for (const Valore &value : valori) {
        if (value.getDataOra().date().month() == currentMonth) {
            somma += value.getValore();
            ++count;
        } else {
            media = (count > 0) ? somma / count : 0;
            QPointF point(pos+OFFSET, media);
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

void Chart::chartMese(int &max, int &min, int giorniMese, bool lampadina, bool dimmer){
    axisX->setRange(0,giorniMese);
    int counter = 0;
    Valore value = valori[0];

    cout << dimmer << endl;
    for (int i = 0; i < giorniMese; i++) {
        if (lampadina != 0){
            value = mediaLampadina(counter, dimmer);
            counter = 24*i;
            // cout<<value.getValore()<<" "<<value.getDataOra().toString("dd/MM/yyyy").toStdString()<<endl;
            // cout<<counter<<endl;
        }else{
            value = valori[counter+i];
            cout << value.getValore() <<" "<<value.getDataOra().date().day()<< endl;
        }
        QPointF point(i+OFFSET, value.getValore());
        series->append(point);
        markerSeries->append(point);
        if (value.getValore() > max || max == -1){
            max = value.getValore();
        }
        if (value.getValore() < min || min == -1){
            min = value.getValore();
        }
        axisX->append(QString::number(i+1),i+1);
    }
    //cout <<"ORA ESCO"<< endl;
}

void Chart::chartSettimana(int &max, int &min, bool lampadina, bool dimmer){
    axisX->setRange(0,7);

    int counter = 0;
    Valore value = valori[0];

    for (int i = 0; i < 7; i++) {
        if (lampadina != 0){
            value = mediaLampadina(counter, dimmer);
            counter = 24*i;
            //cout<<value.getValore()<<" "<<value.getDataOra().toString("dd/MM/yyyy").toStdString()<<endl;
            //cout<<counter<<endl;
        }else{
            value = valori[counter+i-1];
        }
        QPointF point(i+OFFSET, value.getValore());
        series->append(point);
        markerSeries->append(point);
        if (value.getValore() > max || max == -1){
            max = value.getValore();
        }
        if (value.getValore() < min || min == -1){
            min = value.getValore();
        }
        axisX->append(QString::number(i+1),i+1);

    }
}

void Chart::chartGiorno(int &max, int &min){
    axisX->setRange(0,24);
    for (int i = 0; i < 24; i++) {
        QPointF point(i+OFFSET, valori[i].getValore());
        series->append(point);
        markerSeries->append(point);
        if (valori[i].getValore() > max || max == -1){
            max = valori[i].getValore();
        }
        if (valori[i].getValore() < min || min == -1){
            min = valori[i].getValore();
        }
        axisX->append(QString::number(i+1),i+1);

    }
}


Valore Chart::mediaLampadina(int &counter, bool dimmer){
    int somma = 0, maxVal = -1;
    Valore value = valori[counter];
    for (int i = 0; i < 24; i++){
        if (dimmer != 0){ //se è dimmerabile sommo tutti i valori
            somma += valori[counter+i].getValore();
            //cout << valori[counter+i].getValore() << endl;
        }else{
            if (valori[counter+i].getValore() == 0){//se non è dimmerabile controllo se è spenta (se !dimmer gli unici val che può assumere sono 0 o max)
                somma += 1;//somma tutte le volte che è spenta
            }
            if (valori[counter+i].getValore() > maxVal){
                maxVal = valori[counter+i].getValore();//prendo il max val
            }
        }
    }
    if (dimmer != 0){
        cout << "media: " << somma/24<< endl;
        value.setValore(somma/24);
    }else{
        if (somma >= 12){//se più della metà delle volte è spenta allora gli assegno 0
            value.setValore(0);
        }else{
            value.setValore(maxVal);//altrimenti il max valore
        }
    }
    return value;
}
/*Questo discorso di assegnare 0 o max è per far capire che non è dimmerabile. Se facessi per lampadina dimmerabile o meno la media quest'ultima falserebbe il valore della non dimmerabile es:
Lampadina NON dimmerabile min 0 max 20

1: 0              13: 0         somma = 80
2: 20             14: 0         media = 80/24 = 3
3: 0              15: 0         se applicassi lo stesso metodo che applico per la dimmerabile dovrei mettere il valore 3 nel grafico
4: 0              16: 0         ma non essendo dimmerabile la lampadina può assumere solo 0 o 20 ed essendoci su 24 valori ben 20 valori 0 e 4 valori 20
5: 0              17: 0         nel grafico metterò 0
6: 0              18: 0
7: 0              19: 0
8: 0              20: 0
9: 0              21: 0
10: 20            22: 0
11: 20            23: 0
12: 20            24: 0
*/

void Chart::onClick(const QPointF &point) {
    QMessageBox msgBox;
    msgBox.setText(QString("Punto cliccato: (%1, %2)").arg(point.x()+1-OFFSET).arg(point.y()));
    msgBox.exec();
}

