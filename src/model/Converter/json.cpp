#include "json.h"
#include <QJsonArray>

namespace Converter {

QJsonObject Json::fromObject(const Sensore& sensor) {
    JsonVisitor json_visitor;
    sensor.accept(json_visitor);
    return json_visitor.getObject();
}

Sensore& Json::toObject(const QJsonObject& json) {
    Reader reader;
    return *(reader.read(json));
}

}
