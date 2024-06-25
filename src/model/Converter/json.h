#ifndef SENSOR_CONVERTER_JSON_H
#define SENSOR_CONVERTER_JSON_H

#include "reader.h"
#include "jsonVisitor.h"

namespace Converter {

class Json {
  public:
    static QJsonObject fromObject(const Sensore& sensor);
    static Sensore& toObject(const QJsonObject& json);
};

}
#endif
