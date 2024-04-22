#include "../headers/sensoreelettricita.h"
#include "../headers/sensore.h"

SensoreElettricita::SensoreElettricita():Sensore(), potenzaMax(0){}

SensoreElettricita::SensoreElettricita(const QString &nome,
                                       const QString &unitaMisura,
                                       const QString &icona,
                                       double potenzaMax,
                                       double valore)
    : Sensore(nome, unitaMisura, icona, valore)
    , potenzaMax(potenzaMax){}
