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
    carica();
}

JsonRepository JsonRepository::dalPercorso(std::string path) {    // Static factory method
    DataMapper::JsonFile data_mapper = DataMapper::JsonFile::dalPercorso(path);
    JsonRepository repository(data_mapper);
    return repository;
}

const DataMapper::JsonFile& JsonRepository::getDataMapper() const {
    return data_mapper;
}

const std::map<unsigned int, Sensore*>& JsonRepository::getRepository() const {
    return repository;
}

const std::string& JsonRepository::getPercorso() const {
    return data_mapper.getPercorso();
}

void JsonRepository::setPercorso(std::string path) {
    data_mapper.setPercorso(path);
}

void JsonRepository::inserisciSensore(Sensore* sensor) {
    repository[sensor->getId()] = sensor;
}

Sensore* JsonRepository::leggiSensore(const unsigned int identifier) const {
    auto it = repository.find(identifier);
    if (it == repository.end()) {
        throw std::out_of_range("ID 'out of range'");
    }
    return it->second;
}

void JsonRepository::aggiornaRepository(Sensore* sensor) {
    inserisciSensore(sensor);
}

void JsonRepository::rimuoviSensoreRepository(const unsigned int identifier) {
    auto it = repository.find(identifier);
    if (it != repository.end()) {
        delete it->second;
        repository.erase(it);
    }
}

std::vector<Sensore*> JsonRepository::leggiSensoriRepository() const {
    std::vector<Sensore*> sensori;
    for (const auto& entry : repository) {
        sensori.push_back(entry.second);
    }
    return sensori;
}

void JsonRepository::sovrascrivi(const std::vector<Sensore*> newSensors) {
    repository.clear();

    // Itera attraverso il vettore di sensori della MainWindow e inserisce i loro cloni nella mappa
    for (Sensore* sensor : newSensors) {
        Sensore* clonedSensor = sensor->clone();
        repository[clonedSensor->getId()] = clonedSensor;
    }
}

void JsonRepository::salva() {
    data_mapper.scriviJson(leggiSensoriRepository());
}

void JsonRepository::carica() {
    std::vector<Sensore*> new_sensors(data_mapper.caricaSensoriJson());

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
