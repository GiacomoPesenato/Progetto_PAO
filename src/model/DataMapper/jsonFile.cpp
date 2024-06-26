#ifdef _WIN32
#define NOMINMAX // Avoid conflicts with min/max macros
#include <windows.h>
#undef byte // Undefine byte to avoid conflicts with std::byte
#include <cstddef> // For std::byte
#endif

#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>

#include "jsonFile.h"

namespace DataMapper {

JsonFile::JsonFile(const std::string& percorso) : percorso(percorso) {}

JsonFile JsonFile::dalPercorso(const std::string& percorso) {
    JsonFile data_mapper(percorso);
    return data_mapper;
}

const std::string& JsonFile::getPercorso() const {
    return percorso;
}

void JsonFile::setPercorso(const std::string& percorso) {
    this->percorso = percorso;
}

void JsonFile::scriviJson(const std::vector<Sensore*>& sensori) {
    QJsonArray jsonSensori;
    for (const Sensore* sensori : sensori) {
        jsonSensori.push_back(Converter::Json::daOggetto(*sensori));
    }
    QJsonDocument documento(jsonSensori);
    QFile jsonFile(percorso.c_str());
    jsonFile.open(QFile::WriteOnly);
    jsonFile.write(documento.toJson());
    jsonFile.close();
}

std::vector<Sensore*> JsonFile::caricaSensoriJson() {
    std::vector<Sensore*> sensori;
    QFile jsonFile(percorso.c_str());
    jsonFile.open(QFile::ReadOnly);
    QByteArray data = jsonFile.readAll();
    jsonFile.close();
    QJsonDocument documento = QJsonDocument::fromJson(data);
    QJsonArray jsonSensori = documento.array();

    for (const QJsonValue& valori : jsonSensori) {
        QJsonObject jsonOggetto = valori.toObject();
        sensori.push_back(&(Converter::Json::aOggetto(jsonOggetto)));
    }
    return sensori;
}

}
