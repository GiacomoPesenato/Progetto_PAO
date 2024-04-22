#include "../headers/sensoretemperatura.h"
#include "../headers/sensore.h"

SensoreTemperatura::SensoreTemperatura():Sensore(), valoreTarget(0), tempMax(0), tempMin(0){}

SensoreTemperatura::SensoreTemperatura(const QString &nome,
                               const QString &unitaMisura,
                               const QString &icona,
                               double valoreTarget,
                               double tempMin,
                               double tempMax,
                               double valore)
    : Sensore(nome, unitaMisura, icona, valore)
    , valoreTarget(valoreTarget), tempMin(tempMin), tempMax(tempMax){}

