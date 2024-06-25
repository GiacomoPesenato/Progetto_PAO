#ifndef SENSOR_REPOSITORY_H
#define SENSOR_REPOSITORY_H

#include <vector>

#include "../sensore.h"

namespace Repository {

class sensoreRepo {
public:
    virtual void create(Sensore* sensor) = 0;
    virtual Sensore* read(const unsigned int identifier) const = 0;
    virtual void update(Sensore* sensor) = 0;
    virtual void remove(const unsigned int identifier) = 0;
    virtual std::vector<Sensore*> readAll() const = 0;
    virtual void overwrite(const std::vector<Sensore*> newSensors) = 0;

    virtual ~sensoreRepo() = default;
};

}

#endif
