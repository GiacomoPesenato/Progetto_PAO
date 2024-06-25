#ifdef _WIN32
#define NOMINMAX // Avoid conflicts with min/max macros
#include <windows.h>
#undef byte // Undefine byte to avoid conflicts with std::byte
#include <cstddef> // For std::byte
#endif

#include <stdexcept>
#include <QJsonArray>
#include <iostream>

#include "reader.h"
#include "../sensore.h"

namespace Converter {

const std::map<unsigned int, Sensore*>& Reader::getCache() const {
    return cache;
}

Reader& Reader::clear() {
    cache.clear();
    return *this;
}

Sensore* Reader::read(const QJsonObject& object) {
    QJsonValue type = object.value("type");
    if (type.isUndefined()) {
        throw std::invalid_argument("Manca il 'type'");
    }

    const unsigned int identifier = object.value("id").toInt();

    if (cache.count(identifier) > 0) {
        return cache[identifier];
    }
    else if (type.toString().compare("SensoreAria") == 0) {
        cache[identifier] = leggiSensoreAria(object);
    }
    else if (type.toString().compare("SensoreElettrodomestico") == 0) {
        cache[identifier] = leggiSensoreElettrodomestico(object);
    }
    else if (type.toString().compare("SensoreLampadina") == 0) {
        cache[identifier] = leggiSensoreLampadina(object);
    }
    else if (type.toString().compare("SensorePannelli") == 0) {
        cache[identifier] = leggiSensorePannelli(object);
    }
    else if (type.toString().compare("SensoreTemperatura") == 0) {
        cache[identifier] = leggiSensoreTemperatura(object);
    }
    else if (type.toString().compare("SensoreUmidita") == 0) {
        cache[identifier] = leggiSensoreUmidita(object);
    }
    else {
        throw std::invalid_argument("Type non riconosciuto");
    }

    return cache[identifier];
}

SensoreAria* Reader::leggiSensoreAria(const QJsonObject& object) const {
    return new SensoreAria(
        object.value("id").toInt(),
        object.value("nome").toString(),
        object.value("unitaMisura").toString(),
        object.value("icona").toString(),
        object.value("gruppo").toString(),
        object.value("sogliaMassima").toDouble(),
        object.value("valore").toDouble()
    );
}

SensoreElettrodomestico* Reader::leggiSensoreElettrodomestico(const QJsonObject& object) const {
    return new SensoreElettrodomestico(
        object.value("id").toInt(),
        object.value("nome").toString(),
        object.value("unitaMisura").toString(),
        object.value("icona").toString(),
        object.value("gruppo").toString(),
        object.value("classeEnergetica").toString(),
        object.value("potenzaMax").toDouble(),
        object.value("valore").toDouble()
    );
}

SensoreLampadina* Reader::leggiSensoreLampadina(const QJsonObject& object) const {
    return new SensoreLampadina(
        object.value("id").toInt(),
        object.value("nome").toString(),
        object.value("unitaMisura").toString(),
        object.value("icona").toString(),
        object.value("gruppo").toString(),
        object.value("dimmer").toDouble(),
        object.value("potenzaMax").toDouble(),
        object.value("valore").toDouble()
    );
}

SensorePannelli* Reader::leggiSensorePannelli(const QJsonObject& object) const {
    return new SensorePannelli(
        object.value("id").toInt(),
        object.value("nome").toString(),
        object.value("unitaMisura").toString(),
        object.value("icona").toString(),
        object.value("gruppo").toString(),
        object.value("nPannelli").toInt(),
        object.value("potenzaPannello").toDouble(),
        object.value("potenzaMax").toDouble(),
        object.value("valore").toDouble()
    );
}

SensoreTemperatura* Reader::leggiSensoreTemperatura(const QJsonObject& object) const {
    return new SensoreTemperatura(
        object.value("id").toInt(),
        object.value("nome").toString(),
        object.value("unitaMisura").toString(),
        object.value("icona").toString(),
        object.value("gruppo").toString(),
        object.value("valoreTarget").toDouble(),
        object.value("tempMin").toDouble(),
        object.value("tempMax").toDouble(),
        object.value("valore").toDouble()
    );
}

SensoreUmidita* Reader::leggiSensoreUmidita(const QJsonObject& object) const {
    return new SensoreUmidita(
        object.value("id").toInt(),
        object.value("nome").toString(),
        object.value("unitaMisura").toString(),
        object.value("icona").toString(),
        object.value("gruppo").toString(),
        object.value("valoreTarget").toDouble(),
        object.value("valore").toDouble()
    );
}

// Accelerometer* Reader::readAccelerometer(const QJsonObject& object) const {
//     try {
//         return new Accelerometer(
//             object.value("id").toInt(),
//             object.value("name").toString().toStdString(),
//             static_cast<Chronometer&>(Json::toObject(object.value("chronometer").toObject())),
//             static_cast<SpeedSensor&>(Json::toObject(object.value("speedSensor").toObject()))//,
//             //Json::QJsonArrayToStdVector(object.value("data").toArray())
//         );
//     } catch (const std::bad_cast& e) {
//         std::cerr << "Static_cast fallito! " << e.what() << std::endl;
//         return nullptr;
//     }
// }

// Chronometer* Reader::readChronometer(const QJsonObject& object) const {
//     return new Chronometer(
//         object.value("id").toInt(),
//         object.value("name").toString().toStdString(),
//         //Json::QJsonArrayToStdVector(object.value("data").toArray())
//         object.value("min_value").toDouble(),
//         object.value("max_value").toDouble(),
//         object.value("mean").toDouble(),
//         object.value("variance").toDouble(),
//         object.value("lambda").toDouble()
//     );
// }

// DistanceCoveredSensor* Reader::readDistanceCoveredSensor(const QJsonObject& object) const {
//     return new DistanceCoveredSensor(
//         object.value("id").toInt(),
//         object.value("name").toString().toStdString(),
//         //Json::QJsonArrayToStdVector(object.value("data").toArray())
//         object.value("min_value").toDouble(),
//         object.value("max_value").toDouble(),
//         object.value("mean").toDouble(),
//         object.value("variance").toDouble(),
//         object.value("lambda").toDouble()
//     );
// }

// SpeedSensor* Reader::readSpeedSensor(const QJsonObject& object) const {
//     try {
//         return new SpeedSensor(
//             object.value("id").toInt(),
//             object.value("name").toString().toStdString(),
//             static_cast<DistanceCoveredSensor&>(Json::toObject(object.value("distanceCoveredSensor").toObject())),
//             static_cast<Chronometer&>(Json::toObject(object.value("chronometer").toObject()))//,
//             //Json::QJsonArrayToStdVector(object.value("data").toArray())
//         );
//     } catch (const std::bad_cast& e) {
//         std::cerr << "Static_cast fallito! " << e.what() << std::endl;
//         return nullptr;
//     }
// }

}
