#ifndef SENSOR_READER_H
#define SENSOR_READER_H

#include <map>
#include <QJsonObject>

#include "sensoreLettura.h"
#include "../sensorearia.h"
#include "../sensoreelettrodomestico.h"
#include "../sensorelampadina.h"
#include "../sensorepannelli.h"
#include "../sensoretemperatura.h"
#include "../sensoreumidita.h"

namespace Converter {

class Reader: public sensoreLettura {
private:
    std::map<unsigned int, Sensore*> cache;
    SensoreAria* leggiSensoreAria(const QJsonObject& oggetto) const;
    SensoreElettrodomestico* leggiSensoreElettrodomestico(const QJsonObject& oggetto) const;
    SensoreLampadina* leggiSensoreLampadina(const QJsonObject& oggetto) const;
    SensorePannelli* leggiSensorePannelli(const QJsonObject& oggetto) const;
    SensoreTemperatura* leggiSensoreTemperatura(const QJsonObject& oggetto) const;
    SensoreUmidita* leggiSensoreUmidita(const QJsonObject& oggetto) const;
public:
    const std::map<unsigned int, Sensore*>& getCache() const;
    Reader& pulisci();

    Sensore* leggiSensore(const QJsonObject& oggetto) override;
};

}

#endif
