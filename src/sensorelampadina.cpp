#include "../headers/sensorelampadina.h"
#include "../headers/sensoreelettricita.h"
#include "../headers/chart.h"
#include <QtWidgets>
#include <iostream>

SensoreLampadina::SensoreLampadina():SensoreElettricita(), dimmer(false) {}

SensoreLampadina::SensoreLampadina(const unsigned int id,
                                   const QString &nome,
                                   const QString &unitaMisura,
                                   const QString &icona,
                                   const QString gruppo,
                                   bool dimmer,
                                   double potenzaMax,
                                   double valore
                                   )
    : SensoreElettricita(id, nome, unitaMisura, icona, gruppo, potenzaMax,valore), dimmer(dimmer){}

bool SensoreLampadina::getDimmer() const {
    return dimmer;
}
void SensoreLampadina::setDimmer(bool value) {
    dimmer = value;
}

Sensore *SensoreLampadina::clone() const {
    return new SensoreLampadina(*this);
}

Valore SensoreLampadina::getRandom(const QDateTime &dataOra){
    int min = 0;
    int max = getPotenzaMax();
    int randVal;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribution(min, max);

    // Se non è dimmer, restituisci min o max
    if (!getDimmer()) {
        if (std::rand() % 2 == 0) {
            randVal = min;
        } else {
            randVal = max;
        }
    }
    else {
        randVal = distribution(gen);
    }
    //cout << "Valore random: " << randVal <<" data e ora: " <<dataOra.toString().toStdString() << endl;
    return Valore(randVal, dataOra);
}


void SensoreLampadina::generaDati() {
    QDate dataCorrente = QDate::currentDate();
    QDate primoDelMese = QDate(dataCorrente.year(), dataCorrente.month(), 1);
    QTime startTime(0, 0, 0);
    QDateTime data(primoDelMese, startTime);
    for (int i = 0; i < 366*24; ++i) {
        Valore val = this->getRandom(data);
        this->setValore(val.getValore());
        data = data.addSecs(3600);
        this->addValore(val);
    }
}


int emain(int argc, char *argv[]) {
    SensoreLampadina lampadina = SensoreLampadina(1, "lampadina", "W", "resources/lampadina.png", "casa", false, 100, 50);
    lampadina.generaDati();
    QString abc = "settimana";

    QApplication a(argc, argv);
    QMainWindow window;
    Chart palle;
    window.setCentralWidget(palle.getChart(lampadina, abc));
    window.resize(1000,1000);
    window.show();
    return a.exec();
    return 0;
}
