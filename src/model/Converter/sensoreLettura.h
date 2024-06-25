#ifndef SENSOR_CONVERTER_S_READER_H
#define SENSOR_CONVERTER_S_READER_H

#include <QJsonObject>

#include "../sensore.h"

namespace Converter {

class sensoreLettura {
  public:
    virtual ~sensoreLettura() = default;
    virtual Sensore* read(const QJsonObject& object) = 0;
};

}
#endif
