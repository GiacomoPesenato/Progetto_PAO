#include "../headers/sensoreelettricita.h"
#include "../headers/sensore.h"

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
