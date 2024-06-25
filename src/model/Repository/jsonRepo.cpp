#ifdef _WIN32
#define NOMINMAX // Avoid conflicts with min/max macros
#include <windows.h>
#undef byte // Undefine byte to avoid conflicts with std::byte
#include <cstddef> // For std::byte
#endif

#include "jsonRepo.h"

namespace Repository {

JsonRepository::JsonRepository(DataMapper::JsonFile data_mapper)
    : data_mapper(data_mapper)
{
    load();
}

JsonRepository JsonRepository::fromPath(std::string path) {    // Static factory method
    DataMapper::JsonFile data_mapper = DataMapper::JsonFile::fromPath(path);
    JsonRepository repository(data_mapper);
    return repository;
}

const DataMapper::JsonFile& JsonRepository::getDataMapper() const {
    return data_mapper;
}

const std::map<unsigned int, Sensore*>& JsonRepository::getRepository() const {
    return repository;
}

const std::string& JsonRepository::getPath() const {
    return data_mapper.getPath();
}

void JsonRepository::setPath(std::string path) {
    data_mapper.setPath(path);
}

void JsonRepository::create(Sensore* sensor) {
    repository[sensor->getId()] = sensor;
}

Sensore* JsonRepository::read(const unsigned int identifier) const {
    auto it = repository.find(identifier);
    if (it == repository.end()) {
        throw std::out_of_range("Trying to read an undefined id.");
    }
    return it->second;
}

void JsonRepository::update(Sensore* sensor) {
    create(sensor);
}

void JsonRepository::remove(const unsigned int identifier) {
    auto it = repository.find(identifier);
    if (it != repository.end()) {
        delete it->second;
        repository.erase(it);
    }
}

std::vector<Sensore*> JsonRepository::readAll() const {
    std::vector<Sensore*> sensors;
    for (const auto& entry : repository) {
        sensors.push_back(entry.second);
    }
    return sensors;
}

void JsonRepository::overwrite(const std::vector<Sensore*> newSensors) {
    repository.clear();

    // Itera attraverso il vettore di sensori della MainWindow e inserisce i loro cloni nella mappa
    for (Sensore* sensor : newSensors) {
        Sensore* clonedSensor = sensor->clone();
        repository[clonedSensor->getId()] = clonedSensor;
    }
}

void JsonRepository::store() {
    data_mapper.store(readAll());
}

void JsonRepository::load() {
    std::vector<Sensore*> new_sensors(data_mapper.load());

    for(Sensore* sensor : new_sensors){
        repository[sensor->getId()] = sensor;
    }
}

JsonRepository::~JsonRepository() {
    for (const auto& pair : repository) {
        delete pair.second;
    }
    repository.clear();
}

}
