#include "sensorepannelli.h"
#include "../view/chart.h"
#include <QtWidgets>
SensorePannelli::SensorePannelli():SensoreElettricita(), nPannelli(65535), potenzaPannello(0) {}

SensorePannelli::SensorePannelli(const unsigned int id,
                                 const QString &nome,
                                 const QString &unitaMisura,
                                 const QString &icona,
                                 const QString gruppo,
                                 int nPannelli,
                                 double potenzaPannello,
                                 double potenzaMax,
                                 double valore)
    : SensoreElettricita(id, nome, unitaMisura, icona, gruppo, potenzaMax, valore), nPannelli(nPannelli), potenzaPannello(potenzaPannello) {}

int SensorePannelli::getNPannelli() const {
    return nPannelli;
}

void SensorePannelli::setNPannelli(const int &valore) {
    nPannelli = valore;
}

double SensorePannelli::getPotenzaPannello() const {
    return potenzaPannello;
}

void SensorePannelli::setPotenzaPannello(const double &valore) {
    potenzaPannello = valore;
}

Sensore *SensorePannelli::clone() const {
    return new SensorePannelli(*this);
}

Valore SensorePannelli::getRandom(const QDateTime &data) {
    std::random_device rd;
    std::mt19937 gen(rd());

    double minVal = 0.0;
    double media = getPotenzaMax();
    double potenza, devStd;
    int mese = data.date().month();

    //aggiunta una mappa per tenere conto la deviazione standard mensile, std::pair utilizzato per poter avere 3 elementi nella map
    //la map è composta come segue {mese, {media, deviazione standard}}
    std::map<int, std::pair<double, double>> devStdMensile = {
        {1, {media * 0.3, media * 0.1}},
        {2, {media * 0.4, media * 0.1}},
        {3, {media * 0.6, media * 0.1}},
        {4, {media * 0.7, media * 0.1}},
        {5, {media * 0.8, media * 0.1}},
        {6, {media * 0.9, media * 0.1}},
        {7, {media * 0.9, media * 0.1}},
        {8, {media * 0.9, media * 0.1}},
        {9, {media * 0.7, media * 0.1}},
        {10, {media * 0.6, media * 0.1}},
        {11, {media * 0.4, media * 0.1}},
        {12, {media * 0.3, media * 0.1}}
    };

    potenza = devStdMensile[mese].first;
    devStd = devStdMensile[mese].second;

    std::normal_distribution<double> dis(potenza, devStd);
    double potenzaRandom = dis(gen);

    if (potenzaRandom < minVal) potenzaRandom = minVal;
    if (potenzaRandom > media) potenzaRandom = media;

    potenzaRandom = std::round(potenzaRandom * 100.0) / 100.0;

    return Valore(potenzaRandom, data);
}

void SensorePannelli::accetta(sensoreVisitor& visitor) const {
    visitor.visita(*this);
}
