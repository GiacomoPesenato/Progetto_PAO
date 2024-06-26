#ifndef SENSORE_LETTURA_H
#define SENSORE_LETTURA_H

#include <QJsonObject>

#include "../sensore.h"

namespace Converter {

class sensoreLettura {
  public:
    virtual ~sensoreLettura() = default;
    virtual Sensore* leggiSensore(const QJsonObject& oggetto) = 0;
};

}
#endif
