#include "jsonVisitor.h"

#include <QJsonArray>


namespace Converter {

QJsonObject JsonVisitor::getOggetto() const {
    return oggetto;
}

void JsonVisitor::visita(const SensoreAria& aria){
    QJsonObject ariaObject;

    ariaObject.insert("type", QJsonValue::fromVariant("SensoreAria"));
    ariaObject.insert("id", QJsonValue::fromVariant(aria.getId()));
    ariaObject.insert("nome", QJsonValue::fromVariant(aria.getNome()));
    ariaObject.insert("unitaMisura", QJsonValue::fromVariant(aria.getUnitaMisura()));
    ariaObject.insert("icona", QJsonValue::fromVariant(aria.getIcona()));
    ariaObject.insert("gruppo", QJsonValue::fromVariant(aria.getGruppo()));
    ariaObject.insert("sogliaMassima", QJsonValue::fromVariant(aria.getSogliaMassima()));
    ariaObject.insert("valore", QJsonValue::fromVariant(aria.getValore()));

    oggetto = ariaObject;

}

void JsonVisitor::visita(const SensoreElettrodomestico& elettrodomestico){
    QJsonObject elettrodomesticoObject;

    elettrodomesticoObject.insert("type", QJsonValue::fromVariant("SensoreElettrodomestico"));
    elettrodomesticoObject.insert("id", QJsonValue::fromVariant(elettrodomestico.getId()));
    elettrodomesticoObject.insert("nome", QJsonValue::fromVariant(elettrodomestico.getNome()));
    elettrodomesticoObject.insert("unitaMisura", QJsonValue::fromVariant(elettrodomestico.getUnitaMisura()));
    elettrodomesticoObject.insert("icona", QJsonValue::fromVariant(elettrodomestico.getIcona()));
    elettrodomesticoObject.insert("gruppo", QJsonValue::fromVariant(elettrodomestico.getGruppo()));
    elettrodomesticoObject.insert("classeEnergetica", QJsonValue::fromVariant(elettrodomestico.getClasseEnergetica()));
    elettrodomesticoObject.insert("potenzaMax", QJsonValue::fromVariant(elettrodomestico.getPotenzaMax()));
    elettrodomesticoObject.insert("valore", QJsonValue::fromVariant(elettrodomestico.getValore()));

    oggetto = elettrodomesticoObject;
}

void JsonVisitor::visita(const SensoreLampadina& lampadina){
    QJsonObject lampadinaObject;

    lampadinaObject.insert("type", QJsonValue::fromVariant("SensoreLampadina"));
    lampadinaObject.insert("id", QJsonValue::fromVariant(lampadina.getId()));
    lampadinaObject.insert("nome", QJsonValue::fromVariant(lampadina.getNome()));
    lampadinaObject.insert("unitaMisura", QJsonValue::fromVariant(lampadina.getUnitaMisura()));
    lampadinaObject.insert("icona", QJsonValue::fromVariant(lampadina.getIcona()));
    lampadinaObject.insert("gruppo", QJsonValue::fromVariant(lampadina.getGruppo()));
    lampadinaObject.insert("dimmer", QJsonValue::fromVariant(lampadina.getDimmer()));
    lampadinaObject.insert("potenzaMax", QJsonValue::fromVariant(lampadina.getPotenzaMax()));
    lampadinaObject.insert("valore", QJsonValue::fromVariant(lampadina.getValore()));

    oggetto = lampadinaObject;
}

void JsonVisitor::visita(const SensorePannelli& pannelli){
    QJsonObject pannelliObject;

    pannelliObject.insert("type", QJsonValue::fromVariant("SensorePannelli"));
    pannelliObject.insert("id", QJsonValue::fromVariant(pannelli.getId()));
    pannelliObject.insert("nome", QJsonValue::fromVariant(pannelli.getNome()));
    pannelliObject.insert("unitaMisura", QJsonValue::fromVariant(pannelli.getUnitaMisura()));
    pannelliObject.insert("icona", QJsonValue::fromVariant(pannelli.getIcona()));
    pannelliObject.insert("gruppo", QJsonValue::fromVariant(pannelli.getGruppo()));
    pannelliObject.insert("nPannelli", QJsonValue::fromVariant(pannelli.getNPannelli()));
    pannelliObject.insert("potenzaPannello", QJsonValue::fromVariant(pannelli.getPotenzaPannello()));
    pannelliObject.insert("potenzaMax", QJsonValue::fromVariant(pannelli.getPotenzaMax()));
    pannelliObject.insert("valore", QJsonValue::fromVariant(pannelli.getValore()));

    oggetto = pannelliObject;
}

void JsonVisitor::visita(const SensoreTemperatura& temperatura){
    QJsonObject temperaturaObject;

    temperaturaObject.insert("type", QJsonValue::fromVariant("SensoreTemperatura"));
    temperaturaObject.insert("id", QJsonValue::fromVariant(temperatura.getId()));
    temperaturaObject.insert("nome", QJsonValue::fromVariant(temperatura.getNome()));
    temperaturaObject.insert("unitaMisura", QJsonValue::fromVariant(temperatura.getUnitaMisura()));
    temperaturaObject.insert("icona", QJsonValue::fromVariant(temperatura.getIcona()));
    temperaturaObject.insert("gruppo", QJsonValue::fromVariant(temperatura.getGruppo()));
    temperaturaObject.insert("valoreTarget", QJsonValue::fromVariant(temperatura.getValoreTarget()));
    temperaturaObject.insert("tempMin", QJsonValue::fromVariant(temperatura.getTempMin()));
    temperaturaObject.insert("tempMax", QJsonValue::fromVariant(temperatura.getTempMax()));
    temperaturaObject.insert("valore", QJsonValue::fromVariant(temperatura.getValore()));

    oggetto = temperaturaObject;
}


void JsonVisitor::visita(const SensoreUmidita& umidita){
    QJsonObject umiditaObject;

    umiditaObject.insert("type", QJsonValue::fromVariant("SensoreUmidita"));
    umiditaObject.insert("id", QJsonValue::fromVariant(umidita.getId()));
    umiditaObject.insert("nome", QJsonValue::fromVariant(umidita.getNome()));
    umiditaObject.insert("unitaMisura", QJsonValue::fromVariant(umidita.getUnitaMisura()));
    umiditaObject.insert("icona", QJsonValue::fromVariant(umidita.getIcona()));
    umiditaObject.insert("gruppo", QJsonValue::fromVariant(umidita.getGruppo()));
    umiditaObject.insert("valoreTarget", QJsonValue::fromVariant(umidita.getValoreTarget()));
    umiditaObject.insert("valore", QJsonValue::fromVariant(umidita.getValore()));

    oggetto = umiditaObject;
}
}
