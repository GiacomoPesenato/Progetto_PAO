#include "../headers/sensoretemperatura.h"
#include "../headers/sensore.h"

SensoreTemperatura::SensoreTemperatura():Sensore(), valoreTarget(0), tempMin(0), tempMax(0){}

SensoreTemperatura::SensoreTemperatura(const unsigned int id,
                                       const QString &nome,
                                       const QString &unitaMisura,
                                       const QString &icona,
                                       const QString gruppo,
                                       double valoreTarget,
                                       double tempMin,
                                       double tempMax,
                                       double valore)
    : Sensore(id, nome, unitaMisura, icona, gruppo, valore)
    , valoreTarget(valoreTarget), tempMin(tempMin), tempMax(tempMax){}

