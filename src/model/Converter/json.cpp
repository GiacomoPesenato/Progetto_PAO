#ifdef _WIN32
#define NOMINMAX // Avoid conflicts with min/max macros
#include <windows.h>
#undef byte // Undefine byte to avoid conflicts with std::byte
#include <cstddef> // For std::byte
#endif

#include "json.h"
#include <QJsonArray>

namespace Converter {

QJsonObject Json::daOggetto(const Sensore& sensor) {
    JsonVisitor json_visitor;
    sensor.accetta(json_visitor);
    return json_visitor.getOggetto();
}

Sensore& Json::aOggetto(const QJsonObject& json) {
    Reader reader;
    return *(reader.leggiSensore(json));
}

}
