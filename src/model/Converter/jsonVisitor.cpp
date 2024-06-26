#include "jsonVisitor.h"

#include <QJsonArray>


namespace Converter {

QJsonObject JsonVisitor::getOggetto() const {
    return oggetto;
}

void JsonVisitor::visita(const SensoreAria& aria){
    QJsonObject oggettoAria;

    oggettoAria.insert("tipo", QJsonValue::fromVariant("SensoreAria"));
    oggettoAria.insert("id", QJsonValue::fromVariant(aria.getId()));
    oggettoAria.insert("nome", QJsonValue::fromVariant(aria.getNome()));
    oggettoAria.insert("unitaMisura", QJsonValue::fromVariant(aria.getUnitaMisura()));
    oggettoAria.insert("icona", QJsonValue::fromVariant(aria.getIcona()));
    oggettoAria.insert("gruppo", QJsonValue::fromVariant(aria.getGruppo()));
    oggettoAria.insert("sogliaMassima", QJsonValue::fromVariant(aria.getSogliaMassima()));
    oggettoAria.insert("valore", QJsonValue::fromVariant(aria.getValore()));

    oggetto = oggettoAria;

}

void JsonVisitor::visita(const SensoreElettrodomestico& elettrodomestico){
    QJsonObject oggettoElettrodomestico;

    oggettoElettrodomestico.insert("tipo", QJsonValue::fromVariant("SensoreElettrodomestico"));
    oggettoElettrodomestico.insert("id", QJsonValue::fromVariant(elettrodomestico.getId()));
    oggettoElettrodomestico.insert("nome", QJsonValue::fromVariant(elettrodomestico.getNome()));
    oggettoElettrodomestico.insert("unitaMisura", QJsonValue::fromVariant(elettrodomestico.getUnitaMisura()));
    oggettoElettrodomestico.insert("icona", QJsonValue::fromVariant(elettrodomestico.getIcona()));
    oggettoElettrodomestico.insert("gruppo", QJsonValue::fromVariant(elettrodomestico.getGruppo()));
    oggettoElettrodomestico.insert("classeEnergetica", QJsonValue::fromVariant(elettrodomestico.getClasseEnergetica()));
    oggettoElettrodomestico.insert("potenzaMax", QJsonValue::fromVariant(elettrodomestico.getPotenzaMax()));
    oggettoElettrodomestico.insert("valore", QJsonValue::fromVariant(elettrodomestico.getValore()));

    oggetto = oggettoElettrodomestico;
}

void JsonVisitor::visita(const SensoreLampadina& lampadina){
    QJsonObject oggettoLampadina;

    oggettoLampadina.insert("tipo", QJsonValue::fromVariant("SensoreLampadina"));
    oggettoLampadina.insert("id", QJsonValue::fromVariant(lampadina.getId()));
    oggettoLampadina.insert("nome", QJsonValue::fromVariant(lampadina.getNome()));
    oggettoLampadina.insert("unitaMisura", QJsonValue::fromVariant(lampadina.getUnitaMisura()));
    oggettoLampadina.insert("icona", QJsonValue::fromVariant(lampadina.getIcona()));
    oggettoLampadina.insert("gruppo", QJsonValue::fromVariant(lampadina.getGruppo()));
    oggettoLampadina.insert("dimmer", QJsonValue::fromVariant(lampadina.getDimmer()));
    oggettoLampadina.insert("potenzaMax", QJsonValue::fromVariant(lampadina.getPotenzaMax()));
    oggettoLampadina.insert("valore", QJsonValue::fromVariant(lampadina.getValore()));

    oggetto = oggettoLampadina;
}

void JsonVisitor::visita(const SensorePannelli& pannelli){
    QJsonObject oggettoPannelli;

    oggettoPannelli.insert("tipo", QJsonValue::fromVariant("SensorePannelli"));
    oggettoPannelli.insert("id", QJsonValue::fromVariant(pannelli.getId()));
    oggettoPannelli.insert("nome", QJsonValue::fromVariant(pannelli.getNome()));
    oggettoPannelli.insert("unitaMisura", QJsonValue::fromVariant(pannelli.getUnitaMisura()));
    oggettoPannelli.insert("icona", QJsonValue::fromVariant(pannelli.getIcona()));
    oggettoPannelli.insert("gruppo", QJsonValue::fromVariant(pannelli.getGruppo()));
    oggettoPannelli.insert("nPannelli", QJsonValue::fromVariant(pannelli.getNPannelli()));
    oggettoPannelli.insert("potenzaPannello", QJsonValue::fromVariant(pannelli.getPotenzaPannello()));
    oggettoPannelli.insert("potenzaMax", QJsonValue::fromVariant(pannelli.getPotenzaMax()));
    oggettoPannelli.insert("valore", QJsonValue::fromVariant(pannelli.getValore()));

    oggetto = oggettoPannelli;
}

void JsonVisitor::visita(const SensoreTemperatura& temperatura){
    QJsonObject oggettoTemperatura;

    oggettoTemperatura.insert("tipo", QJsonValue::fromVariant("SensoreTemperatura"));
    oggettoTemperatura.insert("id", QJsonValue::fromVariant(temperatura.getId()));
    oggettoTemperatura.insert("nome", QJsonValue::fromVariant(temperatura.getNome()));
    oggettoTemperatura.insert("unitaMisura", QJsonValue::fromVariant(temperatura.getUnitaMisura()));
    oggettoTemperatura.insert("icona", QJsonValue::fromVariant(temperatura.getIcona()));
    oggettoTemperatura.insert("gruppo", QJsonValue::fromVariant(temperatura.getGruppo()));
    oggettoTemperatura.insert("valoreTarget", QJsonValue::fromVariant(temperatura.getValoreTarget()));
    oggettoTemperatura.insert("tempMin", QJsonValue::fromVariant(temperatura.getTempMin()));
    oggettoTemperatura.insert("tempMax", QJsonValue::fromVariant(temperatura.getTempMax()));
    oggettoTemperatura.insert("valore", QJsonValue::fromVariant(temperatura.getValore()));

    oggetto = oggettoTemperatura;
}


void JsonVisitor::visita(const SensoreUmidita& umidita){
    QJsonObject oggettoUmidita;

    oggettoUmidita.insert("tipo", QJsonValue::fromVariant("SensoreUmidita"));
    oggettoUmidita.insert("id", QJsonValue::fromVariant(umidita.getId()));
    oggettoUmidita.insert("nome", QJsonValue::fromVariant(umidita.getNome()));
    oggettoUmidita.insert("unitaMisura", QJsonValue::fromVariant(umidita.getUnitaMisura()));
    oggettoUmidita.insert("icona", QJsonValue::fromVariant(umidita.getIcona()));
    oggettoUmidita.insert("gruppo", QJsonValue::fromVariant(umidita.getGruppo()));
    oggettoUmidita.insert("valoreTarget", QJsonValue::fromVariant(umidita.getValoreTarget()));
    oggettoUmidita.insert("valore", QJsonValue::fromVariant(umidita.getValore()));

    oggetto = oggettoUmidita;
}
}
