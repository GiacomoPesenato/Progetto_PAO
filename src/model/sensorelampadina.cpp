#include "sensorelampadina.h"
#include "../view/chart.h"
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
void SensoreLampadina::setDimmer(bool valore) {
    dimmer = valore;
}

Sensore *SensoreLampadina::clone() const {
    return new SensoreLampadina(*this);
}

Valore SensoreLampadina::getRandom(const QDateTime &dataOra) {
    std::random_device rd;
    std::mt19937 gen(rd());

    int min = 0;
    int max = getPotenzaMax();
    int valoreRandom;
    std::uniform_int_distribution<int> distribution(min, max);

    int orario = dataOra.time().hour();
    //aggiunto controllo se l'ora è compresa tra le 22 e le 6 per simulare la notte.Ho inoltre aggiunto che alla notte ho meno probabilità di avere la lampadina accesa
    //con uniform_int_distribution posso generare un numero da 0 a 4 e se il numero è 0 allora la lampadina sarà accesa altrimenti no. Facendo così la notte ho il 20% che la lampadina sia accesa
    if (!getDimmer()) {
        if (orario >= 22 || orario < 6) {
            std::uniform_int_distribution<int> distribuzioneNotte(0, 4);
            valoreRandom = (distribuzioneNotte(gen) == 0) ? max : min;
        } else {
            std::uniform_int_distribution<int> distribuzioneGiorno(0, 1);
            valoreRandom = (distribuzioneGiorno(gen) == 0) ? min : max;
        }
    } else {
        //qua invece alla notte se la lampadina è dimmerabile la sua potenza e quindi la sua luminosità sarà ridotta di 4 volte rispetto al giorno
        if (orario >= 22 || orario < 6) {
            std::uniform_int_distribution<int> distribuzioneNotte(min, max / 4);
            valoreRandom = distribuzioneNotte(gen);
        } else {
            valoreRandom = distribution(gen);
        }
    }

    return Valore(valoreRandom, dataOra);
}


void SensoreLampadina::generaDati() {
    QDate dataCorrente = QDate::currentDate();
    QDate primoDelMese = QDate(dataCorrente.year(), dataCorrente.month(), 1);
    QTime orarioInizio(0, 0, 0);
    QDateTime data(primoDelMese, orarioInizio);
    for (int i = 0; i < 365*24; ++i) {
        Valore val = this->getRandom(data);
        this->setValore(val.getValore());
        this->addValore(val);
        std::cout<<val.getValore()<<" "<<val.getDataOra().toString().toStdString()<<std::endl;
        data = data.addSecs(3600);
    }
}

void SensoreLampadina::accetta(sensoreVisitor& visitor) const {
    visitor.visita(*this);
}


int gfmain(int argc, char *argv[]) {
    SensoreLampadina lampadina = SensoreLampadina(1, "lampadina", "W", "resources/lampadina.png", "casa", false, 10, 10);
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
