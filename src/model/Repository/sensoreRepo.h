#ifndef SENSORE_REPO_H
#define SENSORE_REPO_H

#include <vector>

#include "../sensore.h"

namespace Repository {

class sensoreRepo {
public:
    virtual void inserisciSensore(Sensore* sensor) = 0;
    virtual Sensore* leggiSensore(const unsigned int identifier) const = 0;
    virtual void aggiornaRepository(Sensore* sensor) = 0;
    virtual void rimuoviSensoreRepository(const unsigned int identifier) = 0;
    virtual std::vector<Sensore*> leggiSensoriRepository() const = 0;
    virtual void sovrascrivi(const std::vector<Sensore*> newSensors) = 0;

    virtual ~sensoreRepo() = default;
};

}

#endif
