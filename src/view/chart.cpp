#ifdef _WIN32
#define NOMINMAX // Avoid conflicts with min/max macros
#include <windows.h>
#undef byte // Undefine byte to avoid conflicts with std::byte
#include <cstddef> // For std::byte
#endif

#include <QtCharts>
#include <QVector>
#include <QObject>
#include <iostream>
#include "chart.h"
#include "../model/sensorelampadina.h"

#define OFFSET 0.5
#define MARGIN_TOP 1.1
#define MARGIN_BOTTOM 0.9

Chart::Chart(QObject *parent) : QObject(parent)
  {}

QChartView* Chart::getChart(const Sensore &s, QString tipo) {
    markerSeries = new QScatterSeries;
    chart = new QChart();
    chartView = new QChartView(chart);
    series = new QLineSeries;
    asseX = new QCategoryAxis();
    asseY = new QValueAxis();
    valori = s.getValori();
    this->tipo = tipo;
    int currentMonth = valori[0].getDataOra().date().month();
    int max = -1, min = -1;
    bool lampadina = false, dimmer = false;
    mesi = {
        "Gennaio", "Febbraio", "Marzo", "Aprile", "Maggio", "Giugno",
        "Luglio", "Agosto", "Settembre", "Ottobre", "Novembre", "Dicembre"
    };

    std::cout << "Tipo: " << tipo.toStdString() << std::endl;

    if (const SensoreLampadina *lamp = dynamic_cast<const SensoreLampadina*>(&s)) {
        lampadina = true;
        dimmer = lamp->getDimmer();
    }
    if(tipo == "anno"){
        chartAnno(currentMonth, max, min);
        asseY->setRange(min*MARGIN_BOTTOM, max*MARGIN_TOP);
        chart->setTitle("Visione Annuale");
    } else if (tipo == "mese"){
        int giorniMese = valori[0].getDataOra().date().daysInMonth();
        chartMese(max, min, giorniMese, lampadina, dimmer);
        asseY->setRange(min*MARGIN_BOTTOM, max*MARGIN_TOP);
        chart->setTitle("Visione Mensile");
    } else if (tipo == "settimana"){
        chartSettimana(max, min, lampadina, dimmer);
        asseY->setRange(min*MARGIN_BOTTOM, max*MARGIN_TOP);
        chart->setTitle("Visione Settimanale");
    } else if (tipo == "giorno"){
        chartGiorno(max);
        asseY->setRange(0, max*MARGIN_TOP);
        chart->setTitle("Visione Giornaliera");
    }

    asseY->setTickCount(5);
    asseY->setLabelFormat("%d");

    markerSeries->setMarkerSize(10);
    markerSeries->setMarkerShape(QScatterSeries::MarkerShapeCircle);
    markerSeries->setColor(Qt::red);

    chart->addSeries(series);
    chart->addSeries(markerSeries);

    chart->addAxis(asseX, Qt::AlignBottom);
    chart->addAxis(asseY, Qt::AlignLeft);
    series->attachAxis(asseX);
    series->attachAxis(asseY);
    markerSeries->attachAxis(asseX);
    markerSeries->attachAxis(asseY);

    chart->legend()->hide();
    chartView->setRenderHint(QPainter::Antialiasing);

    connect(markerSeries, &QScatterSeries::clicked, this, &Chart::onClick);

    return chartView;
}


void Chart::chartAnno(int currentMonth, int &maxMedia, int &minMedia){
    double somma = 0.0,media = 0.0;
    int count = 0, pos = 0;

    for (int i = 0; i < valori.size(); ++i){
        Valore value = valori[i];
        int mese = value.getDataOra().date().month();

        if (mese == currentMonth) {
            somma += value.getValore();
            ++count;
        } else {
            media = (count > 0) ? somma / count : 0.0;
            QPointF point(pos + OFFSET, media);
            series->append(point);
            markerSeries->append(point);

            if (media > maxMedia || maxMedia == -1) {
                maxMedia = media;
            }
            if (media < minMedia || minMedia == -1) {
                minMedia = media;
            }

            pos++;
            currentMonth = mese;
            somma = value.getValore();
            count = 1;
        }
    }

    // aggiunta dell'ultimo mese
    media = (count > 0) ? somma / count : 0.0;
    QPointF point(pos + OFFSET, media);
    series->append(point);
    markerSeries->append(point);

    if (media > maxMedia || maxMedia == -1) {
        maxMedia = media;
    }
    if (media < minMedia || minMedia == -1) {
        minMedia = media;
    }

    asseX->setRange(0, 12);
    for (int i = 0; i < 12; ++i) {
        asseX->append(mesi[(i + currentMonth) % 12], i + 1);
    }
}


void Chart::chartMese(int &max, int &min, int giorniMese, bool lampadina, bool dimmer){
    asseX->setRange(0,giorniMese);

    int counter = 0;
    Valore value = valori[0];

    for (int i = 0; i < giorniMese; i++) {
        if (lampadina != 0){
            value = mediaLampadina(counter, dimmer);
            counter = 24*i;
            // cout<<value.getValore()<<" "<<value.getDataOra().toString("dd/MM/yyyy").toStdString()<<endl;
            // cout<<counter<<endl;
        }else{
            value = valori[counter+i];
            std::cout << value.getValore() <<" "<<value.getDataOra().date().day()<< std::endl;
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
        asseX->append(QString::number(i+1),i+1);
    }
    //cout <<"ORA ESCO"<< endl;
}

void Chart::chartSettimana(int &max, int &min, bool lampadina, bool dimmer){
    asseX->setRange(0,7);

    int counter = 0;
    Valore value = valori[0];

    for (int i = 0; i < 7; i++) {
        if (lampadina != 0){
            value = mediaLampadina(counter, dimmer);
            counter = 24*i;
            //cout<<value.getValore()<<" "<<value.getDataOra().toString("dd/MM/yyyy").toStdString()<<endl;
            //cout<<counter<<endl;
        }else{
            value = valori[counter+i];
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
        asseX->append(QString::number(i+1),i+1);

    }
}

void Chart::chartGiorno(int &max){
    asseX->setRange(0,24);
    for (int i = 0; i < 24; i++) {
        QPointF point(i+OFFSET, valori[i].getValore());
        series->append(point);
        markerSeries->append(point);
        if (valori[i].getValore() > max || max == -1){
            max = valori[i].getValore();
        }
        asseX->append(QString::number(i+1),i+1);

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
        value.setValore(somma/24);
    }else{
        //cout << "somma: " << somma << endl;
        if (somma >= 16){//se più di 16 volte è 0 gli assegno 0, ho scelto 16 in quanto 20% di 24
            //cout << "spenta" << endl;
            value.setValore(0);
        }else{
            //cout << "accesa" << endl;
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
    if (tipo == "anno"){
        int nMese = point.x()-OFFSET;
        int currentMonth = QDateTime::currentDateTime().date().month();
        msgBox.setText(QString("Punto cliccato: (%1, %2)").arg(mesi[((nMese+currentMonth)%12)>0 ? ((nMese+currentMonth)%12)-1 : 11]).arg(QString::number(point.y(), 'f', 2)));
        msgBox.exec();
    }else{
        msgBox.setText(QString("Punto cliccato: (%1, %2)").arg(point.x()-OFFSET+1).arg(QString::number(point.y(), 'f', 2)));
        msgBox.exec();
    }
}

