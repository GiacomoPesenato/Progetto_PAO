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
    SensoreAria* leggiSensoreAria(const QJsonObject& object) const;
    SensoreElettrodomestico* leggiSensoreElettrodomestico(const QJsonObject& object) const;
    SensoreLampadina* leggiSensoreLampadina(const QJsonObject& object) const;
    SensorePannelli* leggiSensorePannelli(const QJsonObject& object) const;
    SensoreTemperatura* leggiSensoreTemperatura(const QJsonObject& object) const;
    SensoreUmidita* leggiSensoreUmidita(const QJsonObject& object) const;
public:
    const std::map<unsigned int, Sensore*>& getCache() const;
    Reader& clear();

    Sensore* read(const QJsonObject& object) override;
};

}

#endif
