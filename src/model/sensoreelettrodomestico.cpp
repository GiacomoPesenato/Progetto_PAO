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
    cout << "Usato questo getRandom " << randomValue << endl;

    return Valore(randomValue, dataOra);
}


int smain(int argc, char *argv[])
{
    SensoreElettrodomestico s = SensoreElettrodomestico(0,"Sensore1", "Kw/h", "prova","cucina","A",100,rand()%100);
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
