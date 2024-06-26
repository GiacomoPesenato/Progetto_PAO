#ifndef SENSORE_REPO_JSON_REPOSITORY_H
#define SENSORE_REPO_JSON_REPOSITORY_H

#include <string>
#include <map>

#include "sensoreRepo.h"
#include "../DataMapper/jsonFile.h"

namespace Repository {

class JsonRepository : public sensoreRepo {
  private:
    DataMapper::JsonFile data_mapper;
    std::map<unsigned int, Sensore*> repository;

  public:
    JsonRepository(DataMapper::JsonFile data_mapper);
    
    static JsonRepository dalPercorso(const std::string percorso);
    const DataMapper::JsonFile& getDataMapper() const;
    const std::map<unsigned int, Sensore*>& getRepository() const;
    const std::string& getPercorso() const;
    void setPercorso(std::string percorso);
    void inserisciSensore(Sensore* sensore) override;
    Sensore* leggiSensore(const unsigned int id) const override;
    void aggiornaRepository(Sensore* sensor) override;
    void rimuoviSensoreRepository(const unsigned int id) override;
    std::vector<Sensore*> leggiSensoriRepository() const override;
    void sovrascrivi(const std::vector<Sensore*> nuoviSensori) override;
    void salva();
    void carica();

    ~JsonRepository() override;
};
}
#endif
