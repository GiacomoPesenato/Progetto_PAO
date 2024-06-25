#include "sensoreelettricita.h"

SensoreElettricita::SensoreElettricita():Sensore(), potenzaMax(0){}

SensoreElettricita::SensoreElettricita(const unsigned int id,
                                       const QString &nome,
                                       const QString &unitaMisura,
                                       const QString &icona,
                                       const QString gruppo,
                                       double potenzaMax,
                                       double valore)
    : Sensore(id, nome, unitaMisura, icona, gruppo, valore)
    , potenzaMax(potenzaMax){}

double SensoreElettricita::getPotenzaMax() const {
    return potenzaMax;
}

void SensoreElettricita::setPotenzaMax(const double &value) {
    potenzaMax = value;
}
