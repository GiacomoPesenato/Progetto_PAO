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
    QJsonObject object;

public:
    QJsonObject getObject() const;

    void visit(const SensoreAria& aria);
    void visit(const SensoreElettrodomestico& elettrodomestico);
    void visit(const SensoreLampadina& lampadina);
    void visit(const SensorePannelli& pannelli);
    void visit(const SensoreTemperatura& temperatura);
    void visit(const SensoreUmidita& umidita);
};

}

#endif
