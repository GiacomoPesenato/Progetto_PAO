#ifdef _WIN32
#define NOMINMAX // Avoid conflicts with min/max macros
#include <windows.h>
#undef byte // Undefine byte to avoid conflicts with std::byte
#include <cstddef> // For std::byte
#endif

#include "sensoretemperatura.h"
#include "../view/chart.h"
#include <QtWidgets>
#include <iostream>

SensoreTemperatura::SensoreTemperatura():Sensore(), valoreTarget(0), tempMin(0), tempMax(0){}

SensoreTemperatura::SensoreTemperatura(const unsigned int id,
                                       const QString &nome,
                                       const QString &unitaMisura,
                                       const QString &icona,
                                       const QString gruppo,
                                       double valoreTarget,
                                       double tempMin,
                                       double tempMax,
                                       double valore)
    : Sensore(id, nome, unitaMisura, icona, gruppo, valore)
    , valoreTarget(valoreTarget), tempMin(tempMin), tempMax(tempMax){}

double SensoreTemperatura::getValoreTarget() const
{
    return valoreTarget;
}

void SensoreTemperatura::setValoreTarget(const double &valore)
{
    valoreTarget = valore;
}

double SensoreTemperatura::getTempMin() const
{
    return tempMin;
}

void SensoreTemperatura::setTempMin(const double &valore)
{
    tempMin = valore;
}

double SensoreTemperatura::getTempMax() const
{
    return tempMax;
}

void SensoreTemperatura::setTempMax(const double &valore)
{
    tempMax = valore;
}

Sensore *SensoreTemperatura::clone() const
{
    return new SensoreTemperatura(*this);
}

Valore SensoreTemperatura::getRandom(const QDateTime &dataOra) {
    std::random_device rd;
    std::mt19937 gen(rd());

    double media, devStd;
    int mese = dataOra.date().month();

    std::map<int, std::pair<double, double>> devStdMensile = {
        {1, {tempMin + (tempMax - tempMin) * 0.1, 6.0}},
        {2, {tempMin + (tempMax - tempMin) * 0.2, 5.0}},
        {3, {tempMin + (tempMax - tempMin) * 0.3, 4.0}},
        {4, {tempMin + (tempMax - tempMin) * 0.4, 3.0}},
        {5, {tempMin + (tempMax - tempMin) * 0.6, 3.0}},
        {6, {tempMin + (tempMax - tempMin) * 0.7, 2.0}},
        {7, {tempMin + (tempMax - tempMin) * 0.8, 2.0}},
        {8, {tempMin + (tempMax - tempMin) * 0.8, 2.0}},
        {9, {tempMin + (tempMax - tempMin) * 0.6, 2.0}},
        {10, {tempMin + (tempMax - tempMin) * 0.5, 3.0}},
        {11, {tempMin + (tempMax - tempMin) * 0.3, 4.0}},
        {12, {tempMin + (tempMax - tempMin) * 0.1, 5.0}}
    };

    media = devStdMensile[mese].first;
    devStd = devStdMensile[mese].second;

    std::normal_distribution<> dis(media, devStd);
    double valoreRandom = dis(gen);

    if (valoreRandom < tempMin) valoreRandom = tempMin;
    if (valoreRandom > tempMax) valoreRandom = tempMax;

    return Valore(valoreRandom, dataOra);
}

void SensoreTemperatura::accetta(sensoreVisitor& visitor) const {
    visitor.visita(*this);
}

int jhgmain(int argc, char *argv[]) {
    SensoreTemperatura termometro = SensoreTemperatura(1, "temperatura", "°C", "termometro", "casa", 20, -10, 40, 20);
    termometro.generaDati();
    QString abc = "mese";
    QApplication a(argc, argv);
    QMainWindow window;
    Chart palle;
    window.setCentralWidget(palle.getChart(termometro, abc));
    window.resize(1000,1000);
    window.show();
    return a.exec();
}
