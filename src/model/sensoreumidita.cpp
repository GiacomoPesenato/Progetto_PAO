#ifdef _WIN32
#define NOMINMAX // Avoid conflicts with min/max macros
#include <windows.h>
#undef byte // Undefine byte to avoid conflicts with std::byte
#include <cstddef> // For std::byte
#endif

#include "sensoreumidita.h"
#include "../view/chart.h"
#include <random>
#include <iostream>

SensoreUmidita::SensoreUmidita()
    : Sensore()
    , valoreTarget(80)
{}

SensoreUmidita::SensoreUmidita(const unsigned int id,
                               const QString &nome,
                               const QString &unitaMisura,
                               const QString &icona,
                               const QString gruppo,
                               double valoreTarget,
                               double valore)
    : Sensore(id, nome, unitaMisura, icona, gruppo, valore)
    , valoreTarget(valoreTarget)
{}

double SensoreUmidita::getValoreTarget() const
{
    return valoreTarget;
}

void SensoreUmidita::setValoreTarget(const double &valore)
{
    valoreTarget = valore;
}

Sensore *SensoreUmidita::clone() const
{
    return new SensoreUmidita(*this);
}

Valore SensoreUmidita::getRandom(const QDateTime &dataOra) {
    std::random_device rd;
    std::mt19937 gen(rd());

    double minRange = valoreTarget*0.7;
    double maxRange = valoreTarget*1.3;

    if (minRange < 0) minRange = 0;
    if (maxRange > 100) maxRange = 100;

    std::uniform_real_distribution<> dis(minRange, maxRange);
    double valoreRandom = dis(gen);

    return Valore(valoreRandom,dataOra);
}

void SensoreUmidita::accetta(sensoreVisitor& visitor) const {
    visitor.visita(*this);
}

int umimain(int argc, char *argv[]) {
    SensoreUmidita umido = SensoreUmidita(1, "Umidità", "%", "umidita.png", "Clima", 80, 0);
    umido.generaDati();
    QString abc = "mese";
    QApplication a(argc, argv);
    QMainWindow window;
    Chart palle;
    window.setCentralWidget(palle.getChart(umido, abc));
    window.resize(1000,1000);
    window.show();
    return a.exec();
}
