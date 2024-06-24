#include "sensoreelettrodomestico.h"
#include "../view/chart.h"
#include <QtWidgets>
#include <iostream>

SensoreElettrodomestico::SensoreElettrodomestico() : SensoreElettricita(), classeEnergetica("0") {}

SensoreElettrodomestico::SensoreElettrodomestico(const unsigned int id,
                                                 const QString &nome,
                                                 const QString &unitaMisura,
                                                 const QString &icona,
                                                 const QString gruppo,
                                                 QString classeEnergetica,
                                                 double potenzaMax,
                                                 double valore)
    : SensoreElettricita(id, nome, unitaMisura, icona, gruppo, potenzaMax, valore), classeEnergetica(classeEnergetica) {}

QString SensoreElettrodomestico::getClasseEnergetica() const {
    return classeEnergetica;
}

void SensoreElettrodomestico::setClasseEnergetica(const QString &value) {
    classeEnergetica = value;
}

Sensore *SensoreElettrodomestico::clone() const {
    return new SensoreElettrodomestico(*this);
}

Valore SensoreElettrodomestico::getRandom(const QDateTime &dataOra) {
    double minVal, maxVal;
    double potenzaMax = getPotenzaMax();

    if (classeEnergetica == "A") {
        minVal = 0.01 * potenzaMax;
        maxVal = 0.20 * potenzaMax;
    } else if (classeEnergetica == "B") {
        minVal = 0.20 * potenzaMax;
        maxVal = 0.30 * potenzaMax;
    } else if (classeEnergetica == "C") {
        minVal = 0.30 * potenzaMax;
        maxVal = 0.40 * potenzaMax;
    } else if (classeEnergetica == "D") {
        minVal = 0.40 * potenzaMax;
        maxVal = 0.50 * potenzaMax;
    } else if (classeEnergetica == "E") {
        minVal = 0.50 * potenzaMax;
        maxVal = 0.60 * potenzaMax;
    } else if (classeEnergetica == "F") {
        minVal = 0.60 * potenzaMax;
        maxVal = 0.80 * potenzaMax;
    } else if (classeEnergetica == "G") {
        minVal = 0.80 * potenzaMax;
        maxVal = potenzaMax;
    } else {
        minVal = 0.0;
        maxVal = potenzaMax;
    }
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(minVal, maxVal);
    double randomValue = dis(gen);

    return Valore(randomValue, dataOra);
}

void SensoreElettrodomestico::generaDati() {
    QDate dataCorrente = QDate::currentDate();
    QDate primoDelMese = QDate(dataCorrente.year(), dataCorrente.month(), 1);
    QTime startTime(0, 0, 0);
    QDateTime data(primoDelMese, startTime);

    double sommaValoriMese = 0.0;
    int giorniNelMese = primoDelMese.daysInMonth();
    int meseCorrente = primoDelMese.month();

    for (int i = 0; i < 365; ++i) {
        Valore val = this->getRandom(data);
        //cout<<"Valore: "<<val.getValore()<<" Data: "<<data.toString().toStdString()<<endl;
        this->setValore(val.getValore());
        this->addValore(val);
        data =data.addDays(1);
        // Aggiorna la somma dei valori per il mese corrente
        sommaValoriMese += val.getValore();
        // Controlla se siamo passati a un nuovo mese
        if (data.date().month() != meseCorrente) {
            // Calcola e stampa la media per il mese corrente
            double media = sommaValoriMese / giorniNelMese;
            cout << "Mese: " << meseCorrente << " Media:" << media<<endl;

            // Reset della somma e aggiornamento dei contatori per il nuovo mese
            sommaValoriMese = val.getValore();
            meseCorrente = data.date().month();
            giorniNelMese = data.date().daysInMonth();
        }
    }
}


int nmain(int argc, char *argv[])
{
    SensoreElettrodomestico s = SensoreElettrodomestico(0,"Sensore1", "Kw/h", "prova","cucina","D",100,rand()%100);
    s.generaDati();
    QString abc = "settimana";
    QApplication a(argc, argv);
    QMainWindow window;
    Chart palle;
    window.setCentralWidget(palle.getChart(s, abc));
    window.resize(1000,1000);
    window.show();
    return a.exec();
}
