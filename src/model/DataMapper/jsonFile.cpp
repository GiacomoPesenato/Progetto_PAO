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

JsonFile::JsonFile(const std::string& path) : path(path) {}

JsonFile JsonFile::fromPath(const std::string& path) {
    JsonFile data_mapper(path);
    return data_mapper;
}

const std::string& JsonFile::getPath() const {
    return path;
}

void JsonFile::setPath(const std::string& path) {
    this->path = path;
}

void JsonFile::store(const std::vector<Sensore*>& sensors) {
    QJsonArray json_sensors;
    for (const Sensore* sensor : sensors) {
        json_sensors.push_back(Converter::Json::fromObject(*sensor));
    }
    QJsonDocument document(json_sensors);
    QFile json_file(path.c_str());
    json_file.open(QFile::WriteOnly);
    json_file.write(document.toJson());
    json_file.close();
}

std::vector<Sensore*> JsonFile::load() {
    std::vector<Sensore*> sensors;
    QFile json_file(path.c_str());
    json_file.open(QFile::ReadOnly);
    QByteArray data = json_file.readAll();
    json_file.close();
    QJsonDocument document = QJsonDocument::fromJson(data);
    QJsonArray json_sensors = document.array();

    for (const QJsonValue& value : json_sensors) {
        QJsonObject json_object = value.toObject();
        sensors.push_back(&(Converter::Json::toObject(json_object)));
    }
    return sensors;
}

}
