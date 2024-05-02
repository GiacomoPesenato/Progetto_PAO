#include "../headers/sensoreelettrodomestico.h"
#include "../headers/sensoreelettricita.h"
#include <QtWidgets>


SensoreElettrodomestico::SensoreElettrodomestico():SensoreElettricita(), classeEnergetica("0") {}

SensoreElettrodomestico::SensoreElettrodomestico(const unsigned int id,
                                                 const QString &nome,
                                                 const QString &unitaMisura,
                                                 const QString &icona,
                                                 const QString gruppo,
                                                 QString classeEnergetica,
                                                 double potenzaMax,
                                                 double valore
                                                 )
    : SensoreElettricita(id, nome, unitaMisura, icona, gruppo, potenzaMax, valore), classeEnergetica(classeEnergetica){}
