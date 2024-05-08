#include "../headers/sensorelampadina.h"
#include "../headers/sensoreelettricita.h"
#include <QtWidgets>


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
    return Valore(randVal, dataOra);
}


