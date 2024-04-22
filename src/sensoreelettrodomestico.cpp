#include "../headers/sensoreelettrodomestico.h"
#include "../headers/sensoreelettricita.h"
#include <QtWidgets>


SensoreElettrodomestico::SensoreElettrodomestico():SensoreElettricita(), classeEnergetica("0") {}

SensoreElettrodomestico::SensoreElettrodomestico(const QString &nome,
                                   const QString &unitaMisura,
                                   const QString &icona,
                                   QString classeEnergetica,
                                   double potenzaMax,
                                   double valore
                                   )
    : SensoreElettricita(nome, unitaMisura, icona, potenzaMax, valore)
    , classeEnergetica(classeEnergetica){}
