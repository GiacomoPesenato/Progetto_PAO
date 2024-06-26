#ifndef SENSOR_CONVERTER_JSON_H
#define SENSOR_CONVERTER_JSON_H

#include "reader.h"
#include "jsonVisitor.h"

namespace Converter {

class Json {
  public:
    static QJsonObject daOggetto(const Sensore& sensor);
    static Sensore& aOggetto(const QJsonObject& json);
};

}
#endif
