#include "sensoreelettrodomestico.h"
#include <QtWidgets>

SensoreElettrodomestico::SensoreElettrodomestico() : SensoreElettricita(), classeEnergetica("0"), tipoElettrodomestico("") {}

SensoreElettrodomestico::SensoreElettrodomestico(const unsigned int id,
                                                 const QString &nome,
                                                 const QString &unitaMisura,
                                                 const QString &icona,
                                                 const QString gruppo,
                                                 QString classeEnergetica,
                                                 double potenzaMax,
                                                 double valore,
                                                 QString tipoElettrodomestico)
    : SensoreElettricita(id, nome, unitaMisura, icona, gruppo, potenzaMax, valore), classeEnergetica(classeEnergetica), tipoElettrodomestico(tipoElettrodomestico) {}

QString SensoreElettrodomestico::getClasseEnergetica() const {
    return classeEnergetica;
}

void SensoreElettrodomestico::setClasseEnergetica(const QString &valore) {
    classeEnergetica = valore;
}

QString SensoreElettrodomestico::getTipoElettrodomestico() const {
    return tipoElettrodomestico;
}

void SensoreElettrodomestico::setTipoElettrodomestico(const QString &valore){
    tipoElettrodomestico = valore;
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
    double valoreRandom = std::round(dis(gen) * 100.0) / 100.0;;

    return Valore(valoreRandom, dataOra);
}

void SensoreElettrodomestico::accetta(sensoreVisitor& visitor) const {
    visitor.visita(*this);
}
