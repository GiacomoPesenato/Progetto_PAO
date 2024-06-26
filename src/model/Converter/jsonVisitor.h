#ifndef JSON_VISITOR_H
#define JSON_VISITOR_H

#include <QJsonObject>

#include "../sensorearia.h"
#include "../sensoreelettrodomestico.h"
#include "../sensorelampadina.h"
#include "../sensorepannelli.h"
#include "../sensoretemperatura.h"
#include "../sensoreumidita.h"

namespace Converter {

class JsonVisitor: public sensoreVisitor {
private:
    QJsonObject oggetto;

public:
    QJsonObject getOggetto() const;

    void visita(const SensoreAria& aria);
    void visita(const SensoreElettrodomestico& elettrodomestico);
    void visita(const SensoreLampadina& lampadina);
    void visita(const SensorePannelli& pannelli);
    void visita(const SensoreTemperatura& temperatura);
    void visita(const SensoreUmidita& umidita);
};

}

#endif
