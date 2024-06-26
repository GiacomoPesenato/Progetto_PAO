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

Reader& Reader::pulisci() {
    cache.clear();
    return *this;
}

Sensore* Reader::leggiSensore(const QJsonObject& oggetto) {
    QJsonValue type = oggetto.value("tipo");
    if (type.isUndefined()) {
        throw std::invalid_argument("Manca il 'tipo'");
    }

    const unsigned int id = oggetto.value("id").toInt();

    if (cache.count(id) > 0) {
        return cache[id];
    }
    else if (type.toString().compare("SensoreAria") == 0) {
        cache[id] = leggiSensoreAria(oggetto);
    }
    else if (type.toString().compare("SensoreElettrodomestico") == 0) {
        cache[id] = leggiSensoreElettrodomestico(oggetto);
    }
    else if (type.toString().compare("SensoreLampadina") == 0) {
        cache[id] = leggiSensoreLampadina(oggetto);
    }
    else if (type.toString().compare("SensorePannelli") == 0) {
        cache[id] = leggiSensorePannelli(oggetto);
    }
    else if (type.toString().compare("SensoreTemperatura") == 0) {
        cache[id] = leggiSensoreTemperatura(oggetto);
    }
    else if (type.toString().compare("SensoreUmidita") == 0) {
        cache[id] = leggiSensoreUmidita(oggetto);
    }
    else {
        throw std::invalid_argument("Tipo non riconosciuto");
    }

    return cache[id];
}

SensoreAria* Reader::leggiSensoreAria(const QJsonObject& oggetto) const {
    return new SensoreAria(
        oggetto.value("id").toInt(),
        oggetto.value("nome").toString(),
        oggetto.value("unitaMisura").toString(),
        oggetto.value("icona").toString(),
        oggetto.value("gruppo").toString(),
        oggetto.value("sogliaMassima").toDouble(),
        oggetto.value("valore").toDouble()
    );
}

SensoreElettrodomestico* Reader::leggiSensoreElettrodomestico(const QJsonObject& oggetto) const {
    return new SensoreElettrodomestico(
        oggetto.value("id").toInt(),
        oggetto.value("nome").toString(),
        oggetto.value("unitaMisura").toString(),
        oggetto.value("icona").toString(),
        oggetto.value("gruppo").toString(),
        oggetto.value("classeEnergetica").toString(),
        oggetto.value("potenzaMax").toDouble(),
        oggetto.value("valore").toDouble(),
        oggetto.value("tipoElettrodomestico").toString()
    );
}

SensoreLampadina* Reader::leggiSensoreLampadina(const QJsonObject& oggetto) const {
    return new SensoreLampadina(
        oggetto.value("id").toInt(),
        oggetto.value("nome").toString(),
        oggetto.value("unitaMisura").toString(),
        oggetto.value("icona").toString(),
        oggetto.value("gruppo").toString(),
        oggetto.value("dimmer").toBool(),
        oggetto.value("potenzaMax").toDouble(),
        oggetto.value("valore").toDouble()
    );
}

SensorePannelli* Reader::leggiSensorePannelli(const QJsonObject& oggetto) const {
    return new SensorePannelli(
        oggetto.value("id").toInt(),
        oggetto.value("nome").toString(),
        oggetto.value("unitaMisura").toString(),
        oggetto.value("icona").toString(),
        oggetto.value("gruppo").toString(),
        oggetto.value("nPannelli").toInt(),
        oggetto.value("potenzaPannello").toDouble(),
        oggetto.value("potenzaMax").toDouble(),
        oggetto.value("valore").toDouble()
    );
}

SensoreTemperatura* Reader::leggiSensoreTemperatura(const QJsonObject& oggetto) const {
    return new SensoreTemperatura(
        oggetto.value("id").toInt(),
        oggetto.value("nome").toString(),
        oggetto.value("unitaMisura").toString(),
        oggetto.value("icona").toString(),
        oggetto.value("gruppo").toString(),
        oggetto.value("valoreTarget").toDouble(),
        oggetto.value("tempMin").toDouble(),
        oggetto.value("tempMax").toDouble(),
        oggetto.value("valore").toDouble()
    );
}

SensoreUmidita* Reader::leggiSensoreUmidita(const QJsonObject& oggetto) const {
    return new SensoreUmidita(
        oggetto.value("id").toInt(),
        oggetto.value("nome").toString(),
        oggetto.value("unitaMisura").toString(),
        oggetto.value("icona").toString(),
        oggetto.value("gruppo").toString(),
        oggetto.value("valoreTarget").toDouble(),
        oggetto.value("valore").toDouble()
    );
}

}
