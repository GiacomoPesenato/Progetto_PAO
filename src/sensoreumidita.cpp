#include "../headers/sensoreumidita.h"
#include "../headers/sensore.h"
#include "../headers/chart.h"
#include <random>
#include <iostream>

using namespace std;

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

void SensoreUmidita::setValoreTarget(const double &value)
{
    valoreTarget = value;
}

Sensore *SensoreUmidita::clone() const
{
    return new SensoreUmidita(*this);
}

void SensoreUmidita::generaDati() {
    QDate dataCorrente = QDate::currentDate();
    QDate primoDelMese = QDate(dataCorrente.year(), dataCorrente.month(), 1);
    QTime startTime(0, 0, 0);
    QDateTime data(primoDelMese, startTime);

    for (int i = 0; i < 365; i++) {
        Valore val = this->getRandom(data);
        std::cout << "Valore: " << val.getValore() << " Data: " << data.toString().toStdString() << std::endl;
        this->setValore(val.getValore());
        this->addValore(val);
        data = data.addDays(1);
    }
}

Valore SensoreUmidita::getRandom(const QDateTime &dataOra) {
    random_device rd;
    mt19937 gen(rd());

    double minRange = valoreTarget*0.7;
    double maxRange = valoreTarget*1.3;

    if (minRange < 0) minRange = 0;
    if (maxRange > 100) maxRange = 100;

    uniform_real_distribution<> dis(minRange, maxRange);
    double valoreRandom = dis(gen);

    return Valore(valoreRandom,dataOra);
}

int main(int argc, char *argv[]) {
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
