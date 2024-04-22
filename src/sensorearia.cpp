#include "../headers/sensorearia.h"
#include "../headers/sensore.h"

#include <QDateTime>
#include <QtCharts>
#include <QChartView>
#include <QBarSet>
#include <QBarSeries>
#include <QBarCategoryAxis>
#include <QChart>
#include <iostream>
#include <vector>

using namespace std;

SensoreAria::SensoreAria():Sensore(), sogliaMassima(180){}

SensoreAria::SensoreAria(const QString &nome,
                                       const QString &unitaMisura,
                                       const QString &icona,
                                       double sogliaMassima,
                                       double valore
                                       )
    : Sensore(nome, unitaMisura, icona, valore)
    , sogliaMassima(sogliaMassima){}

Valore SensoreAria::getRandom(const QDateTime &dataOra)  {

    random_device rd;
    mt19937 gen(rd());
    double maxVariation = 5.0;

    double min = (this->getValore() - maxVariation)>0 ? this->getValore() - maxVariation : 0;
    double max = ((this->getValore() + maxVariation)< 180) ? this->getValore() + maxVariation : 180;
    uniform_real_distribution<double> distribution(min, max);
    double randomNumber = distribution(gen);
    // Calcola l'intervallo massimo rispetto al valore precedente
    double variationFromPrev = randomNumber - this->getValore();
    double adjustedRandom = randomNumber;
    uniform_real_distribution<double> re_distribution(0, maxVariation);
    if(variationFromPrev >maxVariation){
        adjustedRandom = this->getValore()+re_distribution(gen);
    }else if(variationFromPrev < -maxVariation){
        adjustedRandom = this->getValore()-re_distribution(gen);
    }
    adjustedRandom = std::max(10.0, std::min(180.0, adjustedRandom));

    // Aggiungi una maggiore probabilità per i numeri tra 50 e 75
    uniform_real_distribution<double> distributionBias(0.0, 1.0);
    double bias = distributionBias(gen);

    if (bias < 0.15) { // 60% di probabilità
        // Rendi più probabili i valori tra 40 e 60
        uniform_real_distribution<double> distributionBiased(50.0, 75.0);
        double biasedNumber = distributionBiased(gen);

    // Aggiorna il valore finale solo se il valore biasato è significativamente diverso
        if ((biasedNumber >= this->getValore() - maxVariation) && (biasedNumber <= this->getValore() + maxVariation)) {
            adjustedRandom = biasedNumber;
        }
    }
    Valore valore = Valore(adjustedRandom, dataOra);
    return valore;
}


void SensoreAria::modificaData(QDateTime &data, int hours){
    // Aggiorna la data aggiungendo un'ora
    data = data.addSecs(3600); // Aggiunge 3600 secondi (1 ora)

    hours++;

    // Ogni 24 ore (24 iterazioni)
    if (hours == 24) {
        data = data.addDays(1); // Aumenta il giorno di 1
        hours = 0; // Resetta il conteggio delle ore

        // Verifica se è necessario aumentare il mese
        int currentMonth = data.date().month();
        if (data.date().daysInMonth() < data.date().day()) {
            // Se il giorno supera i giorni totali del mese, aumenta il mese
            data = data.addMonths(1);
            // Se era l'ultimo giorno di dicembre, aumenta anche l'anno
            if (currentMonth == 12) {
                data = data.addYears(1);
            }
            // Imposta il giorno a 1 per il nuovo mese
            data.setDate(QDate(data.date().year(), data.date().month(), 1));
        }
    }
}

QChartView* createBarChart(const vector<Valore>& vect) {
    QBarSeries *series = new QBarSeries();
    const QVector<QColor> colors = {
        QColor(0, 0, 255), QColor(0, 255, 255), QColor(0, 255, 0), QColor(255, 255, 0),
        QColor(255, 153, 51), QColor(255, 0, 0), QColor(153, 0, 153)
    };
    QVector<QString> mese = {
        "Gennaio", "Febbraio", "Marzo", "Aprile", "Maggio", "Giugno",
        "Luglio", "Agosto", "Settembre", "Ottobre", "Novembre", "Dicembre"
    };

    int currentMonth = vect[0].getDataOra().date().month();
    int sommaQualita = 0, mediaQualita = 0, count = 0;

    for (const auto& value : vect) {
        if (value.getDataOra().date().month() == currentMonth) {
            sommaQualita += value.getValore();
            ++count;
        } else {
            // Calculate average quality for the current month
            mediaQualita = (count > 0) ? sommaQualita / count : 0;
            cout << "Per il mese di " << currentMonth << " la qualità è di: " << mediaQualita << endl;

            QBarSet *set0 = new QBarSet(mese[currentMonth - 1]);
            *set0 << mediaQualita; // Append average quality value to the QBarSet

            // Set color based on quality range
            if (mediaQualita <= 50) {
                set0->setColor(colors[0]);
            } else if (mediaQualita <= 75) {
                set0->setColor(colors[1]);
            } else if (mediaQualita <= 100) {
                set0->setColor(colors[2]);
            } else if (mediaQualita <= 125) {
                set0->setColor(colors[3]);
            } else if (mediaQualita <= 150) {
                set0->setColor(colors[4]);
            } else if (mediaQualita <= 175) {
                set0->setColor(colors[5]);
            } else {
                set0->setColor(colors[6]);
            }

            series->append(set0); // Append the QBarSet to the QBarSeries

            // Reset for the next month
            currentMonth = value.getDataOra().date().month();
            sommaQualita = value.getValore();
            count = 1;
        }
    }

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Grafico a Barre");

    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    for (int i = 0; i < 12; ++i) {
        axisX->append(mese[i]);
    }
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis();
    axisY->setRange(10, 180);
    axisY->setTickCount(18);
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    return chartView;
}




int qmain(int argc, char *argv[])
{
    QDateTime data = QDateTime::currentDateTime();
    data.setTime(QTime(0,0,0));
    int hours = 0;
    SensoreAria s = SensoreAria("Sensore1", "IQA", "prova",180,50);
    Valore valore = s.getRandom(data);
    s.modificaData(data,hours);
    vector<Valore> vectValori;
    vectValori.push_back(valore);
    for (int i = 1; i < 366 * 24; ++i) {
        Valore val = s.getRandom(data);
        s.setValore(val.getValore());
        s.modificaData(data,hours);
        cout<<data.toString(Qt::ISODate).toStdString()<<". Qualità dell'aria: "<<val.getValore()<<endl;
        //vectValori.push_back(val);
        s.addValore(val);
    }
    QApplication a(argc, argv);
    QMainWindow window;
    //window.setCentralWidget(createBarChart(vectValori)); // Aggiungi il grafico alla finestra principale
    window.setCentralWidget(createBarChart(s.getValori()));
    window.resize(1000,1000);
    window.show();
    return a.exec();
}
