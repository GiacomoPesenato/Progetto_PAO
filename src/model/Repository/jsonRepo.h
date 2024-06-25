#ifndef SENSOR_REPOSITORY_JSON_REPOSITORY_H
#define SENSOR_REPOSITORY_JSON_REPOSITORY_H

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
    
    static JsonRepository fromPath(const std::string path); // Static factory method
    const DataMapper::JsonFile& getDataMapper() const;
    const std::map<unsigned int, Sensore*>& getRepository() const;
    const std::string& getPath() const;
    void setPath(std::string path);
    void create(Sensore* sensor) override;
    Sensore* read(const unsigned int identifier) const override;
    void update(Sensore* sensor) override;
    void remove(const unsigned int identifier) override;
    std::vector<Sensore*> readAll() const override;
    void overwrite(const std::vector<Sensore*> newSensors) override;
    void store();
    void load();

    ~JsonRepository() override;
};
}
#endif
